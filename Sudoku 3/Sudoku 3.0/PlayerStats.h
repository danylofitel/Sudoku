// Danylo Fitel 2026

#pragma once

namespace Sudoku_3_0
{
    // Holds statistics that persist across individual game sessions.
    // Lifetime: created once at app start, never reset between games.
    ref class PlayerStats
    {
    public:
        // Number of consecutive completed games in which the user never gave up.
        // Incremented on every win, including wins that used hints or fixes;
        // reset to zero the moment the user gives up (seeing the solution breaks
        // the streak, and completing that same puzzle afterwards does not count).
        unsigned int winStreak;

        PlayerStats()
        {
            this->winStreak = 0;
        }
    };
}
