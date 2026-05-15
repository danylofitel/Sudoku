// Danylo Fitel 2013

#include <iostream>
#include <string>
#include "SudokuEngine.h"
#include "SudokuEngineBenchmark.h"
#include "Sudoku.h"
#include "SudokuBenchmark.h"
#include "SudokuTest.h"
#include "SudokuStressTest.h"
#include "SudokuDistribution.h"

typedef unsigned char IndexType;
typedef unsigned char BooleanType;
const IndexType sizeFactor = 3;

int main()
{
	SudokuGameEngine::SudokuEngine<IndexType, BooleanType, sizeFactor> engine;

	char input(0);
	char activityChoice(0);
	char engineChoice(0);
	std::string numberInput("");
	SudokuGameEngine::DifficultyLevel difficulty(SudokuGameEngine::DifficultyLevel::VeryEasy);
	unsigned int iterations(0);
	unsigned int loops(0);

	while (true)
	{
		do
		{
			std::cout << "Choose activity" << std::endl;
			std::cout << "1. Run combination generation benchmark" << std::endl;
			std::cout << "2. Run game generation benchmark" << std::endl;
			std::cout << "3. Run solving benchmark" << std::endl;
			std::cout << "4. Generate new combination" << std::endl;
			std::cout << "5. Generate new game" << std::endl;
			std::cout << "6. Compare original vs new (solving benchmark)" << std::endl;
			std::cout << "7. Run new engine (sudoku::) smoke test" << std::endl;
			std::cout << "8. Solver stress test: original vs new (Very Hard, percentiles)" << std::endl;
			std::cout << "9. Hide-count distribution: original vs new" << std::endl;
			std::cout << "E. Exit" << std::endl;
			std::cout << "->";
			std::cin >> input;
			std::cout << std::endl;

			switch (input)
			{
			case '1': case '2': case '3': case '4': case '5': case '6':
				activityChoice = input;
				break;
			case '7':
				sudoku_test::runAll();
				input = 0;
				continue;
			case '8':
			{
				int np = 0, sp = 0;
				do { std::cout << "Number of puzzles (>= 1000 recommended)\n->"; std::cin >> numberInput;
					try { np = std::stoi(numberInput); } catch (...) { np = 0; } } while (np <= 0);
				do { std::cout << "Solves per puzzle (>= 10 recommended)\n->"; std::cin >> numberInput;
					try { sp = std::stoi(numberInput); } catch (...) { sp = 0; } } while (sp <= 0);
				sudoku_stress::runVeryHardComparison(np, sp);
				input = 0;
				continue;
			}
			case '9':
			{
				int dchoice = 0, ns = 0;
				do {
					std::cout << "Difficulty:\n  1. Very easy\n  2. Easy\n  3. Medium\n  4. Hard\n  5. Very hard\n->";
					std::cin >> numberInput;
					try { dchoice = std::stoi(numberInput); } catch (...) { dchoice = 0; }
				} while (dchoice < 1 || dchoice > 5);
				do { std::cout << "Samples per engine\n->"; std::cin >> numberInput;
					try { ns = std::stoi(numberInput); } catch (...) { ns = 0; } } while (ns <= 0);
				const SudokuGameEngine::DifficultyLevel diffs[] = {
					SudokuGameEngine::DifficultyLevel::VeryEasy,
					SudokuGameEngine::DifficultyLevel::Easy,
					SudokuGameEngine::DifficultyLevel::Medium,
					SudokuGameEngine::DifficultyLevel::Hard,
					SudokuGameEngine::DifficultyLevel::VeryHard,
				};
				sudoku_dist::analyzeDifficultyDistribution(diffs[dchoice - 1], ns);
				input = 0;
				continue;
			}
			case 'E': case 'e':
				return 0;
				break;
			default:
				input = 0;
			}
		} while (input == 0);

		if (activityChoice != '1' && activityChoice != '4' && activityChoice != '6')
		{
			do
			{
				std::cout << "Choose engine version" << std::endl;
				std::cout << "1. Original engine" << std::endl;
				std::cout << "2. New engine (sudoku::)" << std::endl;
				std::cout << "B. Back" << std::endl;
				std::cout << "E. Exit" << std::endl;
				std::cout << "->";
				std::cin >> input;
				std::cout << std::endl;

				switch (input)
				{
				case '1': case '2':
					engineChoice = input;
					break;
				case 'B': case 'b':
					break;
				case 'E': case 'e':
					return 0;
				default:
					input = 0;
					break;
				}
			} while (input == 0);

			if (input == 'B' || input == 'b')
			{
				continue;
			}
		}

		if (activityChoice != '1' && activityChoice != '4')
		{
			do
			{
				std::cout << "Choose difficulty level" << std::endl;
				std::cout << "1. Very easy" << std::endl;
				std::cout << "2. Easy" << std::endl;
				std::cout << "3. Medium" << std::endl;
				std::cout << "4. Hard" << std::endl;
				std::cout << "5. Very hard" << std::endl;
				std::cout << "B. Back" << std::endl;
				std::cout << "E. Exit" << std::endl;
				std::cout << "->";
				std::cin >> input;
				std::cout << std::endl;

				switch (input)
				{
				case '1':
					difficulty = SudokuGameEngine::DifficultyLevel::VeryEasy;
					break;
				case '2':
					difficulty = SudokuGameEngine::DifficultyLevel::Easy;
					break;
				case '3':
					difficulty = SudokuGameEngine::DifficultyLevel::Medium;
					break;
				case '4':
					difficulty = SudokuGameEngine::DifficultyLevel::Hard;
					break;
				case '5':
					difficulty = SudokuGameEngine::DifficultyLevel::VeryHard;
					break;
					break;
				case 'B': case 'b':
					break;
				case 'E': case 'e':
					return 0;
				default:
					input = 0;
					break;
				}
			} while (input == 0);

			if (input == 'B' || input == 'b')
			{
				continue;
			}
		}

		if (activityChoice == '4')
		{
			if (engineChoice == '2')
			{
				sudoku::Generator<3> gen;
				const auto p = gen.generate(sudoku::Generator<3>::Difficulty::VeryEasy);
				std::cout << "sudoku::Generator combination:\n" << p.solution.toString() << std::endl;
			}
			else
			{
				engine.newCombination();
				std::cout << engine << std::endl;
			}
		}
		else if (activityChoice == '5')
		{
			if (engineChoice == '2')
			{
				sudoku::Generator<3> gen;
				const auto p = gen.generate(sudoku_bench::mapDifficulty(difficulty));
				std::cout << "sudoku::Generator new game:\n"
				          << "  givens:   " << p.givens.toString()   << "\n"
				          << "  solution: " << p.solution.toString() << std::endl;
			}
			else
			{
				engine.newGame(difficulty);
				std::cout << engine << std::endl;
			}
		}
		else if (activityChoice == '6')
		{
			// Comparison benchmark
			do
			{
				std::cout << "Number of iterations per loop" << std::endl;
				std::cout << "->";
				std::cin >> numberInput;
				try
				{
					iterations = std::stoi(numberInput);
				}
				catch (...)
				{
					std::cout << "Try again" << std::endl;
					iterations = 0;
				}
				std::cout << std::endl;
			} while (iterations <= 0);

			do
			{
				std::cout << "Number of loops" << std::endl;
				std::cout << "->";
				std::cin >> numberInput;
				try
				{
					loops = std::stoi(numberInput);
				}
				catch (...)
				{
					std::cout << "Try again" << std::endl;
					loops = 0;
				}
				std::cout << std::endl;
			} while (loops <= 0);

			std::cout << "========== ORIGINAL ENGINE ==========" << std::endl;
			long long originalTimeMicros = SudokuGameEngine::SudokuEngineBenchmark<IndexType, BooleanType, sizeFactor>::benchmarkGameSolving(difficulty, iterations, loops);
			std::cout << std::endl;

			std::cout << "========== NEW (sudoku::) ENGINE ==========" << std::endl;
			long long newTimeMicros = sudoku_bench::benchmarkGameSolving(difficulty, iterations, loops);
			std::cout << std::endl;

			std::cout << "========== COMPARISON ==========" << std::endl;
			std::cout << "Original time: " << originalTimeMicros << " microseconds (" << (originalTimeMicros / 1000000.0) << " seconds)" << std::endl;
			std::cout << "New time:      " << newTimeMicros << " microseconds (" << (newTimeMicros / 1000000.0) << " seconds)" << std::endl;
			if (newTimeMicros > 0)
				std::cout << "New vs Original: " << (static_cast<double>(originalTimeMicros) / static_cast<double>(newTimeMicros)) << "x faster" << std::endl;
			std::cout << std::endl;
		}
		else
		{
			do
			{
				std::cout << "Number of iterations per loop" << std::endl;
				std::cout << "->";
				std::cin >> numberInput;
				try
				{
					iterations = std::stoi(numberInput);
				}
				catch (...)
				{
					std::cout << "Try again" << std::endl;
					iterations = 0;
				}
				std::cout << std::endl;
			} while (iterations <= 0);
			
			do
			{
				std::cout << "Number of loops" << std::endl;
				std::cout << "->";
				std::cin >> numberInput;
				try
				{
					loops = std::stoi(numberInput);
				}
				catch (...)
				{
					std::cout << "Try again" << std::endl;
					loops = 0;
				}
				std::cout << std::endl;
			} while (loops <= 0);

			switch (activityChoice)
			{
			case '1':
				if (engineChoice == '2')
					sudoku_bench::benchmarkCombinationGeneration(iterations, loops);
				else
					SudokuGameEngine::SudokuEngineBenchmark<IndexType, BooleanType, sizeFactor>::benchmarkCombinationGeneration(iterations, loops);
				break;
			case '2':
				if (engineChoice == '2')
					sudoku_bench::benchmarkGameGeneration(difficulty, iterations, loops);
				else
					SudokuGameEngine::SudokuEngineBenchmark<IndexType, BooleanType, sizeFactor>::benchmarkGameGeneration(difficulty, iterations, loops);
				break;
			case '3':
				if (engineChoice == '2')
					sudoku_bench::benchmarkGameSolving(difficulty, iterations, loops);
				else
					SudokuGameEngine::SudokuEngineBenchmark<IndexType, BooleanType, sizeFactor>::benchmarkGameSolving(difficulty, iterations, loops);
				break;
			default:
				break;
			}
		}

		std::cout << std::endl;
	}

	return 0;
}
