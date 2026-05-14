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
		static const unsigned int benchmarkCombinationGeneration(
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

			// Return time spent in seconds
			return static_cast<unsigned int>(totalElapsed / 1000000);
		}

		// Benchmark game generation speed
		static const unsigned int benchmarkGameGeneration(
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

			// Return time spent in seconds
			return static_cast<unsigned int>(totalElapsed / 1000000);
		}

		// Benchmark game solution speed
		static const unsigned int benchmarkGameSolving(
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

			// Report the result
			std::cout << std::endl << iterationsPerLoop * loops << " iterations finished in " <<
				totalElapsedMicros << " microseconds (" << (totalElapsedMicros / 1000000.0) << " seconds)" << std::endl << std::endl;

			// Return time spent in seconds
			return static_cast<unsigned int>(totalElapsedMicros / 1000000);
		}
	};
}

#endif
