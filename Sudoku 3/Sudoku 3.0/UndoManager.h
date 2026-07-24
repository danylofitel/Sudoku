// Danylo Fitel 2026

#pragma once
#include <climits>

namespace Sudoku_3_0
{
    // Manages the undo stack. It has no UI dependency: it raises a caller-supplied callback
    // whenever the stack changes (push, batch, pop, clear), and the caller (the form) uses
    // canUndo to sync its Undo button and menu item.
    ref class UndoManager
    {
    public:
        // A single saved cell state that can be restored by undo.
        ref class Entry
        {
        public:
            unsigned int cellIndex;
            unsigned char previousValue;   // 0 = empty, 1-9
            int previousPencilMarks;

            Entry(unsigned int cellIndex, unsigned char previousValue, int previousPencilMarks)
            {
                this->cellIndex = cellIndex;
                this->previousValue = previousValue;
                this->previousPencilMarks = previousPencilMarks;
            }
        };

        // onChanged is invoked after every *change* to the stack (may be nullptr). It is not
        // fired from the constructor: the initial (empty) state is not a change, and firing it
        // here would call back before the caller has finished wiring itself up.
        UndoManager(System::Action^ onChanged)
        {
            this->stack = gcnew System::Collections::Generic::Stack<Entry^>();
            this->onChanged = onChanged;
        }

        // True if there is at least one operation available to undo.
        property bool canUndo
        {
            bool get() { return this->stack->Count > 0; }
        }

        // Records a single-cell change.
        void push(unsigned int cellIndex, unsigned char previousValue, int previousPencilMarks)
        {
            this->stack->Push(gcnew Entry(cellIndex, previousValue, previousPencilMarks));
            this->notifyChanged();
        }

        // Opens a batch operation by pushing the bottom sentinel.
        // Must be followed by one or more push() calls and then endBatch().
        void beginBatch()
        {
            this->stack->Push(gcnew Entry(Sentinel, 0, 0));
        }

        // Closes a batch operation by pushing the top sentinel.
        void endBatch()
        {
            this->stack->Push(gcnew Entry(Sentinel, 0, 0));
            this->notifyChanged();
        }

        // Pops one logical operation (single entry or full batch).
        // Returns the entries to restore in the order they should be processed.
        // Returns an empty list if nothing is available to undo.
        System::Collections::Generic::List<Entry^>^ popOperation()
        {
            auto result = gcnew System::Collections::Generic::List<Entry^>();
            if (this->stack->Count == 0) return result;

            auto top = this->stack->Pop();

            if (top->cellIndex == Sentinel)
            {
                // Batch undo: pop all entries until the bottom sentinel
                while (this->stack->Count > 0)
                {
                    auto entry = this->stack->Pop();
                    if (entry->cellIndex == Sentinel) break;
                    result->Add(entry);
                }
            }
            else
            {
                result->Add(top);
            }

            this->notifyChanged();
            return result;
        }

        // Discards all undo history.
        void clear()
        {
            this->stack->Clear();
            this->notifyChanged();
        }

    private:
        // Sentinel cellIndex value used to bracket batch operations in the stack.
        static const unsigned int Sentinel = UINT_MAX;

        System::Collections::Generic::Stack<Entry^>^ stack;
        System::Action^ onChanged;

        void notifyChanged()
        {
            if (this->onChanged != nullptr) this->onChanged();
        }
    };
}
