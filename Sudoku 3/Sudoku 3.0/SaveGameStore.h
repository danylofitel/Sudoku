// Danylo Fitel 2026

#pragma once

#include "SavedGame.h"
#include "GameValidator.h"
#include "ClipboardPuzzleFormatter.h"
#include "GameMode.h"
#include "UnsupportedSaveVersionException.h"

using namespace System::IO;
using namespace System::Collections::Generic;

namespace Sudoku_3_0
{
    // Reads and writes SavedGame objects to/from disk. This class owns the entire on-disk
    // representation: callers work only with typed SavedGame data and never see the wire format.
    // Which games are valid is GameValidator's job; Load runs it on everything it reads.
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

            // Parse: everything below only reads the text format (required keys, numbers that
            // parse, digit strings made of digits). Every rule about the values lives in
            // GameValidator, which runs before the caller applies anything - so a value the form
            // cannot take fails the load up front, not halfway through applying it.
            SavedGame^ game = gcnew SavedGame();
            game->difficulty = RequireUInt(fields, "difficulty");
            game->candidateAssist = static_cast<CandidateDisplay>(RequireUInt(fields, "candidateAssist"));
            game->numberOfRestarts = RequireUInt(fields, "numberOfRestarts");
            game->numberOfHints = RequireUInt(fields, "numberOfHints");
            game->numberOfFixes = RequireUInt(fields, "numberOfFixes");
            game->numberOfGiveUps = RequireUInt(fields, "numberOfGiveUps");
            game->gameFinished = RequireUInt(fields, "gameFinished") != 0;
            game->elapsedSeconds = RequireUInt(fields, "elapsedSeconds");
            game->mode = static_cast<GameMode>(RequireUInt(fields, "gameMode"));
            game->values = DecodeDigits(RequireStr(fields, "value"), "value");
            game->states = DecodeDigits(RequireStr(fields, "state"), "state");
            game->clues = DecodeDigits(RequireStr(fields, "clues"), "clue");
            game->solution = DecodeDigits(RequireStr(fields, "solution"), "solution");
            game->pencilMarks = DecodePencilMarks(RequireStr(fields, "pencilMarks"));

            GameValidator::Validate(game, expectedNumberOfCells);

            // The undo/redo history is always written, but it is non-essential: the game is fully
            // playable without it. So unlike every field above, a history that cannot be used -
            // missing (e.g. a file from before history was saved), malformed, or inconsistent
            // with the board - never fails the load. Both histories are dropped together (they
            // only make sense as a pair) and the game loads without them.
            try
            {
                game->undoHistory = DecodeHistory(RequireStr(fields, "undo"));
                game->redoHistory = DecodeHistory(RequireStr(fields, "redo"));
                GameValidator::ValidateHistory(game);
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

        // Decodes a string of ASCII digits into a byte array. Format only: every character must
        // be a digit; the length and the allowed range are GameValidator's job.
        static array<unsigned char>^ DecodeDigits(System::String^ text, System::String^ fieldName)
        {
            array<unsigned char>^ result = gcnew array<unsigned char>(text->Length);
            for (int i = 0; i < text->Length; ++i)
            {
                wchar_t c = text[i];
                if (c < L'0' || c > L'9')
                    throw gcnew System::Exception("Invalid character '" + c.ToString() + "' in field '" + fieldName + "' at index " + i.ToString());
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

        // Decodes space-separated pencil-mark bitmasks into an array. Format only: every entry
        // must be an integer; the count and the allowed bits are GameValidator's job.
        static array<int>^ DecodePencilMarks(System::String^ text)
        {
            array<System::String^>^ parts = text->Length == 0
                ? gcnew array<System::String^>(0)
                : text->Split(' ');

            array<int>^ marks = gcnew array<int>(parts->Length);
            for (int i = 0; i < parts->Length; ++i)
            {
                if (!System::Int32::TryParse(parts[i], marks[i]))
                    throw gcnew System::Exception("Invalid pencilMarks value '" + parts[i] + "' at index " + i.ToString());
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

        // Parses the EncodeHistory format, checking only its shape (four numbers per entry, each
        // fitting its field); GameValidator::ValidateHistory checks the snapshots against the game.
        static array<array<UndoManager::CellState^>^>^ DecodeHistory(System::String^ text)
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

                    // Format only: each number must fit its field without being cut short (a
                    // value of 300 must not silently become 44). Whether it is a valid cell,
                    // digit, kind, or set of marks is GameValidator's job.
                    if (value > System::Byte::MaxValue || kind > System::Byte::MaxValue
                        || marks > (unsigned int)System::Int32::MaxValue)
                        throw gcnew System::Exception("Out-of-range history entry '" + cells[i] + "'");

                    history[op][i] = gcnew UndoManager::CellState(
                        index, (unsigned char)value, static_cast<CellKind>(kind), (int)marks);
                }
            }
            return history;
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
