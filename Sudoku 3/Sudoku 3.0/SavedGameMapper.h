// Danylo Fitel 2026

#pragma once

#include "GameSession.h"
#include "SavedGame.h"
#include "Puzzle.h"
#include "UndoManager.h"

namespace Sudoku_3_0
{
    // Translates between the live GameSession/Board (plus its undo/redo history) and the flat
    // SavedGame DTO. This is the pure data mapping only, so it is unit-testable without a form:
    // the elapsed play time, which originates outside the session (in the timer), is passed in
    // on capture, and every UI side-effect of loading (controls, timer, rendering, clipboard)
    // stays in the form.
    ref class SavedGameMapper abstract sealed
    {
    public:
        // Builds a SavedGame snapshot from the current session state, its undo/redo history
        // (nullptr = none), and the elapsed play time.
        static SavedGame^ Capture(GameSession^ session, UndoManager^ history, unsigned int elapsedSeconds)
        {
            SavedGame^ game = gcnew SavedGame();
            game->difficulty = session->difficulty;
            game->numberOfRestarts = session->numberOfRestarts;
            game->numberOfHints = session->numberOfHints;
            game->numberOfFixes = session->numberOfFixes;
            game->numberOfGiveUps = session->numberOfGiveUps;
            game->candidateAssist = session->maxCandidateAssist;
            game->mode = session->mode;
            game->gameFinished = session->finished;
            game->elapsedSeconds = elapsedSeconds;

            // The board model serializes directly (value + kind-as-state-code + pencil marks).
            game->values = session->board->copyValues();
            game->states = session->board->copyStates();
            game->pencilMarks = session->board->copyPencilMarks();

            // The puzzle snapshot may not exist yet (a custom puzzle still being entered in Solver
            // mode). In that case persist empty clues/solution; the board is fully recoverable from
            // the per-cell values and states alone.
            game->clues = session->puzzle != nullptr
                ? session->puzzle->clues : gcnew array<unsigned char>(0);
            game->solution = session->puzzle != nullptr
                ? session->puzzle->solution : gcnew array<unsigned char>(0);

            game->undoHistory = history != nullptr
                ? history->exportUndo() : gcnew array<array<UndoManager::CellState^>^>(0);
            game->redoHistory = history != nullptr
                ? history->exportRedo() : gcnew array<array<UndoManager::CellState^>^>(0);
            return game;
        }

        // Restores a validated SavedGame into the session, its board, and the undo/redo history
        // (history may be nullptr to skip it). Does not touch controls, the timer, or rendering -
        // those are the caller's responsibility.
        static void Restore(SavedGame^ save, GameSession^ session, UndoManager^ history)
        {
            session->difficulty = save->difficulty;
            session->numberOfRestarts = save->numberOfRestarts;
            session->numberOfHints = save->numberOfHints;
            session->numberOfFixes = save->numberOfFixes;
            session->numberOfGiveUps = save->numberOfGiveUps;
            session->maxCandidateAssist = save->candidateAssist;
            session->mode = save->mode;
            session->finished = save->gameFinished;

            // A Solver session saved mid-entry has no solution yet, so the puzzle stays nullptr
            // until solved. (Puzzle defensively copies the arrays, so passing them directly is safe.)
            session->puzzle = save->clues->Length > 0
                ? gcnew Puzzle(save->clues, save->solution)
                : nullptr;

            session->board->restoreFrom(save->values, save->states, save->pencilMarks);

            if (history != nullptr)
                history->importHistory(save->undoHistory, save->redoHistory);
        }
    };
}
