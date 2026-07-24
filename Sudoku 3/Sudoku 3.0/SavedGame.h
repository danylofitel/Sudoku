// Danylo Fitel 2026

#pragma once

#include "GameMode.h"

namespace Sudoku_3_0
{
    // Plain in-memory data carrier for a saved game, exchanged between SudokuForm and
    // SaveGameStore. It holds typed domain data only; SaveGameStore owns all on-disk
    // (text) encoding and decoding, so no wire format leaks into callers.
    ref class SavedGame
    {
    public:
        // Difficulty index: 0=VeryEasy .. 4=VeryHard
        unsigned int difficulty;

        // Assist counters, cumulative across restarts of the same puzzle
        unsigned int numberOfHints;
        unsigned int numberOfFixes;
        unsigned int numberOfGiveUps;

        // Game vs Solver session
        GameMode mode;

        // Whether the puzzle is finished (won, given up, or solved)
        bool gameFinished;

        // Total play time in whole seconds
        unsigned int elapsedSeconds;

        // Immutable puzzle snapshot, each of length numberOfCells:
        //   clues[i]    : 0 = hidden cell, 1-9 = engine clue
        //   solution[i] : 1-9 = correct value
        // Both are empty (length 0) for a custom puzzle entered in Solver mode that has
        // not been solved yet.
        array<unsigned char>^ clues;
        array<unsigned char>^ solution;

        // Per-cell board state, each of length numberOfCells:
        //   values[i]      : 0 = empty, 1-9 = filled
        //   states[i]      : 0 = engine clue, 1 = empty, 2 = user-filled, 3 = confirmed correct,
        //                    4 = hint, 5 = given-up reveal, 6 = solver-filled
        //   pencilMarks[i] : bitmask of pencilled digits (bits 1-9)
        array<unsigned char>^ values;
        array<unsigned char>^ states;
        array<int>^ pencilMarks;
    };
}
