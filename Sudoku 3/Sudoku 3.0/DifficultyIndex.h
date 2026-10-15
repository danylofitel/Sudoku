// Danylo Fitel 2026

#pragma once

namespace Sudoku_3_0
{
    // Difficulty is stored and shown as an index: 0 = Very Easy, 1 = Easy, 2 = Medium,
    // 3 = Hard, 4 = Very Hard - in settings, save files, and the difficulty dropdown. The index
    // range lives here, apart from Difficulty.h (which maps indices to the engine's levels and
    // pulls in the whole engine), so settings and save validation can share it cheaply.
    const unsigned int MaxDifficultyIndex = 4;
}
