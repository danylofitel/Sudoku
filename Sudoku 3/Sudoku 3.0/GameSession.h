// Danylo Fitel 2026

#pragma once

#include "GameMode.h"
#include "Puzzle.h"
#include "Board.h"

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

        // The authoritative board model: per-cell value, kind (provenance), and pencil marks.
        // It also tracks the filled-cell count (board->FilledCount).
        Board^ board;

        // Number of times the puzzle has been restarted so far
        unsigned int numberOfRestarts;

        // Number of hints used so far
        unsigned int numberOfHints;

        // Number of times Fix was used so far (> 0 means Fix has been used at least once)
        unsigned int numberOfFixes;

        // Number of times the user gave up on this puzzle (> 0 means they have given up at
        // least once; can exceed 1 since Restart re-enables Give Up without clearing this)
        unsigned int numberOfGiveUps;

        // One-time initialization with a default difficulty. The caller (SudokuForm)
        // immediately starts a real game, so the initial difficulty is only transient.
        GameSession(unsigned int numberOfCells)
        {
            this->board = gcnew Board(numberOfCells);
            this->difficulty = 2;
            this->reset(GameMode::Game);
        }

        // Resets all per-puzzle state for a new standard game at the given difficulty.
        void startNewGame(unsigned int difficultyIndex)
        {
            this->difficulty = difficultyIndex;
            this->reset(GameMode::Game);
        }

        // Resets all per-puzzle state for entering a new custom puzzle (Solver mode).
        void startCustomPuzzle()
        {
            this->reset(GameMode::Solver);
        }

    private:
        // Resets every per-puzzle field (board and counters) to its initial state for the given
        // mode. Difficulty is set by the caller, since it is a game-only concept.
        void reset(GameMode mode)
        {
            this->mode = mode;
            this->puzzle = nullptr;
            this->board->clearToEmpty();
            this->numberOfRestarts = 0;
            this->numberOfHints = 0;
            this->numberOfFixes = 0;
            this->numberOfGiveUps = 0;
        }
    };
}
