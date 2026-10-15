// Danylo Fitel 2026
// Unit tests for GameSession: per-puzzle state resets (finished flag) and its derived queries
// (clean-win test, clue count).

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

        // A Game session whose first `numClues` cells are clues filled from the solution.
        static GameSession^ MakeGameWithClues(int numClues)
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
            return s;
        }

    public:
        // ---- finished ----

        [TestMethod]
        void New_IsNotFinished()
        {
            Assert::IsFalse((gcnew GameSession(Cells))->finished);
        }

        [TestMethod]
        void StartNewGame_ClearsFinished()
        {
            GameSession^ s = gcnew GameSession(Cells);
            s->finished = true;
            s->startNewGame(2);
            Assert::IsFalse(s->finished);
        }

        [TestMethod]
        void StartCustomPuzzle_ClearsFinished()
        {
            GameSession^ s = gcnew GameSession(Cells);
            s->finished = true;
            s->startCustomPuzzle();
            Assert::IsFalse(s->finished);
            Assert::IsTrue(s->mode == GameMode::Solver);
        }

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
            Assert::AreEqual(30, MakeGameWithClues(30)->clueCount());
        }

        [TestMethod]
        void ClueCount_ZeroWhenNoPuzzle()
        {
            GameSession^ s = gcnew GameSession(Cells);
            s->startCustomPuzzle(); // Solver mode, no puzzle snapshot yet
            Assert::AreEqual(0, s->clueCount());
        }
    };
}
