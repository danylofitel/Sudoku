// Danylo Fitel 2026

#pragma once
#include <climits>

namespace Sudoku_3_0
{
    // Manages the undo stack and keeps the undo button and menu item in sync.
    // Every push, beginBatch/endBatch, and clear automatically reflects in the UI controls,
    // so call sites never need to touch Enabled directly.
    ref class UndoManager
    {
    public:
        // A single saved cell state that can be restored by undo.
        ref class Entry
        {
        public:
            unsigned int cellIndex;
            System::String^ previousText;
            int previousPencilMarks;

            Entry(unsigned int cellIndex, System::String^ previousText, int previousPencilMarks)
            {
                this->cellIndex = cellIndex;
                this->previousText = previousText;
                this->previousPencilMarks = previousPencilMarks;
            }
        };

        UndoManager(
            System::Windows::Forms::Button^ button,
            System::Windows::Forms::ToolStripMenuItem^ menuItem)
        {
            this->stack = gcnew System::Collections::Generic::Stack<Entry^>();
            this->button = button;
            this->menuItem = menuItem;
            this->syncControls();
        }

        // True if there is at least one operation available to undo.
        property bool canUndo
        {
            bool get() { return this->stack->Count > 0; }
        }

        // Records a single-cell change and enables the undo controls.
        void push(unsigned int cellIndex, System::String^ previousText, int previousPencilMarks)
        {
            this->stack->Push(gcnew Entry(cellIndex, previousText, previousPencilMarks));
            this->syncControls();
        }

        // Opens a batch operation by pushing the bottom sentinel.
        // Must be followed by one or more push() calls and then endBatch().
        void beginBatch()
        {
            this->stack->Push(gcnew Entry(Sentinel, System::String::Empty, 0));
        }

        // Closes a batch operation by pushing the top sentinel and enabling the undo controls.
        void endBatch()
        {
            this->stack->Push(gcnew Entry(Sentinel, System::String::Empty, 0));
            this->syncControls();
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

            this->syncControls();
            return result;
        }

        // Discards all undo history and disables the undo controls.
        void clear()
        {
            this->stack->Clear();
            this->syncControls();
        }

    private:
        // Sentinel cellIndex value used to bracket batch operations in the stack.
        static const unsigned int Sentinel = UINT_MAX;

        System::Collections::Generic::Stack<Entry^>^ stack;
        System::Windows::Forms::Button^ button;
        System::Windows::Forms::ToolStripMenuItem^ menuItem;

        void syncControls()
        {
            bool hasEntries = this->stack->Count > 0;
            this->button->Enabled = hasEntries;
            this->menuItem->Enabled = hasEntries;
        }
    };
}
