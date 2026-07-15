// Danylo Fitel 2013

#pragma once

namespace Sudoku_3_0
{
    // Active game mode
    enum class GameMode : unsigned int
    {
        None = 0, // No active game (initial state or finished)
        Game = 1, // Standard puzzle game session
        Solver = 2, // Custom puzzle solver session
    };
}
