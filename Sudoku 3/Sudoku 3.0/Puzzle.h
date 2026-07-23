// Danylo Fitel 2026

#pragma once

namespace Sudoku_3_0
{
    // Immutable snapshot of a puzzle captured at game-start or after a successful solve.
    // clues[i]    = 0 means the cell was hidden (user must fill it);
    //               1-9 means the cell is an engine-provided clue (immutable).
    // solution[i] = 1-9, the correct value for every cell.
    // Both arrays have length numberOfCells and are set once; never mutated afterward.
    ref class Puzzle
    {
    public:
        array<unsigned char>^ clues;
        array<unsigned char>^ solution;

        Puzzle(array<unsigned char>^ clues, array<unsigned char>^ solution)
        {
            this->clues = clues;
            this->solution = solution;
        }
    };
}
