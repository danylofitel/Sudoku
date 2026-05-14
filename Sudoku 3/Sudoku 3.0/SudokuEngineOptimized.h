// Danylo Fitel 2013
// Optimized Sudoku engine - bitset constraint tracking, recursive backtracking
// with constraint propagation (naked + hidden singles) and incremental
// empty-cell tracking.

#ifndef _SUDOKU_ENGINE_OPTIMIZED_H_
#define _SUDOKU_ENGINE_OPTIMIZED_H_

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <iostream>
#include <limits>
#include <random>

#include "SudokuEngine.h"

#ifdef _MSC_VER
#include <intrin.h>
#define POPCOUNT(x) __popcnt(x)
#define CTZ(x)      _tzcnt_u32(x)
inline int CTZ64(uint64_t x)
{
#if defined(_M_X64) || defined(_M_ARM64)
    unsigned long idx;
    _BitScanForward64(&idx, x);
    return static_cast<int>(idx);
#else
    unsigned long idx;
    if (_BitScanForward(&idx, static_cast<uint32_t>(x)))
        return static_cast<int>(idx);
    _BitScanForward(&idx, static_cast<uint32_t>(x >> 32));
    return static_cast<int>(idx) + 32;
#endif
}
#elif defined(__GNUC__)
#define POPCOUNT(x) __builtin_popcount(x)
#define CTZ(x)      __builtin_ctz(x)
#define CTZ64(x)    __builtin_ctzll(x)
#else
inline int POPCOUNT(uint32_t x) { int n = 0; while (x) { ++n; x &= x - 1; } return n; }
inline int CTZ(uint32_t x) { int n = 0; while (!(x & 1)) { x >>= 1; ++n; } return n; }
inline int CTZ64(uint64_t x) { int n = 0; while (!(x & 1)) { x >>= 1; ++n; } return n; }
#endif

namespace SudokuGameEngine
{
    namespace detail
    {
        // Fast, unbiased-enough RNG. Replaces rand(), which on MSVC takes a
        // critical section and is per-thread-process-global state.
        class XorShift32
        {
            uint32_t _state;
        public:
            explicit XorShift32(uint32_t seed = 0x9E3779B9u)
                : _state(seed ? seed : 0x9E3779B9u) {}

            uint32_t next()
            {
                uint32_t x = _state;
                x ^= x << 13;
                x ^= x >> 17;
                x ^= x << 5;
                _state = x;
                return x;
            }

            // Returns a value in [0, n). n must be > 0.
            uint32_t bounded(uint32_t n) { return next() % n; }
        };

        inline uint32_t makeSeed(const void* salt)
        {
            static std::random_device rd;
            uint64_t mix = static_cast<uint64_t>(rd());
            mix ^= static_cast<uint64_t>(
                std::chrono::high_resolution_clock::now().time_since_epoch().count());
            mix ^= reinterpret_cast<std::uintptr_t>(salt);
            mix ^= mix >> 32;
            uint32_t s = static_cast<uint32_t>(mix * 0x9E3779B1u);
            return s ? s : 0x9E3779B9u;
        }
    }

    template <typename IndexType = unsigned char, IndexType sizeFactor = 3>
    class SudokuEngineOptimized
    {
        static const IndexType   boardSize = sizeFactor * sizeFactor;
        static const IndexType   numberOfCells = boardSize * boardSize;
        static const uint16_t    allValuesMask = static_cast<uint16_t>((1u << boardSize) - 1u);
        static const std::size_t emptyMaskWords = (static_cast<std::size_t>(boardSize) * boardSize + 63) / 64;

    public:
        static const IndexType sizeOfTheBlock() { return sizeFactor; }
        static const IndexType sizeOfTheBoard() { return boardSize; }
        static const IndexType numberOfBoardCells() { return numberOfCells; }

        SudokuEngineOptimized()
            : _filledCount(0), _solutions(0), _state(SudokuEngineState::Empty),
            _capturedFirst(false), _rng(detail::makeSeed(this))
        {
            static_assert(std::numeric_limits<IndexType>::is_integer, "IndexType must be integer");
            static_assert(!std::numeric_limits<IndexType>::is_signed, "IndexType must be unsigned");
            static_assert(sizeFactor > 1, "sizeFactor must be > 1");
            // Catch numberOfCells overflow: e.g. sizeFactor=5 with unsigned char wraps from 625 to 113.
            static_assert(
                static_cast<std::size_t>(sizeFactor) * sizeFactor * sizeFactor * sizeFactor
                == static_cast<std::size_t>(numberOfCells),
                "IndexType too small: numberOfCells overflows");
            static_assert(boardSize > sizeFactor && numberOfCells > boardSize, "IndexType too small");
            static_assert(static_cast<unsigned>(boardSize) <= 16,
                "boardSize > 16 unsupported (uint16_t candidate masks)");
            reset();
        }

        SudokuEngineOptimized(const SudokuEngineOptimized& other)
            : _capturedFirst(false), _rng(detail::makeSeed(this))
        {
            copyFrom(other);
        }
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

        // setFilled(false) clears a cell. setFilled(true) is a no-op:
        // the optimized engine has no separate filled bit - value 0 means empty.
        // A cell becomes "filled" when setCellValue is called with a non-zero value.
        void setFilled(const IndexType row, const IndexType column, const bool filled)
        {
            validateCoords(row, column);
            if (!filled) _board[row][column] = 0;
            _solutions = 0;
            _state = SudokuEngineState::BeingEdited;
        }

        const IndexType getCellValue(const IndexType row, const IndexType column) const
        {
            validateCoords(row, column);
            return _board[row][column];
        }

        // Values are stored directly. Mask caches are NOT updated incrementally here
        // (a user-driven sequence can introduce conflicts that corrupt incremental
        // masks); they are rebuilt from _board on the next state-checking call.
        void setCellValue(const IndexType row, const IndexType column, const IndexType value)
        {
            if (row >= boardSize || column >= boardSize || value > boardSize)
                throw std::invalid_argument("Cell modifier arguments out of range");
            _board[row][column] = value;
            _solutions = 0;
            _state = SudokuEngineState::BeingEdited;
        }

        void clear() { reset(); }

        const bool showSolution()
        {
            const SudokuEngineState state = currentState();
            if (state == SudokuEngineState::NewGame || state == SudokuEngineState::HasUniqueSolution)
            {
                if (_filledCount < numberOfCells)
                {
                    const bool ok = solve();
                    assert(ok); (void)ok;
                }
                _solutions = 1;
                _state = SudokuEngineState::FilledValid;
                return true;
            }
            return false;
        }

        const SudokuEngineState getCurrentState() const { return _state; }

        const SudokuEngineState currentState()
        {
            if (_state != SudokuEngineState::BeingEdited) return _state;
            syncFromBoard();
            if (_filledCount == 0)
                _state = SudokuEngineState::Empty;
            else if (_filledCount == numberOfCells)
                _state = noConflictsExist() ? SudokuEngineState::FilledValid : SudokuEngineState::FilledInvalid;
            else if (!noConflictsExist())
                _state = SudokuEngineState::HasNoSolution;
            else
            {
                _capturedFirst = false;
                const IndexType sol = countSolutionsImpl(2, nullptr);
                if (sol == 0) _state = SudokuEngineState::HasNoSolution;
                else if (sol == 1) _state = SudokuEngineState::HasUniqueSolution;
                else               _state = SudokuEngineState::HasMultipleSolutions;
            }
            return _state;
        }

        const SudokuEngineState trySolve()
        {
            if (_state == SudokuEngineState::BeingEdited)
            {
                syncFromBoard();
                if (_filledCount == 0)
                    _state = SudokuEngineState::Empty;
                else if (_filledCount == numberOfCells)
                    _state = noConflictsExist() ? SudokuEngineState::FilledValid : SudokuEngineState::FilledInvalid;
                else if (!noConflictsExist())
                    _state = SudokuEngineState::HasNoSolution;
                else
                {
                    // Unified search: find first solution AND check uniqueness in one pass.
                    // The previous code did this in two passes (countSolutions then solve).
                    IndexType firstSolution[boardSize][boardSize] = {};
                    _capturedFirst = false;
                    const IndexType count = countSolutionsImpl(2, firstSolution);
                    if (count == 0)
                        _state = SudokuEngineState::HasNoSolution;
                    else if (count >= 2)
                        _state = SudokuEngineState::HasMultipleSolutions;
                    else
                    {
                        for (IndexType r = 0; r < boardSize; ++r)
                            for (IndexType c = 0; c < boardSize; ++c)
                                if (_board[r][c] == 0)
                                    place(r, c, firstSolution[r][c]);
                        _solutions = 1;
                        _state = SudokuEngineState::FilledValid;
                    }
                }
            }
            // NewGame or HasUniqueSolution (left over from a prior currentState call):
            // the puzzle is known solvable - just fill in the solution.
            if (_state == SudokuEngineState::NewGame || _state == SudokuEngineState::HasUniqueSolution)
            {
                if (_filledCount < numberOfCells)
                {
                    const bool ok = solve();
                    assert(ok); (void)ok;
                }
                assert(_filledCount == numberOfCells);
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
            generateFull(0);
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
            const IndexType toHide = static_cast<IndexType>(
                _rng.bounded(static_cast<uint32_t>(maxHide - minHide + 1)) + minHide);
            return hideCells(toHide);
        }

    private:
        IndexType         _board[boardSize][boardSize];    // 0 = empty, 1..boardSize = filled
        uint16_t          _rowUsed[boardSize];
        uint16_t          _colUsed[boardSize];
        uint16_t          _boxUsed[boardSize];
        uint64_t          _emptyMask[emptyMaskWords];      // bit per cell, set iff empty
        IndexType         _filledCount;
        IndexType         _solutions;
        SudokuEngineState _state;
        bool              _capturedFirst;                  // set by countSolutionsImpl during recursion
        detail::XorShift32 _rng;

        struct BoxLUT { IndexType data[boardSize][boardSize]; };
        static const BoxLUT& boxLUT()
        {
            static const BoxLUT lut = []() {
                BoxLUT t = {};
                for (IndexType i = 0; i < boardSize; ++i)
                    for (IndexType j = 0; j < boardSize; ++j)
                        t.data[i][j] = static_cast<IndexType>(
                            (i / sizeFactor) * sizeFactor + (j / sizeFactor));
                return t;
                }();
            return lut;
        }

        __forceinline IndexType boxOf(IndexType r, IndexType c) const
        {
            return boxLUT().data[r][c];
        }

        __forceinline uint16_t candidates(IndexType r, IndexType c) const
        {
            return static_cast<uint16_t>(
                ~(_rowUsed[r] | _colUsed[c] | _boxUsed[boxOf(r, c)]) & allValuesMask);
        }

        __forceinline void addConstraint(IndexType r, IndexType c, IndexType v)
        {
            const uint16_t mask = static_cast<uint16_t>(1u << (v - 1));
            _rowUsed[r] |= mask;
            _colUsed[c] |= mask;
            _boxUsed[boxOf(r, c)] |= mask;
        }

        __forceinline void removeConstraint(IndexType r, IndexType c, IndexType v)
        {
            const uint16_t mask = static_cast<uint16_t>(1u << (v - 1));
            _rowUsed[r] = static_cast<uint16_t>(_rowUsed[r] & ~mask);
            _colUsed[c] = static_cast<uint16_t>(_colUsed[c] & ~mask);
            _boxUsed[boxOf(r, c)] = static_cast<uint16_t>(_boxUsed[boxOf(r, c)] & ~mask);
        }

        __forceinline void place(IndexType r, IndexType c, IndexType v)
        {
            _board[r][c] = v;
            addConstraint(r, c, v);
            const std::size_t idx = static_cast<std::size_t>(r) * boardSize + c;
            _emptyMask[idx >> 6] &= ~(uint64_t(1) << (idx & 63));
            ++_filledCount;
        }

        __forceinline void unplace(IndexType r, IndexType c)
        {
            removeConstraint(r, c, _board[r][c]);
            _board[r][c] = 0;
            const std::size_t idx = static_cast<std::size_t>(r) * boardSize + c;
            _emptyMask[idx >> 6] |= uint64_t(1) << (idx & 63);
            --_filledCount;
        }

        __forceinline void unplaceByIndex(std::size_t idx)
        {
            const IndexType r = static_cast<IndexType>(idx / boardSize);
            const IndexType c = static_cast<IndexType>(idx % boardSize);
            unplace(r, c);
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
            for (std::size_t w = 0; w < emptyMaskWords; ++w) _emptyMask[w] = ~uint64_t(0);
            // Mask off bits beyond numberOfCells.
            const std::size_t totalBits = emptyMaskWords * 64;
            const std::size_t cellBits = static_cast<std::size_t>(numberOfCells);
            if (totalBits > cellBits)
                _emptyMask[emptyMaskWords - 1] &= (~uint64_t(0) >> (totalBits - cellBits));
            _filledCount = 0;
            _solutions = 0;
            _state = SudokuEngineState::Empty;
            _capturedFirst = false;
        }

        void copyFrom(const SudokuEngineOptimized& o)
        {
            for (IndexType i = 0; i < boardSize; ++i)
            {
                for (IndexType j = 0; j < boardSize; ++j) _board[i][j] = o._board[i][j];
                _rowUsed[i] = o._rowUsed[i];
                _colUsed[i] = o._colUsed[i];
                _boxUsed[i] = o._boxUsed[i];
            }
            for (std::size_t w = 0; w < emptyMaskWords; ++w) _emptyMask[w] = o._emptyMask[w];
            _filledCount = o._filledCount;
            _solutions = o._solutions;
            _state = o._state;
        }

        // Rebuild masks, empty mask, and filled count from _board. Called whenever the
        // engine transitions out of BeingEdited (user input may have left masks stale).
        void syncFromBoard()
        {
            for (IndexType i = 0; i < boardSize; ++i)
                _rowUsed[i] = _colUsed[i] = _boxUsed[i] = 0;
            for (std::size_t w = 0; w < emptyMaskWords; ++w) _emptyMask[w] = 0;
            _filledCount = 0;
            for (IndexType r = 0; r < boardSize; ++r)
                for (IndexType c = 0; c < boardSize; ++c)
                {
                    const std::size_t idx = static_cast<std::size_t>(r) * boardSize + c;
                    const IndexType v = _board[r][c];
                    if (v != 0)
                    {
                        const uint16_t m = static_cast<uint16_t>(1u << (v - 1));
                        _rowUsed[r] |= m;
                        _colUsed[c] |= m;
                        _boxUsed[boxOf(r, c)] |= m;
                        ++_filledCount;
                    }
                    else
                    {
                        _emptyMask[idx >> 6] |= uint64_t(1) << (idx & 63);
                    }
                }
        }

        // Walks the board fresh - does not rely on cached masks (which may not detect
        // duplicate values after user-driven setCellValue calls).
        bool noConflictsExist() const
        {
            uint16_t row[boardSize] = {};
            uint16_t col[boardSize] = {};
            uint16_t box[boardSize] = {};
            for (IndexType r = 0; r < boardSize; ++r)
                for (IndexType c = 0; c < boardSize; ++c)
                {
                    const IndexType v = _board[r][c];
                    if (v == 0) continue;
                    const uint16_t m = static_cast<uint16_t>(1u << (v - 1));
                    const IndexType b = boxOf(r, c);
                    if ((row[r] & m) || (col[c] & m) || (box[b] & m)) return false;
                    row[r] |= m; col[c] |= m; box[b] |= m;
                }
            return true;
        }

        // MRV: scan empty cells via _emptyMask and return the count of the best.
        // Short-circuits to 0 on a dead-end cell.
        int bestCell(IndexType& br, IndexType& bc) const
        {
            int minCount = boardSize + 1;
            br = 0; bc = 0;
            bool found = false;
            for (std::size_t w = 0; w < emptyMaskWords; ++w)
            {
                uint64_t word = _emptyMask[w];
                while (word)
                {
                    const int bitIdx = CTZ64(word);
                    word &= word - 1;
                    const std::size_t idx = w * 64 + bitIdx;
                    const IndexType r = static_cast<IndexType>(idx / boardSize);
                    const IndexType c = static_cast<IndexType>(idx % boardSize);
                    const int cnt = static_cast<int>(POPCOUNT(candidates(r, c)));
                    if (cnt < minCount)
                    {
                        minCount = cnt; br = r; bc = c; found = true;
                        if (cnt == 0) return 0;
                    }
                }
            }
            return found ? minCount : 0;
        }

        // Constraint propagation: repeatedly place naked singles (cell with 1 candidate)
        // and hidden singles (value with 1 location in a row/col/box). Returns false on
        // contradiction. `placed` is appended with the cells filled so the caller can unwind.
        bool propagate(uint16_t* placed, std::size_t& placedCount)
        {
            bool progress = true;
            while (progress)
            {
                progress = false;
                if (_filledCount == numberOfCells) return true;

                // ----- Naked singles -----
                bool nakedProgress = false;
                for (std::size_t w = 0; w < emptyMaskWords; ++w)
                {
                    uint64_t word = _emptyMask[w];
                    while (word)
                    {
                        const int bitIdx = CTZ64(word);
                        word &= word - 1;
                        const std::size_t idx = w * 64 + bitIdx;
                        const IndexType r = static_cast<IndexType>(idx / boardSize);
                        const IndexType c = static_cast<IndexType>(idx % boardSize);
                        // Skip cells already filled by an earlier placement in this pass.
                        if (_board[r][c] != 0) continue;
                        const uint16_t cands = candidates(r, c);
                        if (cands == 0) return false;
                        if ((cands & (cands - 1)) == 0)
                        {
                            const IndexType v = static_cast<IndexType>(CTZ(cands) + 1);
                            place(r, c, v);
                            placed[placedCount++] = static_cast<uint16_t>(idx);
                            nakedProgress = true;
                        }
                    }
                }
                if (nakedProgress) { progress = true; continue; }
                if (_filledCount == numberOfCells) return true;

                // ----- Hidden singles in rows -----
                for (IndexType r = 0; r < boardSize; ++r)
                {
                    uint16_t once = 0, more = 0;
                    for (IndexType c = 0; c < boardSize; ++c)
                    {
                        if (_board[r][c] == 0)
                        {
                            const uint16_t m = candidates(r, c);
                            more |= once & m;
                            once |= m;
                        }
                    }
                    if (allValuesMask & ~_rowUsed[r] & ~once) return false;
                    uint16_t singles = static_cast<uint16_t>(once & ~more);
                    while (singles)
                    {
                        const IndexType v = static_cast<IndexType>(CTZ(singles) + 1);
                        const uint16_t vmask = static_cast<uint16_t>(1u << (v - 1));
                        singles &= singles - 1;
                        bool placedThis = false;
                        for (IndexType c = 0; c < boardSize; ++c)
                        {
                            if (_board[r][c] == 0 && (candidates(r, c) & vmask))
                            {
                                place(r, c, v);
                                placed[placedCount++] = static_cast<uint16_t>(
                                    static_cast<std::size_t>(r) * boardSize + c);
                                progress = true;
                                placedThis = true;
                                break;
                            }
                        }
                        if (!placedThis) return false;
                    }
                }
                if (_filledCount == numberOfCells) return true;

                // ----- Hidden singles in columns -----
                for (IndexType c = 0; c < boardSize; ++c)
                {
                    uint16_t once = 0, more = 0;
                    for (IndexType r = 0; r < boardSize; ++r)
                    {
                        if (_board[r][c] == 0)
                        {
                            const uint16_t m = candidates(r, c);
                            more |= once & m;
                            once |= m;
                        }
                    }
                    if (allValuesMask & ~_colUsed[c] & ~once) return false;
                    uint16_t singles = static_cast<uint16_t>(once & ~more);
                    while (singles)
                    {
                        const IndexType v = static_cast<IndexType>(CTZ(singles) + 1);
                        const uint16_t vmask = static_cast<uint16_t>(1u << (v - 1));
                        singles &= singles - 1;
                        bool placedThis = false;
                        for (IndexType r = 0; r < boardSize; ++r)
                        {
                            if (_board[r][c] == 0 && (candidates(r, c) & vmask))
                            {
                                place(r, c, v);
                                placed[placedCount++] = static_cast<uint16_t>(
                                    static_cast<std::size_t>(r) * boardSize + c);
                                progress = true;
                                placedThis = true;
                                break;
                            }
                        }
                        if (!placedThis) return false;
                    }
                }
                if (_filledCount == numberOfCells) return true;

                // ----- Hidden singles in boxes -----
                for (IndexType b = 0; b < boardSize; ++b)
                {
                    const IndexType brBase = static_cast<IndexType>((b / sizeFactor) * sizeFactor);
                    const IndexType bcBase = static_cast<IndexType>((b % sizeFactor) * sizeFactor);
                    uint16_t once = 0, more = 0;
                    for (IndexType i = 0; i < sizeFactor; ++i)
                        for (IndexType j = 0; j < sizeFactor; ++j)
                        {
                            const IndexType r = static_cast<IndexType>(brBase + i);
                            const IndexType c = static_cast<IndexType>(bcBase + j);
                            if (_board[r][c] == 0)
                            {
                                const uint16_t m = candidates(r, c);
                                more |= once & m;
                                once |= m;
                            }
                        }
                    if (allValuesMask & ~_boxUsed[b] & ~once) return false;
                    uint16_t singles = static_cast<uint16_t>(once & ~more);
                    while (singles)
                    {
                        const IndexType v = static_cast<IndexType>(CTZ(singles) + 1);
                        const uint16_t vmask = static_cast<uint16_t>(1u << (v - 1));
                        singles &= singles - 1;
                        bool placedThis = false;
                        for (IndexType i = 0; i < sizeFactor && !placedThis; ++i)
                            for (IndexType j = 0; j < sizeFactor; ++j)
                            {
                                const IndexType r = static_cast<IndexType>(brBase + i);
                                const IndexType c = static_cast<IndexType>(bcBase + j);
                                if (_board[r][c] == 0 && (candidates(r, c) & vmask))
                                {
                                    place(r, c, v);
                                    placed[placedCount++] = static_cast<uint16_t>(
                                        static_cast<std::size_t>(r) * boardSize + c);
                                    progress = true;
                                    placedThis = true;
                                    break;
                                }
                            }
                        if (!placedThis) return false;
                    }
                }
            }
            return true;
        }

        void unwindPropagation(const uint16_t* placed, std::size_t placedCount)
        {
            for (std::size_t i = placedCount; i > 0; --i)
                unplaceByIndex(placed[i - 1]);
        }

        // Find any solution; on success the board is left fully filled.
        // On failure, the board is restored to its entry state.
        bool solve()
        {
            uint16_t placed[numberOfCells];
            std::size_t placedCount = 0;
            if (!propagate(placed, placedCount))
            {
                unwindPropagation(placed, placedCount);
                return false;
            }
            if (_filledCount == numberOfCells) return true;

            IndexType r = 0, c = 0;
            const int minCount = bestCell(r, c);
            if (minCount == 0)
            {
                unwindPropagation(placed, placedCount);
                return false;
            }
            uint16_t cands = candidates(r, c);
            while (cands)
            {
                const IndexType v = static_cast<IndexType>(CTZ(cands) + 1);
                cands &= cands - 1;
                place(r, c, v);
                if (solve()) return true;
                unplace(r, c);
            }
            unwindPropagation(placed, placedCount);
            return false;
        }

        // Count solutions up to `limit`. If `capture` is non-null, the first solution
        // found is written to it (subsequent ones are not). Board restored on return.
        IndexType countSolutionsImpl(IndexType limit, IndexType(*capture)[boardSize])
        {
            uint16_t placed[numberOfCells];
            std::size_t placedCount = 0;
            if (!propagate(placed, placedCount))
            {
                unwindPropagation(placed, placedCount);
                return 0;
            }
            if (_filledCount == numberOfCells)
            {
                if (capture && !_capturedFirst)
                {
                    for (IndexType i = 0; i < boardSize; ++i)
                        for (IndexType j = 0; j < boardSize; ++j)
                            capture[i][j] = _board[i][j];
                    _capturedFirst = true;
                }
                unwindPropagation(placed, placedCount);
                return 1;
            }

            IndexType r = 0, c = 0;
            const int minCount = bestCell(r, c);
            if (minCount == 0)
            {
                unwindPropagation(placed, placedCount);
                return 0;
            }
            uint16_t cands = candidates(r, c);
            IndexType total = 0;
            while (cands && total < limit)
            {
                const IndexType v = static_cast<IndexType>(CTZ(cands) + 1);
                cands &= cands - 1;
                place(r, c, v);
                total = static_cast<IndexType>(
                    total + countSolutionsImpl(static_cast<IndexType>(limit - total), capture));
                unplace(r, c);
            }
            unwindPropagation(placed, placedCount);
            return total;
        }

        // Randomized full-board generation. `start` is the first row-major index to scan
        // from - cells fill in order, so earlier cells are guaranteed filled.
        bool generateFull(std::size_t start)
        {
            if (_filledCount == numberOfCells)
            {
                _solutions = 1;
                _state = SudokuEngineState::FilledValid;
                return true;
            }
            std::size_t idx = start;
            while (idx < numberOfCells&& _board[idx / boardSize][idx % boardSize] != 0) ++idx;
            if (idx >= numberOfCells) return false;
            const IndexType r = static_cast<IndexType>(idx / boardSize);
            const IndexType c = static_cast<IndexType>(idx % boardSize);

            const uint16_t cands = candidates(r, c);
            IndexType vals[boardSize];
            int n = 0;
            for (uint16_t tmp = cands; tmp; tmp &= tmp - 1)
                vals[n++] = static_cast<IndexType>(CTZ(tmp) + 1);
            for (int i = n - 1; i > 0; --i)
            {
                const int j = static_cast<int>(_rng.bounded(static_cast<uint32_t>(i + 1)));
                const IndexType t = vals[i]; vals[i] = vals[j]; vals[j] = t;
            }
            for (int i = 0; i < n; ++i)
            {
                place(r, c, vals[i]);
                if (generateFull(idx + 1)) return true;
                unplace(r, c);
            }
            return false;
        }

        // Hide cells while preserving uniqueness. After removing the cell holding V, we
        // already know one valid completion exists (the original board). The removal is
        // safe iff no other value W in candidates(r,c) leads to any full solution - so we
        // only need to disprove the W-branches, skipping the V-branch entirely.
        bool hideCells(IndexType toHide)
        {
            uint16_t order[numberOfCells];
            for (std::size_t i = 0; i < numberOfCells; ++i) order[i] = static_cast<uint16_t>(i);
            for (std::size_t i = numberOfCells - 1; i > 0; --i)
            {
                const std::size_t j = _rng.bounded(static_cast<uint32_t>(i + 1));
                const uint16_t t = order[i]; order[i] = order[j]; order[j] = t;
            }

            IndexType hidden = 0;
            for (std::size_t i = 0; i < numberOfCells && hidden < toHide; ++i)
            {
                const IndexType r = static_cast<IndexType>(order[i] / boardSize);
                const IndexType c = static_cast<IndexType>(order[i] % boardSize);
                if (_board[r][c] == 0) continue;
                const IndexType savedValue = _board[r][c];
                unplace(r, c);

                const uint16_t vmask = static_cast<uint16_t>(1u << (savedValue - 1));
                uint16_t altCands = static_cast<uint16_t>(candidates(r, c) & ~vmask);
                bool foundAlt = false;
                while (altCands && !foundAlt)
                {
                    const IndexType w = static_cast<IndexType>(CTZ(altCands) + 1);
                    altCands &= altCands - 1;
                    place(r, c, w);
                    if (countSolutionsImpl(1, nullptr) >= 1) foundAlt = true;
                    unplace(r, c);
                }
                if (foundAlt) place(r, c, savedValue);
                else ++hidden;
            }

            _solutions = 1;
            _state = SudokuEngineState::NewGame;
            return hidden == toHide;
        }
    };

    template <typename IndexType, IndexType sizeFactor>
    std::ostream& operator<<(std::ostream& os, const SudokuEngineOptimized<IndexType, sizeFactor>& e)
    {
        os << "Current state: " << e.getCurrentState() << "\n"
            << "Total number of cells: " << (unsigned int)e.numberOfBoardCells() << "\n"
            << "Number of filled cells: " << (unsigned int)e.numberOfFilledCells() << "\n"
            << "Number of free cells: " << (unsigned int)e.numberOfFreeCells() << "\n\n";
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
