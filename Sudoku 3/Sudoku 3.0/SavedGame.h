// Danylo Fitel 2013

#pragma once

using namespace System;

[Serializable]
public ref class SavedGame
{
public:
    // Size of a single block
    unsigned int sizeFactor;

    // Game difficulty level
    unsigned int difficulty;

    // Number of used hints (cumulative across restarts)
    unsigned int numberOfHints;

    // Number of times Fix was used (cumulative across restarts)
    unsigned int numberOfFixes;

    // Whether the user has given up at least once on this puzzle
    bool hasGivenUp;

    // Whether the user has used Fix at least once on this puzzle
    bool hasUsedFix;

    // State of the game: 1 - game, 2 - solver
    unsigned int gameMode;

    // The game has been finished
    bool gameFinished;

    // Values of all cells
    System::String^ value;

    // State of all cells: 0 - filled by the engine, 1 - empty, 2 - filled by user,
    // 3 - filled by user and confirmed, 4 - hint, 5 - filled when the user gave up,
    // 6 - filled by the solver
    System::String^ state;

    // Pencil mark bitmasks for all cells, space-separated (may be null for old saves)
    System::String^ pencilMarks;
};
