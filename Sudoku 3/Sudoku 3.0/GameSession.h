// Danylo Fitel 2013

#pragma once

#include "GameMode.h"
#include "Puzzle.h"

namespace Sudoku_3_0
{
    // Holds all mutable state for a single puzzle session.
    ref class GameSession
    {
    public:
        // Active game mode
        GameMode mode;

        // Immutable snapshot of the current puzzle (clues + solution).
        // nullptr in GameMode::None or before the first puzzle is created.
        Puzzle^ puzzle;

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

        // Pencil mark bitmask per cell
        array<int>^ pencilMarks;

        // Whether pencil mode is active
        bool pencilMode;

        // Whether hint mode is active (next cell click reveals the solution value)
        bool hintMode;

        // Index of the cell currently under the mouse (-1 if none); used for pencil ghost-mark rendering
        int hoveredCellIndex;

        // One-time initialization; call once from SudokuForm::initialize.
        GameSession(unsigned int numberOfCells)
        {
            this->mode = GameMode::None;
            this->puzzle = nullptr;
            this->difficulty = 2;
            this->numberOfFilledCells = 0;
            this->numberOfHints = 0;
            this->numberOfFixes = 0;
            this->hasGivenUp = false;
            this->hasUsedFix = false;
            this->pencilMarks = gcnew array<int>(numberOfCells);
            this->pencilMode = false;
            this->hintMode = false;
            this->hoveredCellIndex = -1;
        }

        // Resets all per-game fields for a new standard game.
        void startNewGame(unsigned int difficultyIndex, unsigned int numberOfCells)
        {
            this->mode = GameMode::Game;
            this->puzzle = nullptr;
            this->difficulty = difficultyIndex;
            this->numberOfFilledCells = 0;
            this->numberOfHints = 0;
            this->numberOfFixes = 0;
            this->hasGivenUp = false;
            this->hasUsedFix = false;
            this->pencilMode = false;
            this->hintMode = false;
            this->pencilMarks = gcnew array<int>(numberOfCells);
        }
    };
}
