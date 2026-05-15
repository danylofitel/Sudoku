// Smoke tests for the new sudoku:: engine. Prints results to stdout.
// Returns true iff every assertion passes.

#ifndef SUDOKU_TEST_H_
#define SUDOKU_TEST_H_

#include <iostream>
#include <string>
#include <string_view>

#include "Sudoku.h"
#include "SudokuEngine.h"           // original (used as oracle)

namespace sudoku_test
{
    // ---- conversion helpers between old engines and sudoku::Board<3> ----

    template <typename OldEngine>
    inline void readPuzzleFromOld(const OldEngine& e, sudoku::Board<3>& out)
    {
        for (int r = 0; r < 9; ++r)
            for (int c = 0; c < 9; ++c)
                out.set(r, c, e.getFilled(static_cast<unsigned char>(r),
                                          static_cast<unsigned char>(c))
                                ? e.getCellValue(static_cast<unsigned char>(r),
                                                 static_cast<unsigned char>(c))
                                : 0);
    }

    template <typename OldEngine>
    inline void readFullSolutionFromOld(const OldEngine& e, sudoku::Board<3>& out)
    {
        for (int r = 0; r < 9; ++r)
            for (int c = 0; c < 9; ++c)
                out.set(r, c, e.getCellValue(static_cast<unsigned char>(r),
                                             static_cast<unsigned char>(c)));
    }

    template <typename OldEngine>
    inline void writePuzzleToOld(OldEngine& e, const sudoku::Board<3>& puzzle)
    {
        e.clear();
        for (int r = 0; r < 9; ++r)
            for (int c = 0; c < 9; ++c)
            {
                const auto v = puzzle.at(r, c);
                if (v > 0)
                {
                    e.setCellValue(static_cast<unsigned char>(r),
                                   static_cast<unsigned char>(c),
                                   static_cast<unsigned char>(v));
                    e.setFilled(static_cast<unsigned char>(r),
                                static_cast<unsigned char>(c), true);
                }
                else
                {
                    e.setFilled(static_cast<unsigned char>(r),
                                static_cast<unsigned char>(c), false);
                }
            }
    }

    inline bool checkBoardCodec()
    {
        using Board = sudoku::Board<3>;

        // A well-known easy puzzle (Norvig).
        const std::string_view puzzle =
            "003020600"
            "900305001"
            "001806400"
            "008102900"
            "700000008"
            "006708200"
            "002609500"
            "800203009"
            "005010300";

        const auto parsed = Board::fromString(puzzle);
        if (!parsed) { std::cerr << "fromString(digits) failed\n"; return false; }
        if (parsed->toString().size() != 81) { std::cerr << "toString length\n"; return false; }

        // Round-trip with '.' for empty.
        std::string dotted = parsed->toString();
        const auto parsed2 = Board::fromString(dotted);
        if (!parsed2 || !(parsed2->cells == parsed->cells))
        {
            std::cerr << "round trip failed\n"; return false;
        }

        // Strict length rejection.
        if (Board::fromString(std::string_view("123")).has_value())
        {
            std::cerr << "short string accepted\n"; return false;
        }
        // Strict char rejection.
        std::string bad(81, '.');
        bad[0] = 'Z';
        if (Board::fromString(bad).has_value())
        {
            std::cerr << "bad char accepted\n"; return false;
        }
        return true;
    }

    inline bool checkSolverUnique()
    {
        using Solver = sudoku::Solver<3>;
        using Board  = sudoku::Board<3>;

        const std::string_view puzzle =
            "003020600"
            "900305001"
            "001806400"
            "008102900"
            "700000008"
            "006708200"
            "002609500"
            "800203009"
            "005010300";
        const std::string_view expected =
            "483921657"
            "967345821"
            "251876493"
            "548132976"
            "729564138"
            "136798245"
            "372689514"
            "814253769"
            "695417382";

        Solver s;
        const auto r = s.solve(*Board::fromString(puzzle));
        if (r.status != Solver::Status::Unique)
        {
            std::cerr << "expected Unique, got status " << int(r.status) << "\n";
            return false;
        }
        if (r.solution.toString() != expected)
        {
            std::cerr << "wrong solution\n";
            std::cerr << "got:  " << r.solution.toString() << "\n";
            std::cerr << "want: " << expected << "\n";
            return false;
        }
        return true;
    }

    inline bool checkSolverMultiple()
    {
        // Empty board has many solutions.
        using Solver = sudoku::Solver<3>;
        using Board  = sudoku::Board<3>;
        Board empty;
        Solver s;
        const auto r = s.solve(empty);
        if (r.status != Solver::Status::MultipleSolutions)
        {
            std::cerr << "empty board not reported as MultipleSolutions\n";
            return false;
        }
        if (s.countSolutions(empty, 5) != 5)
        {
            std::cerr << "countSolutions limit not respected\n"; return false;
        }
        return true;
    }

    inline bool checkSolverNoSolution()
    {
        using Solver = sudoku::Solver<3>;
        using Board  = sudoku::Board<3>;
        // Duplicate '1' in row 0.
        const std::string_view puzzle =
            "11......."
            "........."
            "........."
            "........."
            "........."
            "........."
            "........."
            "........."
            ".........";
        const auto p = Board::fromString(puzzle);
        if (!p) { std::cerr << "puzzle parse failed\n"; return false; }
        Solver s;
        if (s.solve(*p).status != Solver::Status::NoSolution)
        {
            std::cerr << "duplicate not reported as NoSolution\n"; return false;
        }
        return true;
    }

    inline bool checkGeneratorRoundtrip()
    {
        using Generator = sudoku::Generator<3>;
        using Solver    = sudoku::Solver<3>;

        Generator g(/*seed=*/0xDEADBEEFCAFEBABEull);
        Solver s;

        for (int i = 0; i < 5; ++i)
        {
            const auto p = g.generate(Generator::Difficulty::Medium);
            // Solution must be complete.
            if (!p.solution.isComplete())
            {
                std::cerr << "generator solution not complete\n"; return false;
            }
            // Givens must be a subset of the solution (where non-zero, they match).
            for (int k = 0; k < 81; ++k)
            {
                if (p.givens.cells[k] != 0 && p.givens.cells[k] != p.solution.cells[k])
                {
                    std::cerr << "givens disagree with solution\n"; return false;
                }
            }
            // Puzzle must have a unique solution.
            const auto r = s.solve(p.givens);
            if (r.status != Solver::Status::Unique)
            {
                std::cerr << "generated puzzle not Unique (status="
                          << int(r.status) << ")\n";
                std::cerr << "givens:   " << p.givens.toString()   << "\n";
                std::cerr << "solution: " << p.solution.toString() << "\n";
                return false;
            }
            // And the solver's solution must match the generator's.
            if (r.solution != p.solution)
            {
                std::cerr << "solver's solution doesn't match generator's\n";
                return false;
            }
        }
        return true;
    }

    // Generate K puzzles with the original SudokuEngine (the source of truth)
    // and solve each with the new sudoku::Solver. Verify Unique status and
    // matching solution.
    inline bool crossValidateOldGenNewSolve(int K, SudokuGameEngine::DifficultyLevel d)
    {
        using OldEngine = SudokuGameEngine::SudokuEngine<unsigned char, unsigned char, 3>;
        OldEngine oldEngine;
        sudoku::Solver<3> newSolver;

        for (int i = 0; i < K; ++i)
        {
            oldEngine.newGame(d);
            sudoku::Board<3> puzzle, oldSolution;
            readPuzzleFromOld(oldEngine, puzzle);
            readFullSolutionFromOld(oldEngine, oldSolution);

            const auto r = newSolver.solve(puzzle);
            if (r.status != sudoku::Solver<3>::Status::Unique)
            {
                std::cerr << "iter " << i << ": new Solver did not report Unique on a puzzle "
                          << "generated by SudokuEngine (status=" << int(r.status) << ")\n"
                          << "puzzle: " << puzzle.toString() << "\n";
                return false;
            }
            if (r.solution != oldSolution)
            {
                std::cerr << "iter " << i << ": new Solver disagrees with SudokuEngine\n"
                          << "puzzle: " << puzzle.toString() << "\n"
                          << "old:    " << oldSolution.toString() << "\n"
                          << "new:    " << r.solution.toString() << "\n";
                return false;
            }
        }
        return true;
    }

    // Generate K puzzles with sudoku::Generator and solve them with the
    // original SudokuEngine. Verify the old engine considers them uniquely
    // solvable and produces the same solution the generator promised.
    inline bool crossValidateNewGenOldSolve(int K, SudokuGameEngine::DifficultyLevel d)
    {
        using OldEngine = SudokuGameEngine::SudokuEngine<unsigned char, unsigned char, 3>;
        using NewDifficulty = sudoku::Generator<3>::Difficulty;
        const NewDifficulty newD =
            (d == SudokuGameEngine::DifficultyLevel::VeryEasy) ? NewDifficulty::VeryEasy :
            (d == SudokuGameEngine::DifficultyLevel::Easy)     ? NewDifficulty::Easy     :
            (d == SudokuGameEngine::DifficultyLevel::Medium)   ? NewDifficulty::Medium   :
            (d == SudokuGameEngine::DifficultyLevel::Hard)     ? NewDifficulty::Hard     :
                                                                  NewDifficulty::VeryHard;

        sudoku::Generator<3> newGen;
        OldEngine oldEngine;

        for (int i = 0; i < K; ++i)
        {
            const auto p = newGen.generate(newD);
            writePuzzleToOld(oldEngine, p.givens);
            const auto st = oldEngine.updateState();
            if (st != SudokuGameEngine::SudokuEngineState::HasUniqueSolution)
            {
                std::cerr << "iter " << i << ": SudokuEngine did not consider generated puzzle "
                          << "uniquely solvable (state=" << st << ")\n"
                          << "puzzle: " << p.givens.toString() << "\n";
                return false;
            }
            oldEngine.trySolve();
            sudoku::Board<3> oldSolution;
            readFullSolutionFromOld(oldEngine, oldSolution);
            if (oldSolution != p.solution)
            {
                std::cerr << "iter " << i << ": SudokuEngine's solution disagrees with generator's\n"
                          << "puzzle:   " << p.givens.toString()   << "\n"
                          << "generator:" << p.solution.toString() << "\n"
                          << "old:      " << oldSolution.toString() << "\n";
                return false;
            }
        }
        return true;
    }

    inline bool checkCrossValidationMedium()
    {
        const int K = 5;
        const auto d = SudokuGameEngine::DifficultyLevel::Medium;
        return crossValidateOldGenNewSolve(K, d)
            && crossValidateNewGenOldSolve(K, d);
    }

    inline bool runAll()
    {
        struct Case { const char* name; bool (*fn)(); };
        const Case cases[] = {
            {"Board codec",                       &checkBoardCodec},
            {"Solver unique",                     &checkSolverUnique},
            {"Solver multiple",                   &checkSolverMultiple},
            {"Solver no solution",                &checkSolverNoSolution},
            {"Generator roundtrip",               &checkGeneratorRoundtrip},
            {"Cross-validation (Medium, K=5)",    &checkCrossValidationMedium},
        };
        bool ok = true;
        for (const auto& c : cases)
        {
            const bool passed = c.fn();
            std::cout << (passed ? "[PASS] " : "[FAIL] ") << c.name << "\n";
            ok = ok && passed;
        }
        std::cout << (ok ? "All tests passed.\n" : "Some tests FAILED.\n");
        return ok;
    }
}

#endif
