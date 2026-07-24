// Danylo Fitel 2026

#pragma once

#include "CellKind.h"

namespace Sudoku_3_0
{
    // The authoritative model of the board. For each cell it holds a value (0 = empty, 1-9),
    // a kind (its provenance), and a pencil-mark bitmask. It has no dependency on the UI or the
    // engine: the form renders from it and routes user intents into it.
    //
    // All mutators go through assign(), which maintains the invariants:
    //   - value == 0  <=>  kind == UserEmpty  (UserEmpty is the only empty kind)
    //   - FilledCount always equals the number of non-empty cells
    //   - filling or revealing a cell clears its pencil marks
    ref class Board
    {
    public:
        Board(unsigned int numberOfCells)
        {
            this->values = gcnew array<unsigned char>(numberOfCells);
            this->kinds = gcnew array<CellKind>(numberOfCells);
            this->marks = gcnew array<int>(numberOfCells);
            this->filled = 0;
            this->clearToEmpty();
        }

        // ---- Queries ----

        property unsigned int Count { unsigned int get() { return (unsigned int)this->values->Length; } }
        property unsigned int FilledCount { unsigned int get() { return this->filled; } }

        unsigned char valueAt(unsigned int index) { return this->values[index]; }
        CellKind kindAt(unsigned int index) { return this->kinds[index]; }
        int pencilMarksAt(unsigned int index) { return this->marks[index]; }

        bool isEmpty(unsigned int index) { return this->values[index] == 0; }

        // Editable = the user can change it: an empty or user-filled cell (never a clue/reveal).
        bool isEditable(unsigned int index)
        {
            return this->kinds[index] == CellKind::UserEmpty || this->kinds[index] == CellKind::UserFilled;
        }

        // ---- User edits ----

        // Applies a user's choice to a cell: 1-9 fills it (UserFilled, clearing its pencil marks);
        // 0 empties it (UserEmpty, keeping any pencil marks).
        void setUserValue(unsigned int index, unsigned char value)
        {
            RequireValue(value, true);
            if (value == 0)
                this->assign(index, 0, CellKind::UserEmpty, this->marks[index]);
            else
                this->assign(index, value, CellKind::UserFilled, 0);
        }

        // Toggles a pencil mark (digit 1-9) on an empty, editable cell; a no-op anywhere else.
        void togglePencilMark(unsigned int index, int digit)
        {
            if (digit < 1 || digit > 9) return;
            if (!this->isEditable(index) || !this->isEmpty(index)) return;
            this->marks[index] ^= (1 << digit);
        }

        // ---- Puzzle setup / reveals / locking ----

        // Marks a cell as an immutable engine clue with the given value (1-9).
        void setClue(unsigned int index, unsigned char value)
        {
            RequireValue(value, false);
            this->assign(index, value, CellKind::Clue, 0);
        }

        // Empties a cell into an editable state, discarding any pencil marks.
        void setEmpty(unsigned int index)
        {
            this->assign(index, 0, CellKind::UserEmpty, 0);
        }

        // Reveals a cell's value as a locked, non-editable cell. kind must be Hint, GivenUp, or Solved.
        void reveal(unsigned int index, unsigned char value, CellKind kind)
        {
            RequireValue(value, false);
            if (kind != CellKind::Hint && kind != CellKind::GivenUp && kind != CellKind::Solved)
                throw gcnew System::ArgumentException("reveal expects a Hint, GivenUp or Solved kind.");
            this->assign(index, value, kind, 0);
        }

        // Locks an already-filled cell as confirmed-correct (on win), keeping its value.
        void lockAsCorrect(unsigned int index)
        {
            if (this->isEmpty(index))
                throw gcnew System::InvalidOperationException("Cannot lock an empty cell as correct.");
            this->assign(index, this->values[index], CellKind::Correct, 0);
        }

        // Restores an editable cell to a previous value and pencil marks (for undo). The kind
        // follows from the value: UserFilled if non-empty, otherwise UserEmpty.
        void restoreUserCell(unsigned int index, unsigned char value, int pencilMarks)
        {
            RequireValue(value, true);
            CellKind kind = value == 0 ? CellKind::UserEmpty : CellKind::UserFilled;
            this->assign(index, value, kind, pencilMarks);
        }

        // ---- Bulk operations ----

        // Resets every cell from a clues array: non-zero -> immutable clue, zero -> empty.
        void resetToClues(array<unsigned char>^ clues)
        {
            for (unsigned int i = 0; i < this->Count; ++i)
            {
                if (clues[i] != 0) this->setClue(i, clues[i]);
                else this->setEmpty(i);
            }
        }

        // Clears the whole board to empty, editable cells with no pencil marks.
        void clearToEmpty()
        {
            for (unsigned int i = 0; i < (unsigned int)this->values->Length; ++i)
                this->assign(i, 0, CellKind::UserEmpty, 0);
        }

        // ---- Serialization helpers (used by save/load) ----

        array<unsigned char>^ copyValues()
        {
            return safe_cast<array<unsigned char>^>(this->values->Clone());
        }

        // Cell kinds as their numeric state codes.
        array<unsigned char>^ copyStates()
        {
            array<unsigned char>^ states = gcnew array<unsigned char>(this->values->Length);
            for (int i = 0; i < states->Length; ++i)
                states[i] = static_cast<unsigned char>(this->kinds[i]);
            return states;
        }

        array<int>^ copyPencilMarks()
        {
            return safe_cast<array<int>^>(this->marks->Clone());
        }

        // Bulk-restores the board from saved arrays (values, state codes, pencil marks).
        // Inputs are assumed already validated (e.g. by SaveGameStore::Load).
        void restoreFrom(array<unsigned char>^ values, array<unsigned char>^ states, array<int>^ pencilMarks)
        {
            for (unsigned int i = 0; i < this->Count; ++i)
                this->assign(i, values[i], static_cast<CellKind>(states[i]), pencilMarks[i]);
        }

    private:
        array<unsigned char>^ values;
        array<CellKind>^ kinds;
        array<int>^ marks;
        unsigned int filled;

        // The single mutation point: writes a cell and keeps FilledCount consistent.
        void assign(unsigned int index, unsigned char value, CellKind kind, int pencilMarks)
        {
            unsigned char previous = this->values[index];
            this->values[index] = value;
            this->kinds[index] = kind;
            this->marks[index] = pencilMarks;

            if (previous == 0 && value != 0) ++this->filled;
            else if (previous != 0 && value == 0) --this->filled;
        }

        // Validates a cell value: 0-9 when allowEmpty, otherwise 1-9.
        static void RequireValue(unsigned char value, bool allowEmpty)
        {
            unsigned char minValue = allowEmpty ? (unsigned char)0 : (unsigned char)1;
            if (value < minValue || value > 9)
                throw gcnew System::ArgumentOutOfRangeException("value", "Cell value must be 1-9" +
                    (allowEmpty ? gcnew System::String(" or 0 for empty.") : gcnew System::String(".")));
        }
    };
}
