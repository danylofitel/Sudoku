// Danylo Fitel 2013

#pragma once

namespace Sudoku_3_0
{
    // Detects same-value conflicts between cells and updates their background colors accordingly.
    // A cell is in conflict when another cell in the same row, column, or block contains the same digit.
    ref class ConflictDetector
    {
    private:
        array<System::Windows::Forms::Button^>^ cells;
        unsigned int sizeFactor;
        unsigned int boardSize;
        unsigned int numberOfCells;

        static const System::Drawing::Color conflictBackColor = System::Drawing::Color::Red;
        static const System::Drawing::Color conflictBackColorImmutable = System::Drawing::Color::LightCoral;
        static const System::Drawing::Color defaultBackColor = System::Drawing::SystemColors::Menu;

    public:
        ConflictDetector(
            array<System::Windows::Forms::Button^>^ cells,
            unsigned int sizeFactor)
            : cells(cells),
            sizeFactor(sizeFactor),
            boardSize(sizeFactor * sizeFactor),
            numberOfCells(sizeFactor * sizeFactor * sizeFactor * sizeFactor)
        {
            if (cells == nullptr)
            {
                throw gcnew System::ArgumentNullException("cells");
            }
            if ((unsigned int)cells->Length != this->numberOfCells)
            {
                throw gcnew System::ArgumentException(
                    System::String::Format(
                        "cells array length ({0}) does not match the expected number of cells ({1}) for sizeFactor {2}.",
                        cells->Length, this->numberOfCells, sizeFactor),
                    "cells");
            }
        }

        // Returns a bitmask of digits present in any peer of cellIndex (row, column, or block).
        // Bit N is set if digit N appears in at least one peer. Bit 0 is unused.
        int getBlockedDigits(unsigned int cellIndex)
        {
            int blocked = 0;
            const unsigned int rowIndex = cellIndex / this->boardSize;
            const unsigned int columnIndex = cellIndex % this->boardSize;

            unsigned int row = rowIndex * this->boardSize;
            unsigned int column = columnIndex;

            while (row < this->numberOfCells && column < this->numberOfCells)
            {
                if (row != cellIndex && this->cells[row]->Text->Length > 0)
                    blocked |= (1 << int::Parse(this->cells[row]->Text));
                if (column != cellIndex && column != row && this->cells[column]->Text->Length > 0)
                    blocked |= (1 << int::Parse(this->cells[column]->Text));
                row += 1;
                column += this->boardSize;
            }

            const unsigned int rBegin = (rowIndex / this->sizeFactor) * this->sizeFactor;
            const unsigned int cBegin = (columnIndex / this->sizeFactor) * this->sizeFactor;
            const unsigned int rEnd = rBegin + this->sizeFactor;
            const unsigned int cEnd = cBegin + this->sizeFactor;

            for (unsigned int i = rBegin; i < rEnd; ++i)
                for (unsigned int j = cBegin; j < cEnd; ++j)
                {
                    const unsigned int peer = i * this->boardSize + j;
                    if (peer != cellIndex && this->cells[peer]->Text->Length > 0)
                        blocked |= (1 << int::Parse(this->cells[peer]->Text));
                }

            return blocked;
        }

        // Returns true if the cell at cellIndex has a conflict with any peer in its row, column, or block.
        bool hasConflict(unsigned int cellIndex)
        {
            if (this->cells[cellIndex]->Text->Length == 0)
            {
                return false;
            }
            int digit = int::Parse(this->cells[cellIndex]->Text);
            return (getBlockedDigits(cellIndex) & (1 << digit)) != 0;
        }

        // Updates the background color of cellIndex to reflect its current conflict state.
        void highlight(unsigned int cellIndex)
        {
            if (this->hasConflict(cellIndex))
            {
                this->cells[cellIndex]->BackColor =
                    this->cells[cellIndex]->Enabled ? conflictBackColor : conflictBackColorImmutable;
            }
            else
            {
                this->cells[cellIndex]->BackColor = defaultBackColor;
            }
            this->cells[cellIndex]->Invalidate();
        }

        // Re-evaluates conflict highlighting for every cell on the board.
        void highlightAll()
        {
            for (unsigned int i = 0; i < this->numberOfCells; ++i)
            {
                this->highlight(i);
            }
        }

        // Re-evaluates conflict highlighting for cellIndex and all of its peers.
        void highlightWithPeers(unsigned int cellIndex)
        {
            this->highlight(cellIndex);

            const unsigned int rowIndex = cellIndex / this->boardSize;
            const unsigned int columnIndex = cellIndex % this->boardSize;

            unsigned int row = rowIndex * this->boardSize;
            unsigned int column = columnIndex;

            while (row < this->numberOfCells && column < this->numberOfCells)
            {
                if (row != cellIndex)
                {
                    this->highlight(row);
                }

                if (column != cellIndex && column != row)
                {
                    this->highlight(column);
                }

                row += 1;
                column += this->boardSize;
            }

            const unsigned int rBegin = (rowIndex / this->sizeFactor) * this->sizeFactor;
            const unsigned int cBegin = (columnIndex / this->sizeFactor) * this->sizeFactor;
            const unsigned int rEnd = rBegin + this->sizeFactor;
            const unsigned int cEnd = cBegin + this->sizeFactor;

            for (unsigned int i = rBegin; i < rEnd; ++i)
            {
                for (unsigned int j = cBegin; j < cEnd; ++j)
                {
                    const unsigned int peer = i * this->boardSize + j;
                    if (peer != cellIndex)
                    {
                        this->highlight(peer);
                    }
                }
            }
        }
    };
}
