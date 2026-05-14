// Danylo Fitel 2013
// Optimized Sudoku engine - bitset constraint tracking, recursive backtracking

#ifndef _SUDOKU_ENGINE_OPTIMIZED_H_
#define _SUDOKU_ENGINE_OPTIMIZED_H_

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <exception>
#include <iostream>
#include <limits>
#include <time.h>

#include "SudokuEngine.h"

#ifdef _MSC_VER
#include <intrin.h>
#define POPCOUNT(x) __popcnt(x)
#define CTZ(x)      _tzcnt_u32(x)
#elif defined(__GNUC__)
#define POPCOUNT(x) __builtin_popcount(x)
#define CTZ(x)      __builtin_ctz(x)
#else
inline int POPCOUNT(uint32_t x) { int n = 0; while (x) { ++n; x &= x-1; } return n; }
inline int CTZ(uint32_t x) { int n = 0; while (!(x & 1)) { x >>= 1; ++n; } return n; }
#endif

namespace SudokuGameEngine
{
    template <typename IndexType = unsigned char, IndexType sizeFactor = 3>
    class SudokuEngineOptimized
    {
        static const IndexType  boardSize     = sizeFactor * sizeFactor;
        static const IndexType  numberOfCells = boardSize * boardSize;
        static const uint16_t   allValuesMask = (1 << boardSize) - 1;

    public:
        static const IndexType sizeOfTheBlock()     { return sizeFactor;    }
        static const IndexType sizeOfTheBoard()     { return boardSize;     }
        static const IndexType numberOfBoardCells() { return numberOfCells; }

        SudokuEngineOptimized()
        {
            static_assert(std::numeric_limits<IndexType>::is_integer,  "IndexType must be integer");
            static_assert(!std::numeric_limits<IndexType>::is_signed,  "IndexType must be unsigned");
            static_assert(sizeFactor > 1,                              "sizeFactor must be > 1");
            static_assert(boardSize > sizeFactor && numberOfCells > boardSize, "IndexType too small");
            srand(static_cast<unsigned int>(time(nullptr)));
            reset();
        }

        SudokuEngineOptimized(const SudokuEngineOptimized& other) { copyFrom(other); }
        ~SudokuEngineOptimized() {}

        SudokuEngineOptimized& operator=(const SudokuEngineOptimized& other)
        {
            if (this != &other) copyFrom(other);
            return *this;
        }

        const IndexType operator()(const IndexType row, const IndexType column) const
        {
            validateCoords(row, column);
            return _board[row][column];
        }

        const bool getFilled(const IndexType row, const IndexType column) const
        {
            validateCoords(row, column);
            return _board[row][column] != 0;
        }

        void setFilled(const IndexType row, const IndexType column, const bool filled)
        {
            validateCoords(row, column);
            bool isFilled = _board[row][column] != 0;
            if (isFilled != filled)
            {
                if (filled && _board[row][column] != 0) { addConstraint(row, column, _board[row][column]); ++_filledCount; }
                else if (!filled && _board[row][column] != 0) { removeConstraint(row, column, _board[row][column]); --_filledCount; _board[row][column] = 0; }
            }
            _solutions = 0; _state = SudokuEngineState::BeingEdited;
        }

        const IndexType getCellValue(const IndexType row, const IndexType column) const
        {
            validateCoords(row, column);
            return _board[row][column];
        }

        void setCellValue(const IndexType row, const IndexType column, const IndexType value)
        {
            if (row >= boardSize || column >= boardSize || value > boardSize)
                throw std::invalid_argument("Cell modifier arguments out of range");
            IndexType old = _board[row][column];
            if (old != 0)   { removeConstraint(row, column, old);   --_filledCount; }
            _board[row][column] = value;
            if (value != 0) { addConstraint(row, column, value); ++_filledCount; }
            _solutions = 0; _state = SudokuEngineState::BeingEdited;
        }

        void clear() { reset(); }

        const bool showSolution()
        {
            SudokuEngineState state = currentState();
            if ((state == SudokuEngineState::HasUniqueSolution || state == SudokuEngineState::NewGame) &&
                state != SudokuEngineState::FilledValid)
            {
                _filledCount = numberOfCells;
                _state = SudokuEngineState::FilledValid;
                return true;
            }
            return false;
        }

        const SudokuEngineState getCurrentState() const { return _state; }

        const SudokuEngineState currentState()
        {
            if (_state != SudokuEngineState::BeingEdited) return _state;
            if (_filledCount == 0)
                _state = SudokuEngineState::Empty;
            else if (_filledCount == numberOfCells)
                _state = noConflictsExist() ? SudokuEngineState::FilledValid : SudokuEngineState::FilledInvalid;
            else if (!noConflictsExist())
                _state = SudokuEngineState::HasNoSolution;
            else
            {
                IndexType sol = countSolutions(2);
                if      (sol == 0) _state = SudokuEngineState::HasNoSolution;
                else if (sol == 1) _state = SudokuEngineState::HasUniqueSolution;
                else               _state = SudokuEngineState::HasMultipleSolutions;
            }
            return _state;
        }

        const SudokuEngineState trySolve()
        {
            SudokuEngineState state = currentState();
            if (state == SudokuEngineState::HasUniqueSolution || state == SudokuEngineState::NewGame)
            {
                assert(_filledCount < numberOfCells);
                bool ok = solve();
                assert(ok);
                assert(_filledCount == numberOfCells);
                assert(noConflictsExist());
                _solutions = 1;
                _state = SudokuEngineState::FilledValid;
            }
            return _state;
        }

        const IndexType numberOfFilledCells() const { return _filledCount; }
        const IndexType numberOfFreeCells()   const { return numberOfCells - _filledCount; }

        const SudokuEngineState newCombination()
        {
            reset();
            generateFull();
            assert(_filledCount == numberOfCells);
            assert(noConflictsExist());
            return _state;
        }

        const bool newGame(const DifficultyLevel difficulty)
        {
            newCombination();
            IndexType minHide, maxHide;
            switch (difficulty)
            {
                case DifficultyLevel::VeryEasy: minHide = 20; maxHide = 30; break;
                case DifficultyLevel::Easy:     minHide = 30; maxHide = 40; break;
                case DifficultyLevel::Medium:   minHide = 40; maxHide = 50; break;
                case DifficultyLevel::Hard:     minHide = 50; maxHide = 55; break;
                case DifficultyLevel::VeryHard: minHide = 55; maxHide = 60; break;
                default:                        minHide = 40; maxHide = 50; break;
            }
            IndexType toHide = static_cast<IndexType>(rand() % (maxHide - minHide + 1)) + minHide;
            return hideCells(toHide);
        }

    private:
        IndexType         _board[boardSize][boardSize]; // 0 = empty, 1-9 = filled
        mutable uint16_t  _rowUsed[boardSize];
        mutable uint16_t  _colUsed[boardSize];
        mutable uint16_t  _boxUsed[boardSize];
        IndexType         _filledCount;
        IndexType         _solutions;
        SudokuEngineState _state;

        __forceinline IndexType box(IndexType r, IndexType c) const
        {
            return static_cast<IndexType>((r / sizeFactor) * sizeFactor + (c / sizeFactor));
        }

        __forceinline uint16_t candidates(IndexType r, IndexType c) const
        {
            return (~(_rowUsed[r] | _colUsed[c] | _boxUsed[box(r, c)])) & allValuesMask;
        }

        __forceinline void addConstraint(IndexType r, IndexType c, IndexType v)
        {
            uint16_t mask = static_cast<uint16_t>(1 << (v - 1));
            _rowUsed[r] |= mask; _colUsed[c] |= mask; _boxUsed[box(r, c)] |= mask;
        }

        __forceinline void removeConstraint(IndexType r, IndexType c, IndexType v)
        {
            uint16_t mask = static_cast<uint16_t>(1 << (v - 1));
            _rowUsed[r] &= ~mask; _colUsed[c] &= ~mask; _boxUsed[box(r, c)] &= ~mask;
        }

        __forceinline void place(IndexType r, IndexType c, IndexType v)
        {
            _board[r][c] = v; addConstraint(r, c, v); ++_filledCount;
        }

        __forceinline void unplace(IndexType r, IndexType c)
        {
            removeConstraint(r, c, _board[r][c]); _board[r][c] = 0; --_filledCount;
        }

        void validateCoords(IndexType r, IndexType c) const
        {
            if (r >= boardSize || c >= boardSize)
                throw std::invalid_argument("Cell selector arguments out of range");
        }

        void reset()
        {
            for (IndexType i = 0; i < boardSize; ++i)
            {
                for (IndexType j = 0; j < boardSize; ++j) _board[i][j] = 0;
                _rowUsed[i] = _colUsed[i] = _boxUsed[i] = 0;
            }
            _filledCount = 0; _solutions = 0; _state = SudokuEngineState::Empty;
        }

        void copyFrom(const SudokuEngineOptimized& o)
        {
            for (IndexType i = 0; i < boardSize; ++i)
            {
                for (IndexType j = 0; j < boardSize; ++j) _board[i][j] = o._board[i][j];
                _rowUsed[i] = o._rowUsed[i]; _colUsed[i] = o._colUsed[i]; _boxUsed[i] = o._boxUsed[i];
            }
            _filledCount = o._filledCount; _solutions = o._solutions; _state = o._state;
        }

        bool noConflictsExist() const
        {
            for (IndexType i = 0; i < boardSize; ++i)
                for (IndexType j = 0; j < boardSize; ++j)
                    if (_board[i][j] != 0)
                    {
                        uint16_t mask = static_cast<uint16_t>(1 << (_board[i][j] - 1));
                        _rowUsed[i] &= ~mask; _colUsed[j] &= ~mask; _boxUsed[box(i,j)] &= ~mask;
                        bool ok = ((_rowUsed[i] | _colUsed[j] | _boxUsed[box(i,j)]) & mask) == 0;
                        _rowUsed[i] |= mask;  _colUsed[j] |= mask;  _boxUsed[box(i,j)] |= mask;
                        if (!ok) return false;
                    }
            return true;
        }

        // MRV: find empty cell with fewest candidates
        bool bestCell(IndexType& br, IndexType& bc) const
        {
            int minCount = boardSize + 1; bool found = false;
            for (IndexType i = 0; i < boardSize; ++i)
                for (IndexType j = 0; j < boardSize; ++j)
                    if (_board[i][j] == 0)
                    {
                        int cnt = POPCOUNT(candidates(i, j));
                        if (cnt < minCount) { minCount = cnt; br = i; bc = j; found = true; if (cnt == 0) return true; }
                    }
            return found;
        }

        // Recursive solver - fills the board with the unique solution
        bool solve()
        {
            if (_filledCount == numberOfCells) return true;
            IndexType r = 0, c = 0;
            bestCell(r, c);
            for (uint16_t cands = candidates(r, c); cands; cands &= cands - 1)
            {
                place(r, c, static_cast<IndexType>(CTZ(cands) + 1));
                if (solve()) return true;
                unplace(r, c);
            }
            return false;
        }

        // Count solutions, stopping early at `limit`
        IndexType countSolutions(IndexType limit)
        {
            if (_filledCount == numberOfCells) return 1;
            IndexType r = 0, c = 0;
            if (!bestCell(r, c)) return 0;
            uint16_t cands = candidates(r, c);
            if (cands == 0) return 0;
            IndexType total = 0;
            while (cands && total < limit)
            {
                place(r, c, static_cast<IndexType>(CTZ(cands) + 1));
                cands &= cands - 1;
                total += countSolutions(static_cast<IndexType>(limit - total));
                unplace(r, c);
            }
            return total;
        }

        // Randomised board fill for newCombination
        bool generateFull()
        {
            if (_filledCount == numberOfCells) { _solutions = 1; _state = SudokuEngineState::FilledValid; return true; }
            IndexType r = 0, c = 0;
            for (IndexType i = 0; i < numberOfCells; ++i)
                if (_board[i / boardSize][i % boardSize] == 0) { r = i / boardSize; c = i % boardSize; break; }

            // Collect candidates into a small array and shuffle
            uint16_t cands = candidates(r, c);
            IndexType vals[boardSize]; int n = 0;
            for (uint16_t tmp = cands; tmp; tmp &= tmp - 1) vals[n++] = static_cast<IndexType>(CTZ(tmp) + 1);
            for (int i = n - 1; i > 0; --i) { int j = rand() % (i + 1); IndexType t = vals[i]; vals[i] = vals[j]; vals[j] = t; }

            for (int i = 0; i < n; ++i)
            {
                place(r, c, vals[i]);
                if (generateFull()) return true;
                unplace(r, c);
            }
            return false;
        }

        // Hide cells one by one, checking uniqueness after each removal
        bool hideCells(IndexType toHide)
        {
            // Shuffle all cell indices
            IndexType order[numberOfCells];
            for (IndexType i = 0; i < numberOfCells; ++i) order[i] = i;
            for (IndexType i = numberOfCells - 1; i > 0; --i)
            {
                IndexType j = static_cast<IndexType>(rand() % (i + 1));
                IndexType t = order[i]; order[i] = order[j]; order[j] = t;
            }

            IndexType hidden = 0;
            for (IndexType i = 0; i < numberOfCells && hidden < toHide; ++i)
            {
                IndexType r = order[i] / boardSize, c = order[i] % boardSize;
                if (_board[r][c] == 0) continue;
                IndexType saved = _board[r][c];
                unplace(r, c);
                if (countSolutions(2) == 1) { ++hidden; }
                else { place(r, c, saved); }
            }

            assert(countSolutions(2) == 1);
            _solutions = 1; _state = SudokuEngineState::NewGame;
            return hidden == toHide;
        }
    };

    template <typename IndexType, IndexType sizeFactor>
    std::ostream& operator<<(std::ostream& os, const SudokuEngineOptimized<IndexType, sizeFactor>& e)
    {
        os << "Current state: " << e.getCurrentState() << "\n"
           << "Total number of cells: "  << (unsigned int)e.numberOfBoardCells()  << "\n"
           << "Number of filled cells: " << (unsigned int)e.numberOfFilledCells() << "\n"
           << "Number of free cells: "   << (unsigned int)e.numberOfFreeCells()   << "\n\n";
        for (IndexType i = 0; i < e.sizeOfTheBoard(); ++i)
        {
            for (IndexType j = 0; j < e.sizeOfTheBoard(); ++j)
                os << static_cast<unsigned int>(e(i, j)) << ", ";
            os << "\n";
        }
        return os;
    }
}

#endif