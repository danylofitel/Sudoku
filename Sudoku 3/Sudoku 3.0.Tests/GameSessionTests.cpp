// Danylo Fitel 2026
// Unit tests for GameSession's derived queries: clean-win test, clue count, and the
// "mostly hints" (barely-better-than-giving-up) threshold.

#include "GameSession.h"

using namespace System;
using namespace Sudoku_3_0;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace Sudoku_3_0_Tests
{
    [TestClass]
    public ref class GameSessionTests
    {
    private:
        literal int Cells = 81;

        // A Game session with `numClues` clue cells filled from the solution and `numHints` of the
        // remaining cells revealed as hints.
        static GameSession^ MakeGameWithHints(int numClues, int numHints)
        {
            GameSession^ s = gcnew GameSession(Cells);
            s->startNewGame(2);

            array<unsigned char>^ clues = gcnew array<unsigned char>(Cells);
            array<unsigned char>^ solution = gcnew array<unsigned char>(Cells);
            for (int i = 0; i < Cells; ++i)
            {
                unsigned char sol = (unsigned char)(1 + (i % 9));
                solution[i] = sol;
                bool isClue = (i < numClues);
                clues[i] = isClue ? sol : (unsigned char)0;
                if (isClue) s->board->setClue(i, sol);
            }
            s->puzzle = gcnew Puzzle(clues, solution);

            int revealed = 0;
            for (int i = numClues; i < Cells && revealed < numHints; ++i, ++revealed)
                s->board->reveal(i, solution[i], CellKind::Hint);
            return s;
        }

    public:
        // ---- isClean ----

        [TestMethod]
        void IsClean_TrueForFreshGame()
        {
            GameSession^ s = gcnew GameSession(Cells);
            s->startNewGame(2);
            Assert::IsTrue(s->isClean());
        }

        [TestMethod]
        void IsClean_FalseAfterAnyAssist()
        {
            GameSession^ s = gcnew GameSession(Cells);
            s->startNewGame(2);

            s->numberOfHints = 1;
            Assert::IsFalse(s->isClean());

            s->numberOfHints = 0;
            s->maxCandidateAssist = CandidateDisplay::AllCells;
            Assert::IsFalse(s->isClean()); // candidate assist disqualifies too
        }

        // ---- clueCount ----

        [TestMethod]
        void ClueCount_CountsNonZeroClues()
        {
            Assert::AreEqual(30, MakeGameWithHints(30, 0)->clueCount());
        }

        [TestMethod]
        void ClueCount_ZeroWhenNoPuzzle()
        {
            GameSession^ s = gcnew GameSession(Cells);
            s->startCustomPuzzle(); // Solver mode, no puzzle snapshot yet
            Assert::AreEqual(0, s->clueCount());
        }

        // ---- hintCount ----

        [TestMethod]
        void HintCount_CountsRevealedHints()
        {
            Assert::AreEqual(5, MakeGameWithHints(30, 5)->hintCount());
        }

        [TestMethod]
        void HintCount_ZeroWithNoHints()
        {
            Assert::AreEqual(0, MakeGameWithHints(30, 0)->hintCount());
        }
    };
}
