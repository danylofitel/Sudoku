// Danylo Fitel 2026

#pragma once

#include "SudokuEngine.h"
#include "Strings.h"

namespace Sudoku_3_0
{
    // Single source of truth for the five difficulty levels: the mapping between the 0-4 UI index
    // (combo box / registry / session), the engine's DifficultyLevel enum, and the localized name
    // string id. Centralizing these keeps "add a difficulty" from meaning "hunt down every switch."
    ref class Difficulty abstract sealed
    {
    public:
        // Number of difficulty levels (indices 0 .. Count-1).
        literal unsigned int Count = 5;

        // 0-based index -> engine enum. Out-of-range falls back to Medium.
        static SudokuGameEngine::DifficultyLevel toEngineLevel(unsigned int index)
        {
            switch (index)
            {
            case 0:  return SudokuGameEngine::DifficultyLevel::VeryEasy;
            case 1:  return SudokuGameEngine::DifficultyLevel::Easy;
            case 2:  return SudokuGameEngine::DifficultyLevel::Medium;
            case 3:  return SudokuGameEngine::DifficultyLevel::Hard;
            case 4:  return SudokuGameEngine::DifficultyLevel::VeryHard;
            default: return SudokuGameEngine::DifficultyLevel::Medium;
            }
        }

        // Engine enum -> 0-based index. Unknown values fall back to Medium (2).
        static unsigned int toIndex(SudokuGameEngine::DifficultyLevel level)
        {
            switch (level)
            {
            case SudokuGameEngine::DifficultyLevel::VeryEasy: return 0;
            case SudokuGameEngine::DifficultyLevel::Easy:     return 1;
            case SudokuGameEngine::DifficultyLevel::Medium:   return 2;
            case SudokuGameEngine::DifficultyLevel::Hard:     return 3;
            case SudokuGameEngine::DifficultyLevel::VeryHard: return 4;
            default:                                          return 2;
            }
        }

        // 0-based index -> the StringId of that level's localized name.
        static StringId nameStringId(unsigned int index)
        {
            switch (index)
            {
            case 0:  return StringId::DifficultyVeryEasy;
            case 1:  return StringId::DifficultyEasy;
            case 2:  return StringId::DifficultyMedium;
            case 3:  return StringId::DifficultyHard;
            case 4:  return StringId::DifficultyVeryHard;
            default: return StringId::DifficultyMedium;
            }
        }
    };
}
