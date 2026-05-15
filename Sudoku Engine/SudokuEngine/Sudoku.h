// Clean stateless Sudoku engine.
//
// Three types:
//   sudoku::Board<N>      - plain data, no logic. 81-char codec for N=3.
//   sudoku::Solver<N>     - solve / countSolutions / findAny. Workspace is
//                           reusable across calls but reset every call.
//   sudoku::Generator<N>  - generate(Difficulty) -> {givens, solution}.
//
// N is the block size; the board is N*N by N*N. N in [2, 4] -> boards 4x4,
// 9x9, 16x16. All candidate masks are uint16_t.

#ifndef SUDOKU_H_
#define SUDOKU_H_

#include <array>
#include <bit>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <random>
#include <string>
#include <string_view>

namespace sudoku
{

// ----------------------------------------------------------------------------
// Board<N>
// ----------------------------------------------------------------------------

template <int N = 3>
struct Board
{
    static_assert(N >= 2 && N <= 4, "N must be in [2, 4] (boards 4x4 to 16x16)");

    static constexpr int Size  = N * N;          // 4, 9, 16
    static constexpr int Cells = Size * Size;    // 16, 81, 256

    // 0 = empty, 1..Size = filled.
    std::array<std::uint8_t, Cells> cells{};

    constexpr std::uint8_t at(int row, int col) const
    {
        return cells[static_cast<std::size_t>(row) * Size + col];
    }

    constexpr void set(int row, int col, std::uint8_t value)
    {
        cells[static_cast<std::size_t>(row) * Size + col] = value;
    }

    constexpr int filledCount() const
    {
        int n = 0;
        for (std::uint8_t v : cells) n += (v != 0);
        return n;
    }

    constexpr bool isComplete() const
    {
        for (std::uint8_t v : cells) if (v == 0) return false;
        return true;
    }

    // Standard 81-char codec for 9x9; generalized for other N.
    //   empty cell -> '.'
    //   1..9       -> '1'..'9'
    //   10..16     -> 'A'..'G'
    // fromString accepts '0' or '.' for empty and is case-insensitive for hex.
    std::string toString() const;
    static std::optional<Board> fromString(std::string_view s);

    bool operator==(const Board&) const = default;
};

// ----------------------------------------------------------------------------
// Solver<N>
// ----------------------------------------------------------------------------

template <int N = 3>
class Solver
{
public:
    enum class Status : std::uint8_t
    {
        Unique,             // exactly one solution; `solution` is it
        NoSolution,         // the givens conflict, or no completion exists
        MultipleSolutions,  // at least two solutions; `solution` is one of them
    };

    struct Result
    {
        Status   status;
        Board<N> solution;  // valid iff status == Unique or MultipleSolutions
    };

    Solver() = default;

    // Solve a puzzle and report uniqueness in one pass. The solver is reset on
    // entry; nothing persists between calls.
    Result solve(const Board<N>& puzzle);

    // Find any one solution. Returns true on success and writes it to `out`.
    // Does not check uniqueness - faster than solve() when uniqueness is known
    // (e.g. inside the generator after a successful hide).
    bool findAny(const Board<N>& puzzle, Board<N>& out);

    // Count solutions up to `limit` (>= 1). Useful for uniqueness probes.
    int countSolutions(const Board<N>& puzzle, int limit = 2);

private:
    static constexpr int           Size           = N * N;
    static constexpr int           Cells          = Size * Size;
    static constexpr std::uint16_t AllValuesMask = static_cast<std::uint16_t>((1u << Size) - 1u);
    static constexpr std::size_t   EmptyMaskWords = (Cells + 63) / 64;

    // Workspace - mutated during search, rebuilt from input on every public call.
    std::uint8_t  _board[Cells];
    std::uint16_t _rowUsed[Size];
    std::uint16_t _colUsed[Size];
    std::uint16_t _boxUsed[Size];
    std::uint64_t _emptyMask[EmptyMaskWords];
    int           _filled;
    bool          _captured;       // first-solution latch for countImpl
    Board<N>      _firstSolution;  // captured solution (if requested)

    static constexpr int boxOf(int r, int c) { return (r / N) * N + (c / N); }

    std::uint16_t candidates(int r, int c) const
    {
        return static_cast<std::uint16_t>(
            ~(_rowUsed[r] | _colUsed[c] | _boxUsed[boxOf(r, c)]) & AllValuesMask);
    }

    void place(int r, int c, int v);
    void unplace(int r, int c);
    void unplaceByIndex(int idx);

    // Returns false if the input has a direct duplicate, true otherwise.
    bool loadFrom(const Board<N>& b);
    void writeTo(Board<N>& b) const;

    bool propagate(std::uint16_t* placedTrail, int& trailCount);
    void unwindPropagation(const std::uint16_t* trail, int count);

    // MRV. Returns the candidate count of the best cell, or 0 if any empty
    // cell has zero candidates. Sets (br, bc) to that cell on return.
    int bestCell(int& br, int& bc) const;

    bool findAnyImpl();
    int  countImpl(int limit, bool capture);
};

// ----------------------------------------------------------------------------
// Generator<N>
// ----------------------------------------------------------------------------

template <int N = 3>
class Generator
{
public:
    enum class Difficulty : std::uint8_t
    {
        VeryEasy, Easy, Medium, Hard, VeryHard
    };

    struct Puzzle
    {
        Board<N> givens;    // the puzzle as the player sees it (cells hidden)
        Board<N> solution;  // the unique completion
    };

    explicit Generator(std::uint64_t seed = makeSeed());

    Puzzle generate(Difficulty d);

private:
    static constexpr int Size  = N * N;
    static constexpr int Cells = Size * Size;

    // xorshift32 - fast, good enough for shuffles and difficulty jitter.
    std::uint32_t _rng;

    static std::uint64_t makeSeed();
    std::uint32_t next32();
    std::uint32_t bounded(std::uint32_t n) { return next32() % n; }

    // Generate a uniformly-shuffled full board by randomized backtracking.
    // Uses simple constraint masks (no propagation needed - branching factor
    // is low because each cell is filled in row-major order).
    void generateFullBoard(Board<N>& out);

    // Hide cells while preserving uniqueness. Caller passes the full board in
    // `puzzle` and the same board in `solution` (used to skip the V-branch
    // during uniqueness checks - we already know V works).
    int hideCells(Board<N>& puzzle, const Board<N>& solution, int targetHidden);

    void difficultyRange(Difficulty d, int& minHide, int& maxHide) const;
};

// ============================================================================
// Implementation
// ============================================================================

namespace detail
{
    inline char encodeValue(std::uint8_t v)
    {
        if (v == 0) return '.';
        if (v <= 9) return static_cast<char>('0' + v);
        return static_cast<char>('A' + (v - 10));
    }

    // Returns -1 on unknown character.
    inline int decodeChar(char c, int maxValue)
    {
        if (c == '.' || c == '0') return 0;
        if (c >= '1' && c <= '9') return c - '0';
        if (c >= 'A' && c <= 'G') return (c - 'A') + 10;
        if (c >= 'a' && c <= 'g') return (c - 'a') + 10;
        (void)maxValue;
        return -1;
    }
}

// --- Board ---

template <int N>
std::string Board<N>::toString() const
{
    std::string s;
    s.reserve(static_cast<std::size_t>(Cells));
    for (std::uint8_t v : cells) s.push_back(detail::encodeValue(v));
    return s;
}

template <int N>
std::optional<Board<N>> Board<N>::fromString(std::string_view s)
{
    if (s.size() != static_cast<std::size_t>(Cells)) return std::nullopt;
    Board<N> b;
    for (int i = 0; i < Cells; ++i)
    {
        const int v = detail::decodeChar(s[i], Size);
        if (v < 0 || v > Size) return std::nullopt;
        b.cells[i] = static_cast<std::uint8_t>(v);
    }
    return b;
}

// --- Solver ---

template <int N>
void Solver<N>::place(int r, int c, int v)
{
    const std::uint16_t mask = static_cast<std::uint16_t>(1u << (v - 1));
    _rowUsed[r] |= mask;
    _colUsed[c] |= mask;
    _boxUsed[boxOf(r, c)] |= mask;
    const int idx = r * Size + c;
    _board[idx] = static_cast<std::uint8_t>(v);
    _emptyMask[idx >> 6] &= ~(std::uint64_t{1} << (idx & 63));
    ++_filled;
}

template <int N>
void Solver<N>::unplace(int r, int c)
{
    const int idx = r * Size + c;
    const std::uint8_t v = _board[idx];
    assert(v != 0);
    const std::uint16_t mask = static_cast<std::uint16_t>(~(1u << (v - 1)));
    _rowUsed[r] &= mask;
    _colUsed[c] &= mask;
    _boxUsed[boxOf(r, c)] &= mask;
    _board[idx] = 0;
    _emptyMask[idx >> 6] |= (std::uint64_t{1} << (idx & 63));
    --_filled;
}

template <int N>
void Solver<N>::unplaceByIndex(int idx)
{
    unplace(idx / Size, idx % Size);
}

template <int N>
bool Solver<N>::loadFrom(const Board<N>& b)
{
    for (int i = 0; i < Size; ++i)
    {
        _rowUsed[i] = 0;
        _colUsed[i] = 0;
        _boxUsed[i] = 0;
    }
    for (std::size_t w = 0; w < EmptyMaskWords; ++w) _emptyMask[w] = 0;
    _filled = 0;
    _captured = false;

    for (int r = 0; r < Size; ++r)
    {
        for (int c = 0; c < Size; ++c)
        {
            const int idx = r * Size + c;
            const std::uint8_t v = b.cells[idx];
            _board[idx] = v;
            if (v == 0)
            {
                _emptyMask[idx >> 6] |= std::uint64_t{1} << (idx & 63);
            }
            else
            {
                if (v > Size) return false;
                const std::uint16_t mask = static_cast<std::uint16_t>(1u << (v - 1));
                if ((_rowUsed[r] | _colUsed[c] | _boxUsed[boxOf(r, c)]) & mask)
                    return false;
                _rowUsed[r] |= mask;
                _colUsed[c] |= mask;
                _boxUsed[boxOf(r, c)] |= mask;
                ++_filled;
            }
        }
    }
    return true;
}

template <int N>
void Solver<N>::writeTo(Board<N>& b) const
{
    for (int i = 0; i < Cells; ++i) b.cells[i] = _board[i];
}

template <int N>
int Solver<N>::bestCell(int& br, int& bc) const
{
    int minCount = Size + 1;
    br = 0; bc = 0;
    bool found = false;
    for (std::size_t w = 0; w < EmptyMaskWords; ++w)
    {
        std::uint64_t word = _emptyMask[w];
        while (word)
        {
            const int bitIdx = std::countr_zero(word);
            word &= word - 1;
            const int idx = static_cast<int>(w) * 64 + bitIdx;
            const int r = idx / Size;
            const int c = idx % Size;
            const int cnt = std::popcount(candidates(r, c));
            if (cnt < minCount)
            {
                minCount = cnt; br = r; bc = c; found = true;
                if (cnt <= 1) return cnt;  // unbeatable
            }
        }
    }
    return found ? minCount : 0;
}

template <int N>
bool Solver<N>::propagate(std::uint16_t* trail, int& trailCount)
{
    bool progress = true;
    while (progress)
    {
        progress = false;
        if (_filled == Cells) return true;

        // ----- Naked singles -----
        for (std::size_t w = 0; w < EmptyMaskWords; ++w)
        {
            std::uint64_t word = _emptyMask[w];
            while (word)
            {
                const int bitIdx = std::countr_zero(word);
                word &= word - 1;
                const int idx = static_cast<int>(w) * 64 + bitIdx;
                if (_board[idx] != 0) continue;     // filled by earlier pass
                const int r = idx / Size;
                const int c = idx % Size;
                const std::uint16_t cands = candidates(r, c);
                if (cands == 0) return false;
                if ((cands & (cands - 1)) == 0)
                {
                    const int v = std::countr_zero(cands) + 1;
                    place(r, c, v);
                    trail[trailCount++] = static_cast<std::uint16_t>(idx);
                    progress = true;
                }
            }
        }
        if (progress) continue;
        if (_filled == Cells) return true;

        // ----- Hidden singles in rows -----
        for (int r = 0; r < Size; ++r)
        {
            std::uint16_t once = 0, more = 0;
            for (int c = 0; c < Size; ++c)
            {
                if (_board[r * Size + c] == 0)
                {
                    const std::uint16_t m = candidates(r, c);
                    more |= once & m;
                    once |= m;
                }
            }
            if (static_cast<std::uint16_t>(AllValuesMask & ~_rowUsed[r] & ~once)) return false;
            std::uint16_t singles = static_cast<std::uint16_t>(once & ~more);
            while (singles)
            {
                const int v = std::countr_zero(singles) + 1;
                const std::uint16_t vmask = static_cast<std::uint16_t>(1u << (v - 1));
                singles = static_cast<std::uint16_t>(singles & (singles - 1));
                bool placedThis = false;
                for (int c = 0; c < Size; ++c)
                {
                    const int idx = r * Size + c;
                    if (_board[idx] == 0 && (candidates(r, c) & vmask))
                    {
                        place(r, c, v);
                        trail[trailCount++] = static_cast<std::uint16_t>(idx);
                        progress = true;
                        placedThis = true;
                        break;
                    }
                }
                if (!placedThis) return false;
            }
        }
        if (_filled == Cells) return true;

        // ----- Hidden singles in columns -----
        for (int c = 0; c < Size; ++c)
        {
            std::uint16_t once = 0, more = 0;
            for (int r = 0; r < Size; ++r)
            {
                if (_board[r * Size + c] == 0)
                {
                    const std::uint16_t m = candidates(r, c);
                    more |= once & m;
                    once |= m;
                }
            }
            if (static_cast<std::uint16_t>(AllValuesMask & ~_colUsed[c] & ~once)) return false;
            std::uint16_t singles = static_cast<std::uint16_t>(once & ~more);
            while (singles)
            {
                const int v = std::countr_zero(singles) + 1;
                const std::uint16_t vmask = static_cast<std::uint16_t>(1u << (v - 1));
                singles = static_cast<std::uint16_t>(singles & (singles - 1));
                bool placedThis = false;
                for (int r = 0; r < Size; ++r)
                {
                    const int idx = r * Size + c;
                    if (_board[idx] == 0 && (candidates(r, c) & vmask))
                    {
                        place(r, c, v);
                        trail[trailCount++] = static_cast<std::uint16_t>(idx);
                        progress = true;
                        placedThis = true;
                        break;
                    }
                }
                if (!placedThis) return false;
            }
        }
        if (_filled == Cells) return true;

        // ----- Hidden singles in boxes -----
        for (int b = 0; b < Size; ++b)
        {
            const int brBase = (b / N) * N;
            const int bcBase = (b % N) * N;
            std::uint16_t once = 0, more = 0;
            for (int i = 0; i < N; ++i)
            {
                for (int j = 0; j < N; ++j)
                {
                    const int r = brBase + i;
                    const int c = bcBase + j;
                    if (_board[r * Size + c] == 0)
                    {
                        const std::uint16_t m = candidates(r, c);
                        more |= once & m;
                        once |= m;
                    }
                }
            }
            if (static_cast<std::uint16_t>(AllValuesMask & ~_boxUsed[b] & ~once)) return false;
            std::uint16_t singles = static_cast<std::uint16_t>(once & ~more);
            while (singles)
            {
                const int v = std::countr_zero(singles) + 1;
                const std::uint16_t vmask = static_cast<std::uint16_t>(1u << (v - 1));
                singles = static_cast<std::uint16_t>(singles & (singles - 1));
                bool placedThis = false;
                for (int i = 0; i < N && !placedThis; ++i)
                {
                    for (int j = 0; j < N; ++j)
                    {
                        const int r = brBase + i;
                        const int c = bcBase + j;
                        const int idx = r * Size + c;
                        if (_board[idx] == 0 && (candidates(r, c) & vmask))
                        {
                            place(r, c, v);
                            trail[trailCount++] = static_cast<std::uint16_t>(idx);
                            progress = true;
                            placedThis = true;
                            break;
                        }
                    }
                }
                if (!placedThis) return false;
            }
        }
    }
    return true;
}

template <int N>
void Solver<N>::unwindPropagation(const std::uint16_t* trail, int count)
{
    for (int i = count; i > 0; --i) unplaceByIndex(trail[i - 1]);
}

template <int N>
bool Solver<N>::findAnyImpl()
{
    std::uint16_t trail[Cells];
    int trailCount = 0;
    if (!propagate(trail, trailCount))
    {
        unwindPropagation(trail, trailCount);
        return false;
    }
    if (_filled == Cells) return true;

    int r = 0, c = 0;
    if (bestCell(r, c) == 0)
    {
        unwindPropagation(trail, trailCount);
        return false;
    }
    std::uint16_t cands = candidates(r, c);
    while (cands)
    {
        const int v = std::countr_zero(cands) + 1;
        cands = static_cast<std::uint16_t>(cands & (cands - 1));
        place(r, c, v);
        if (findAnyImpl()) return true;
        unplace(r, c);
    }
    unwindPropagation(trail, trailCount);
    return false;
}

template <int N>
int Solver<N>::countImpl(int limit, bool capture)
{
    std::uint16_t trail[Cells];
    int trailCount = 0;
    if (!propagate(trail, trailCount))
    {
        unwindPropagation(trail, trailCount);
        return 0;
    }
    if (_filled == Cells)
    {
        if (capture && !_captured)
        {
            writeTo(_firstSolution);
            _captured = true;
        }
        unwindPropagation(trail, trailCount);
        return 1;
    }

    int r = 0, c = 0;
    if (bestCell(r, c) == 0)
    {
        unwindPropagation(trail, trailCount);
        return 0;
    }
    std::uint16_t cands = candidates(r, c);
    int total = 0;
    while (cands && total < limit)
    {
        const int v = std::countr_zero(cands) + 1;
        cands = static_cast<std::uint16_t>(cands & (cands - 1));
        place(r, c, v);
        total += countImpl(limit - total, capture);
        unplace(r, c);
    }
    unwindPropagation(trail, trailCount);
    return total;
}

template <int N>
typename Solver<N>::Result Solver<N>::solve(const Board<N>& puzzle)
{
    Result result{Status::NoSolution, {}};
    if (!loadFrom(puzzle)) return result;
    const int count = countImpl(2, /*capture=*/true);
    if (count == 0)       result.status = Status::NoSolution;
    else if (count == 1)  { result.status = Status::Unique;            result.solution = _firstSolution; }
    else                  { result.status = Status::MultipleSolutions; result.solution = _firstSolution; }
    return result;
}

template <int N>
bool Solver<N>::findAny(const Board<N>& puzzle, Board<N>& out)
{
    if (!loadFrom(puzzle)) return false;
    if (!findAnyImpl()) return false;
    writeTo(out);
    return true;
}

template <int N>
int Solver<N>::countSolutions(const Board<N>& puzzle, int limit)
{
    assert(limit >= 1);
    if (!loadFrom(puzzle)) return 0;
    return countImpl(limit, /*capture=*/false);
}

// --- Generator ---

template <int N>
std::uint64_t Generator<N>::makeSeed()
{
    static std::random_device rd;
    std::uint64_t mix = static_cast<std::uint64_t>(rd());
    mix ^= static_cast<std::uint64_t>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count());
    mix ^= mix >> 32;
    mix *= 0x9E3779B97F4A7C15ull;
    return mix ? mix : 0x9E3779B97F4A7C15ull;
}

template <int N>
Generator<N>::Generator(std::uint64_t seed)
    : _rng(static_cast<std::uint32_t>(seed ^ (seed >> 32)))
{
    if (_rng == 0) _rng = 0x9E3779B9u;
}

template <int N>
std::uint32_t Generator<N>::next32()
{
    std::uint32_t x = _rng;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    _rng = x;
    return x;
}

template <int N>
void Generator<N>::difficultyRange(Difficulty d, int& minHide, int& maxHide) const
{
    // Calibrated for 9x9. Scaled proportionally to Cells for other sizes.
    int loPct, hiPct;
    switch (d)
    {
        case Difficulty::VeryEasy: loPct = 25; hiPct = 37; break;
        case Difficulty::Easy:     loPct = 37; hiPct = 49; break;
        case Difficulty::Medium:   loPct = 49; hiPct = 61; break;
        case Difficulty::Hard:     loPct = 61; hiPct = 67; break;
        case Difficulty::VeryHard: loPct = 67; hiPct = 74; break;
        default:                   loPct = 49; hiPct = 61; break;
    }
    minHide = (Cells * loPct) / 100;
    maxHide = (Cells * hiPct) / 100;
}

template <int N>
void Generator<N>::generateFullBoard(Board<N>& out)
{
    // Local constraint masks. We fill in row-major order so candidate
    // sets only need three peers per cell, no propagation required.
    std::uint16_t rowUsed[Size] = {};
    std::uint16_t colUsed[Size] = {};
    std::uint16_t boxUsed[Size] = {};
    std::uint8_t  board[Cells]  = {};

    constexpr std::uint16_t allMask = static_cast<std::uint16_t>((1u << Size) - 1u);

    // Backtracking stack: entry per cell records the remaining candidates
    // (with already-tried values cleared). We commit to a cell by picking a
    // random set bit; on backtrack we just clear that bit and retry.
    std::uint16_t remaining[Cells];

    int idx = 0;
    remaining[0] = static_cast<std::uint16_t>(
        allMask & ~(rowUsed[0] | colUsed[0] | boxUsed[0]));

    while (idx >= 0 && idx < Cells)
    {
        std::uint16_t cands = remaining[idx];
        if (cands == 0)
        {
            // Dead end: clear this cell and backtrack.
            if (idx == 0) break;  // shouldn't happen on an empty start
            const int prev = idx - 1;
            const int pr = prev / Size, pc = prev % Size;
            const std::uint8_t pv = board[prev];
            const std::uint16_t pmask = static_cast<std::uint16_t>(~(1u << (pv - 1)));
            rowUsed[pr] &= pmask;
            colUsed[pc] &= pmask;
            boxUsed[(pr / N) * N + (pc / N)] &= pmask;
            board[prev] = 0;
            idx = prev;
            continue;
        }

        // Pick a uniformly random set bit.
        const int nCands = std::popcount(cands);
        int pick = static_cast<int>(bounded(static_cast<std::uint32_t>(nCands)));
        std::uint16_t bit = 0;
        for (;;)
        {
            const int b = std::countr_zero(cands);
            bit = static_cast<std::uint16_t>(1u << b);
            if (pick == 0) break;
            cands = static_cast<std::uint16_t>(cands & (cands - 1));
            --pick;
        }
        // Remove this bit from this cell's remaining for future retries.
        remaining[idx] = static_cast<std::uint16_t>(remaining[idx] & ~bit);

        const int r = idx / Size, c = idx % Size;
        const int v = std::countr_zero(bit) + 1;
        rowUsed[r] |= bit;
        colUsed[c] |= bit;
        boxUsed[(r / N) * N + (c / N)] |= bit;
        board[idx] = static_cast<std::uint8_t>(v);

        ++idx;
        if (idx < Cells)
        {
            const int nr = idx / Size, nc = idx % Size;
            remaining[idx] = static_cast<std::uint16_t>(
                allMask & ~(rowUsed[nr] | colUsed[nc] | boxUsed[(nr / N) * N + (nc / N)]));
        }
    }

    assert(idx == Cells);
    for (int i = 0; i < Cells; ++i) out.cells[i] = board[i];
}

template <int N>
int Generator<N>::hideCells(Board<N>& puzzle, const Board<N>& /*solution*/, int targetHidden)
{
    // Random order of cells to attempt to hide.
    std::uint16_t order[Cells];
    for (int i = 0; i < Cells; ++i) order[i] = static_cast<std::uint16_t>(i);
    for (int i = Cells - 1; i > 0; --i)
    {
        const int j = static_cast<int>(bounded(static_cast<std::uint32_t>(i + 1)));
        const std::uint16_t t = order[i]; order[i] = order[j]; order[j] = t;
    }

    Solver<N> probe;
    int hidden = 0;

    for (int i = 0; i < Cells && hidden < targetHidden; ++i)
    {
        const int idx = order[i];
        const std::uint8_t v = puzzle.cells[idx];
        if (v == 0) continue;

        // Compute candidates at this cell after hypothetical removal by
        // scanning peers in puzzle (it has at most one given per cell).
        const int r = idx / Size, c = idx % Size;
        std::uint16_t used = 0;
        for (int k = 0; k < Size; ++k)
        {
            const std::uint8_t rv = puzzle.cells[r * Size + k];
            const std::uint8_t cv = puzzle.cells[k * Size + c];
            if (rv) used = static_cast<std::uint16_t>(used | (1u << (rv - 1)));
            if (cv) used = static_cast<std::uint16_t>(used | (1u << (cv - 1)));
        }
        const int brBase = (r / N) * N, bcBase = (c / N) * N;
        for (int i2 = 0; i2 < N; ++i2)
            for (int j2 = 0; j2 < N; ++j2)
            {
                const std::uint8_t bv = puzzle.cells[(brBase + i2) * Size + (bcBase + j2)];
                if (bv) used = static_cast<std::uint16_t>(used | (1u << (bv - 1)));
            }
        // Clear V itself - candidates for the (now-empty) cell.
        used = static_cast<std::uint16_t>(used & ~(1u << (v - 1)));
        constexpr std::uint16_t allMask = static_cast<std::uint16_t>((1u << Size) - 1u);
        const std::uint16_t altCandsRaw = static_cast<std::uint16_t>(~used & allMask);
        // Remove V itself from the set we test - we already know V completes.
        std::uint16_t altCands = static_cast<std::uint16_t>(altCandsRaw & ~(1u << (v - 1)));

        // Tentatively hide.
        puzzle.cells[idx] = 0;

        // Test each alternative W != V: if any leads to a full solution,
        // removing the given would create ambiguity.
        bool ambiguous = false;
        while (altCands && !ambiguous)
        {
            const int w = std::countr_zero(altCands) + 1;
            altCands = static_cast<std::uint16_t>(altCands & (altCands - 1));
            puzzle.cells[idx] = static_cast<std::uint8_t>(w);
            if (probe.countSolutions(puzzle, 1) >= 1) ambiguous = true;
        }
        puzzle.cells[idx] = 0;

        if (ambiguous)
            puzzle.cells[idx] = v;
        else
            ++hidden;
    }

    return hidden;
}

template <int N>
typename Generator<N>::Puzzle Generator<N>::generate(Difficulty d)
{
    Puzzle p;
    generateFullBoard(p.solution);
    p.givens = p.solution;

    int minHide, maxHide;
    difficultyRange(d, minHide, maxHide);
    const int target = minHide
        + static_cast<int>(bounded(static_cast<std::uint32_t>(maxHide - minHide + 1)));
    hideCells(p.givens, p.solution, target);
    return p;
}

} // namespace sudoku

#endif // SUDOKU_H_
