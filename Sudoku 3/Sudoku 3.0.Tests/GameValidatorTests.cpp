// Danylo Fitel 2026
// Unit tests for GameValidator: the rules for a valid game, one test per invariant, checked on
// in-memory games (no files). Every reachable session state passes; each way of breaking a rule
// is rejected, and for its own reason (the test checks the rejection message).

#include "GameValidator.h"
#include "SavedGameFixtures.h"

using namespace System;
using namespace Sudoku_3_0;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace Sudoku_3_0_Tests
{
    using namespace SavedGameFixtures;

    [TestClass]
    public ref class GameValidatorTests
    {
    private:
        // The message Validate throws for g, or nullptr if it accepts it.
        static String^ ValidateMessage(SavedGame^ g)
        {
            try
            {
                GameValidator::Validate(g, Cells);
                return nullptr;
            }
            catch (Exception^ ex)
            {
                return ex->Message;
            }
        }

        static void AssertValid(SavedGame^ g)
        {
            String^ message = ValidateMessage(g);
            Assert::IsNull(message, "Rejected a valid game: " + message);
        }

        // Asserts that Validate rejects g for the stated reason (a fragment of the message)
        static void AssertInvalid(SavedGame^ g, String^ reason)
        {
            String^ message = ValidateMessage(g);
            Assert::IsNotNull(message, "Accepted an invalid game; expected rejection: " + reason);
            Assert::IsTrue(message->Contains(reason), "Expected rejection '" + reason + "' but got: " + message);
        }

        static void AssertValidHistory(SavedGame^ g)
        {
            AssertValid(g);
            GameValidator::ValidateHistory(g);
        }

        // Asserts that ValidateHistory rejects g's history for the stated reason. The game itself
        // must be valid, so only the history can be at fault.
        static void AssertInvalidHistory(SavedGame^ g, String^ reason)
        {
            AssertValid(g);
            try
            {
                GameValidator::ValidateHistory(g);
            }
            catch (Exception^ ex)
            {
                Assert::IsTrue(ex->Message->Contains(reason), "Expected rejection '" + reason + "' but got: " + ex->Message);
                return;
            }
            Assert::Fail("Accepted an invalid history; expected rejection: " + reason);
        }

        // The same, for a single-cell undo history
        static void AssertInvalidHistory(SavedGame^ g, UndoManager::CellState^ cell, String^ reason)
        {
            g->undoHistory = MakeHistory(Op(cell));
            AssertInvalidHistory(g, reason);
        }

    public:
        // ---- Every reachable session state is valid ----

        [TestMethod]
        void AcceptsEveryReachableSessionState()
        {
            Assert::IsNull(ValidateMessage(MakeGameSave()));
            Assert::IsNull(ValidateMessage(MakeWonGameSave()));
            Assert::IsNull(ValidateMessage(MakeGivenUpGameSave()));
            Assert::IsNull(ValidateMessage(MakeSolverInProgressSave()));
            Assert::IsNull(ValidateMessage(MakeSolvedSolverSave()));
        }
        [TestMethod]
        void Rejects_WrongLengthBoard()
        {
            SavedGame^ g = MakeGameSave();
            g->values = gcnew array<unsigned char>(Cells - 1);
            Assert::IsTrue(ValidateMessage(g)->Contains("Invalid length for field 'value'"));
        }
        [TestMethod]
        void Rejects_MissingPuzzleArrays()
        {
            // Capture always supplies empty arrays for "no puzzle"; nullptr is a bug, not "none"
            SavedGame^ g = MakeSolverInProgressSave();
            g->clues = nullptr;
            Assert::IsTrue(ValidateMessage(g)->Contains("Missing puzzle snapshot"));
        }
        // ---- Values and the puzzle snapshot ----

        [TestMethod]
        void Rejects_GameWithoutPuzzle()
        {
            // Game mode requires a solution; strip the puzzle from an otherwise-valid save.
            SavedGame^ g = MakeGameSave();
            g->clues = gcnew array<unsigned char>(0);
            g->solution = gcnew array<unsigned char>(0);
            AssertInvalid(g, "A saved game must contain a puzzle solution");
        }
        [TestMethod]
        void Rejects_ValueStateMismatch()
        {
            SavedGame^ g = MakeGameSave();
            g->states[0] = 1; // cell 0 holds a value but is marked empty (state 1)
            AssertInvalid(g, "Mismatched cell value and state");
        }
        [TestMethod]
        void Rejects_SolverFilledCellInGameMode()
        {
            SavedGame^ g = MakeGameSave();
            g->states[0] = 6; // cell 0 is filled; solver state 6 is illegal in Game mode
            AssertInvalid(g, "cannot occur in this session state");
        }
        [TestMethod]
        void Rejects_GameRevealInSolverMode()
        {
            SavedGame^ g = MakeSolverInProgressSave();
            g->states[0] = 3; // 'correct' is a Game reveal, illegal in Solver mode
            AssertInvalid(g, "cannot occur in this session state");
        }
        [TestMethod]
        void Rejects_ClueSolutionMismatch()
        {
            SavedGame^ g = MakeGameSave();
            // Give clue 0 a value that differs from the solution at that cell.
            g->clues[0] = (unsigned char)(g->solution[0] == 9 ? 1 : g->solution[0] + 1);
            AssertInvalid(g, "Clue/solution mismatch");
        }
        [TestMethod]
        void Rejects_InvalidSolutionDigit()
        {
            SavedGame^ g = MakeGameSave();
            g->solution[0] = 0; // solution digits must be 1-9
            AssertInvalid(g, "Invalid solution value");
        }
        [TestMethod]
        void Rejects_InvalidPencilMarkBit()
        {
            // Bit 0 is never a valid pencil mark (digits are bits 1-9), so value 1 is rejected.
            SavedGame^ g = MakeGameSave();
            g->pencilMarks[0] = 1; // bit 0 set
            AssertInvalid(g, "Invalid pencilMarks value");
        }
        [TestMethod]
        void Rejects_DifficultyOutOfRange()
        {
            // Only 0..4 are valid; anything else must fail the load before it is applied.
            SavedGame^ g = MakeGameSave();
            g->difficulty = 5;
            AssertInvalid(g, "Invalid difficulty value");
        }
        [TestMethod]
        void Rejects_CandidateAssistOutOfRange()
        {
            // Only 0..2 (None/CurrentCell/AllCells) are valid.
            SavedGame^ g = MakeGameSave();
            g->candidateAssist = static_cast<CandidateDisplay>(3);
            AssertInvalid(g, "Invalid candidateAssist value");
        }

        // ---- Board invariants, per session state (see GameValidator::ValidateBoard) ----

        [TestMethod]
        void Rejects_PencilMarksOnFilledCell()
        {
            SavedGame^ g = MakeGameSave();
            g->pencilMarks[0] = 1 << 4; // cell 0 is a clue
            AssertInvalid(g, "Pencil marks on a filled cell");
        }
        [TestMethod]
        void Rejects_ClueCellWherePuzzleHasNoClue()
        {
            SavedGame^ g = MakeGameSave();
            g->values[1] = g->solution[1]; // cell 1 is not a clue in the puzzle
            g->states[1] = 0;
            g->pencilMarks[1] = 0;
            AssertInvalid(g, "Clue cell does not match the puzzle's clues");
        }
        [TestMethod]
        void Rejects_PuzzleClueNotLockedAsClue()
        {
            SavedGame^ g = MakeGameSave();
            g->states[0] = 2; // cell 0 is a clue, but marked user-filled with the same digit
            AssertInvalid(g, "Clue cell does not match the puzzle's clues");
        }
        [TestMethod]
        void Rejects_ClueCellWithWrongDigit()
        {
            SavedGame^ g = MakeGameSave();
            g->values[0] = (unsigned char)(g->solution[0] % 9 + 1);
            AssertInvalid(g, "Locked cell does not hold its solution digit");
        }
        [TestMethod]
        void InProgress_AcceptsWrongGuessesAndHints()
        {
            SavedGame^ g = MakeGameSave();
            g->values[1] = (unsigned char)(g->solution[1] % 9 + 1); // a wrong guess is fine
            g->states[1] = 2;
            g->pencilMarks[1] = 0;
            g->values[2] = g->solution[2];                          // and so is a hint
            g->states[2] = 4;
            g->pencilMarks[2] = 0;
            AssertValid(g);
        }
        [TestMethod]
        void InProgress_Rejects_CorrectCell()
        {
            SavedGame^ g = MakeGameSave();
            g->values[1] = g->solution[1];
            g->states[1] = 3;
            g->pencilMarks[1] = 0;
            AssertInvalid(g, "cannot occur in this session state");
        }
        [TestMethod]
        void InProgress_Rejects_GivenUpCell()
        {
            SavedGame^ g = MakeGameSave();
            g->values[1] = g->solution[1];
            g->states[1] = 5;
            g->pencilMarks[1] = 0;
            AssertInvalid(g, "cannot occur in this session state");
        }
        [TestMethod]
        void InProgress_Rejects_SolverFilledCell()
        {
            SavedGame^ g = MakeGameSave();
            g->values[1] = g->solution[1];
            g->states[1] = 6;
            g->pencilMarks[1] = 0;
            AssertInvalid(g, "cannot occur in this session state");
        }
        [TestMethod]
        void InProgress_Rejects_HintWithWrongDigit()
        {
            SavedGame^ g = MakeGameSave();
            g->values[1] = (unsigned char)(g->solution[1] % 9 + 1);
            g->states[1] = 4;
            g->pencilMarks[1] = 0;
            AssertInvalid(g, "Locked cell does not hold its solution digit");
        }
        [TestMethod]
        void InProgress_Rejects_FewerHintsCountedThanHintCells()
        {
            // Hint cells with numberOfHints == 0 would pass for a clean win.
            SavedGame^ g = MakeGameSave();
            g->numberOfHints = 0;
            g->values[1] = g->solution[1];
            g->states[1] = 4;
            g->pencilMarks[1] = 0;
            AssertInvalid(g, "numberOfHints is below the number of hint cells");
        }
        [TestMethod]
        void InProgress_Rejects_AlreadySolvedBoard()
        {
            // Filling the last cell correctly wins on the spot, so this state is never saved.
            SavedGame^ g = MakeGameSave();
            for (int i = 0; i < Cells; ++i)
            {
                if (g->states[i] != 1) continue;
                g->values[i] = g->solution[i];
                g->states[i] = 2;
                g->pencilMarks[i] = 0;
            }
            AssertInvalid(g, "An unfinished game cannot already be solved");
        }
        [TestMethod]
        void InProgress_AcceptsFullBoardWithAWrongDigit()
        {
            SavedGame^ g = MakeGameSave();
            for (int i = 0; i < Cells; ++i)
            {
                if (g->states[i] != 1) continue;
                g->values[i] = g->solution[i];
                g->states[i] = 2;
                g->pencilMarks[i] = 0;
            }
            g->values[1] = (unsigned char)(g->solution[1] % 9 + 1);
            AssertValid(g);
        }
        [TestMethod]
        void Won_Rejects_EmptyCell()
        {
            SavedGame^ g = MakeWonGameSave();
            g->values[1] = 0;
            g->states[1] = 1;
            AssertInvalid(g, "cannot occur in this session state");
        }
        [TestMethod]
        void Won_Rejects_UserFilledCell()
        {
            SavedGame^ g = MakeWonGameSave();
            g->states[1] = 2; // a win locks every user cell as Correct
            AssertInvalid(g, "cannot occur in this session state");
        }
        [TestMethod]
        void Won_Rejects_CorrectCellWithWrongDigit()
        {
            SavedGame^ g = MakeWonGameSave();
            g->values[1] = (unsigned char)(g->solution[1] % 9 + 1);
            AssertInvalid(g, "Locked cell does not hold its solution digit");
        }
        [TestMethod]
        void Finished_Rejects_BothWonAndGivenUp()
        {
            SavedGame^ g = MakeWonGameSave();
            g->numberOfGiveUps = 1;
            g->states[1] = 5;
            AssertInvalid(g, "A game cannot be both won and given up");
        }
        [TestMethod]
        void Finished_Rejects_PencilMarks()
        {
            SavedGame^ g = MakeWonGameSave();
            g->pencilMarks[1] = 1 << 3;
            AssertInvalid(g, "Pencil marks on a filled cell");
        }
        [TestMethod]
        void GivenUp_Rejects_UncountedGiveUp()
        {
            SavedGame^ g = MakeGivenUpGameSave();
            g->numberOfGiveUps = 0;
            AssertInvalid(g, "A given-up game must count the give-up");
        }
        [TestMethod]
        void GivenUp_Rejects_UserFilledCell()
        {
            SavedGame^ g = MakeGivenUpGameSave();
            g->states[1] = 2; // giving up reveals every user cell
            AssertInvalid(g, "cannot occur in this session state");
        }
        [TestMethod]
        void GivenUp_Rejects_RevealWithWrongDigit()
        {
            SavedGame^ g = MakeGivenUpGameSave();
            g->values[1] = (unsigned char)(g->solution[1] % 9 + 1);
            AssertInvalid(g, "Locked cell does not hold its solution digit");
        }
        [TestMethod]
        void Entering_Rejects_ClueCell()
        {
            // Cells lock only when Solve succeeds; an unsolved custom puzzle has no clues.
            SavedGame^ g = MakeSolverInProgressSave();
            g->states[0] = 0; // cell 0 holds a value, so only the lock is wrong
            AssertInvalid(g, "cannot occur in this session state");
        }
        [TestMethod]
        void Entering_Rejects_SolverFilledCell()
        {
            SavedGame^ g = MakeSolverInProgressSave();
            g->states[0] = 6;
            AssertInvalid(g, "cannot occur in this session state");
        }
        [TestMethod]
        void Entering_Rejects_GameOnlyCells()
        {
            for each (unsigned char state in gcnew array<unsigned char>{ 3, 4, 5 }) // correct, hint, given up
            {
                SavedGame^ g = MakeSolverInProgressSave();
                g->states[0] = state;
                AssertInvalid(g, "cannot occur in this session state");
            }
        }
        [TestMethod]
        void Entering_Rejects_Solution()
        {
            // Solve both captures the solution and finishes; an unfinished entry cannot have it.
            SavedGame^ g = MakeSolvedSolverSave();
            g->gameFinished = false;
            for (int i = 0; i < Cells; ++i)
                g->states[i] = 2; // every cell editable, so only the snapshot is wrong
            AssertInvalid(g, "cannot have a solution");
        }
        [TestMethod]
        void Entering_Rejects_PencilMarks()
        {
            SavedGame^ g = MakeSolverInProgressSave();
            g->pencilMarks[80] = 1 << 5; // cell 80 is empty, but Pencil is game-only
            AssertInvalid(g, "Pencil marks in Solver mode");
        }
        [TestMethod]
        void Entering_Rejects_GameCounters()
        {
            for (int counter = 0; counter < 4; ++counter)
            {
                SavedGame^ g = MakeSolverInProgressSave();
                switch (counter)
                {
                case 0:  g->numberOfHints = 1; break;
                case 1:  g->numberOfFixes = 1; break;
                case 2:  g->numberOfGiveUps = 1; break;
                default: g->numberOfRestarts = 1; break;
                }
                AssertInvalid(g, "Solver sessions have no hint, fix, give-up or restart counts");
            }
        }
        [TestMethod]
        void Solved_Rejects_MissingSolution()
        {
            // "Finished" in Solver mode means solved; without a solution it never happened.
            SavedGame^ g = MakeSolverInProgressSave();
            g->gameFinished = true;
            AssertInvalid(g, "must contain its solution");
        }
        [TestMethod]
        void Solved_Rejects_EmptyCell()
        {
            SavedGame^ g = MakeSolvedSolverSave();
            g->values[1] = 0; // cell 1 is solver-filled in the fixture
            g->states[1] = 1;
            AssertInvalid(g, "cannot occur in this session state");
        }
        [TestMethod]
        void Solved_Rejects_UserFilledCell()
        {
            SavedGame^ g = MakeSolvedSolverSave();
            g->states[1] = 2;
            AssertInvalid(g, "cannot occur in this session state");
        }
        [TestMethod]
        void Solved_Rejects_CellNotMatchingSolution()
        {
            SavedGame^ g = MakeSolvedSolverSave();
            g->values[1] = (unsigned char)(g->solution[1] % 9 + 1);
            AssertInvalid(g, "Locked cell does not hold its solution digit");
        }
        [TestMethod]
        void Solved_Rejects_ClueMarkedAsSolverFilled()
        {
            SavedGame^ g = MakeSolvedSolverSave();
            g->states[0] = 6; // cell 0 is a clue in the fixture
            AssertInvalid(g, "Clue cell does not match the puzzle's clues");
        }
        [TestMethod]
        void Solved_Rejects_SolverCellMarkedAsClue()
        {
            SavedGame^ g = MakeSolvedSolverSave();
            g->states[1] = 0; // cell 1 was filled by the solver, not entered
            AssertInvalid(g, "Clue cell does not match the puzzle's clues");
        }
        [TestMethod]
        void Solved_Rejects_GameCounters()
        {
            SavedGame^ g = MakeSolvedSolverSave();
            g->numberOfHints = 1;
            AssertInvalid(g, "Solver sessions have no hint, fix, give-up or restart counts");
        }
        // ---- Undo/redo history (see GameValidator::ValidateHistory) ----

        [TestMethod]
        void History_AcceptsSnapshotsPlayCanRecord()
        {
            // Cell 1 empty with marks, then a two-cell batch; redo re-reveals cell 1 as its hint
            SavedGame^ g = MakeGameSave();
            g->undoHistory = MakeHistory(
                Op(Cell(1, 0, CellKind::UserEmpty, 1 << 2)),
                Op(Cell(2, 0, CellKind::UserEmpty, 0), Cell(4, 7, CellKind::UserFilled, 0)));
            g->redoHistory = MakeHistory(Op(Cell(1, 2, CellKind::Hint, 0)));
            AssertValidHistory(g);
        }

        [TestMethod]
        void History_Rejects_TouchingAClue()
        {
            // Restoring it would turn the clue in cell 0 into an editable cell
            AssertInvalidHistory(MakeGameSave(), Cell(0, 0, CellKind::UserEmpty, 0), "History touches a locked cell");
        }

        [TestMethod]
        void History_Rejects_LockedKinds()
        {
            AssertInvalidHistory(MakeGameSave(), Cell(1, 2, CellKind::Clue, 0), "Invalid history kind");
            AssertInvalidHistory(MakeGameSave(), Cell(1, 2, CellKind::Correct, 0), "Invalid history kind");
            AssertInvalidHistory(MakeGameSave(), Cell(1, 2, CellKind::GivenUp, 0), "Invalid history kind");
            AssertInvalidHistory(MakeGameSave(), Cell(1, 2, CellKind::Solved, 0), "Invalid history kind");
        }

        [TestMethod]
        void History_Rejects_ValueKindMismatch()
        {
            AssertInvalidHistory(MakeGameSave(), Cell(1, 0, CellKind::UserFilled, 0), "Mismatched history value and kind");
            AssertInvalidHistory(MakeGameSave(), Cell(1, 5, CellKind::UserEmpty, 0), "Mismatched history value and kind");
            AssertInvalidHistory(MakeGameSave(), Cell(1, 0, CellKind::Hint, 0), "Mismatched history value and kind");
        }

        [TestMethod]
        void History_Rejects_CellOffTheBoard()
        {
            AssertInvalidHistory(MakeGameSave(), Cell(Cells, 0, CellKind::UserEmpty, 0), "History cell is off the board");
        }

        [TestMethod]
        void History_Rejects_ValueAboveNine()
        {
            // Would pass every other check, then make Board::restoreCell throw on Undo
            AssertInvalidHistory(MakeGameSave(), Cell(1, 12, CellKind::UserFilled, 0), "Invalid history value 12");
        }

        [TestMethod]
        void History_Rejects_UnknownKind()
        {
            AssertInvalidHistory(MakeGameSave(), Cell(1, 2, static_cast<CellKind>(7), 0), "Invalid history kind");
        }

        [TestMethod]
        void History_Rejects_MissingEntry()
        {
            SavedGame^ g = MakeGameSave();
            g->undoHistory = MakeHistory(gcnew array<UndoManager::CellState^>(1)); // one null entry
            AssertInvalidHistory(g, "Missing history entry");
        }

        [TestMethod]
        void History_Rejects_HintWithWrongDigit()
        {
            // Cell 1's solution is 2; a "hint" of 9 would lock a wrong digit into the board
            AssertInvalidHistory(MakeGameSave(), Cell(1, 9, CellKind::Hint, 0), "Invalid history hint");
        }

        [TestMethod]
        void History_Rejects_HintInSolverMode()
        {
            AssertInvalidHistory(MakeSolverInProgressSave(), Cell(10, 5, CellKind::Hint, 0), "Invalid history hint");
        }

        [TestMethod]
        void History_Rejects_InvalidPencilMarks()
        {
            AssertInvalidHistory(MakeGameSave(), Cell(1, 0, CellKind::UserEmpty, 1), "Invalid history pencil marks");    // bit 0
            AssertInvalidHistory(MakeGameSave(), Cell(1, 5, CellKind::UserFilled, 4), "Invalid history pencil marks");   // on a filled cell
        }

        [TestMethod]
        void History_Rejects_EmptyOperation()
        {
            SavedGame^ g = MakeGameSave();
            g->undoHistory = MakeHistory(gcnew array<UndoManager::CellState^>(0));
            AssertInvalidHistory(g, "Empty history operation");
        }

        [TestMethod]
        void History_Rejects_AnyHistoryInAFinishedGame()
        {
            // Cell 2 of the won save is a hint, which a history may touch: only "finished" is wrong
            SavedGame^ g = MakeWonGameSave();
            g->redoHistory = MakeHistory(Op(Cell(2, 0, CellKind::UserEmpty, 0)));
            AssertInvalidHistory(g, "A finished game has no undo history");
        }

        [TestMethod]
        void History_ChecksTheRedoHalfToo()
        {
            SavedGame^ g = MakeGameSave();
            g->undoHistory = MakeHistory(Op(Cell(1, 0, CellKind::UserEmpty, 0)));
            g->redoHistory = MakeHistory(Op(Cell(0, 0, CellKind::UserEmpty, 0)));
            AssertInvalidHistory(g, "History touches a locked cell");
        }
    };
}
