// Danylo Fitel 2013

#pragma once

#include "SavedGame.h"
#include "GameMode.h"

using namespace System::IO;
using namespace System::Runtime::Serialization::Formatters::Binary;

namespace Sudoku_3_0
{
    // Handles reading and writing SavedGame objects to/from disk.
    // Contains no UI logic — callers are responsible for applying loaded state.
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
            array<unsigned char>^ clues,
            array<unsigned char>^ solution,
            array<unsigned char>^ values,
            array<unsigned char>^ states,
            array<int>^ pencilMarks)
        {
            SavedGame^ save = gcnew SavedGame();
            save->sizeFactor    = sizeFactor;
            save->difficulty    = difficulty;
            save->numberOfHints = numberOfHints;
            save->numberOfFixes = numberOfFixes;
            save->hasGivenUp    = hasGivenUp;
            save->hasUsedFix    = hasUsedFix;
            save->gameMode      = static_cast<unsigned int>(mode);
            save->gameFinished  = gameFinished;

            // Encode clues and solution
            System::Text::StringBuilder^ cluesSb    = gcnew System::Text::StringBuilder(clues->Length);
            System::Text::StringBuilder^ solutionSb = gcnew System::Text::StringBuilder(solution->Length);
            for (int i = 0; i < clues->Length; ++i)
            {
                cluesSb->Append((wchar_t)(L'0' + clues[i]));
                solutionSb->Append((wchar_t)(L'0' + solution[i]));
            }
            save->clues    = cluesSb->ToString();
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

            FileStream^ fs = nullptr;
            try
            {
                fs = File::Create(filePath);
                (gcnew BinaryFormatter())->Serialize(fs, save);
            }
            finally
            {
                if (fs != nullptr) fs->Close();
            }
        }

        // Reads and validates a SavedGame from the given file path.
        // Throws a descriptive string on any validation or I/O failure.
        static SavedGame^ Load(System::String^ filePath, unsigned int expectedNumberOfCells)
        {
            FileStream^ fs = nullptr;
            SavedGame^ save = nullptr;
            try
            {
                fs = File::OpenRead(filePath);
                save = (SavedGame^)(gcnew BinaryFormatter())->Deserialize(fs);
            }
            finally
            {
                if (fs != nullptr) fs->Close();
            }

            // Structural validation
            if (save->sizeFactor != 3)
                throw "Invalid sizeFactor value " + save->sizeFactor.ToString();

            if ((unsigned int)save->value->Length != expectedNumberOfCells)
                throw "Invalid number of cell values " + save->value->Length.ToString();

            if (save->state->Length != save->value->Length)
                throw "Invalid number of cell states " + save->state->Length.ToString();

            if (save->clues == nullptr || (unsigned int)save->clues->Length != expectedNumberOfCells)
                throw "Invalid clues field length";

            if (save->solution == nullptr || (unsigned int)save->solution->Length != expectedNumberOfCells)
                throw "Invalid solution field length";

            // Validate clues and solution
            for (int i = 0; i < save->clues->Length; ++i)
            {
                wchar_t c = save->clues[i];
                wchar_t s = save->solution[i];
                if (c < L'0' || c > L'9')
                    throw "Invalid clue value " + c.ToString() + " at index " + i.ToString();
                if (s < L'1' || s > L'9')
                    throw "Invalid solution value " + s.ToString() + " at index " + i.ToString();
                if (c != L'0' && c != s)
                    throw "Clue/solution mismatch at index " + i.ToString();
            }

            unsigned int gameMode = save->gameMode;
            if (gameMode != static_cast<unsigned int>(GameMode::Game) &&
                gameMode != static_cast<unsigned int>(GameMode::Solver))
            {
                throw "Invalid gameMode value " + gameMode.ToString();
            }

            // Per-cell validation
            for (int i = 0; i < save->value->Length; ++i)
            {
                wchar_t v = save->value[i];
                wchar_t s = save->state[i];

                if (v < L'0' || v > L'9')
                    throw "Invalid cell value " + v.ToString() + " at index " + i.ToString();

                if (s < L'0' || s > L'6')
                    throw "Invalid cell state " + s.ToString() + " at index " + i.ToString();

                // state '1' means empty cell, so value must be '0' and vice versa
                if ((v == L'0') != (s == L'1'))
                    throw "Mismatched cell value and state at index " + i.ToString();

                // Validate state is legal for the saved game mode
                if (gameMode == static_cast<unsigned int>(GameMode::Game))
                {
                    if (s == L'6')
                        throw "Invalid state 6 in game mode at index " + i.ToString();
                }
                else // Solver
                {
                    if (s == L'3' || s == L'4' || s == L'5')
                        throw "Invalid state " + s.ToString() + " in solver mode at index " + i.ToString();
                }
            }

            return save;
        }
    };
}
