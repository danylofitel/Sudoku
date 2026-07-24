// Danylo Fitel 2026

#pragma once

namespace Sudoku_3_0
{
    // Immutable snapshot of a puzzle captured at game-start or after a successful solve.
    // clues[i]    = 0 means the cell was hidden (user must fill it);
    //               1-9 means the cell is an engine-provided clue (immutable).
    // solution[i] = 1-9, the correct value for every cell.
    //
    // The two arrays are validated and defensively copied on construction, then exposed as
    // initonly fields, so a Puzzle instance can never be reassigned or repointed. (Callers
    // still index the arrays directly; by convention they only read them.)
    ref class Puzzle
    {
    public:
        initonly array<unsigned char>^ clues;
        initonly array<unsigned char>^ solution;

        Puzzle(array<unsigned char>^ clues, array<unsigned char>^ solution)
        {
            if (clues == nullptr)
                throw gcnew System::ArgumentNullException("clues");
            if (solution == nullptr)
                throw gcnew System::ArgumentNullException("solution");
            if (clues->Length != solution->Length)
                throw gcnew System::ArgumentException("clues and solution must have the same length.");

            // Defensive copies: the snapshot owns its data and cannot be mutated through the
            // arrays the caller passed in.
            this->clues = safe_cast<array<unsigned char>^>(clues->Clone());
            this->solution = safe_cast<array<unsigned char>^>(solution->Clone());
        }
    };
}
