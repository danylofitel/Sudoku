// Danylo Fitel 2026

#pragma once

#include "Board.h"

namespace Sudoku_3_0
{
    // Pure Sudoku conflict logic over a Board: a cell conflicts when a peer in the same row,
    // column, or block holds the same digit. It reads the board only and returns answers; it
    // does no rendering, so the form owns all painting.
    ref class ConflictDetector
    {
    private:
        Board^ board;
        unsigned int sizeFactor;
        unsigned int boardSize;
        unsigned int numberOfCells;

        // Returns the digit bit for a peer cell (0 if it is the cell itself or empty).
        int digitBit(unsigned int peerIndex, unsigned int selfIndex)
        {
            if (peerIndex == selfIndex) return 0;
            unsigned char value = this->board->valueAt(peerIndex);
            return value == 0 ? 0 : (1 << value);
        }

    public:
        ConflictDetector(Board^ board, unsigned int sizeFactor)
            : board(board),
            sizeFactor(sizeFactor),
            boardSize(sizeFactor* sizeFactor),
            numberOfCells(boardSize* boardSize)
        {
            if (board == nullptr)
                throw gcnew System::ArgumentNullException("board");
            if (board->Count != this->numberOfCells)
                throw gcnew System::ArgumentException(
                    System::String::Format(
                        "board cell count ({0}) does not match the expected count ({1}) for sizeFactor {2}.",
                        board->Count, this->numberOfCells, sizeFactor),
                    "board");
        }

        // Returns a bitmask of digits present in any peer of cellIndex (row, column, or block).
        // Bit N is set if digit N appears in at least one peer. Bit 0 is unused.
        int getBlockedDigits(unsigned int cellIndex)
        {
            int blocked = 0;
            const unsigned int row = cellIndex / this->boardSize;
            const unsigned int column = cellIndex % this->boardSize;

            for (unsigned int c = 0; c < this->boardSize; ++c)
                blocked |= this->digitBit(row * this->boardSize + c, cellIndex);
            for (unsigned int r = 0; r < this->boardSize; ++r)
                blocked |= this->digitBit(r * this->boardSize + column, cellIndex);

            const unsigned int rBegin = (row / this->sizeFactor) * this->sizeFactor;
            const unsigned int cBegin = (column / this->sizeFactor) * this->sizeFactor;
            for (unsigned int r = rBegin; r < rBegin + this->sizeFactor; ++r)
                for (unsigned int c = cBegin; c < cBegin + this->sizeFactor; ++c)
                    blocked |= this->digitBit(r * this->boardSize + c, cellIndex);

            return blocked;
        }

        // True if the cell has a conflict with any peer in its row, column, or block.
        bool hasConflict(unsigned int cellIndex)
        {
            unsigned char value = this->board->valueAt(cellIndex);
            if (value == 0) return false;
            return (this->getBlockedDigits(cellIndex) & (1 << value)) != 0;
        }

        // Returns the indices of every peer of cellIndex (its row, column, and block, excluding
        // the cell itself). Used by the form to know which cells to re-render when a change may
        // have altered their conflict state. A handful of indices repeat where the row/column
        // cross the block; that is harmless, since re-rendering a cell is idempotent.
        array<unsigned int>^ peersOf(unsigned int cellIndex)
        {
            System::Collections::Generic::List<unsigned int>^ peers =
                gcnew System::Collections::Generic::List<unsigned int>();

            const unsigned int row = cellIndex / this->boardSize;
            const unsigned int column = cellIndex % this->boardSize;

            for (unsigned int c = 0; c < this->boardSize; ++c)
                this->addPeer(peers, row * this->boardSize + c, cellIndex);
            for (unsigned int r = 0; r < this->boardSize; ++r)
                this->addPeer(peers, r * this->boardSize + column, cellIndex);

            const unsigned int rBegin = (row / this->sizeFactor) * this->sizeFactor;
            const unsigned int cBegin = (column / this->sizeFactor) * this->sizeFactor;
            for (unsigned int r = rBegin; r < rBegin + this->sizeFactor; ++r)
                for (unsigned int c = cBegin; c < cBegin + this->sizeFactor; ++c)
                    this->addPeer(peers, r * this->boardSize + c, cellIndex);

            return peers->ToArray();
        }

    private:
        void addPeer(System::Collections::Generic::List<unsigned int>^ peers,
            unsigned int peerIndex, unsigned int selfIndex)
        {
            if (peerIndex != selfIndex) peers->Add(peerIndex);
        }
    };
}
