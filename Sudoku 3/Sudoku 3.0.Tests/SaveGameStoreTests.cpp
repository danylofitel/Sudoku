// Danylo Fitel 2026
// Unit tests for SaveGameStore: the file format (round-trips, parsing errors, versions), safe
// writes, and loading the undo/redo history. The rules for a valid game are GameValidator's and
// are tested in GameValidatorTests; the tests here only show that Load applies them.
// SaveGameStore is pure logic over a file path, so tests round-trip through temp files.

#include "SaveGameStore.h"
#include "SavedGameFixtures.h"

using namespace System;
using namespace System::IO;
using namespace Sudoku_3_0;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace Sudoku_3_0_Tests
{
    using namespace SavedGameFixtures;

    [TestClass]
    public ref class SaveGameStoreTests
    {
    private:
        // Asserts that loading this hand-written file fails, and fails for the stated reason (a
        // fragment of the rejection message) - so each test proves its own rule, not any error.
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
        void Load_Rejects_MissingPencilMarks()
        {
            // pencilMarks is a required field: a save missing it is rejected, not silently zeroed.
            AssertRejectedWithLine(MakeGameSave(), "pencilMarks", nullptr, "Missing field: pencilMarks");
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

        // ---- Load runs GameValidator (the rules themselves are tested in GameValidatorTests) ----

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

        // The message Load throws after saving g, or nullptr if it loads.
        static String^ LoadMessage(SavedGame^ g)
        {
            try
            {
                SaveAndReload(g);
                return nullptr;
            }
            catch (Exception^ ex)
            {
                return ex->Message;
            }
        }

        // A spread of broken games, one per kind of rule.
        static array<SavedGame^>^ InvalidGames()
        {
            System::Collections::Generic::List<SavedGame^>^ games = gcnew System::Collections::Generic::List<SavedGame^>();
            SavedGame^ g;

            g = MakeGameSave(); g->difficulty = 5; games->Add(g);                         // range
            g = MakeGameSave(); g->states[0] = 1; games->Add(g);                          // value/state
            g = MakeGameSave(); g->solution[0] = 0; games->Add(g);                        // solution digit
            g = MakeGameSave(); g->pencilMarks[0] = 1; games->Add(g);                     // pencil bits
            g = MakeGameSave(); g->clues = gcnew array<unsigned char>(0);
                                g->solution = gcnew array<unsigned char>(0); games->Add(g); // no puzzle
            g = MakeSolverInProgressSave(); g->gameFinished = true; games->Add(g);        // snapshot
            g = MakeWonGameSave(); g->states[1] = 2; games->Add(g);                       // session state
            g = MakeGivenUpGameSave(); g->numberOfGiveUps = 0; games->Add(g);             // counters
            return games->ToArray();
        }

    public:
        [TestMethod]
        void Load_RejectsExactlyWhatTheValidatorRejects()
        {
            // The crash save relies on this: a game the validator accepts always loads again, and
            // one it rejects would have been rejected on the next launch - for the same reason.
            for each (SavedGame ^ g in InvalidGames())
            {
                String^ validate = ValidateMessage(g);
                Assert::IsNotNull(validate, "Validate accepted an invalid game");
                Assert::AreEqual(validate, LoadMessage(g));
            }
        }

        [TestMethod]
        void Load_Rejects_NonDigitCharacter()
        {
            // A format error, caught while parsing, before Validate sees the game
            AssertRejectedWithLine(MakeGameSave(), "value", "value=" + gcnew String(L'x', Cells), "Invalid character 'x' in field 'value'");
        }

        [TestMethod]
        void Load_Rejects_WrongLengthBoard()
        {
            AssertRejectedWithLine(MakeGameSave(), "state", "state=0", "Invalid length for field 'state'");
        }

        // ---- Board invariants: every reachable session state survives a save and load ----

        [TestMethod]
        void Load_AcceptsEveryReachableSessionState()
        {
            SaveAndReload(MakeGameSave());            // game in progress
            SaveAndReload(MakeWonGameSave());         // game won
            SaveAndReload(MakeGivenUpGameSave());     // game given up
            SaveAndReload(MakeSolverInProgressSave()); // entering a custom puzzle
            SaveAndReload(MakeSolvedSolverSave());    // custom puzzle solved
        }

        [TestMethod]
        void RoundTrip_PreservesHighestDifficulty()
        {
            SavedGame^ g = MakeGameSave();
            g->difficulty = 4;
            Assert::AreEqual(4, (int)SaveAndReload(g)->difficulty);
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
            AssertGameHistoryDropped("1:300:2:0");        // value too big for its field (would wrap to 44)
            AssertGameHistoryDropped("1:0:256:0");        // kind too big for its field
            AssertGameHistoryDropped("1:0:1:4294967295"); // marks too big for their field
        }

        [TestMethod]
        void Load_HistoryIndexOffBoard_IsDropped()
        {
            AssertGameHistoryDropped("81:0:1:0");         // parses, then GameValidator rejects it
            AssertGameHistoryDropped("4294967296:0:1:0"); // overflows a 32-bit index while parsing
        }

        [TestMethod]
        void Load_HistoryBreakingARule_IsDropped()
        {
            // One example of GameValidator::ValidateHistory at work in Load (the rules themselves
            // are tested in GameValidatorTests): touching the clue in cell 0 drops the history.
            AssertGameHistoryDropped("0:0:1:0");
        }

        [TestMethod]
        void Load_HistoryMarksOutOfRange_IsDropped()
        {
            AssertGameHistoryDropped("1:0:1:1024"); // bit 10 is not a digit (GameValidator)
        }

        [TestMethod]
        void Load_InvalidRedo_DropsValidUndoToo()
        {
            AssertHistoryDropped(MakeGameSave(), "1:0:1:0", "0:0:1:0");
        }

    };
}
