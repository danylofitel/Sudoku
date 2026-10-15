// Danylo Fitel 2026

#pragma once

#include "SavedGame.h"
#include "ClipboardPuzzleFormatter.h"
#include "GameMode.h"
#include "UnsupportedSaveVersionException.h"

using namespace System::IO;
using namespace System::Collections::Generic;

namespace Sudoku_3_0
{
    // Reads and writes SavedGame objects to/from disk. This class owns the entire on-disk
    // representation: callers work only with typed SavedGame data and never see the wire format.
    //
    // File format (UTF-8 text, one "key=value" per line):
    //   Sudoku3Save=<format version>
    //   difficulty, candidateAssist, numberOfRestarts, numberOfHints, numberOfFixes,
    //   numberOfGiveUps, gameMode, gameFinished   (all integers; gameFinished is 0/1)
    //   elapsedSeconds                       (total play time in whole seconds)
    //   clues, solution, value, state        (digit strings, one char per cell)
    //   pencilMarks                          (space-separated bitmasks, one per cell)
    //   undo, redo                           (non-essential history, ignored if unreadable;
    //                                         see EncodeHistory)
    // The order of lines is not significant; unknown keys are ignored. Older builds therefore
    // open files with history too - they just start without it.
    ref class SaveGameStore abstract sealed
    {
    public:
        // Writes a SavedGame to the given file path. Throws on I/O error.
        //
        // The save is written in full to "<filePath>.tmp" next to the target, flushed to disk,
        // and only then swapped into place. So the target always holds either its previous
        // contents or the complete new save - never a partial file - even if the write fails
        // midway (disk full, a locked file) or power is lost. On failure the temp file is removed
        // and the target is untouched. Its fixed name means a temp file left behind by a killed
        // process is simply overwritten by the next save. (Concurrent saves from two running
        // instances are not coordinated; the last swap wins.)
        static void Save(System::String^ filePath, SavedGame^ game)
        {
            System::String^ tempPath = filePath + ".tmp";
            try
            {
                WriteTo(tempPath, game);

                // Same folder, so the swap is a rename on one volume. .NET Framework's File::Move
                // cannot overwrite, hence File::Replace when the target already exists.
                if (File::Exists(filePath))
                    File::Replace(tempPath, filePath, nullptr);
                else
                    File::Move(tempPath, filePath);
            }
            catch (System::Exception^)
            {
                try { File::Delete(tempPath); }
                catch (System::Exception^) { /* best effort; the next save overwrites it */ }
                throw;
            }
        }

    private:
        // Writes the save to the given path and flushes it to disk before returning, so the
        // rename in Save can never make a file current whose contents did not reach the disk.
        static void WriteTo(System::String^ filePath, SavedGame^ game)
        {
            // Write as UTF-8 text (no BOM), one key=value per line.
            FileStream^ stream = nullptr;
            StreamWriter^ writer = nullptr;
            try
            {
                stream = gcnew FileStream(filePath, FileMode::Create, FileAccess::Write, FileShare::None);
                writer = gcnew StreamWriter(stream, gcnew System::Text::UTF8Encoding(false));
                writer->WriteLine("Sudoku3Save=" + FormatVersion.ToString());
                writer->WriteLine("difficulty=" + game->difficulty.ToString());
                writer->WriteLine("candidateAssist=" + (static_cast<unsigned int>(game->candidateAssist)).ToString());
                writer->WriteLine("numberOfRestarts=" + game->numberOfRestarts.ToString());
                writer->WriteLine("numberOfHints=" + game->numberOfHints.ToString());
                writer->WriteLine("numberOfFixes=" + game->numberOfFixes.ToString());
                writer->WriteLine("numberOfGiveUps=" + game->numberOfGiveUps.ToString());
                writer->WriteLine("gameMode=" + (static_cast<unsigned int>(game->mode)).ToString());
                writer->WriteLine("gameFinished=" + (game->gameFinished ? 1 : 0).ToString());
                writer->WriteLine("elapsedSeconds=" + game->elapsedSeconds.ToString());
                // The digit fields use the clipboard's one-digit-per-cell puzzle string, so the
                // encoder is shared (and a save's clues line pastes straight into Enter Puzzle).
                // Decoding stays separate (DecodeDigits): the clipboard is lenient with foreign
                // input, while a save file is validated strictly.
                writer->WriteLine("clues=" + ClipboardPuzzleFormatter::Encode(game->clues));
                writer->WriteLine("solution=" + ClipboardPuzzleFormatter::Encode(game->solution));
                writer->WriteLine("value=" + ClipboardPuzzleFormatter::Encode(game->values));
                writer->WriteLine("state=" + ClipboardPuzzleFormatter::Encode(game->states));
                writer->WriteLine("pencilMarks=" + EncodePencilMarks(game->pencilMarks));
                writer->WriteLine("undo=" + EncodeHistory(game->undoHistory));
                writer->WriteLine("redo=" + EncodeHistory(game->redoHistory));

                writer->Flush();     // writer buffer -> OS
                stream->Flush(true); // OS cache -> disk
            }
            finally
            {
                // Closing the writer also closes its stream; close the stream directly only if
                // the writer was never created.
                if (writer != nullptr) writer->Close();
                else if (stream != nullptr) stream->Close();
            }
        }

    public:
        // Reads and validates a save file, returning a typed SavedGame.
        // Throws UnsupportedSaveVersionException for a newer format, or System::Exception on
        // any other I/O or validation failure.
        static SavedGame^ Load(System::String^ filePath, unsigned int expectedNumberOfCells)
        {
            Dictionary<System::String^, System::String^>^ fields =
                gcnew Dictionary<System::String^, System::String^>();

            StreamReader^ reader = nullptr;
            try
            {
                reader = gcnew StreamReader(filePath);
                System::String^ line;
                while ((line = reader->ReadLine()) != nullptr)
                {
                    int eq = line->IndexOf(L'=');
                    if (eq < 0) continue;
                    fields[line->Substring(0, eq)] = line->Substring(eq + 1);
                }
            }
            finally
            {
                if (reader != nullptr) reader->Close();
            }

            if (!fields->ContainsKey("Sudoku3Save"))
                throw gcnew System::Exception("Not a recognized Sudoku save file.");

            // Check the format version before parsing anything else, so a file written by a newer
            // build fails with a clear "unsupported version" reason instead of a confusing error
            // deeper in parsing. Files at or below FormatVersion are considered loadable; when a
            // future breaking change bumps FormatVersion, add per-version migration handling here.
            unsigned int fileVersion = RequireUInt(fields, "Sudoku3Save");
            if (fileVersion > FormatVersion)
                throw gcnew UnsupportedSaveVersionException(fileVersion, FormatVersion);

            SavedGame^ game = gcnew SavedGame();
            // Validate everything here, before the caller applies anything: a value the form
            // cannot take (e.g. a combo index past VeryHard) must fail the load up front, not
            // halfway through applying it.
            game->difficulty = RequireUInt(fields, "difficulty");
            if (game->difficulty > MaxDifficulty)
                throw gcnew System::Exception("Invalid difficulty value " + game->difficulty.ToString());

            unsigned int candidateAssist = RequireUInt(fields, "candidateAssist");
            if (candidateAssist > static_cast<unsigned int>(CandidateDisplay::AllCells))
                throw gcnew System::Exception("Invalid candidateAssist value " + candidateAssist.ToString());
            game->candidateAssist = static_cast<CandidateDisplay>(candidateAssist);

            game->numberOfRestarts = RequireUInt(fields, "numberOfRestarts");
            game->numberOfHints = RequireUInt(fields, "numberOfHints");
            game->numberOfFixes = RequireUInt(fields, "numberOfFixes");
            game->numberOfGiveUps = RequireUInt(fields, "numberOfGiveUps");
            game->gameFinished = RequireUInt(fields, "gameFinished") != 0;
            game->elapsedSeconds = RequireUInt(fields, "elapsedSeconds");

            unsigned int gameMode = RequireUInt(fields, "gameMode");
            if (gameMode != static_cast<unsigned int>(GameMode::Game) &&
                gameMode != static_cast<unsigned int>(GameMode::Solver))
            {
                throw gcnew System::Exception("Invalid gameMode value " + gameMode.ToString());
            }
            game->mode = static_cast<GameMode>(gameMode);

            // Board state is always present and full-length.
            game->values = DecodeDigits(RequireStr(fields, "value"), expectedNumberOfCells, L'0', L'9', "value");
            game->states = DecodeDigits(RequireStr(fields, "state"), expectedNumberOfCells, L'0', L'6', "state");

            // The puzzle snapshot (clues + solution) is optional: a Solver session that has not
            // been solved yet has no known solution, so both fields are empty. When present, both
            // must be full-length and consistent. Game mode always requires a solution.
            System::String^ cluesStr = RequireStr(fields, "clues");
            System::String^ solutionStr = RequireStr(fields, "solution");
            bool hasPuzzle = cluesStr->Length > 0 || solutionStr->Length > 0;

            if (game->mode == GameMode::Game && !hasPuzzle)
                throw gcnew System::Exception("A saved game must contain a puzzle solution.");

            // In Solver mode the snapshot exists exactly when the puzzle is solved: Solve both
            // captures it and finishes the session, and nothing else does either.
            if (game->mode == GameMode::Solver && hasPuzzle != game->gameFinished)
                throw gcnew System::Exception(game->gameFinished
                    ? "A solved custom puzzle must contain its solution."
                    : "A custom puzzle still being entered cannot have a solution.");

            if (hasPuzzle)
            {
                game->clues = DecodeDigits(cluesStr, expectedNumberOfCells, L'0', L'9', "clue");
                game->solution = DecodeDigits(solutionStr, expectedNumberOfCells, L'1', L'9', "solution");
                for (unsigned int i = 0; i < expectedNumberOfCells; ++i)
                    if (game->clues[i] != 0 && game->clues[i] != game->solution[i])
                        throw gcnew System::Exception("Clue/solution mismatch at index " + i.ToString());
            }
            else
            {
                game->clues = gcnew array<unsigned char>(0);
                game->solution = gcnew array<unsigned char>(0);
            }

            game->pencilMarks = DecodePencilMarks(RequireStr(fields, "pencilMarks"), expectedNumberOfCells);

            ValidateBoard(game);

            // The undo/redo history is always written, but it is non-essential: the game is fully
            // playable without it. So unlike every field above, a history that cannot be used -
            // missing (e.g. a file from before history was saved), malformed, or inconsistent
            // with the board - never fails the load. Both histories are dropped together (they
            // only make sense as a pair) and the game loads without them.
            try
            {
                game->undoHistory = DecodeHistory(RequireStr(fields, "undo"), expectedNumberOfCells);
                game->redoHistory = DecodeHistory(RequireStr(fields, "redo"), expectedNumberOfCells);
                bool hasHistory = game->undoHistory->Length > 0 || game->redoHistory->Length > 0;
                if (hasHistory && game->gameFinished)
                    throw gcnew System::Exception("A finished game has no undo history.");
                ValidateHistory(game->undoHistory, game);
                ValidateHistory(game->redoHistory, game);
            }
            catch (System::Exception^)
            {
                game->undoHistory = gcnew array<array<UndoManager::CellState^>^>(0);
                game->redoHistory = gcnew array<array<UndoManager::CellState^>^>(0);
            }

            return game;
        }

    private:
        // Bumped whenever the on-disk format changes in a breaking way.
        static const unsigned int FormatVersion = 1;

        // Difficulty indices run 0 (VeryEasy) .. 4 (VeryHard), as in Difficulty and Settings.
        static const unsigned int MaxDifficulty = 4;

        // Decodes a string of ASCII digits into a byte array, validating both its length and
        // that every character lies within [minDigit, maxDigit].
        static array<unsigned char>^ DecodeDigits(
            System::String^ text, unsigned int expectedLength,
            wchar_t minDigit, wchar_t maxDigit, System::String^ fieldName)
        {
            if ((unsigned int)text->Length != expectedLength)
                throw gcnew System::Exception("Invalid length for field '" + fieldName + "'");

            array<unsigned char>^ result = gcnew array<unsigned char>(text->Length);
            for (int i = 0; i < text->Length; ++i)
            {
                wchar_t c = text[i];
                if (c < minDigit || c > maxDigit)
                    throw gcnew System::Exception("Invalid " + fieldName + " value '" + c.ToString() + "' at index " + i.ToString());
                result[i] = (unsigned char)(c - L'0');
            }
            return result;
        }

        // Encodes pencil-mark bitmasks as space-separated integers.
        static System::String^ EncodePencilMarks(array<int>^ marks)
        {
            System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder();
            for (int i = 0; i < marks->Length; ++i)
            {
                if (i > 0) sb->Append(L' ');
                sb->Append(marks[i]);
            }
            return sb->ToString();
        }

        // Decodes space-separated pencil-mark bitmasks into an array. Strict, like the digit
        // fields: there must be exactly expectedLength entries, each a valid bitmask (only bits
        // 1-9 may be set, matching what the game writes).
        static array<int>^ DecodePencilMarks(System::String^ text, unsigned int expectedLength)
        {
            // A full board always writes expectedLength space-separated tokens (all-zero cells
            // included), so an empty value is only well-formed when no cells are expected.
            array<System::String^>^ parts = text->Length == 0
                ? gcnew array<System::String^>(0)
                : text->Split(' ');
            if ((unsigned int)parts->Length != expectedLength)
                throw gcnew System::Exception("Invalid length for field 'pencilMarks'");

            const int validBits = 0x3FE; // bits 1..9
            array<int>^ marks = gcnew array<int>(expectedLength);
            for (unsigned int i = 0; i < expectedLength; ++i)
            {
                int m = 0;
                if (!System::Int32::TryParse(parts[i], m) || m < 0 || (m & ~validBits) != 0)
                    throw gcnew System::Exception("Invalid pencilMarks value '" + parts[i] + "' at index " + i.ToString());
                marks[i] = m;
            }
            return marks;
        }

        // Checks that the board and counters form a state the app can actually reach, so a loaded
        // game is never in a situation play could not produce. The reachable session states:
        //
        //   Session state       Cell kinds allowed                  Also required
        //   ------------------  ----------------------------------  -------------------------------
        //   Game, in progress   Clue, UserEmpty, UserFilled, Hint   board not already solved
        //   Game, won           Clue, Correct, Hint                 -
        //   Game, given up      Clue, GivenUp, Hint                 numberOfGiveUps >= 1
        //   Solver, entering    UserEmpty, UserFilled               no solution; pencil marks and
        //                                                           all counters are zero
        //   Solver, solved      Clue, Solved                        solution present; counters zero
        //
        // and for every cell, in every state:
        //   - empty (value 0) exactly when its kind is UserEmpty
        //   - a Clue exactly where the puzzle has a clue, holding that clue
        //   - a Correct, Hint, GivenUp, or Solved cell holds its solution digit
        //   - pencil marks only on an empty cell
        // plus: numberOfHints is at least the number of Hint cells (Undo can revert a hint
        // reveal, but never uncounts it), so a file cannot claim hint cells as a clean win.
        // (Solver mode has no puzzle, and therefore no clues, until it is solved; the game-only
        // kinds Correct, Hint and GivenUp never appear in it.)
        static void ValidateBoard(SavedGame^ game)
        {
            bool inGame = game->mode == GameMode::Game;
            bool hasPuzzle = game->solution->Length > 0;
            int count = game->values->Length;

            // Kinds present on the board, to check the per-state rules after the cell loop.
            unsigned int hintCells = 0;
            bool anyCorrect = false, anyGivenUp = false, anyEmpty = false;
            bool allEditableSolved = true; // every UserFilled cell holds its solution digit

            for (int i = 0; i < count; ++i)
            {
                unsigned char value = game->values[i];
                CellKind kind = static_cast<CellKind>(game->states[i]);
                System::String^ where = " at index " + i.ToString();

                if ((value == 0) != (kind == CellKind::UserEmpty))
                    throw gcnew System::Exception("Mismatched cell value and state" + where);

                if (game->pencilMarks[i] != 0 && kind != CellKind::UserEmpty)
                    throw gcnew System::Exception("Pencil marks on a filled cell" + where);
                if (game->pencilMarks[i] != 0 && !inGame)
                    throw gcnew System::Exception("Pencil marks in Solver mode" + where); // Pencil is game-only

                // Cell kinds allowed in this session state
                bool allowed;
                if (inGame && !game->gameFinished)
                    allowed = kind == CellKind::Clue || kind == CellKind::UserEmpty
                        || kind == CellKind::UserFilled || kind == CellKind::Hint;
                else if (inGame)
                    allowed = kind == CellKind::Clue || kind == CellKind::Correct
                        || kind == CellKind::Hint || kind == CellKind::GivenUp;
                else if (!game->gameFinished)
                    allowed = kind == CellKind::UserEmpty || kind == CellKind::UserFilled;
                else
                    allowed = kind == CellKind::Clue || kind == CellKind::Solved;
                if (!allowed)
                    throw gcnew System::Exception("Cell state " + game->states[i].ToString()
                        + " cannot occur in this session state" + where);

                // Clues: exactly where the puzzle has one, holding it
                if (hasPuzzle && (kind == CellKind::Clue) != (game->clues[i] != 0))
                    throw gcnew System::Exception("Clue cell does not match the puzzle's clues" + where);

                // Locked reveals hold the solution (clues are covered by clue == solution)
                bool revealsSolution = kind == CellKind::Correct || kind == CellKind::Hint
                    || kind == CellKind::GivenUp || kind == CellKind::Solved;
                if ((kind == CellKind::Clue || revealsSolution) && value != game->solution[i])
                    throw gcnew System::Exception("Locked cell does not hold its solution digit" + where);

                if (kind == CellKind::Hint) ++hintCells;
                if (kind == CellKind::Correct) anyCorrect = true;
                if (kind == CellKind::GivenUp) anyGivenUp = true;
                if (kind == CellKind::UserEmpty) anyEmpty = true;
                if (kind == CellKind::UserFilled && hasPuzzle && value != game->solution[i])
                    allEditableSolved = false;
            }

            if (inGame)
            {
                if (game->numberOfHints < hintCells)
                    throw gcnew System::Exception("numberOfHints is below the number of hint cells.");

                // A game whose board is complete and correct was won the moment it got there
                if (!game->gameFinished && !anyEmpty && allEditableSolved)
                    throw gcnew System::Exception("An unfinished game cannot already be solved.");

                // A finished game ended exactly one way: won (Correct) or given up (GivenUp)
                if (anyCorrect && anyGivenUp)
                    throw gcnew System::Exception("A game cannot be both won and given up.");
                if (anyGivenUp && game->numberOfGiveUps == 0)
                    throw gcnew System::Exception("A given-up game must count the give-up.");
            }
            else
            {
                // Hints, Fix, Give Up and Restart do not exist in Solver mode
                if (game->numberOfHints != 0 || game->numberOfFixes != 0
                    || game->numberOfGiveUps != 0 || game->numberOfRestarts != 0)
                    throw gcnew System::Exception("Solver sessions have no hint, fix, give-up or restart counts.");
            }
        }

        // Encodes a history as operations separated by ';', each a ','-separated list of cell
        // snapshots "index:value:kind:pencilMarks" (kind as its state code). Operations are
        // oldest first, snapshots in recording order. No history encodes as an empty string.
        // Example - a single edit, then a two-cell Fix:  "12:0:1:0;3:5:2:0,40:7:2:0"
        static System::String^ EncodeHistory(array<array<UndoManager::CellState^>^>^ history)
        {
            System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder();
            if (history == nullptr) return sb->ToString();

            for (int op = 0; op < history->Length; ++op)
            {
                if (op > 0) sb->Append(L';');
                for (int i = 0; i < history[op]->Length; ++i)
                {
                    UndoManager::CellState^ cell = history[op][i];
                    if (i > 0) sb->Append(L',');
                    sb->Append(cell->cellIndex)->Append(L':')
                        ->Append((unsigned int)cell->value)->Append(L':')
                        ->Append((unsigned int)static_cast<unsigned char>(cell->kind))->Append(L':')
                        ->Append(cell->pencilMarks);
                }
            }
            return sb->ToString();
        }

        // Parses the EncodeHistory format, checking only its shape and that every cell index is
        // on the board; ValidateHistory checks the snapshots against the game.
        static array<array<UndoManager::CellState^>^>^ DecodeHistory(System::String^ text, unsigned int numberOfCells)
        {
            if (text->Length == 0)
                return gcnew array<array<UndoManager::CellState^>^>(0);

            array<System::String^>^ operations = text->Split(L';');
            array<array<UndoManager::CellState^>^>^ history = gcnew array<array<UndoManager::CellState^>^>(operations->Length);
            for (int op = 0; op < operations->Length; ++op)
            {
                array<System::String^>^ cells = operations[op]->Split(L',');
                history[op] = gcnew array<UndoManager::CellState^>(cells->Length);
                for (int i = 0; i < cells->Length; ++i)
                {
                    array<System::String^>^ parts = cells[i]->Split(L':');
                    if (parts->Length != 4)
                        throw gcnew System::Exception("Malformed history entry '" + cells[i] + "'");

                    unsigned int index = ParseHistoryNumber(parts[0]);
                    unsigned int value = ParseHistoryNumber(parts[1]);
                    unsigned int kind = ParseHistoryNumber(parts[2]);
                    unsigned int marks = ParseHistoryNumber(parts[3]);
                    if (index >= numberOfCells || value > 9 || kind > 6 || marks > 0x3FE)
                        throw gcnew System::Exception("Out-of-range history entry '" + cells[i] + "'");

                    history[op][i] = gcnew UndoManager::CellState(
                        index, (unsigned char)value, static_cast<CellKind>(kind), (int)marks);
                }
            }
            return history;
        }

        // Checks that every snapshot is one the game could really have recorded, so restoring it
        // can never produce an impossible board - e.g. turn a clue editable or lock in a wrong
        // digit as a hint. A history only ever touches playable cells (never a clue), and holds
        // them as empty, user-filled, or a correct hint.
        static void ValidateHistory(array<array<UndoManager::CellState^>^>^ history, SavedGame^ game)
        {
            const int validBits = 0x3FE; // bits 1..9
            const unsigned char emptyState = 1, userFilledState = 2, hintState = 4;

            for each (array<UndoManager::CellState^>^ operation in history)
            {
                if (operation->Length == 0)
                    throw gcnew System::Exception("Empty history operation.");

                for each (UndoManager::CellState^ cell in operation)
                {
                    unsigned char boardState = game->states[cell->cellIndex];
                    if (boardState != emptyState && boardState != userFilledState && boardState != hintState)
                        throw gcnew System::Exception("History touches a locked cell at index " + cell->cellIndex.ToString());

                    unsigned char kind = static_cast<unsigned char>(cell->kind);
                    if (kind != emptyState && kind != userFilledState && kind != hintState)
                        throw gcnew System::Exception("Invalid history kind at index " + cell->cellIndex.ToString());

                    if ((cell->value == 0) != (kind == emptyState))
                        throw gcnew System::Exception("Mismatched history value and kind at index " + cell->cellIndex.ToString());

                    if (kind == hintState && (game->mode != GameMode::Game || game->solution->Length == 0
                        || cell->value != game->solution[cell->cellIndex]))
                        throw gcnew System::Exception("Invalid history hint at index " + cell->cellIndex.ToString());

                    if ((cell->pencilMarks & ~validBits) != 0 || (cell->value != 0 && cell->pencilMarks != 0))
                        throw gcnew System::Exception("Invalid history pencil marks at index " + cell->cellIndex.ToString());
                }
            }
        }

        // Plain decimal digits only (no sign, spaces, or separators).
        static unsigned int ParseHistoryNumber(System::String^ text)
        {
            unsigned int result = 0;
            if (!System::UInt32::TryParse(text, System::Globalization::NumberStyles::None,
                System::Globalization::CultureInfo::InvariantCulture, result))
                throw gcnew System::Exception("Invalid number in history: '" + text + "'");
            return result;
        }

        static unsigned int RequireUInt(Dictionary<System::String^, System::String^>^ fields, System::String^ key)
        {
            System::String^ raw = RequireStr(fields, key);
            unsigned int result = 0;
            if (!System::UInt32::TryParse(raw, result))
                throw gcnew System::Exception("Invalid integer for field '" + key + "': " + raw);
            return result;
        }

        static System::String^ RequireStr(Dictionary<System::String^, System::String^>^ fields, System::String^ key)
        {
            if (!fields->ContainsKey(key))
                throw gcnew System::Exception("Missing field: " + key);
            return fields[key];
        }
    };
}
