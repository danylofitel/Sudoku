// Danylo Fitel 2026
// Unit tests for SavedGameMapper: the GameSession/Board <-> SavedGame data mapping, plus a full
// round-trip through SaveGameStore (session -> capture -> save -> load -> restore -> session).

#include "SavedGameMapper.h"
#include "SaveGameStore.h"

using namespace System;
using namespace System::IO;
using namespace Sudoku_3_0;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace Sudoku_3_0_Tests
{
    [TestClass]
    public ref class SavedGameMapperTests
    {
    private:
        literal int Cells = 81;

        // A valid, content-rich Game session: clue cells filled from the solution, one user-filled
        // cell (state 2), and pencil marks on an empty cell (state 1). Valid enough that the
        // captured SavedGame survives SaveGameStore::Load in the round-trip test.
        static GameSession^ MakePopulatedSession()
        {
            GameSession^ s = gcnew GameSession(Cells);
            s->startNewGame(3);
            s->numberOfRestarts = 1;
            s->numberOfHints = 2;
            s->numberOfFixes = 0;
            s->numberOfGiveUps = 0;
            s->maxCandidateAssist = CandidateDisplay::CurrentCell;

            array<unsigned char>^ clues = gcnew array<unsigned char>(Cells);
            array<unsigned char>^ solution = gcnew array<unsigned char>(Cells);
            for (int i = 0; i < Cells; ++i)
            {
                unsigned char sol = (unsigned char)(1 + (i % 9));
                solution[i] = sol;
                bool isClue = (i % 3 == 0);
                clues[i] = isClue ? sol : (unsigned char)0;
                if (isClue) s->board->setClue(i, sol);
            }
            s->puzzle = gcnew Puzzle(clues, solution);

            s->board->setUserValue(1, 5);      // a user-filled cell
            s->board->togglePencilMark(2, 4);  // pencil marks on an empty cell
            return s;
        }

        static void AssertSameGameData(GameSession^ a, GameSession^ b)
        {
            Assert::AreEqual((int)a->difficulty, (int)b->difficulty);
            Assert::AreEqual((int)a->numberOfRestarts, (int)b->numberOfRestarts);
            Assert::AreEqual((int)a->numberOfHints, (int)b->numberOfHints);
            Assert::AreEqual((int)a->numberOfFixes, (int)b->numberOfFixes);
            Assert::AreEqual((int)a->numberOfGiveUps, (int)b->numberOfGiveUps);
            Assert::IsTrue(a->maxCandidateAssist == b->maxCandidateAssist);
            Assert::IsTrue(a->mode == b->mode);

            for (unsigned int i = 0; i < (unsigned int)Cells; ++i)
            {
                Assert::AreEqual((int)a->board->valueAt(i), (int)b->board->valueAt(i));
                Assert::IsTrue(a->board->kindAt(i) == b->board->kindAt(i));
                Assert::AreEqual(a->board->pencilMarksAt(i), b->board->pencilMarksAt(i));
            }

            Assert::AreEqual(a->puzzle != nullptr, b->puzzle != nullptr);
            if (a->puzzle != nullptr)
            {
                for (int i = 0; i < Cells; ++i)
                {
                    Assert::AreEqual((int)a->puzzle->clues[i], (int)b->puzzle->clues[i]);
                    Assert::AreEqual((int)a->puzzle->solution[i], (int)b->puzzle->solution[i]);
                }
            }
        }

    public:
        [TestMethod]
        void Capture_CopiesSessionScalarsAndViewValues()
        {
            GameSession^ s = MakePopulatedSession();
            SavedGame^ g = SavedGameMapper::Capture(s, true, 125);

            Assert::AreEqual((int)s->difficulty, (int)g->difficulty);
            Assert::AreEqual((int)s->numberOfHints, (int)g->numberOfHints);
            Assert::IsTrue(g->mode == GameMode::Game);
            Assert::IsTrue(g->candidateAssist == CandidateDisplay::CurrentCell);
            Assert::IsTrue(g->gameFinished);
            Assert::AreEqual(125, (int)g->elapsedSeconds); // passed-in view value, not from session
            Assert::AreEqual(Cells, g->values->Length);
            Assert::AreEqual(5, (int)g->values[1]);        // the user-filled cell
        }

        [TestMethod]
        void CaptureThenRestore_PreservesAllGameData()
        {
            GameSession^ src = MakePopulatedSession();
            SavedGame^ g = SavedGameMapper::Capture(src, false, 60);

            GameSession^ dst = gcnew GameSession(Cells);
            SavedGameMapper::Restore(g, dst);

            AssertSameGameData(src, dst);
        }

        [TestMethod]
        void RoundTrip_ThroughStore_PreservesAllGameData()
        {
            GameSession^ src = MakePopulatedSession();
            SavedGame^ g = SavedGameMapper::Capture(src, true, 300);

            String^ path = Path::GetTempFileName();
            try
            {
                SaveGameStore::Save(path, g);
                SavedGame^ loaded = SaveGameStore::Load(path, Cells);

                GameSession^ dst = gcnew GameSession(Cells);
                SavedGameMapper::Restore(loaded, dst);

                AssertSameGameData(src, dst);
            }
            finally
            {
                File::Delete(path);
            }
        }
    };
}
