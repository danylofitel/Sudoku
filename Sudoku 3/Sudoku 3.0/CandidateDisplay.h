// Danylo Fitel 2026

#pragma once

namespace Sudoku_3_0
{
    // How the non-conflicting candidate ghost is displayed. A difficulty modifier: any level
    // other than None disqualifies a clean win. Values are ordered (None < CurrentCell < AllCells)
    // and numbered to match the registry and save-file codes, so they can be compared and the
    // "strongest level used" can be tracked with a simple max.
    enum class CandidateDisplay : unsigned int
    {
        None = 0,        // never show candidates
        CurrentCell = 1, // show only on the hovered/focused cell
        AllCells = 2     // show on every empty cell
    };
}
