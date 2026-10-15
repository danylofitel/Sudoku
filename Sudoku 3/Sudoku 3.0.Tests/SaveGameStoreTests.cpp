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

        // A finished Game-mode save, ended either by a win (every cell the player had to fill
        // locked as Correct) or by giving up (every such cell revealed as GivenUp). Cells 0, 3,
        // 6, ... are clues as in MakeGameSave; cells 2, 11, 20, ... (i % 9 == 2) were revealed
        // as hints, and numberOfHints counts them.
        static SavedGame^ MakeFinishedGameSave(CellKind ending)
        {
            SavedGame^ g = gcnew SavedGame();
            g->difficulty = 4;
            g->numberOfRestarts = 0;
            g->numberOfHints = 9;
            g->numberOfFixes = 1;
            g->numberOfGiveUps = ending == CellKind::GivenUp ? 1 : 0;
            g->mode = GameMode::Game;
            g->gameFinished = true;
            g->elapsedSeconds = 600;
            g->clues = gcnew array<unsigned char>(Cells);
            g->solution = gcnew array<unsigned char>(Cells);
            g->values = gcnew array<unsigned char>(Cells);
            g->states = gcnew array<unsigned char>(Cells);
            g->pencilMarks = gcnew array<int>(Cells);

            for (int i = 0; i < Cells; ++i)
            {
                unsigned char sol = (unsigned char)(1 + (i % 9));
                g->solution[i] = sol;
                g->values[i] = sol; // finished: every cell holds its solution
                CellKind kind = (i % 3 == 0) ? CellKind::Clue
                    : (i % 9 == 2) ? CellKind::Hint
                    : ending;
                g->states[i] = static_cast<unsigned char>(kind);
                g->clues[i] = (kind == CellKind::Clue) ? sol : (unsigned char)0;
                g->pencilMarks[i] = 0;
            }
            return g;
        }

        static SavedGame^ MakeWonGameSave() { return MakeFinishedGameSave(CellKind::Correct); }
        static SavedGame^ MakeGivenUpGameSave() { return MakeFinishedGameSave(CellKind::GivenUp); }

        // A solved Solver-mode save: pre-filled cells are clues (state 0), the rest were filled
        // by the solver (state 6). Has a full puzzle snapshot.
        static SavedGame^ MakeSolvedSolverSave()
        {
            SavedGame^ g = gcnew SavedGame();
            g->difficulty = 2;
            g->numberOfRestarts = 0;
            g->numberOfHints = 0;
            g->numberOfFixes = 0;
            g->numberOfGiveUps = 0;
            g->mode = GameMode::Solver;
            g->gameFinished = true;
            g->elapsedSeconds = 30;
            g->clues = gcnew array<unsigned char>(Cells);
            g->solution = gcnew array<unsigned char>(Cells);
            g->values = gcnew array<unsigned char>(Cells);
            g->states = gcnew array<unsigned char>(Cells);
            g->pencilMarks = gcnew array<int>(Cells);

            for (int i = 0; i < Cells; ++i)
            {
                unsigned char sol = (unsigned char)(1 + (i % 9));
                g->solution[i] = sol;
                g->values[i] = sol;
                bool prefilled = (i % 4 == 0);
                g->states[i] = prefilled ? (unsigned char)0 /*clue*/ : (unsigned char)6 /*solved*/;
                g->clues[i] = prefilled ? sol : (unsigned char)0;
                g->pencilMarks[i] = 0;
            }
            return g;
        }

        // Asserts that loading g fails, and fails for the stated reason (a fragment of the
        // rejection message) - so each invariant test proves its own rule, not just any error.
        static void AssertRejected(SavedGame^ g, String^ reason)
        {
            String^ path = Path::GetTempFileName();
            try
            {
                SaveGameStore::Save(path, g);
                AssertFileRejected(path, reason);
            }
            finally
            {
                File::Delete(path);
            }
        }

        // The same check for a hand-written file.
        static void AssertTextRejected(String^ text, String^ reason)
        {
            String^ path = Path::GetTempFileName();
            try
            {
                File::WriteAllText(path, text);
                AssertFileRejected(path, reason);
            }
            finally
            {
                File::Delete(path);
            }
        }

        // The same check for a valid save with one line edited: the line for `key` is replaced
        // by `replacement`, or removed when replacement is nullptr.
        static void AssertRejectedWithLine(SavedGame^ g, String^ key, String^ replacement, String^ reason)
        {
            String^ path = Path::GetTempFileName();
            try
            {
                SaveGameStore::Save(path, g);

                System::Collections::Generic::List<String^>^ lines =
                    gcnew System::Collections::Generic::List<String^>();
                for each (String ^ line in File::ReadAllLines(path))
                {
                    if (!line->StartsWith(key + "=")) lines->Add(line);
                    else if (replacement != nullptr) lines->Add(replacement);
                }
                File::WriteAllLines(path, lines->ToArray());

                AssertFileRejected(path, reason);
            }
            finally
            {
                File::Delete(path);
            }
        }

        static void AssertFileRejected(String^ path, String^ reason)
        {
            try
            {
                SaveGameStore::Load(path, Cells);
            }
            catch (UnsupportedSaveVersionException^)
            {
                throw;
            }
            catch (Exception^ ex)
            {
                Assert::IsTrue(ex->Message->Contains(reason),
                    "Expected rejection '" + reason + "' but got: " + ex->Message);
                return;
            }
            Assert::Fail("Load accepted an invalid save; expected rejection: " + reason);
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

        static array<array<UndoManager::CellState^>^>^ MakeHistory(... array<array<UndoManager::CellState^>^>^ operations)
        {
            return operations;
        }

        static array<UndoManager::CellState^>^ Op(... array<UndoManager::CellState^>^ cells)
        {
            return cells;
        }

        static UndoManager::CellState^ Cell(unsigned int index, unsigned char value, CellKind kind, int marks)
        {
            return gcnew UndoManager::CellState(index, value, kind, marks);
        }

        // Saves g, then overwrites its undo/redo lines with hand-written text and loads it back.
        static SavedGame^ LoadWithHistoryText(SavedGame^ g, String^ undoText, String^ redoText)
        {
            String^ path = Path::GetTempFileName();
            try
            {
                SaveGameStore::Save(path, g);

                System::Collections::Generic::List<String^>^ lines =
                    gcnew System::Collections::Generic::List<String^>();
                for each (String ^ line in File::ReadAllLines(path))
                {
                    if (line->StartsWith("undo=")) lines->Add("undo=" + undoText);
                    else if (line->StartsWith("redo=")) lines->Add("redo=" + redoText);
                    else lines->Add(line);
                }
                File::WriteAllLines(path, lines->ToArray());

                return SaveGameStore::Load(path, Cells);
            }
            finally
            {
                File::Delete(path);
            }
        }

        // A bad history must be dropped (both halves), while the game itself still loads.
        static void AssertHistoryDropped(SavedGame^ g, String^ undoText, String^ redoText)
        {
            SavedGame^ back = LoadWithHistoryText(g, undoText, redoText);
            String^ input = "undo=" + undoText + " redo=" + redoText;
            Assert::AreEqual(Cells, back->values->Length, "game not loaded for " + input);
            Assert::AreEqual(0, back->undoHistory->Length, "undo kept for " + input);
            Assert::AreEqual(0, back->redoHistory->Length, "redo kept for " + input);
        }

        // In MakeGameSave, cells 0, 3, 6, ... are clues and the rest are empty; cell 1's solution
        // is 2. Each caller passes a single-cell undo history that breaks one rule.
        static void AssertGameHistoryDropped(String^ undoText)
        {
            AssertHistoryDropped(MakeGameSave(), undoText, "");
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
        void Load_Rejects_FileThatIsNotASave()
        {
            AssertTextRejected("just some random text\nnot a save\n", "Not a recognized Sudoku save file");
        }

        [TestMethod]
        void Load_Rejects_MissingRequiredField()
        {
            // Recognized header + version, but every other required field is absent.
            AssertTextRejected("Sudoku3Save=1\n", "Missing field");
        }

        [TestMethod]
        void Load_Rejects_GameWithoutPuzzle()
        {
            // Game mode requires a solution; strip the puzzle from an otherwise-valid save.
            SavedGame^ g = MakeGameSave();
            g->clues = gcnew array<unsigned char>(0);
            g->solution = gcnew array<unsigned char>(0);
            AssertRejected(g, "A saved game must contain a puzzle solution");
        }

        [TestMethod]
        void UnsupportedSaveVersionException_CarriesVersions()
        {
            UnsupportedSaveVersionException^ ex = gcnew UnsupportedSaveVersionException(5, 1);
            Assert::AreEqual(5, (int)ex->FileVersion);
            Assert::AreEqual(1, (int)ex->SupportedVersion);
        }

        [TestMethod]
        void RoundTrip_WonGame_PreservesStates()
        {
            SavedGame^ back = SaveAndReload(MakeWonGameSave());

            Assert::IsTrue(back->gameFinished);
            Assert::AreEqual(0, (int)back->states[0]); // clue
            Assert::AreEqual(3, (int)back->states[1]); // correct
            Assert::AreEqual(4, (int)back->states[2]); // hint
        }

        [TestMethod]
        void RoundTrip_GivenUpGame_PreservesStates()
        {
            SavedGame^ back = SaveAndReload(MakeGivenUpGameSave());

            Assert::IsTrue(back->gameFinished);
            Assert::AreEqual(0, (int)back->states[0]); // clue
            Assert::AreEqual(5, (int)back->states[1]); // given up
            Assert::AreEqual(4, (int)back->states[2]); // hint
        }

        [TestMethod]
        void RoundTrip_SolvedSolver_PreservesSolvedState()
        {
            SavedGame^ back = SaveAndReload(MakeSolvedSolverSave());

            Assert::IsTrue(back->mode == GameMode::Solver);
            Assert::IsTrue(back->gameFinished);
            Assert::AreEqual(Cells, back->clues->Length); // a solved puzzle has a snapshot
            Assert::AreEqual(0, (int)back->states[0]);     // pre-filled clue
            Assert::AreEqual(6, (int)back->states[1]);     // solver-filled
        }

        [TestMethod]
        void Load_Rejects_ValueStateMismatch()
        {
            SavedGame^ g = MakeGameSave();
            g->states[0] = 1; // cell 0 holds a value but is marked empty (state 1)
            AssertRejected(g, "Mismatched cell value and state");
        }

        [TestMethod]
        void Load_Rejects_SolverFilledCellInGameMode()
        {
            SavedGame^ g = MakeGameSave();
            g->states[0] = 6; // cell 0 is filled; solver state 6 is illegal in Game mode
            AssertRejected(g, "cannot occur in this session state");
        }

        [TestMethod]
        void Load_Rejects_GameRevealInSolverMode()
        {
            SavedGame^ g = MakeSolverInProgressSave();
            g->states[0] = 3; // 'correct' is a Game reveal, illegal in Solver mode
            AssertRejected(g, "cannot occur in this session state");
        }

        [TestMethod]
        void Load_Rejects_ClueSolutionMismatch()
        {
            SavedGame^ g = MakeGameSave();
            // Give clue 0 a value that differs from the solution at that cell.
            g->clues[0] = (unsigned char)(g->solution[0] == 9 ? 1 : g->solution[0] + 1);
            AssertRejected(g, "Clue/solution mismatch");
        }

        [TestMethod]
        void Load_Rejects_InvalidSolutionDigit()
        {
            SavedGame^ g = MakeGameSave();
            g->solution[0] = 0; // solution digits must be 1-9
            AssertRejected(g, "Invalid solution value");
        }

        [TestMethod]
        void Load_Rejects_MissingPencilMarks()
        {
            // pencilMarks is a required field: a save missing it is rejected, not silently zeroed.
            AssertRejectedWithLine(MakeGameSave(), "pencilMarks", nullptr, "Missing field: pencilMarks");
        }

        [TestMethod]
        void Load_Rejects_InvalidPencilMarkBit()
        {
            // Bit 0 is never a valid pencil mark (digits are bits 1-9), so value 1 is rejected.
            SavedGame^ g = MakeGameSave();
            g->pencilMarks[0] = 1; // bit 0 set
            AssertRejected(g, "Invalid pencilMarks value");
        }

        [TestMethod]
        void RoundTrip_PreservesCandidateAssist()
        {
            SavedGame^ g = MakeGameSave();
            g->candidateAssist = CandidateDisplay::AllCells;
            SavedGame^ back = SaveAndReload(g);
            Assert::IsTrue(back->candidateAssist == CandidateDisplay::AllCells);
        }

        [TestMethod]
        void Load_Rejects_MissingCandidateAssist()
        {
            // candidateAssist is a required field: a save missing it is rejected.
            AssertRejectedWithLine(MakeGameSave(), "candidateAssist", nullptr, "Missing field: candidateAssist");
        }

        [TestMethod]
        void Load_Rejects_CandidateAssistOutOfRange()
        {
            // Only 0..2 (None/CurrentCell/AllCells) are valid.
            AssertRejectedWithLine(MakeGameSave(), "candidateAssist", "candidateAssist=3", "Invalid candidateAssist value");
        }
        // ---- Safe writes: the target is either the old save or the complete new one ----

    private:
        // A fresh path in the temp folder that does not exist yet.
        static String^ NewSavePath()
        {
            return Path::Combine(Path::GetTempPath(), "SudokuSaveTest-" + Guid::NewGuid().ToString("N") + ".sdk3");
        }

        static void DeleteSaveFiles(String^ path)
        {
            File::Delete(path);
            File::Delete(path + ".tmp");
        }

        // A save that throws partway through writing: the header and scalars are written, then
        // encoding the missing board array fails.
        static SavedGame^ MakeSaveThatFailsMidWrite()
        {
            SavedGame^ g = MakeGameSave();
            g->values = nullptr;
            return g;
        }

    public:
        [TestMethod]
        void Save_ToNewPath_CreatesFile_AndLeavesNoTemp()
        {
            String^ path = NewSavePath();
            try
            {
                SaveGameStore::Save(path, MakeGameSave());
                Assert::IsTrue(File::Exists(path));
                Assert::IsFalse(File::Exists(path + ".tmp"));
                Assert::AreEqual(3, (int)SaveGameStore::Load(path, Cells)->difficulty);
            }
            finally
            {
                DeleteSaveFiles(path);
            }
        }

        [TestMethod]
        void Save_OverExistingSave_ReplacesIt_AndLeavesNoTemp()
        {
            String^ path = NewSavePath();
            try
            {
                SaveGameStore::Save(path, MakeGameSave());          // difficulty 3
                SaveGameStore::Save(path, MakeSolvedSolverSave());  // difficulty 2

                Assert::IsFalse(File::Exists(path + ".tmp"));
                SavedGame^ back = SaveGameStore::Load(path, Cells);
                Assert::IsTrue(back->mode == GameMode::Solver);
                Assert::AreEqual(2, (int)back->difficulty);
            }
            finally
            {
                DeleteSaveFiles(path);
            }
        }

        [TestMethod]
        void Save_FailingMidWrite_LeavesExistingSaveIntact_AndNoTemp()
        {
            // The point of writing to a temp file: a failed save never costs the previous one.
            String^ path = NewSavePath();
            try
            {
                SaveGameStore::Save(path, MakeGameSave());
                array<Byte>^ before = File::ReadAllBytes(path);

                bool threw = false;
                try { SaveGameStore::Save(path, MakeSaveThatFailsMidWrite()); }
                catch (Exception^) { threw = true; }

                Assert::IsTrue(threw, "the save should have failed");
                CollectionAssert::AreEqual(before, File::ReadAllBytes(path), "the previous save changed");
                Assert::IsFalse(File::Exists(path + ".tmp"), "the temp file was left behind");
                SaveGameStore::Load(path, Cells); // and it still loads
            }
            finally
            {
                DeleteSaveFiles(path);
            }
        }

        [TestMethod]
        void Save_FailingMidWrite_ToNewPath_CreatesNothing()
        {
            String^ path = NewSavePath();
            try
            {
                bool threw = false;
                try { SaveGameStore::Save(path, MakeSaveThatFailsMidWrite()); }
                catch (Exception^) { threw = true; }

                Assert::IsTrue(threw, "the save should have failed");
                Assert::IsFalse(File::Exists(path), "a partial save was created");
                Assert::IsFalse(File::Exists(path + ".tmp"), "the temp file was left behind");
            }
            finally
            {
                DeleteSaveFiles(path);
            }
        }

        [TestMethod]
        void Save_OverStaleTempFile_Succeeds()
        {
            // A temp file left by a process killed mid-save is overwritten, not an obstacle.
            String^ path = NewSavePath();
            try
            {
                File::WriteAllText(path + ".tmp", "left over from a killed process");
                SaveGameStore::Save(path, MakeGameSave());

                Assert::IsFalse(File::Exists(path + ".tmp"));
                SaveGameStore::Load(path, Cells);
            }
            finally
            {
                DeleteSaveFiles(path);
            }
        }

        // ---- Board invariants (see SaveGameStore::ValidateBoard) ----
        // Every session state the app can reach loads; each way of breaking an invariant is
        // rejected, and for its own reason.

        [TestMethod]
        void Load_AcceptsEveryReachableSessionState()
        {
            SaveAndReload(MakeGameSave());            // game in progress
            SaveAndReload(MakeWonGameSave());         // game won
            SaveAndReload(MakeGivenUpGameSave());     // game given up
            SaveAndReload(MakeSolverInProgressSave()); // entering a custom puzzle
            SaveAndReload(MakeSolvedSolverSave());    // custom puzzle solved
        }

        // -- Every state --

        [TestMethod]
        void Load_Rejects_PencilMarksOnFilledCell()
        {
            SavedGame^ g = MakeGameSave();
            g->pencilMarks[0] = 1 << 4; // cell 0 is a clue
            AssertRejected(g, "Pencil marks on a filled cell");
        }

        [TestMethod]
        void Load_Rejects_ClueCellWherePuzzleHasNoClue()
        {
            SavedGame^ g = MakeGameSave();
            g->values[1] = g->solution[1]; // cell 1 is not a clue in the puzzle
            g->states[1] = 0;
            g->pencilMarks[1] = 0;
            AssertRejected(g, "Clue cell does not match the puzzle's clues");
        }

        [TestMethod]
        void Load_Rejects_PuzzleClueNotLockedAsClue()
        {
            SavedGame^ g = MakeGameSave();
            g->states[0] = 2; // cell 0 is a clue, but marked user-filled with the same digit
            AssertRejected(g, "Clue cell does not match the puzzle's clues");
        }

        [TestMethod]
        void Load_Rejects_ClueCellWithWrongDigit()
        {
            SavedGame^ g = MakeGameSave();
            g->values[0] = (unsigned char)(g->solution[0] % 9 + 1);
            AssertRejected(g, "Locked cell does not hold its solution digit");
        }

        // -- Game in progress: clues, empty, user-filled, and hint cells --

        [TestMethod]
        void Load_InProgress_AcceptsWrongGuessesAndHints()
        {
            SavedGame^ g = MakeGameSave();
            g->values[1] = (unsigned char)(g->solution[1] % 9 + 1); // a wrong guess is fine
            g->states[1] = 2;
            g->pencilMarks[1] = 0;
            g->values[2] = g->solution[2];                          // and so is a hint
            g->states[2] = 4;
            g->pencilMarks[2] = 0;
            SaveAndReload(g);
        }

        [TestMethod]
        void Load_InProgress_Rejects_CorrectCell()
        {
            SavedGame^ g = MakeGameSave();
            g->values[1] = g->solution[1];
            g->states[1] = 3;
            g->pencilMarks[1] = 0;
            AssertRejected(g, "cannot occur in this session state");
        }

        [TestMethod]
        void Load_InProgress_Rejects_GivenUpCell()
        {
            SavedGame^ g = MakeGameSave();
            g->values[1] = g->solution[1];
            g->states[1] = 5;
            g->pencilMarks[1] = 0;
            AssertRejected(g, "cannot occur in this session state");
        }

        [TestMethod]
        void Load_InProgress_Rejects_SolverFilledCell()
        {
            SavedGame^ g = MakeGameSave();
            g->values[1] = g->solution[1];
            g->states[1] = 6;
            g->pencilMarks[1] = 0;
            AssertRejected(g, "cannot occur in this session state");
        }

        [TestMethod]
        void Load_InProgress_Rejects_HintWithWrongDigit()
        {
            SavedGame^ g = MakeGameSave();
            g->values[1] = (unsigned char)(g->solution[1] % 9 + 1);
            g->states[1] = 4;
            g->pencilMarks[1] = 0;
            AssertRejected(g, "Locked cell does not hold its solution digit");
        }

        [TestMethod]
        void Load_InProgress_Rejects_FewerHintsCountedThanHintCells()
        {
            // Hint cells with numberOfHints == 0 would pass for a clean win.
            SavedGame^ g = MakeGameSave();
            g->numberOfHints = 0;
            g->values[1] = g->solution[1];
            g->states[1] = 4;
            g->pencilMarks[1] = 0;
            AssertRejected(g, "numberOfHints is below the number of hint cells");
        }

        [TestMethod]
        void Load_InProgress_Rejects_AlreadySolvedBoard()
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
            AssertRejected(g, "An unfinished game cannot already be solved");
        }

        [TestMethod]
        void Load_InProgress_AcceptsFullBoardWithAWrongDigit()
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
            SaveAndReload(g);
        }

        // -- Game won: clues, correct, and hint cells --

        [TestMethod]
        void Load_Won_Rejects_EmptyCell()
        {
            SavedGame^ g = MakeWonGameSave();
            g->values[1] = 0;
            g->states[1] = 1;
            AssertRejected(g, "cannot occur in this session state");
        }

        [TestMethod]
        void Load_Won_Rejects_UserFilledCell()
        {
            SavedGame^ g = MakeWonGameSave();
            g->states[1] = 2; // a win locks every user cell as Correct
            AssertRejected(g, "cannot occur in this session state");
        }

        [TestMethod]
        void Load_Won_Rejects_CorrectCellWithWrongDigit()
        {
            SavedGame^ g = MakeWonGameSave();
            g->values[1] = (unsigned char)(g->solution[1] % 9 + 1);
            AssertRejected(g, "Locked cell does not hold its solution digit");
        }

        [TestMethod]
        void Load_Finished_Rejects_BothWonAndGivenUp()
        {
            SavedGame^ g = MakeWonGameSave();
            g->numberOfGiveUps = 1;
            g->states[1] = 5;
            AssertRejected(g, "A game cannot be both won and given up");
        }

        [TestMethod]
        void Load_Finished_Rejects_PencilMarks()
        {
            SavedGame^ g = MakeWonGameSave();
            g->pencilMarks[1] = 1 << 3;
            AssertRejected(g, "Pencil marks on a filled cell");
        }

        // -- Game given up: clues, given-up, and hint cells --

        [TestMethod]
        void Load_GivenUp_Rejects_UncountedGiveUp()
        {
            SavedGame^ g = MakeGivenUpGameSave();
            g->numberOfGiveUps = 0;
            AssertRejected(g, "A given-up game must count the give-up");
        }

        [TestMethod]
        void Load_GivenUp_Rejects_UserFilledCell()
        {
            SavedGame^ g = MakeGivenUpGameSave();
            g->states[1] = 2; // giving up reveals every user cell
            AssertRejected(g, "cannot occur in this session state");
        }

        [TestMethod]
        void Load_GivenUp_Rejects_RevealWithWrongDigit()
        {
            SavedGame^ g = MakeGivenUpGameSave();
            g->values[1] = (unsigned char)(g->solution[1] % 9 + 1);
            AssertRejected(g, "Locked cell does not hold its solution digit");
        }

        // -- Entering a custom puzzle: empty and user-filled cells only, nothing else --

        [TestMethod]
        void Load_Entering_Rejects_ClueCell()
        {
            // Cells lock only when Solve succeeds; an unsolved custom puzzle has no clues.
            SavedGame^ g = MakeSolverInProgressSave();
            g->states[0] = 0; // cell 0 holds a value, so only the lock is wrong
            AssertRejected(g, "cannot occur in this session state");
        }

        [TestMethod]
        void Load_Entering_Rejects_SolverFilledCell()
        {
            SavedGame^ g = MakeSolverInProgressSave();
            g->states[0] = 6;
            AssertRejected(g, "cannot occur in this session state");
        }

        [TestMethod]
        void Load_Entering_Rejects_GameOnlyCells()
        {
            for each (unsigned char state in gcnew array<unsigned char>{ 3, 4, 5 }) // correct, hint, given up
            {
                SavedGame^ g = MakeSolverInProgressSave();
                g->states[0] = state;
                AssertRejected(g, "cannot occur in this session state");
            }
        }

        [TestMethod]
        void Load_Entering_Rejects_Solution()
        {
            // Solve both captures the solution and finishes; an unfinished entry cannot have it.
            SavedGame^ g = MakeSolvedSolverSave();
            g->gameFinished = false;
            for (int i = 0; i < Cells; ++i)
                g->states[i] = 2; // every cell editable, so only the snapshot is wrong
            AssertRejected(g, "cannot have a solution");
        }

        [TestMethod]
        void Load_Entering_Rejects_PencilMarks()
        {
            SavedGame^ g = MakeSolverInProgressSave();
            g->pencilMarks[80] = 1 << 5; // cell 80 is empty, but Pencil is game-only
            AssertRejected(g, "Pencil marks in Solver mode");
        }

        [TestMethod]
        void Load_Entering_Rejects_GameCounters()
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
                AssertRejected(g, "Solver sessions have no hint, fix, give-up or restart counts");
            }
        }

        // -- Custom puzzle solved: clues where entered, solver-filled everywhere else --

        [TestMethod]
        void Load_Solved_Rejects_MissingSolution()
        {
            // "Finished" in Solver mode means solved; without a solution it never happened.
            SavedGame^ g = MakeSolverInProgressSave();
            g->gameFinished = true;
            AssertRejected(g, "must contain its solution");
        }

        [TestMethod]
        void Load_Solved_Rejects_EmptyCell()
        {
            SavedGame^ g = MakeSolvedSolverSave();
            g->values[1] = 0; // cell 1 is solver-filled in the fixture
            g->states[1] = 1;
            AssertRejected(g, "cannot occur in this session state");
        }

        [TestMethod]
        void Load_Solved_Rejects_UserFilledCell()
        {
            SavedGame^ g = MakeSolvedSolverSave();
            g->states[1] = 2;
            AssertRejected(g, "cannot occur in this session state");
        }

        [TestMethod]
        void Load_Solved_Rejects_CellNotMatchingSolution()
        {
            SavedGame^ g = MakeSolvedSolverSave();
            g->values[1] = (unsigned char)(g->solution[1] % 9 + 1);
            AssertRejected(g, "Locked cell does not hold its solution digit");
        }

        [TestMethod]
        void Load_Solved_Rejects_ClueMarkedAsSolverFilled()
        {
            SavedGame^ g = MakeSolvedSolverSave();
            g->states[0] = 6; // cell 0 is a clue in the fixture
            AssertRejected(g, "Clue cell does not match the puzzle's clues");
        }

        [TestMethod]
        void Load_Solved_Rejects_SolverCellMarkedAsClue()
        {
            SavedGame^ g = MakeSolvedSolverSave();
            g->states[1] = 0; // cell 1 was filled by the solver, not entered
            AssertRejected(g, "Clue cell does not match the puzzle's clues");
        }

        [TestMethod]
        void Load_Solved_Rejects_GameCounters()
        {
            SavedGame^ g = MakeSolvedSolverSave();
            g->numberOfHints = 1;
            AssertRejected(g, "Solver sessions have no hint, fix, give-up or restart counts");
        }

        [TestMethod]
        void RoundTrip_PreservesHighestDifficulty()
        {
            SavedGame^ g = MakeGameSave();
            g->difficulty = 4;
            Assert::AreEqual(4, (int)SaveAndReload(g)->difficulty);
        }

        [TestMethod]
        void Load_Rejects_DifficultyOutOfRange()
        {
            // Only 0..4 are valid; anything else must fail the load before it is applied.
            SavedGame^ g = MakeGameSave();
            g->difficulty = 5;
            AssertRejected(g, "Invalid difficulty value");
        }

        // ---- Undo/redo history ----

        [TestMethod]
        void RoundTrip_PreservesHistory()
        {
            SavedGame^ g = MakeGameSave();
            g->undoHistory = MakeHistory(
                Op(Cell(1, 0, CellKind::UserEmpty, 1 << 2)),
                Op(Cell(2, 0, CellKind::UserEmpty, 0), Cell(4, 7, CellKind::UserFilled, 0)));
            g->redoHistory = MakeHistory(
                Op(Cell(1, 2, CellKind::Hint, 0)));

            SavedGame^ back = SaveAndReload(g);

            Assert::AreEqual(2, back->undoHistory->Length);
            Assert::AreEqual(1, back->undoHistory[0]->Length);
            Assert::AreEqual((unsigned int)1, back->undoHistory[0][0]->cellIndex);
            Assert::AreEqual(1 << 2, back->undoHistory[0][0]->pencilMarks);
            Assert::AreEqual(2, back->undoHistory[1]->Length);
            Assert::AreEqual((unsigned int)4, back->undoHistory[1][1]->cellIndex);
            Assert::AreEqual(7, (int)back->undoHistory[1][1]->value);
            Assert::IsTrue(back->undoHistory[1][1]->kind == CellKind::UserFilled);

            Assert::AreEqual(1, back->redoHistory->Length);
            Assert::AreEqual(2, (int)back->redoHistory[0][0]->value);
            Assert::IsTrue(back->redoHistory[0][0]->kind == CellKind::Hint);
        }

        [TestMethod]
        void RoundTrip_WithoutHistory_LoadsEmptyHistory()
        {
            SavedGame^ back = SaveAndReload(MakeGameSave()); // history fields left null
            Assert::AreEqual(0, back->undoHistory->Length);
            Assert::AreEqual(0, back->redoHistory->Length);
        }

        [TestMethod]
        void Load_OldSaveWithoutHistoryKeys_LoadsWithEmptyHistory()
        {
            SavedGame^ g = MakeGameSave();
            g->undoHistory = MakeHistory(Op(Cell(1, 0, CellKind::UserEmpty, 0)));
            String^ path = Path::GetTempFileName();
            try
            {
                SaveGameStore::Save(path, g);

                System::Collections::Generic::List<String^>^ kept =
                    gcnew System::Collections::Generic::List<String^>();
                for each (String ^ line in File::ReadAllLines(path))
                    if (!line->StartsWith("undo=") && !line->StartsWith("redo=")) kept->Add(line);
                File::WriteAllLines(path, kept->ToArray());

                SavedGame^ back = SaveGameStore::Load(path, Cells);
                Assert::AreEqual(0, back->undoHistory->Length);
                Assert::AreEqual(0, back->redoHistory->Length);
            }
            finally
            {
                File::Delete(path);
            }
        }

        [TestMethod]
        void Load_MissingRedoKey_DropsUndoToo()
        {
            // Half a history is unreadable as a whole: the valid undo line is dropped with it.
            SavedGame^ g = MakeGameSave();
            g->undoHistory = MakeHistory(Op(Cell(1, 0, CellKind::UserEmpty, 0)));
            String^ path = Path::GetTempFileName();
            try
            {
                SaveGameStore::Save(path, g);

                System::Collections::Generic::List<String^>^ kept =
                    gcnew System::Collections::Generic::List<String^>();
                for each (String ^ line in File::ReadAllLines(path))
                    if (!line->StartsWith("redo=")) kept->Add(line);
                File::WriteAllLines(path, kept->ToArray());

                SavedGame^ back = SaveGameStore::Load(path, Cells);
                Assert::AreEqual(Cells, back->values->Length);
                Assert::AreEqual(0, back->undoHistory->Length);
                Assert::AreEqual(0, back->redoHistory->Length);
            }
            finally
            {
                File::Delete(path);
            }
        }

        [TestMethod]
        void Load_HandWrittenValidHistory_IsKept()
        {
            // Pins the wire format: a single-cell step, then a two-cell batch; redo holds a hint.
            SavedGame^ back = LoadWithHistoryText(MakeGameSave(), "1:0:1:4;2:0:1:0,4:7:2:0", "1:2:4:0");
            Assert::AreEqual(2, back->undoHistory->Length);
            Assert::AreEqual(2, back->undoHistory[1]->Length);
            Assert::AreEqual(1, back->redoHistory->Length);
        }

        [TestMethod]
        void Load_SolverInProgress_KeepsHistoryOfUserCells()
        {
            // Solver mode has no clues yet: user-entered cell 0 may appear in the history.
            SavedGame^ back = LoadWithHistoryText(MakeSolverInProgressSave(), "10:0:1:0;0:0:1:0", "");
            Assert::AreEqual(2, back->undoHistory->Length);
        }

        [TestMethod]
        void Load_MalformedHistory_IsDropped()
        {
            AssertGameHistoryDropped("garbage");
            AssertGameHistoryDropped("1:0:1");            // too few parts
            AssertGameHistoryDropped("1:0:1:0:0");        // too many parts
            AssertGameHistoryDropped("1:+0:1:0");         // sign
            AssertGameHistoryDropped(" 1:0:1:0");         // whitespace
            AssertGameHistoryDropped("1:0:1:0,");         // empty cell entry
            AssertGameHistoryDropped("1:0:1:0;;2:0:1:0"); // empty operation
            AssertGameHistoryDropped("1:0:1:-4");         // negative marks
            AssertGameHistoryDropped("1:10:2:0");         // value out of range
            AssertGameHistoryDropped("1:0:7:0");          // kind out of range
        }

        [TestMethod]
        void Load_HistoryIndexOffBoard_IsDropped()
        {
            AssertGameHistoryDropped("81:0:1:0");
            AssertGameHistoryDropped("4294967296:0:1:0"); // overflows a 32-bit index
        }

        [TestMethod]
        void Load_HistoryTouchingClue_IsDropped()
        {
            // Restoring it would turn the clue in cell 0 into an editable cell.
            AssertGameHistoryDropped("0:0:1:0");
        }

        [TestMethod]
        void Load_HistoryWithLockedKind_IsDropped()
        {
            AssertGameHistoryDropped("1:2:0:0"); // clue
            AssertGameHistoryDropped("1:2:3:0"); // correct
            AssertGameHistoryDropped("1:2:5:0"); // given up
            AssertGameHistoryDropped("1:2:6:0"); // solved
        }

        [TestMethod]
        void Load_HistoryValueKindMismatch_IsDropped()
        {
            AssertGameHistoryDropped("1:0:2:0"); // user-filled but empty
            AssertGameHistoryDropped("1:5:1:0"); // empty but has a value
            AssertGameHistoryDropped("1:0:4:0"); // hint but empty
        }

        [TestMethod]
        void Load_HistoryHintWithWrongDigit_IsDropped()
        {
            // Cell 1's solution is 2; a "hint" of 9 would lock a wrong digit into the board.
            AssertGameHistoryDropped("1:9:4:0");
        }

        [TestMethod]
        void Load_HistoryHintInSolverMode_IsDropped()
        {
            AssertHistoryDropped(MakeSolverInProgressSave(), "10:5:4:0", "");
        }

        [TestMethod]
        void Load_HistoryWithInvalidPencilMarks_IsDropped()
        {
            AssertGameHistoryDropped("1:0:1:1");    // bit 0 is not a digit
            AssertGameHistoryDropped("1:0:1:1024"); // bit 10 is not a digit
            AssertGameHistoryDropped("1:5:2:4");    // marks on a filled cell
        }

        [TestMethod]
        void Load_InvalidRedo_DropsValidUndoToo()
        {
            AssertHistoryDropped(MakeGameSave(), "1:0:1:0", "0:0:1:0");
        }

        [TestMethod]
        void Load_FinishedGameWithHistory_IsDropped()
        {
            // Cell 2 of the won save is a hint, which a history may touch, so the entry is
            // otherwise valid: only "finished games have no history" rejects it.
            AssertHistoryDropped(MakeWonGameSave(), "2:0:1:0", "");
        }
    };
}
