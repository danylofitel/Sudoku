// Danylo Fitel 2013

#pragma once

namespace Sudoku_3_0
{
    // Holds statistics that persist across individual game sessions.
    // Lifetime: created once at app start, never reset between games.
    ref class PlayerStats
    {
    public:
        // Number of consecutive wins without giving up.
        // Incremented on each clean win; reset to zero when the user gives up.
        unsigned int winStreak;

        PlayerStats()
        {
            this->winStreak = 0;
        }
    };
}
