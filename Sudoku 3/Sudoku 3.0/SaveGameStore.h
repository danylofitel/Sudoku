// Danylo Fitel 2026

#pragma once

#include "SavedGame.h"
#include "GameMode.h"
#include "UnsupportedSaveVersionException.h"

using namespace System::IO;
using namespace System::Collections::Generic;

namespace Sudoku_3_0
{
    // Handles reading and writing SavedGame objects to/from disk.
    // Contains no UI logic — callers are responsible for applying loaded state.
    //
    // File format (UTF-8 text, one "key=value" per line):
    //   Sudoku3Save=<format version>
    //   sizeFactor, difficulty, numberOfHints, numberOfFixes, hasGivenUp,
    //   hasUsedFix, gameMode, gameFinished  (all integers; booleans as 0/1)
    //   elapsedSeconds                       (total play time in whole seconds)
    //   clues, solution, value, state       (digit strings, one char per cell)
    //   pencilMarks                          (space-separated bitmasks, one per cell)
    // The order of lines is not significant; unknown keys are ignored.
    ref class SaveGameStore abstract sealed
    {
    public:
        // Builds a SavedGame from the current board state and writes it to the given file path.
        // Throws on I/O error.
        //
        // clues:        cell clue values 1-9 (0 = user-fillable cell)
        // solution:     full solution values 1-9 for every cell
        // values:       cell values 0-9, one per cell (0 = empty)
        // states:       cell state codes, one per cell:
        //                 0 = engine clue (immutable), 1 = empty user cell,
        //                 2 = user-filled, 3 = confirmed correct, 4 = hint,
        //                 5 = given-up reveal, 6 = solver-filled
        // pencilMarks:  bitmask per cell (bits 1-9), space-separated
        static void Save(
            System::String^ filePath,
            unsigned int sizeFactor,
            unsigned int difficulty,
            unsigned int numberOfHints,
            unsigned int numberOfFixes,
            bool hasGivenUp,
            bool hasUsedFix,
            GameMode mode,
            bool gameFinished,
            unsigned int elapsedSeconds,
            array<unsigned char>^ clues,
            array<unsigned char>^ solution,
            array<unsigned char>^ values,
            array<unsigned char>^ states,
            array<int>^ pencilMarks)
        {
            SavedGame^ save = gcnew SavedGame();
            save->sizeFactor = sizeFactor;
            save->difficulty = difficulty;
            save->numberOfHints = numberOfHints;
            save->numberOfFixes = numberOfFixes;
            save->hasGivenUp = hasGivenUp;
            save->hasUsedFix = hasUsedFix;
            save->gameMode = static_cast<unsigned int>(mode);
            save->gameFinished = gameFinished;
            save->elapsedSeconds = elapsedSeconds;

            // Encode clues and solution
            System::Text::StringBuilder^ cluesSb = gcnew System::Text::StringBuilder(clues->Length);
            System::Text::StringBuilder^ solutionSb = gcnew System::Text::StringBuilder(solution->Length);
            for (int i = 0; i < clues->Length; ++i)
            {
                cluesSb->Append((wchar_t)(L'0' + clues[i]));
                solutionSb->Append((wchar_t)(L'0' + solution[i]));
            }
            save->clues = cluesSb->ToString();
            save->solution = solutionSb->ToString();

            // Encode values and states as compact strings
            System::Text::StringBuilder^ valueSb = gcnew System::Text::StringBuilder(values->Length);
            System::Text::StringBuilder^ stateSb = gcnew System::Text::StringBuilder(states->Length);
            for (int i = 0; i < values->Length; ++i)
            {
                valueSb->Append((wchar_t)(L'0' + values[i]));
                stateSb->Append((wchar_t)(L'0' + states[i]));
            }
            save->value = valueSb->ToString();
            save->state = stateSb->ToString();

            // Encode pencil marks as space-separated integers
            System::Text::StringBuilder^ markSb = gcnew System::Text::StringBuilder();
            for (int i = 0; i < pencilMarks->Length; ++i)
            {
                if (i > 0) markSb->Append(L' ');
                markSb->Append(pencilMarks[i]);
            }
            save->pencilMarks = markSb->ToString();

            // Write as UTF-8 text (no BOM), one key=value per line.
            StreamWriter^ writer = nullptr;
            try
            {
                writer = gcnew StreamWriter(filePath, false, gcnew System::Text::UTF8Encoding(false));
                writer->WriteLine("Sudoku3Save=" + FormatVersion.ToString());
                writer->WriteLine("sizeFactor=" + save->sizeFactor.ToString());
                writer->WriteLine("difficulty=" + save->difficulty.ToString());
                writer->WriteLine("numberOfHints=" + save->numberOfHints.ToString());
                writer->WriteLine("numberOfFixes=" + save->numberOfFixes.ToString());
                writer->WriteLine("hasGivenUp=" + (save->hasGivenUp ? 1 : 0).ToString());
                writer->WriteLine("hasUsedFix=" + (save->hasUsedFix ? 1 : 0).ToString());
                writer->WriteLine("gameMode=" + save->gameMode.ToString());
                writer->WriteLine("gameFinished=" + (save->gameFinished ? 1 : 0).ToString());
                writer->WriteLine("elapsedSeconds=" + save->elapsedSeconds.ToString());
                writer->WriteLine("clues=" + save->clues);
                writer->WriteLine("solution=" + save->solution);
                writer->WriteLine("value=" + save->value);
                writer->WriteLine("state=" + save->state);
                writer->WriteLine("pencilMarks=" + save->pencilMarks);
            }
            finally
            {
                if (writer != nullptr) writer->Close();
            }
        }

        // Reads and validates a SavedGame from the given file path.
        // Throws a System::Exception on any validation or I/O failure.
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

            SavedGame^ save = gcnew SavedGame();
            save->sizeFactor = RequireUInt(fields, "sizeFactor");
            save->difficulty = RequireUInt(fields, "difficulty");
            save->numberOfHints = RequireUInt(fields, "numberOfHints");
            save->numberOfFixes = RequireUInt(fields, "numberOfFixes");
            save->hasGivenUp = RequireUInt(fields, "hasGivenUp") != 0;
            save->hasUsedFix = RequireUInt(fields, "hasUsedFix") != 0;
            save->gameMode = RequireUInt(fields, "gameMode");
            save->gameFinished = RequireUInt(fields, "gameFinished") != 0;
            save->elapsedSeconds = RequireUInt(fields, "elapsedSeconds");
            save->clues = RequireStr(fields, "clues");
            save->solution = RequireStr(fields, "solution");
            save->value = RequireStr(fields, "value");
            save->state = RequireStr(fields, "state");
            save->pencilMarks = fields->ContainsKey("pencilMarks")
                ? fields["pencilMarks"] : gcnew System::String(L"");

            // Structural validation
            if (save->sizeFactor != 3)
                throw gcnew System::Exception("Invalid sizeFactor value " + save->sizeFactor.ToString());

            if ((unsigned int)save->value->Length != expectedNumberOfCells)
                throw gcnew System::Exception("Invalid number of cell values " + save->value->Length.ToString());

            if (save->state->Length != save->value->Length)
                throw gcnew System::Exception("Invalid number of cell states " + save->state->Length.ToString());

            unsigned int gameMode = save->gameMode;
            if (gameMode != static_cast<unsigned int>(GameMode::Game) &&
                gameMode != static_cast<unsigned int>(GameMode::Solver))
            {
                throw gcnew System::Exception("Invalid gameMode value " + gameMode.ToString());
            }

            // The puzzle snapshot (clues + solution) is optional: a Solver session that has not
            // been solved yet has no known solution, so both fields are empty. When present, both
            // must be full-length and consistent. Game mode always requires a solution.
            bool hasPuzzle = save->clues->Length > 0 || save->solution->Length > 0;

            if (gameMode == static_cast<unsigned int>(GameMode::Game) && !hasPuzzle)
                throw gcnew System::Exception("A saved game must contain a puzzle solution.");

            if (hasPuzzle)
            {
                if ((unsigned int)save->clues->Length != expectedNumberOfCells)
                    throw gcnew System::Exception("Invalid clues field length");

                if ((unsigned int)save->solution->Length != expectedNumberOfCells)
                    throw gcnew System::Exception("Invalid solution field length");

                // Validate clues and solution
                for (int i = 0; i < save->clues->Length; ++i)
                {
                    wchar_t c = save->clues[i];
                    wchar_t s = save->solution[i];
                    if (c < L'0' || c > L'9')
                        throw gcnew System::Exception("Invalid clue value " + c.ToString() + " at index " + i.ToString());
                    if (s < L'1' || s > L'9')
                        throw gcnew System::Exception("Invalid solution value " + s.ToString() + " at index " + i.ToString());
                    if (c != L'0' && c != s)
                        throw gcnew System::Exception("Clue/solution mismatch at index " + i.ToString());
                }
            }

            // Per-cell validation
            for (int i = 0; i < save->value->Length; ++i)
            {
                wchar_t v = save->value[i];
                wchar_t s = save->state[i];

                if (v < L'0' || v > L'9')
                    throw gcnew System::Exception("Invalid cell value " + v.ToString() + " at index " + i.ToString());

                if (s < L'0' || s > L'6')
                    throw gcnew System::Exception("Invalid cell state " + s.ToString() + " at index " + i.ToString());

                // state '1' means empty cell, so value must be '0' and vice versa
                if ((v == L'0') != (s == L'1'))
                    throw gcnew System::Exception("Mismatched cell value and state at index " + i.ToString());

                // Validate state is legal for the saved game mode
                if (gameMode == static_cast<unsigned int>(GameMode::Game))
                {
                    if (s == L'6')
                        throw gcnew System::Exception("Invalid state 6 in game mode at index " + i.ToString());
                }
                else // Solver
                {
                    if (s == L'3' || s == L'4' || s == L'5')
                        throw gcnew System::Exception("Invalid state " + s.ToString() + " in solver mode at index " + i.ToString());
                }
            }

            return save;
        }

    private:
        // Bumped whenever the on-disk format changes in a breaking way.
        static const unsigned int FormatVersion = 1;

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
