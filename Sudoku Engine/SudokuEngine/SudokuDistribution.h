// Hide-count distribution analyzer.
//
// For a given difficulty, generates `numSamples` puzzles with both the
// original SudokuEngine and the new sudoku::Generator, then prints a
// side-by-side histogram of how many cells each engine actually hides.
// Useful for calibrating the new engine's difficulty bands against the
// original's empirical distribution.

#ifndef SUDOKU_DISTRIBUTION_H_
#define SUDOKU_DISTRIBUTION_H_

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Sudoku.h"
#include "SudokuBenchmark.h"
#include "SudokuEngine.h"
#include "SudokuTest.h"

namespace sudoku_dist
{
    struct Summary
    {
        int    min, max;
        int    p25, p50, p75;
        double mean;
        std::size_t count;
    };

    inline Summary summarize(std::vector<int>& v)
    {
        Summary s{};
        s.count = v.size();
        if (v.empty()) return s;
        std::sort(v.begin(), v.end());
        long long sum = 0;
        for (int x : v) sum += x;
        s.min  = v.front();
        s.max  = v.back();
        s.p25  = v[v.size() / 4];
        s.p50  = v[v.size() / 2];
        s.p75  = v[v.size() * 3 / 4];
        s.mean = static_cast<double>(sum) / static_cast<double>(v.size());
        return s;
    }

    inline void analyzeDifficultyDistribution(
        SudokuGameEngine::DifficultyLevel d, int numSamples)
    {
        using OldEngine = SudokuGameEngine::SudokuEngine<unsigned char, unsigned char, 3>;

        std::cout << "\n========== HIDE-COUNT DISTRIBUTION ==========\n"
                  << "Difficulty: " << d << "\n"
                  << "Samples per engine: " << numSamples << "\n\n";

        // ---- Sample original engine ----
        std::cout << "Sampling original engine..." << std::flush;
        std::vector<int> origHides;
        origHides.reserve(numSamples);
        OldEngine orig;
        auto t0 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < numSamples; ++i)
        {
            orig.newGame(d);
            sudoku::Board<3> b;
            sudoku_test::readPuzzleFromOld(orig, b);
            origHides.push_back(81 - b.filledCount());
        }
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << " done in "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()
                  << " ms.\n";

        // ---- Sample new generator ----
        std::cout << "Sampling new generator..." << std::flush;
        std::vector<int> newHides;
        newHides.reserve(numSamples);
        sudoku::Generator<3> gen;
        const auto newD = sudoku_bench::mapDifficulty(d);
        auto t2 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < numSamples; ++i)
        {
            const auto p = gen.generate(newD);
            newHides.push_back(81 - p.givens.filledCount());
        }
        auto t3 = std::chrono::high_resolution_clock::now();
        std::cout << " done in "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count()
                  << " ms.\n\n";

        // Build count maps before sorting (summarize will sort).
        std::map<int, int> origCount, newCount;
        for (int h : origHides) ++origCount[h];
        for (int h : newHides)  ++newCount[h];

        const Summary origS = summarize(origHides);
        const Summary newS  = summarize(newHides);

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "                     |  ORIGINAL  |    NEW\n"
                  << "  min hidden cells   |     " << std::setw(4) << origS.min
                  << "   |    " << std::setw(4) << newS.min << "\n"
                  << "  p25                |     " << std::setw(4) << origS.p25
                  << "   |    " << std::setw(4) << newS.p25 << "\n"
                  << "  median             |     " << std::setw(4) << origS.p50
                  << "   |    " << std::setw(4) << newS.p50 << "\n"
                  << "  p75                |     " << std::setw(4) << origS.p75
                  << "   |    " << std::setw(4) << newS.p75 << "\n"
                  << "  max hidden cells   |     " << std::setw(4) << origS.max
                  << "   |    " << std::setw(4) << newS.max << "\n"
                  << "  mean               |   " << std::setw(6) << origS.mean
                  << "   |  " << std::setw(6) << newS.mean << "\n"
                  << std::defaultfloat;

        // Bar widths normalized to the biggest single bucket across both.
        int peak = 0;
        for (auto& kv : origCount) peak = std::max(peak, kv.second);
        for (auto& kv : newCount)  peak = std::max(peak, kv.second);
        const int barWidth = 30;
        const double scale = peak > 0 ? static_cast<double>(barWidth) / peak : 0.0;

        // Range spans both distributions.
        const int globalMin = std::min(origS.min, newS.min);
        const int globalMax = std::max(origS.max, newS.max);

        std::cout << "\n hidden | original (#)                     | new (#)\n"
                  <<   " -------+----------------------------------+----------------------------------\n";
        for (int h = globalMin; h <= globalMax; ++h)
        {
            const int oc = origCount.count(h) ? origCount[h] : 0;
            const int nc = newCount.count(h)  ? newCount[h]  : 0;
            const int ow = static_cast<int>(oc * scale);
            const int nw = static_cast<int>(nc * scale);
            std::cout << "   " << std::setw(3) << h << "  | "
                      << std::string(ow, '#')
                      << std::string(barWidth - ow, ' ')
                      << " " << std::setw(5) << oc
                      << " | "
                      << std::string(nw, '#')
                      << std::string(barWidth - nw, ' ')
                      << " " << std::setw(5) << nc
                      << "\n";
        }
        std::cout << "\n";
    }
}

#endif
