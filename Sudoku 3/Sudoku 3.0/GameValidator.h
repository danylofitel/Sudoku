// Danylo Fitel 2026

#pragma once

#include "SavedGame.h"
#include "GameMode.h"
#include "CellKind.h"

namespace Sudoku_3_0
{
    // The rules for a valid game: every state the app can reach, and nothing else. It works on
    // a SavedGame snapshot in memory, with no file involved, so the same rules guard both a
    // file being loaded (SaveGameStore::Load) and a game about to be saved after a crash.
    ref class GameValidator abstract sealed
    {
    public:
        // Checks every rule a game must satisfy: value ranges, array lengths, the puzzle
        // snapshot, and the board invariants (ValidateBoard). Throws System::Exception naming
        // the first rule broken. SaveGameStore::Load runs it on every file it reads; the form
        // runs it before an emergency save after a crash, so that save can never write a game
        // Load would reject. The undo/redo history is checked separately (ValidateHistory): it
        // is non-essential, so Load drops an unusable one rather than rejecting the game.
        static void Validate(SavedGame^ game, unsigned int expectedNumberOfCells)
        {
            if (game->difficulty > MaxDifficulty)
                throw gcnew System::Exception("Invalid difficulty value " + game->difficulty.ToString());

            unsigned int candidateAssist = static_cast<unsigned int>(game->candidateAssist);
            if (candidateAssist > static_cast<unsigned int>(CandidateDisplay::AllCells))
                throw gcnew System::Exception("Invalid candidateAssist value " + candidateAssist.ToString());

            if (game->mode != GameMode::Game && game->mode != GameMode::Solver)
                throw gcnew System::Exception("Invalid gameMode value " + (static_cast<unsigned int>(game->mode)).ToString());

            // Board state is always present and full-length.
            RequireDigits(game->values, expectedNumberOfCells, 0, 9, "value");
            RequireDigits(game->states, expectedNumberOfCells, 0, 6, "state");

            // The puzzle snapshot (clues + solution) is optional: a Solver session that has not
            // been solved yet has no known solution, so both are empty. When present, both must
            // be full-length and consistent. Game mode always requires a solution.
            if (game->clues == nullptr || game->solution == nullptr)
                throw gcnew System::Exception("Missing puzzle snapshot (use empty arrays for none).");
            bool hasPuzzle = game->clues->Length > 0 || game->solution->Length > 0;

            if (game->mode == GameMode::Game && !hasPuzzle)
                throw gcnew System::Exception("A saved game must contain a puzzle solution.");

            // In Solver mode the snapshot exists exactly when the puzzle is solved: Solve both
            // captures it and finishes the session, and nothing else does either.
            if (game->mode == GameMode::Solver && hasPuzzle != game->gameFinished)
                throw gcnew System::Exception(game->gameFinished
                    ? "A solved custom puzzle must contain its solution."
                    : "A custom puzzle still being entered cannot have a solution.");

            if (hasPuzzle)
            {
                RequireDigits(game->clues, expectedNumberOfCells, 0, 9, "clue");
                RequireDigits(game->solution, expectedNumberOfCells, 1, 9, "solution");
                for (unsigned int i = 0; i < expectedNumberOfCells; ++i)
                    if (game->clues[i] != 0 && game->clues[i] != game->solution[i])
                        throw gcnew System::Exception("Clue/solution mismatch at index " + i.ToString());
            }

            // Pencil marks: one bitmask per cell, using only bits 1-9 (the digits)
            if (game->pencilMarks == nullptr || (unsigned int)game->pencilMarks->Length != expectedNumberOfCells)
                throw gcnew System::Exception("Invalid length for field 'pencilMarks'");
            const int validBits = 0x3FE; // bits 1..9
            for (unsigned int i = 0; i < expectedNumberOfCells; ++i)
                if ((game->pencilMarks[i] & ~validBits) != 0)
                    throw gcnew System::Exception("Invalid pencilMarks value " + game->pencilMarks[i].ToString() + " at index " + i.ToString());

            ValidateBoard(game);
        }

        // Checks the game's undo/redo history (both halves) against its board: a finished game
        // has none, and every snapshot must be one play could have recorded (ValidateOperations).
        // Call it only on a game that passed Validate. Throws System::Exception naming the first
        // rule broken; SaveGameStore::Load then drops the history and keeps the game.
        static void ValidateHistory(SavedGame^ game)
        {
            bool hasHistory = (game->undoHistory != nullptr && game->undoHistory->Length > 0)
                || (game->redoHistory != nullptr && game->redoHistory->Length > 0);
            if (hasHistory && game->gameFinished)
                throw gcnew System::Exception("A finished game has no undo history.");
            if (game->undoHistory != nullptr) ValidateOperations(game->undoHistory, game);
            if (game->redoHistory != nullptr) ValidateOperations(game->redoHistory, game);
        }

    private:
        // Difficulty indices run 0 (VeryEasy) .. 4 (VeryHard), as in Difficulty and Settings.
        static const unsigned int MaxDifficulty = 4;

        // Validate's check for a digit field: exactly expectedLength entries, each within
        // [minDigit, maxDigit].
        static void RequireDigits(array<unsigned char>^ digits, unsigned int expectedLength,
            unsigned char minDigit, unsigned char maxDigit, System::String^ fieldName)
        {
            if (digits == nullptr || (unsigned int)digits->Length != expectedLength)
                throw gcnew System::Exception("Invalid length for field '" + fieldName + "'");
            for (int i = 0; i < digits->Length; ++i)
                if (digits[i] < minDigit || digits[i] > maxDigit)
                    throw gcnew System::Exception("Invalid " + fieldName + " value " + digits[i].ToString() + " at index " + i.ToString());
        }

        // Checks that the board and counters form a state the app can actually reach, so a loaded
        // game is never in a situation play could not produce. The reachable session states:
        //
        //   Session state       Cell kinds allowed                  Also required
        //   ------------------  ----------------------------------  -------------------------------
        //   Game, in progress   Clue, UserEmpty, UserFilled, Hint   board not already solved
        //   Game, won           Clue, Correct, Hint                 -
        //   Game, given up      Clue, GivenUp, Hint                 numberOfGiveUps >= 1
        //   Solver, entering    UserEmpty, UserFilled               no solution; pencil marks and
        //                                                           all counters are zero
        //   Solver, solved      Clue, Solved                        solution present; counters zero
        //
        // and for every cell, in every state:
        //   - empty (value 0) exactly when its kind is UserEmpty
        //   - a Clue exactly where the puzzle has a clue, holding that clue
        //   - a Correct, Hint, GivenUp, or Solved cell holds its solution digit
        //   - pencil marks only on an empty cell
        // plus: numberOfHints is at least the number of Hint cells (Undo can revert a hint
        // reveal, but never uncounts it), so a file cannot claim hint cells as a clean win.
        // (Solver mode has no puzzle, and therefore no clues, until it is solved; the game-only
        // kinds Correct, Hint and GivenUp never appear in it.)
        static void ValidateBoard(SavedGame^ game)
        {
            bool inGame = game->mode == GameMode::Game;
            bool hasPuzzle = game->solution->Length > 0;
            int count = game->values->Length;

            // Kinds present on the board, to check the per-state rules after the cell loop.
            unsigned int hintCells = 0;
            bool anyCorrect = false, anyGivenUp = false, anyEmpty = false;
            bool allEditableSolved = true; // every UserFilled cell holds its solution digit

            for (int i = 0; i < count; ++i)
            {
                unsigned char value = game->values[i];
                CellKind kind = static_cast<CellKind>(game->states[i]);
                System::String^ where = " at index " + i.ToString();

                if ((value == 0) != (kind == CellKind::UserEmpty))
                    throw gcnew System::Exception("Mismatched cell value and state" + where);

                if (game->pencilMarks[i] != 0 && kind != CellKind::UserEmpty)
                    throw gcnew System::Exception("Pencil marks on a filled cell" + where);
                if (game->pencilMarks[i] != 0 && !inGame)
                    throw gcnew System::Exception("Pencil marks in Solver mode" + where); // Pencil is game-only

                // Cell kinds allowed in this session state
                bool allowed;
                if (inGame && !game->gameFinished)
                    allowed = kind == CellKind::Clue || kind == CellKind::UserEmpty
                        || kind == CellKind::UserFilled || kind == CellKind::Hint;
                else if (inGame)
                    allowed = kind == CellKind::Clue || kind == CellKind::Correct
                        || kind == CellKind::Hint || kind == CellKind::GivenUp;
                else if (!game->gameFinished)
                    allowed = kind == CellKind::UserEmpty || kind == CellKind::UserFilled;
                else
                    allowed = kind == CellKind::Clue || kind == CellKind::Solved;
                if (!allowed)
                    throw gcnew System::Exception("Cell state " + game->states[i].ToString()
                        + " cannot occur in this session state" + where);

                // Clues: exactly where the puzzle has one, holding it
                if (hasPuzzle && (kind == CellKind::Clue) != (game->clues[i] != 0))
                    throw gcnew System::Exception("Clue cell does not match the puzzle's clues" + where);

                // Locked reveals hold the solution (clues are covered by clue == solution)
                bool revealsSolution = kind == CellKind::Correct || kind == CellKind::Hint
                    || kind == CellKind::GivenUp || kind == CellKind::Solved;
                if ((kind == CellKind::Clue || revealsSolution) && value != game->solution[i])
                    throw gcnew System::Exception("Locked cell does not hold its solution digit" + where);

                if (kind == CellKind::Hint) ++hintCells;
                if (kind == CellKind::Correct) anyCorrect = true;
                if (kind == CellKind::GivenUp) anyGivenUp = true;
                if (kind == CellKind::UserEmpty) anyEmpty = true;
                if (kind == CellKind::UserFilled && hasPuzzle && value != game->solution[i])
                    allEditableSolved = false;
            }

            if (inGame)
            {
                if (game->numberOfHints < hintCells)
                    throw gcnew System::Exception("numberOfHints is below the number of hint cells.");

                // A game whose board is complete and correct was won the moment it got there
                if (!game->gameFinished && !anyEmpty && allEditableSolved)
                    throw gcnew System::Exception("An unfinished game cannot already be solved.");

                // A finished game ended exactly one way: won (Correct) or given up (GivenUp)
                if (anyCorrect && anyGivenUp)
                    throw gcnew System::Exception("A game cannot be both won and given up.");
                if (anyGivenUp && game->numberOfGiveUps == 0)
                    throw gcnew System::Exception("A given-up game must count the give-up.");
            }
            else
            {
                // Hints, Fix, Give Up and Restart do not exist in Solver mode
                if (game->numberOfHints != 0 || game->numberOfFixes != 0
                    || game->numberOfGiveUps != 0 || game->numberOfRestarts != 0)
                    throw gcnew System::Exception("Solver sessions have no hint, fix, give-up or restart counts.");
            }
        }

        // Checks that every snapshot is one the game could really have recorded, so restoring it
        // can never produce an impossible board - e.g. turn a clue editable or lock in a wrong
        // digit as a hint. A history only ever touches playable cells (never a clue), and holds
        // them as empty, user-filled, or a correct hint.
        static void ValidateOperations(array<array<UndoManager::CellState^>^>^ history, SavedGame^ game)
        {
            const int validBits = 0x3FE; // bits 1..9
            const unsigned char emptyState = 1, userFilledState = 2, hintState = 4;

            for each (array<UndoManager::CellState^>^ operation in history)
            {
                if (operation->Length == 0)
                    throw gcnew System::Exception("Empty history operation.");

                for each (UndoManager::CellState^ cell in operation)
                {
                    unsigned char boardState = game->states[cell->cellIndex];
                    if (boardState != emptyState && boardState != userFilledState && boardState != hintState)
                        throw gcnew System::Exception("History touches a locked cell at index " + cell->cellIndex.ToString());

                    unsigned char kind = static_cast<unsigned char>(cell->kind);
                    if (kind != emptyState && kind != userFilledState && kind != hintState)
                        throw gcnew System::Exception("Invalid history kind at index " + cell->cellIndex.ToString());

                    if ((cell->value == 0) != (kind == emptyState))
                        throw gcnew System::Exception("Mismatched history value and kind at index " + cell->cellIndex.ToString());

                    if (kind == hintState && (game->mode != GameMode::Game || game->solution->Length == 0
                        || cell->value != game->solution[cell->cellIndex]))
                        throw gcnew System::Exception("Invalid history hint at index " + cell->cellIndex.ToString());

                    if ((cell->pencilMarks & ~validBits) != 0 || (cell->value != 0 && cell->pencilMarks != 0))
                        throw gcnew System::Exception("Invalid history pencil marks at index " + cell->cellIndex.ToString());
                }
            }
        }
    };
}
