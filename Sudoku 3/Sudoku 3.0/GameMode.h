// Danylo Fitel 2013

#pragma once

namespace Sudoku_3_0
{
    // Active game mode. A session is always in exactly one of these.
    enum class GameMode : unsigned int
    {
        Game = 1, // Standard puzzle game session
        Solver = 2, // Custom puzzle solver session
    };
}
