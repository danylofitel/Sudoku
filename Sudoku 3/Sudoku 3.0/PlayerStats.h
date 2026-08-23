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

        // Number of consecutive clean wins (see GameSession::isClean): a win that used any
        // assistance - a hint, a fix, or the candidate display - resets it, as does a give-up.
        // Always <= winStreak.
        unsigned int cleanWinStreak;

        PlayerStats()
        {
            this->winStreak = 0;
            this->cleanWinStreak = 0;
        }

        // A win always advances the win streak; the clean win streak advances only if the win
        // was clean (no assistance), otherwise it resets to zero.
        void recordWin(bool clean)
        {
            ++this->winStreak;
            this->cleanWinStreak = clean ? this->cleanWinStreak + 1 : 0;
        }

        // Giving up resets both streaks.
        void recordGiveUp()
        {
            this->winStreak = 0;
            this->cleanWinStreak = 0;
        }
    };
}
