// Danylo Fitel 2026

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
        // Always set in Game mode. In Solver mode it is nullptr until Solve succeeds,
        // so a custom puzzle can be entered (and saved) before it has a known solution.
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

        // One-time initialization with a default difficulty. The caller (SudokuForm)
        // immediately starts a real game, so the initial difficulty is only transient.
        GameSession(unsigned int numberOfCells)
        {
            this->resetForNewGame(2, numberOfCells);
        }

        // Resets all per-game fields for a new standard game.
        void startNewGame(unsigned int difficultyIndex, unsigned int numberOfCells)
        {
            this->resetForNewGame(difficultyIndex, numberOfCells);
        }

    private:
        // Resets every per-puzzle field to its initial state, including switching to Game mode.
        // Solver mode is entered separately by the form when the user enters a custom puzzle.
        void resetForNewGame(unsigned int difficultyIndex, unsigned int numberOfCells)
        {
            this->mode = GameMode::Game;
            this->puzzle = nullptr;
            this->difficulty = difficultyIndex;
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
    };
}
