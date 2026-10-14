// Danylo Fitel 2026

#pragma once

#include "Board.h"

namespace Sudoku_3_0
{
    // Manages the undo and redo history. It has no UI dependency: it works on the Board model
    // and raises a caller-supplied callback whenever either history changes (record, batch,
    // undo, redo, clear), and the caller (the form) uses canUndo/canRedo to sync its controls.
    //
    // An operation is a list of cell snapshots taken just before the cells changed. Undo and
    // redo are symmetric: each captures the current state of the operation's cells (which
    // becomes the inverse operation, pushed onto the opposite history) and then restores the
    // snapshots. Snapshots carry the full cell state, including its kind, so undoing and redoing
    // a hint round-trips the locked Hint cell exactly.
    ref class UndoManager
    {
    public:
        // The complete state of one cell at a moment in time.
        ref class CellState
        {
        public:
            unsigned int cellIndex;
            unsigned char value;   // 0 = empty, 1-9
            CellKind kind;
            int pencilMarks;

            CellState(unsigned int cellIndex, unsigned char value, CellKind kind, int pencilMarks)
            {
                this->cellIndex = cellIndex;
                this->value = value;
                this->kind = kind;
                this->pencilMarks = pencilMarks;
            }

            static CellState^ Capture(Board^ board, unsigned int cellIndex)
            {
                return gcnew CellState(cellIndex, board->valueAt(cellIndex),
                    board->kindAt(cellIndex), board->pencilMarksAt(cellIndex));
            }

            void applyTo(Board^ board)
            {
                board->restoreCell(this->cellIndex, this->value, this->kind, this->pencilMarks);
            }
        };

        // onChanged is invoked after every *change* to the histories (may be nullptr). It is not
        // fired from the constructor: the initial (empty) state is not a change, and firing it
        // here would call back before the caller has finished wiring itself up.
        UndoManager(System::Action^ onChanged)
        {
            this->undoStack = gcnew System::Collections::Generic::Stack<Operation^>();
            this->redoStack = gcnew System::Collections::Generic::Stack<Operation^>();
            this->pendingBatch = nullptr;
            this->onChanged = onChanged;
        }

        // True if there is at least one operation available to undo.
        property bool canUndo
        {
            bool get() { return this->undoStack->Count > 0; }
        }

        // True if there is at least one undone operation available to redo.
        property bool canRedo
        {
            bool get() { return this->redoStack->Count > 0; }
        }

        // Records the state of a cell that is about to change. Call it BEFORE mutating the
        // board. Outside a batch this is a complete operation on its own; inside a batch it is
        // collected until endBatch(). Any new operation discards the redo history.
        void record(Board^ board, unsigned int cellIndex)
        {
            CellState^ state = CellState::Capture(board, cellIndex);
            if (this->pendingBatch != nullptr)
            {
                this->pendingBatch->Add(state);
                return;
            }

            Operation^ operation = gcnew Operation();
            operation->Add(state);
            this->commit(operation);
        }

        // Opens a batch: every record() until endBatch() is undone and redone as one operation.
        void beginBatch()
        {
            this->pendingBatch = gcnew Operation();
        }

        // Closes the batch. An empty batch (nothing was recorded) is discarded without touching
        // either history, so callers can bracket a loop that may end up changing nothing.
        void endBatch()
        {
            Operation^ batch = this->pendingBatch;
            this->pendingBatch = nullptr;
            if (batch != nullptr && batch->Count > 0)
                this->commit(batch);
        }

        // Undoes the most recent operation on the board and makes it available to redo.
        // Returns the indices of the cells it restored, in the order they were restored
        // (empty if there was nothing to undo).
        System::Collections::Generic::List<unsigned int>^ undo(Board^ board)
        {
            return this->step(board, this->undoStack, this->redoStack);
        }

        // Re-applies the most recently undone operation and makes it available to undo again.
        // Returns the indices of the cells it restored (empty if there was nothing to redo).
        System::Collections::Generic::List<unsigned int>^ redo(Board^ board)
        {
            return this->step(board, this->redoStack, this->undoStack);
        }

        // Discards all undo and redo history (and any open batch).
        void clear()
        {
            this->undoStack->Clear();
            this->redoStack->Clear();
            this->pendingBatch = nullptr;
            this->notifyChanged();
        }

    private:
        typedef System::Collections::Generic::List<CellState^> Operation;

        System::Collections::Generic::Stack<Operation^>^ undoStack;
        System::Collections::Generic::Stack<Operation^>^ redoStack;
        Operation^ pendingBatch;
        System::Action^ onChanged;

        void commit(Operation^ operation)
        {
            this->undoStack->Push(operation);
            this->redoStack->Clear();
            this->notifyChanged();
        }

        // Pops an operation from one history, applies it, and pushes its inverse onto the other.
        // Snapshots are applied newest-first, so when a batch touched the same cell more than
        // once, the cell ends in its oldest recorded state. Each cell's current state is captured
        // just before it is overwritten; replaying those captures newest-first in turn restores
        // exactly the state we started from.
        System::Collections::Generic::List<unsigned int>^ step(Board^ board,
            System::Collections::Generic::Stack<Operation^>^ from,
            System::Collections::Generic::Stack<Operation^>^ to)
        {
            auto touched = gcnew System::Collections::Generic::List<unsigned int>();
            if (from->Count == 0) return touched;

            Operation^ operation = from->Pop();
            Operation^ inverse = gcnew Operation();
            for (int i = operation->Count - 1; i >= 0; --i)
            {
                CellState^ state = operation[i];
                inverse->Add(CellState::Capture(board, state->cellIndex));
                state->applyTo(board);
                touched->Add(state->cellIndex);
            }
            to->Push(inverse);

            this->notifyChanged();
            return touched;
        }

        void notifyChanged()
        {
            if (this->onChanged != nullptr) this->onChanged();
        }
    };
}
