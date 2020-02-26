// Danylo Fitel 2013

#include <iostream>
#include <string>
#include "SudokuEngine.h"
#include "SudokuEngineBenchmark.h"

typedef unsigned char IndexType;
typedef unsigned char BooleanType;
const IndexType sizeFactor = 3;

int main()
{
	SudokuGameEngine::SudokuEngine<IndexType, BooleanType, sizeFactor> engine;

	char input(0);
	char activityChoice(0);
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
			std::cout << "E. Exit" << std::endl;
			std::cout << "->";
			std::cin >> input;
			std::cout << std::endl;

			switch (input)
			{
			case '1': case '2': case '3': case '4': case '5':
				activityChoice = input;
				break;
			case 'E': case 'e':
				return 0;
				break;
			default:
				input = 0;
			}
		} while (input == 0);

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
			engine.newCombination();
			std::cout << engine << std::endl;
		}
		else if (activityChoice == '5')
		{
			engine.newGame(difficulty);
			std::cout << engine << std::endl;
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
				SudokuGameEngine::SudokuEngineBenchmark<IndexType, BooleanType, sizeFactor>::benchmarkCombinationGeneration(iterations, loops);
				break;
			case '2':
				SudokuGameEngine::SudokuEngineBenchmark<IndexType, BooleanType, sizeFactor>::benchmarkGameGeneration(difficulty, iterations, loops);
				break;
			case '3':
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