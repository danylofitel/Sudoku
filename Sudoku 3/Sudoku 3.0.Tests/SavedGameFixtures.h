// Danylo Fitel 2026
// Shared sample saves for the save/validation tests: one valid SavedGame for every session state
// the app can reach, plus small builders for undo/redo histories. A test file brings them in with
// `using namespace SavedGameFixtures;`. They are free functions rather than members of a shared
// base class, so the app's internal types never appear in a public test class's signature.

#pragma once

#include "SavedGame.h"

using namespace System;
using namespace Sudoku_3_0;

namespace Sudoku_3_0_Tests
{
    namespace SavedGameFixtures
    {
        const int Cells = 81;

        // A valid, in-progress Game-mode save: some clue cells filled, the rest empty.
        inline SavedGame^ MakeGameSave()
        {
            SavedGame^ g = gcnew SavedGame();
            g->difficulty = 3;
            g->numberOfRestarts = 1;
            g->numberOfHints = 2;
            g->numberOfFixes = 4;
            g->numberOfGiveUps = 0;
            g->mode = GameMode::Game;
            g->gameFinished = false;
            g->elapsedSeconds = 125;
            g->clues = gcnew array<unsigned char>(Cells);
            g->solution = gcnew array<unsigned char>(Cells);
            g->values = gcnew array<unsigned char>(Cells);
            g->states = gcnew array<unsigned char>(Cells);
            g->pencilMarks = gcnew array<int>(Cells);

            for (int i = 0; i < Cells; ++i)
            {
                unsigned char sol = (unsigned char)(1 + (i % 9));
                g->solution[i] = sol;
                bool isClue = (i % 3 == 0);
                g->clues[i] = isClue ? sol : (unsigned char)0;
                g->values[i] = isClue ? sol : (unsigned char)0;
                g->states[i] = isClue ? (unsigned char)0 /*clue*/ : (unsigned char)1 /*empty*/;
                g->pencilMarks[i] = isClue ? 0 : (1 << (i % 9 + 1)); // some marks on empty cells
            }
            return g;
        }

        // A valid Solver-mode save that has NOT been solved yet: no puzzle snapshot,
        // board recoverable from values/states alone.
        inline SavedGame^ MakeSolverInProgressSave()
        {
            SavedGame^ g = gcnew SavedGame();
            g->difficulty = 2;
            g->numberOfRestarts = 0;
            g->numberOfHints = 0;
            g->numberOfFixes = 0;
            g->numberOfGiveUps = 0;
            g->mode = GameMode::Solver;
            g->gameFinished = false;
            g->elapsedSeconds = 7;
            g->clues = gcnew array<unsigned char>(0);    // no puzzle yet
            g->solution = gcnew array<unsigned char>(0);
            g->values = gcnew array<unsigned char>(Cells);
            g->states = gcnew array<unsigned char>(Cells);
            g->pencilMarks = gcnew array<int>(Cells);

            for (int i = 0; i < Cells; ++i)
            {
                bool entered = (i < 5);
                g->values[i] = entered ? (unsigned char)(1 + i) : (unsigned char)0;
                g->states[i] = entered ? (unsigned char)2 /*user-filled*/ : (unsigned char)1 /*empty*/;
                g->pencilMarks[i] = 0;
            }
            return g;
        }

        // A finished Game-mode save, ended either by a win (every cell the player had to fill
        // locked as Correct) or by giving up (every such cell revealed as GivenUp). Cells 0, 3,
        // 6, ... are clues as in MakeGameSave; cells 2, 11, 20, ... (i % 9 == 2) were revealed
        // as hints, and numberOfHints counts them.
        inline SavedGame^ MakeFinishedGameSave(CellKind ending)
        {
            SavedGame^ g = gcnew SavedGame();
            g->difficulty = 4;
            g->numberOfRestarts = 0;
            g->numberOfHints = 9;
            g->numberOfFixes = 1;
            g->numberOfGiveUps = ending == CellKind::GivenUp ? 1 : 0;
            g->mode = GameMode::Game;
            g->gameFinished = true;
            g->elapsedSeconds = 600;
            g->clues = gcnew array<unsigned char>(Cells);
            g->solution = gcnew array<unsigned char>(Cells);
            g->values = gcnew array<unsigned char>(Cells);
            g->states = gcnew array<unsigned char>(Cells);
            g->pencilMarks = gcnew array<int>(Cells);

            for (int i = 0; i < Cells; ++i)
            {
                unsigned char sol = (unsigned char)(1 + (i % 9));
                g->solution[i] = sol;
                g->values[i] = sol; // finished: every cell holds its solution
                CellKind kind = (i % 3 == 0) ? CellKind::Clue
                    : (i % 9 == 2) ? CellKind::Hint
                    : ending;
                g->states[i] = static_cast<unsigned char>(kind);
                g->clues[i] = (kind == CellKind::Clue) ? sol : (unsigned char)0;
                g->pencilMarks[i] = 0;
            }
            return g;
        }

        inline SavedGame^ MakeWonGameSave() { return MakeFinishedGameSave(CellKind::Correct); }
        inline SavedGame^ MakeGivenUpGameSave() { return MakeFinishedGameSave(CellKind::GivenUp); }

        // A solved Solver-mode save: pre-filled cells are clues (state 0), the rest were filled
        // by the solver (state 6). Has a full puzzle snapshot.
        inline SavedGame^ MakeSolvedSolverSave()
        {
            SavedGame^ g = gcnew SavedGame();
            g->difficulty = 2;
            g->numberOfRestarts = 0;
            g->numberOfHints = 0;
            g->numberOfFixes = 0;
            g->numberOfGiveUps = 0;
            g->mode = GameMode::Solver;
            g->gameFinished = true;
            g->elapsedSeconds = 30;
            g->clues = gcnew array<unsigned char>(Cells);
            g->solution = gcnew array<unsigned char>(Cells);
            g->values = gcnew array<unsigned char>(Cells);
            g->states = gcnew array<unsigned char>(Cells);
            g->pencilMarks = gcnew array<int>(Cells);

            for (int i = 0; i < Cells; ++i)
            {
                unsigned char sol = (unsigned char)(1 + (i % 9));
                g->solution[i] = sol;
                g->values[i] = sol;
                bool prefilled = (i % 4 == 0);
                g->states[i] = prefilled ? (unsigned char)0 /*clue*/ : (unsigned char)6 /*solved*/;
                g->clues[i] = prefilled ? sol : (unsigned char)0;
                g->pencilMarks[i] = 0;
            }
            return g;
        }

        inline array<array<UndoManager::CellState^>^>^ MakeHistory(... array<array<UndoManager::CellState^>^>^ operations)
        {
            return operations;
        }

        inline array<UndoManager::CellState^>^ Op(... array<UndoManager::CellState^>^ cells)
        {
            return cells;
        }

        inline UndoManager::CellState^ Cell(unsigned int index, unsigned char value, CellKind kind, int marks)
        {
            return gcnew UndoManager::CellState(index, value, kind, marks);
        }
    }
}
