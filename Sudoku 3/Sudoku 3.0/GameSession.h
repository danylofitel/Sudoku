// Danylo Fitel 2013

#pragma once

#include "GameMode.h"

namespace Sudoku_3_0
{
    // Holds all mutable state for a single puzzle session.
    ref class GameSession
    {
    public:
        // Active game mode
        GameMode mode;

        // Difficulty index of current puzzle: 0=VeryEasy, 1=Easy, 2=Medium, 3=Hard, 4=VeryHard
        unsigned int difficulty;

        // Number of cells that currently have a value
        unsigned int numberOfFilledCells;

        // Number of hints used so far
        unsigned int numberOfHints;

        // Number of times Fix was used so far
        unsigned int numberOfFixes;

        // Whether the user has given up at least once on this puzzle
        bool hasGivenUp;

        // Whether the user has used Fix at least once on this puzzle
        bool hasUsedFix;

        // Session-only win streak; persists across games and resets to zero on give-up
        unsigned int winStreak;

        // Pencil mark bitmask per cell: bit N set means digit N is marked (bits 1-9)
        array<int>^ pencilMarks;

        // Whether pencil mode is active
        bool pencilMode;

        // One-time initialization; call once from SudokuForm::initialize.
        GameSession(unsigned int numberOfCells)
        {
            this->mode = GameMode::None;
            this->difficulty = 2;
            this->numberOfFilledCells = 0;
            this->numberOfHints = 0;
            this->numberOfFixes = 0;
            this->hasGivenUp = false;
            this->hasUsedFix = false;
            this->winStreak = 0;
            this->pencilMarks = gcnew array<int>(numberOfCells);
            this->pencilMode = false;
        }

        // Resets all per-game fields for a new standard game.
        // winStreak is intentionally NOT reset here; it is managed by
        // checkGameState and giveUpButton_Click.
        void startNewGame(unsigned int difficultyIndex, unsigned int numberOfCells)
        {
            this->mode = GameMode::Game;
            this->difficulty = difficultyIndex;
            this->numberOfFilledCells = 0;
            this->numberOfHints = 0;
            this->numberOfFixes = 0;
            this->hasGivenUp = false;
            this->hasUsedFix = false;
            this->pencilMode = false;
            this->pencilMarks = gcnew array<int>(numberOfCells);
        }
    };
}
