// Danylo Fitel 2013

#ifndef _SUDOKU_ENGINE_BENCHMARK_H_
#define _SUDOKU_ENGINE_BENCHMARK_H_

#include <iostream>
#include <chrono>
#include <time.h>

#include "SudokuEngine.h"

namespace SudokuGameEngine
{
	// Benchmark for SudokuEngine class
	template <typename IndexType = unsigned char, typename BooleanType = unsigned char, IndexType sizeFactor = 3>
	class SudokuEngineBenchmark
	{
	public:
		// Benchmark filled board generation speed
		static const long long benchmarkCombinationGeneration(
			const unsigned int iterationsPerLoop,
			const unsigned int loops = 1)
		{
			// Create Sudoku engine
			SudokuEngine<IndexType, BooleanType, sizeFactor> engine;

			// Save start time
			auto totalStart = std::chrono::high_resolution_clock::now();

			std::cout << "Sudoku Engine Board Generation Benchmark Started" << std::endl << std::endl;
			std::cout << "Iterations per loop: " << iterationsPerLoop << std::endl;
			std::cout << "Loops: " << loops << std::endl << std::endl;

			// Run all loops
			for (unsigned int loop = 1; loop <= loops; ++loop)
			{
				std::cout << "Running loop #" << loop << " ... ";

				auto loopStart = std::chrono::high_resolution_clock::now();

				//Run all iterations in a loop
				for (unsigned int iteration = 0; iteration < iterationsPerLoop; ++iteration)
				{
					engine.newCombination();
				}

				auto loopEnd = std::chrono::high_resolution_clock::now();
				auto loopElapsed = std::chrono::duration_cast<std::chrono::microseconds>(loopEnd - loopStart).count();

				std::cout << "loop finished in " << loopElapsed << " microseconds" << std::endl;
			}

			// Save finish time
			auto totalEnd = std::chrono::high_resolution_clock::now();
			auto totalElapsed = std::chrono::duration_cast<std::chrono::microseconds>(totalEnd - totalStart).count();

			// Report the result
			std::cout << std::endl << iterationsPerLoop * loops << " iterations finished in " <<
				totalElapsed << " microseconds (" << (totalElapsed / 1000000.0) << " seconds)" << std::endl << std::endl;

			// Return time spent in microseconds
			return totalElapsed;
		}

		// Benchmark game generation speed
		static const long long benchmarkGameGeneration(
			const DifficultyLevel difficulty,
			const unsigned int iterationsPerLoop,
			const unsigned int loops = 1)
		{
			// Create Sudoku engine
			SudokuEngine<IndexType, BooleanType, sizeFactor> engine;

			// Save start time
			auto totalStart = std::chrono::high_resolution_clock::now();

			std::cout << "Sudoku Engine Game Generation Benchmark Started" << std::endl << std::endl;
			std::cout << "Difficulty level: " << difficulty << std::endl;
			std::cout << "Iterations per loop: " << iterationsPerLoop << std::endl;
			std::cout << "Loops: " << loops << std::endl << std::endl;

			// Run all loops
			for (unsigned int loop = 1; loop <= loops; ++loop)
			{
				std::cout << "Running loop #" << loop << " ... ";

				auto loopStart = std::chrono::high_resolution_clock::now();

				//Run all iterations in a loop
				for (unsigned int iteration = 0; iteration < iterationsPerLoop; ++iteration)
				{
					engine.newGame(difficulty);
				}

				auto loopEnd = std::chrono::high_resolution_clock::now();
				auto loopElapsed = std::chrono::duration_cast<std::chrono::microseconds>(loopEnd - loopStart).count();

				std::cout << "loop finished in " << loopElapsed << " microseconds" << std::endl;
			}

			// Save finish time
			auto totalEnd = std::chrono::high_resolution_clock::now();
			auto totalElapsed = std::chrono::duration_cast<std::chrono::microseconds>(totalEnd - totalStart).count();

			// Report the result
			std::cout << std::endl << iterationsPerLoop * loops << " iterations finished in " <<
				totalElapsed << " microseconds (" << (totalElapsed / 1000000.0) << " seconds)" << std::endl << std::endl;

			// Return time spent in microseconds
			return totalElapsed;
		}

		// Benchmark game solution speed
		static const long long benchmarkGameSolving(
			const DifficultyLevel difficulty,
			const unsigned int iterationsPerLoop,
			const unsigned int loops = 1)
		{
			// Create Sudoku engine
			SudokuEngine<IndexType, BooleanType, sizeFactor> engine;

			// Generate a new game
			SudokuEngine<IndexType, BooleanType, sizeFactor> sourceEngine;

			// Total time elapsed
			long long totalElapsedMicros = 0;

			std::cout << "Sudoku Engine Game Solving Benchmark Started" << std::endl << std::endl;
			std::cout << "Difficulty level: " << difficulty << std::endl;
			std::cout << "Iterations per loop: " << iterationsPerLoop << std::endl;
			std::cout << "Loops: " << loops << std::endl << std::endl;

			// Run all loops
			for (unsigned int loop = 1; loop <= loops; ++loop)
			{
				sourceEngine.newGame(difficulty);

				std::cout << "Running loop #" << loop << " ... ";

				auto loopStart = std::chrono::high_resolution_clock::now();

				//Run all iterations in a loop
				for (unsigned int iteration = 0; iteration < iterationsPerLoop; ++iteration)
				{
					// Clear the engine
					engine.clear();

					// Copy the puzzle
					for (IndexType i = 0; i < engine.sizeOfTheBoard(); ++i)
					{
						for (IndexType j = 0; j < engine.sizeOfTheBoard(); ++j)
						{
							if (sourceEngine.getFilled(i, j))
							{
								engine.setFilled(i, j, true);
								engine.setCellValue(i, j, sourceEngine.getCellValue(i, j));
							}
							else
							{
								engine.setFilled(i, j, false);
							}
						}
					}

					// Solve the puzzle
					engine.trySolve();

					// Check if the puzzle has been solved correctly
					assert(engine.currentState() == SudokuEngineState::FilledValid);
				}

				// Calculate the loop was executing
				auto loopEnd = std::chrono::high_resolution_clock::now();
				auto loopElapsed = std::chrono::duration_cast<std::chrono::microseconds>(loopEnd - loopStart).count();
				totalElapsedMicros += loopElapsed;

				std::cout << "loop finished in " << loopElapsed << " microseconds" << std::endl;
			}

			// Return time spent in microseconds
			return totalElapsedMicros;
		}

		// Side-by-side benchmark: VeryHard target-capped (legacy) vs. maximize-hidden (new).
		// Runs both modes via the public newGame API and reports timing + cells-hidden stats.
		//
		// "legacy" = Hard difficulty, which uses a fixed target with no maximize pass.
		//   This is the closest public proxy to the old VeryHard target-capped behavior
		//   (cellsToHide 65% vs 80%, but the same O(n) uniqueness-check structure).
		// "new"    = VeryHard, which now maximizes hidden cells.
		static void benchmarkVeryHardMaximizeVsTarget(
			const unsigned int iterationsPerLoop,
			const unsigned int loops = 1)
		{
			using Engine = SudokuEngine<IndexType, BooleanType, sizeFactor>;
			const IndexType bSize = sizeFactor * sizeFactor;

			struct Stats
			{
				long long totalMicros = 0;
				long long minHidden   = std::numeric_limits<long long>::max();
				long long maxHidden   = 0;
				long long sumHidden   = 0;
				unsigned int count    = 0;
			};

			auto runMode = [&](DifficultyLevel d, Stats& s, const char* label)
			{
				Engine engine;
				std::cout << "--- " << label << " ---\n";
				for (unsigned int loop = 0; loop < loops; ++loop)
				{
					for (unsigned int iter = 0; iter < iterationsPerLoop; ++iter)
					{
						auto t0 = std::chrono::high_resolution_clock::now();
						engine.newGame(d);
						auto t1 = std::chrono::high_resolution_clock::now();

						s.totalMicros += std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();

						long long hidden = 0;
						for (IndexType r = 0; r < bSize; ++r)
							for (IndexType c = 0; c < bSize; ++c)
								if (!engine.getFilled(r, c)) ++hidden;

						if (hidden < s.minHidden) s.minHidden = hidden;
						if (hidden > s.maxHidden) s.maxHidden = hidden;
						s.sumHidden += hidden;
						++s.count;
					}
				}
				std::cout << "  Total time  : " << s.totalMicros << " us ("
						  << s.totalMicros / 1000000.0 << " s)\n"
						  << "  Per puzzle  : " << s.totalMicros / (double)s.count << " us\n"
						  << "  Cells hidden: min=" << s.minHidden
						  << "  max=" << s.maxHidden
						  << "  avg=" << s.sumHidden / (double)s.count << "\n\n";
			};

			const unsigned int total = iterationsPerLoop * loops;
			std::cout << "\n========== VeryHard: Target-Capped vs. Maximize-Hidden =========="
					  << "\nIterations: " << total << "\n\n";

			Stats legacy, newMode;
			runMode(DifficultyLevel::Hard,     legacy,  "Hard (legacy VeryHard proxy, target-capped)");
			runMode(DifficultyLevel::VeryHard, newMode, "VeryHard, maximize-hidden (new behavior)");

			if (newMode.count > 0 && legacy.totalMicros > 0)
			{
				const double slowdown = (double)newMode.totalMicros / (double)legacy.totalMicros;
				std::cout << "  Slowdown (VeryHard-maximize / Hard-legacy): " << slowdown << "x\n";
			}
			std::cout << "=================================================================\n\n";
		}
	};
}

#endif
