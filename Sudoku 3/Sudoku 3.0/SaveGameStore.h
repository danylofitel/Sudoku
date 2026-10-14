// Danylo Fitel 2026

#pragma once

#include "SavedGame.h"
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
        static void Save(System::String^ filePath, SavedGame^ game)
        {
            // Write as UTF-8 text (no BOM), one key=value per line.
            StreamWriter^ writer = nullptr;
            try
            {
                writer = gcnew StreamWriter(filePath, false, gcnew System::Text::UTF8Encoding(false));
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
                writer->WriteLine("clues=" + EncodeDigits(game->clues));
                writer->WriteLine("solution=" + EncodeDigits(game->solution));
                writer->WriteLine("value=" + EncodeDigits(game->values));
                writer->WriteLine("state=" + EncodeDigits(game->states));
                writer->WriteLine("pencilMarks=" + EncodePencilMarks(game->pencilMarks));
                writer->WriteLine("undo=" + EncodeHistory(game->undoHistory));
                writer->WriteLine("redo=" + EncodeHistory(game->redoHistory));
            }
            finally
            {
                if (writer != nullptr) writer->Close();
            }
        }

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
            game->difficulty = RequireUInt(fields, "difficulty");

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

            // Per-cell cross-field validation
            for (unsigned int i = 0; i < expectedNumberOfCells; ++i)
            {
                unsigned char v = game->values[i];
                unsigned char s = game->states[i];

                // state 1 means an empty cell, so value must be 0 and vice versa
                if ((v == 0) != (s == 1))
                    throw gcnew System::Exception("Mismatched cell value and state at index " + i.ToString());

                if (game->mode == GameMode::Game && s == 6)
                    throw gcnew System::Exception("Invalid state 6 in game mode at index " + i.ToString());
                if (game->mode == GameMode::Solver && (s == 3 || s == 4 || s == 5))
                    throw gcnew System::Exception("Invalid state " + s.ToString() + " in solver mode at index " + i.ToString());
            }

            game->pencilMarks = DecodePencilMarks(RequireStr(fields, "pencilMarks"), expectedNumberOfCells);

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

        // Encodes a 0-9 digit array as a string of ASCII digits.
        static System::String^ EncodeDigits(array<unsigned char>^ digits)
        {
            System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder(digits->Length);
            for (int i = 0; i < digits->Length; ++i)
                sb->Append((wchar_t)(L'0' + digits[i]));
            return sb->ToString();
        }

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
