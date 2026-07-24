// Danylo Fitel 2026

#pragma once

namespace Sudoku_3_0
{
    // Provenance / state of a board cell. The numeric values match the on-disk save "state"
    // codes exactly, so persistence is a direct cast in both directions (no lookup table).
    //
    // Editable cells (the only ones the user can change) are UserEmpty and UserFilled; every
    // other kind is a locked cell. Every kind except UserEmpty holds a value of 1-9.
    enum class CellKind : unsigned char
    {
        Clue = 0,       // engine-provided clue, immutable
        UserEmpty = 1,  // editable, no value
        UserFilled = 2, // editable, user-entered value
        Correct = 3,    // user value locked as correct on win
        Hint = 4,       // revealed by Hint
        GivenUp = 5,    // revealed after Give Up
        Solved = 6,     // filled by the solver
    };
}
