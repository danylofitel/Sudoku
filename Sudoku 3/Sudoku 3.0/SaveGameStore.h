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
    //   difficulty, numberOfHints, numberOfFixes, numberOfGiveUps,
    //   gameMode, gameFinished               (all integers; booleans as 0/1)
    //   elapsedSeconds                       (total play time in whole seconds)
    //   clues, solution, value, state        (digit strings, one char per cell)
    //   pencilMarks                          (space-separated bitmasks, one per cell)
    // The order of lines is not significant; unknown keys are ignored.
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

            game->pencilMarks = DecodePencilMarks(
                fields->ContainsKey("pencilMarks") ? fields["pencilMarks"] : gcnew System::String(L""),
                expectedNumberOfCells);

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

        // Decodes space-separated pencil-mark bitmasks into an array of the expected length.
        // Lenient: missing or unparsable entries default to 0 (no marks).
        static array<int>^ DecodePencilMarks(System::String^ text, unsigned int expectedLength)
        {
            array<int>^ marks = gcnew array<int>(expectedLength);
            if (text != nullptr && text->Length > 0)
            {
                array<System::String^>^ parts = text->Split(' ');
                for (unsigned int i = 0; i < expectedLength && i < (unsigned int)parts->Length; ++i)
                {
                    int m = 0;
                    if (System::Int32::TryParse(parts[i], m))
                        marks[i] = m;
                }
            }
            return marks;
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
