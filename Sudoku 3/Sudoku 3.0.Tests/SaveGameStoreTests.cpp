// Danylo Fitel 2026
// Unit tests for SaveGameStore (text round-trip, validation, version handling).
// SaveGameStore is pure logic over a file path, so tests round-trip through temp files.

#include "SaveGameStore.h"

using namespace System;
using namespace System::IO;
using namespace Sudoku_3_0;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace Sudoku_3_0_Tests
{
    [TestClass]
    public ref class SaveGameStoreTests
    {
    private:
        literal int Cells = 81;

        // A valid, in-progress Game-mode save: some clue cells filled, the rest empty.
        static SavedGame^ MakeGameSave()
        {
            SavedGame^ g = gcnew SavedGame();
            g->difficulty = 3;
            g->numberOfRestarts = 1;
            g->numberOfHints = 2;
            g->numberOfFixes = 4;
            g->numberOfGiveUps = 0;
            g->mode = GameMode::Game;
            g->gameFinished = false;
            g->elapsedSeconds = 125;
            g->clues = gcnew array<unsigned char>(Cells);
            g->solution = gcnew array<unsigned char>(Cells);
            g->values = gcnew array<unsigned char>(Cells);
            g->states = gcnew array<unsigned char>(Cells);
            g->pencilMarks = gcnew array<int>(Cells);

            for (int i = 0; i < Cells; ++i)
            {
                unsigned char sol = (unsigned char)(1 + (i % 9));
                g->solution[i] = sol;
                bool isClue = (i % 3 == 0);
                g->clues[i] = isClue ? sol : (unsigned char)0;
                g->values[i] = isClue ? sol : (unsigned char)0;
                g->states[i] = isClue ? (unsigned char)0 /*clue*/ : (unsigned char)1 /*empty*/;
                g->pencilMarks[i] = isClue ? 0 : (1 << (i % 9 + 1)); // some marks on empty cells
            }
            return g;
        }

        // A valid Solver-mode save that has NOT been solved yet: no puzzle snapshot,
        // board recoverable from values/states alone.
        static SavedGame^ MakeSolverInProgressSave()
        {
            SavedGame^ g = gcnew SavedGame();
            g->difficulty = 2;
            g->numberOfRestarts = 0;
            g->numberOfHints = 0;
            g->numberOfFixes = 0;
            g->numberOfGiveUps = 0;
            g->mode = GameMode::Solver;
            g->gameFinished = false;
            g->elapsedSeconds = 7;
            g->clues = gcnew array<unsigned char>(0);    // no puzzle yet
            g->solution = gcnew array<unsigned char>(0);
            g->values = gcnew array<unsigned char>(Cells);
            g->states = gcnew array<unsigned char>(Cells);
            g->pencilMarks = gcnew array<int>(Cells);

            for (int i = 0; i < Cells; ++i)
            {
                bool entered = (i < 5);
                g->values[i] = entered ? (unsigned char)(1 + i) : (unsigned char)0;
                g->states[i] = entered ? (unsigned char)2 /*user-filled*/ : (unsigned char)1 /*empty*/;
                g->pencilMarks[i] = 0;
            }
            return g;
        }

        static SavedGame^ SaveAndReload(SavedGame^ g)
        {
            String^ path = Path::GetTempFileName();
            try
            {
                SaveGameStore::Save(path, g);
                return SaveGameStore::Load(path, Cells);
            }
            finally
            {
                File::Delete(path);
            }
        }

    public:
        [TestMethod]
            void RoundTrip_PreservesScalarFields()
        {
            SavedGame^ back = SaveAndReload(MakeGameSave());

            Assert::AreEqual(3, (int)back->difficulty);
            Assert::AreEqual(1, (int)back->numberOfRestarts);
            Assert::AreEqual(2, (int)back->numberOfHints);
            Assert::AreEqual(4, (int)back->numberOfFixes);
            Assert::AreEqual(0, (int)back->numberOfGiveUps);
            Assert::AreEqual(125, (int)back->elapsedSeconds);
            Assert::IsTrue(back->mode == GameMode::Game);
            Assert::IsFalse(back->gameFinished);
        }

        [TestMethod]
        void RoundTrip_PreservesBoardArrays()
        {
            SavedGame^ original = MakeGameSave();
            SavedGame^ back = SaveAndReload(original);

            Assert::AreEqual(Cells, back->clues->Length);
            Assert::AreEqual(Cells, back->solution->Length);
            Assert::AreEqual(Cells, back->values->Length);
            Assert::AreEqual(Cells, back->states->Length);
            Assert::AreEqual(Cells, back->pencilMarks->Length);

            for (int i = 0; i < Cells; ++i)
            {
                Assert::AreEqual((int)original->clues[i], (int)back->clues[i]);
                Assert::AreEqual((int)original->solution[i], (int)back->solution[i]);
                Assert::AreEqual((int)original->values[i], (int)back->values[i]);
                Assert::AreEqual((int)original->states[i], (int)back->states[i]);
                Assert::AreEqual(original->pencilMarks[i], back->pencilMarks[i]);
            }
        }

        [TestMethod]
        void RoundTrip_SolverWithoutPuzzle_KeepsEmptySnapshot()
        {
            SavedGame^ back = SaveAndReload(MakeSolverInProgressSave());

            Assert::IsTrue(back->mode == GameMode::Solver);
            Assert::AreEqual(0, back->clues->Length);
            Assert::AreEqual(0, back->solution->Length);
            Assert::AreEqual(Cells, back->values->Length);
            Assert::AreEqual(1, (int)back->values[0]);
            Assert::AreEqual(2, (int)back->states[0]);   // user-filled
            Assert::AreEqual(1, (int)back->states[80]);  // empty
        }

        [TestMethod]
        [ExpectedException(UnsupportedSaveVersionException::typeid)]
            void Load_Throws_OnNewerFormatVersion()
        {
            String^ path = Path::GetTempFileName();
            try
            {
                File::WriteAllText(path, "Sudoku3Save=999\n");
                SaveGameStore::Load(path, Cells);
            }
            finally
            {
                File::Delete(path);
            }
        }

        [TestMethod]
        [ExpectedException(Exception::typeid)]
            void Load_Throws_WhenNotASaveFile()
        {
            String^ path = Path::GetTempFileName();
            try
            {
                File::WriteAllText(path, "just some random text\nnot a save\n");
                SaveGameStore::Load(path, Cells);
            }
            finally
            {
                File::Delete(path);
            }
        }

        [TestMethod]
        [ExpectedException(Exception::typeid)]
            void Load_Throws_OnMissingRequiredField()
        {
            // Recognized header + version, but every other required field is absent.
            String^ path = Path::GetTempFileName();
            try
            {
                File::WriteAllText(path, "Sudoku3Save=1\n");
                SaveGameStore::Load(path, Cells);
            }
            finally
            {
                File::Delete(path);
            }
        }

        [TestMethod]
        [ExpectedException(Exception::typeid)]
            void Load_Throws_WhenGameModeHasNoPuzzle()
        {
            // Game mode requires a solution; strip the puzzle from an otherwise-valid save.
            SavedGame^ g = MakeGameSave();
            g->clues = gcnew array<unsigned char>(0);
            g->solution = gcnew array<unsigned char>(0);
            SaveAndReload(g); // Save succeeds; Load must reject
        }

        [TestMethod]
        void UnsupportedSaveVersionException_CarriesVersions()
        {
            UnsupportedSaveVersionException^ ex = gcnew UnsupportedSaveVersionException(5, 1);
            Assert::AreEqual(5, (int)ex->FileVersion);
            Assert::AreEqual(1, (int)ex->SupportedVersion);
        }
    };
}
