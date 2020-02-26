// Danylo Fitel 2013

#ifndef _SUDOKU_ENGINE_BENCHMARK_H_
#define _SUDOKU_ENGINE_BENCHMARK_H_

#include <iostream>
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
			time_t start = time(nullptr);

			std::cout << "Sudoku Engine Board Generation Benchmark Started" << std::endl << std::endl;
			std::cout << "Iterations per loop: " << iterationsPerLoop << std::endl;
			std::cout << "Loops: " << loops << std::endl << std::endl;

			// Run all loops
			for (unsigned int loop = 1; loop <= loops; ++loop)
			{
				std::cout << "Running loop #" << loop << " ... ";

				//Run all iterations in a loop
				for (unsigned int iteration = 0; iteration < iterationsPerLoop; ++iteration)
				{
					engine.newCombination();
				}

				std::cout << "loop finished" << std::endl;
			}

			// Save finish time
			time_t finish = time(nullptr);

			// Report the result
			std::cout << std::endl << iterationsPerLoop * loops << " iterations finished in " <<
				(finish - start) << " seconds!" << std::endl << std::endl;

			// Return time spent
			return static_cast<unsigned int>(finish - start);
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
			time_t start = time(nullptr);

			std::cout << "Sudoku Engine Game Generation Benchmark Started" << std::endl << std::endl;
			std::cout << "Difficulty level: " << difficulty << std::endl;
			std::cout << "Iterations per loop: " << iterationsPerLoop << std::endl;
			std::cout << "Loops: " << loops << std::endl << std::endl;

			// Run all loops
			for (unsigned int loop = 1; loop <= loops; ++loop)
			{
				std::cout << "Running loop #" << loop << " ... ";

				//Run all iterations in a loop
				for (unsigned int iteration = 0; iteration < iterationsPerLoop; ++iteration)
				{
					engine.newGame(difficulty);
				}

				std::cout << "loop finished" << std::endl;
			}

			// Save finish time
			time_t finish = time(nullptr);

			// Report the result
			std::cout << std::endl << iterationsPerLoop * loops << " iterations finished in " <<
				(finish - start) << " seconds!" << std::endl << std::endl;

			// Return time spent
			return static_cast<unsigned int>(finish - start);
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
			time_t timeElapsed = 0;

			std::cout << "Sudoku Engine Game Solving Benchmark Started" << std::endl << std::endl;
			std::cout << "Difficulty level: " << difficulty << std::endl;
			std::cout << "Iterations per loop: " << iterationsPerLoop << std::endl;
			std::cout << "Loops: " << loops << std::endl << std::endl;

			// Run all loops
			for (unsigned int loop = 1; loop <= loops; ++loop)
			{
				sourceEngine.newGame(difficulty);
				time_t start = time(nullptr);

				std::cout << "Running loop #" << loop << " ... ";

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
				time_t finish = time(nullptr);
				timeElapsed += finish - start;

				std::cout << "loop finished" << std::endl;
			}

			// Report the result
			std::cout << std::endl << iterationsPerLoop * loops << " iterations finished in " <<
				timeElapsed << " seconds!" << std::endl << std::endl;

			// Return time spent
			return static_cast<unsigned int>(timeElapsed);
		}
	};
}

#endif