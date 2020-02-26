// Danylo Fitel 2013

#ifndef _SUDOKU_ENGINE_H_
#define _SUDOKU_ENGINE_H_

// Use iterative algorithm to solve puzzles
#undef USE_ITERATIVE_SOLVING_ALGORITHM

#include <algorithm>
#include <cassert>
#include <exception>
#include <iostream>
#include <limits>
#include <time.h>

// Namespace for Sudoku Engine
namespace SudokuGameEngine
{
	// Game difficulty levels
	enum class DifficultyLevel : unsigned char
	{
		VeryEasy,
		Easy,
		Medium,
		Hard,
		VeryHard
	};

	// Enumeration of possible engine states
	enum class SudokuEngineState : unsigned char
	{
		Empty,					// All cells are empty
		BeingEdited,			// Is being edited from outside, actual state undefined
		HasNoSolution,			// Does not have valid solution
		HasUniqueSolution,		// Is a valid puzzle with a unique solution
		HasMultipleSolutions,	// Invalid puzzle with multiple solutions
		NewGame,				// Is a valid puzzle with unique solution, all hidden cells are also valid
		FilledInvalid,			// Completely filled, but not with a valid combination
		FilledValid				// Completely filled with a valid combination
	};

	// Sudoku game engine class
	template <typename IndexType = unsigned char, typename BooleanType = unsigned char, IndexType sizeFactor = 3>
	class SudokuEngine
	{
	public:
		// Size of a single block
		static const IndexType sizeOfTheBlock()
		{
			return sizeFactor;
		}

		// Size of the board
		static const IndexType sizeOfTheBoard()
		{
			return boardSize;
		}

		// Number of cells on the board
		static const IndexType numberOfBoardCells()
		{
			return numberOfCells;
		}

		// Constructor
		SudokuEngine()
		{
			// Make sure the IndexType is integer type
			static_assert(std::numeric_limits<IndexType>::is_integer, "The IndexType has to be integer");

			// Make sure that the IndexType is unsigned
			static_assert(!std::numeric_limits<IndexType>::is_signed, "The IndexType has to be unsigned");

			// Make sure that the size factor is larger than one
			static_assert(sizeFactor > 1, "Sudoku game board size factor has to be larger than 1");

			// Make sure the IndexType is big enough
			static_assert(boardSize > sizeFactor && numberOfCells > boardSize, "The IndexType is not big enough");

			// Initialize random number generator
			srand(static_cast<unsigned int>(time(nullptr)));

			// Initialize the board
			this->initialize();

			// Initialize random sequence of numbers
			this->initializeNumbersToHide();

			return;
		}

		// Copy constructor
		SudokuEngine(const SudokuEngine & other)
		{
			// Copy everything from other
			this->copy(other);

			return;
		}

		// Move constructor
		SudokuEngine(SudokuEngine && other)
		{
			// Copy everything from other
			this->copy(other);

			return;
		}

		// Destructor
		~SudokuEngine()
		{
			return;
		}

		// Assignment operator
		SudokuEngine & operator =(const SudokuEngine & other)
		{
			// Copy everything from other
			this->copy(other);

			return;
		}

		// Get current state
		const SudokuEngineState currentState() const
		{
			return this->_state;
		}

		// Number of filled cells
		const IndexType numberOfFilledCells() const
		{
			return this->_numberOfFilledCells;
		}

		// Number of free cells
		const IndexType numberOfFreeCells() const
		{
			return numberOfCells - this->_numberOfFilledCells;
		}

		// Access by index, returns values only for filled cells, 0 for hidden
		const IndexType operator ()(const IndexType row, const IndexType column) const
		{
			// Check the range of arguments
			if (row < 0 || row > boardSize - 1 || column < 0 || column > boardSize - 1)
			{
				throw std::invalid_argument("Operator () arguments out of range");
			}

			// If the cell it filled, return its value
			if (this->_filled[row][column])
			{
				return this->_value[row][column];
			}
			// Otherwise return 0
			else
			{
				return 0;
			}
		}

		// Filled state of the cell
		const bool getFilled(const IndexType row, const IndexType column) const
		{
			// Check the range of arguments
			if (row < 0 || row > boardSize - 1 || column < 0 || column > boardSize - 1)
			{
				throw std::invalid_argument("Cell filled state selector arguments out of range");
			}

			return (this->_filled[row][column] == 1);
		}

		// Filled state of the cell
		void setFilled(const IndexType row, const IndexType column, const bool filled)
		{
			// Check the range of arguments
			if (row < 0 || row > boardSize - 1 || column < 0 || column > boardSize - 1)
			{
				throw std::invalid_argument("Cell filled state modifier arguments out of range");
			}

			// Change the cell filled state and update the number of filled cells
			if ((this->_filled[row][column] == 1) != filled)
			{
				if (filled)
				{
					++(this->_numberOfFilledCells);
				}
				else
				{
					--(this->_numberOfFilledCells);
				}
			}

			this->_filled[row][column] = filled;

			// Change the engine state
			this->_solutions = 0;
			this->_state = SudokuEngineState::BeingEdited;

			return;
		}

		// Cell value selector
		const IndexType getCellValue(const IndexType row, const IndexType column) const
		{
			// Check the range of arguments
			if (row < 0 || row > boardSize - 1 || column < 0 || column > boardSize - 1)
			{
				throw std::invalid_argument("Cell selector arguments out of range");
			}

			return this->_value[row][column];
		}

		// Cell value modifier
		void setCellValue(const IndexType row, const IndexType column, const IndexType value)
		{
			// Check the range of arguments
			if (row < 0 || row > boardSize - 1 || column < 0 || column > boardSize - 1 || value < 0 || value > boardSize)
			{
				throw std::invalid_argument("Cell modifier arguments out of range");
			}

			// Fill the cell with the value
			this->_value[row][column] = value;

			// Change the engine state
			this->_solutions = 0;
			this->_state = SudokuEngineState::BeingEdited;

			return;
		}

		// Clear the board
		void clear()
		{
			// Clear the board
			this->initialize();

			return;
		}

		// Show solution of a new game
		const bool showSolution()
		{
			// Get the current state
			this->updateState();

			// If the engine state is NewGame, show solution
			if (this->_state == SudokuEngineState::NewGame)
			{
				for (IndexType i = 0; i < boardSize; ++i)
				{
					for (IndexType j = 0; j < boardSize; ++j)
					{
						if (this->_filled[i][j] == 0)
						{
							this->_filled[i][j] = 1;
							++this->_numberOfFilledCells;
						}
					}
				}

				// Check if all cells have been shown
				assert(this->_numberOfFilledCells == numberOfCells);

				// Change the state
				this->_state = SudokuEngineState::FilledValid;

				// The solution was shown
				return true;
			}
			else
			{
				// The engine is not in proper state
				return false;
			}
		}

		// Fill the board with new random combination
		void newCombination()
		{
			// Clear the board
			this->initialize();

			// Generate valid combination
			this->generateFullBoard();

			return;
		}

		// Generate new game
		void newGame(const DifficultyLevel difficulty)
		{
			// Number of cells that need to be hidden
			IndexType cellsToHide(0);

			// Number of cells that typically can be hidden without increasing the number of solutions
			IndexType cellsToHideFirst(0);

			// Select the number of hidden cells depending on the difficulty level
			switch (difficulty)
			{
				case DifficultyLevel::VeryEasy:
					cellsToHide = (sizeFactor <= 3 ? 39 : 25) * numberOfCells / 100;
					cellsToHideFirst = (sizeFactor <= 3 ? 39 : 20) * numberOfCells / 100;
					break;
				case DifficultyLevel::Easy:
					cellsToHide = (sizeFactor <= 3 ? 48 : 30) * numberOfCells / 100;
					cellsToHideFirst = (sizeFactor <= 3 ? 45 : 25) * numberOfCells / 100;
					break;
				case DifficultyLevel::Medium:
					cellsToHide = (sizeFactor <= 3 ? 56 : 35) * numberOfCells / 100;
					cellsToHideFirst = (sizeFactor <= 3 ? 50 : 30) * numberOfCells / 100;
					break;
				case DifficultyLevel::Hard:
					cellsToHide = (sizeFactor <= 3 ? 65 : 40) * numberOfCells / 100;
					cellsToHideFirst = (sizeFactor <= 3 ? 55 : 35) * numberOfCells / 100;
					break;
				case DifficultyLevel::VeryHard:
					cellsToHide = (sizeFactor <= 3 ? 80 : 50) * numberOfCells / 100;
					cellsToHideFirst = (sizeFactor <= 3 ? 65 : 45) * numberOfCells / 100;
					break;
			}

			// Clear the board
			this->initialize();

			// Generate valid combination
			this->generateFullBoard();

			// Hide specified number of cells
			this->hideCells(cellsToHide, cellsToHideFirst);

			return;
		}

		// Check if the current puzzle has a unique solution
		const SudokuEngineState updateState()
		{
			// The state needs to be updated only if it is BeingEdited
			if (this->_state == SudokuEngineState::BeingEdited)
			{
				// Check if number of solutions is set to 0
				assert(this->_solutions == 0);

				// Check if the board is not empty
				if (this->_numberOfFilledCells == 0)
				{
					this->_state = SudokuEngineState::Empty;
				}
				// Check if the board is completely filled
				else if (this->_numberOfFilledCells == numberOfCells)
				{
					// If the solution is valid, change the state
					if (this->noConflictsExist())
					{
						this->_solutions = 1;
						this->_state = SudokuEngineState::FilledValid;
					}
					// Else if the solution is invalid, change the state
					else
					{
						this->_solutions = 0;
						this->_state = SudokuEngineState::FilledInvalid;
					}
				}
				// Otherwise calculate the number of solutions
				else
				{
					// Check if there are no obvious conflicts
					if (this->noConflictsExist())
					{
						// Calculate the number of solutions
						this->calculateSolutions();
					}
					// There are no solutions
					else
					{
						this->_solutions = 0;
					}

					// If it has no solutions
					if (this->_solutions == 0)
					{
						this->_state = SudokuEngineState::HasNoSolution;
					}
					// If it has a unique solution
					else if (this->_solutions == 1)
					{
						this->_state = SudokuEngineState::HasUniqueSolution;
					}
					// If it has multiple solutions
					else if (this->_solutions > 1)
					{
						this->_state = SudokuEngineState::HasMultipleSolutions;
					}
				}
			}

			// Check if the state is no longer BeingEdited
			assert(this->_state != SudokuEngineState::BeingEdited);

			// Return current state
			return this->_state;
		}

		// Try to solve the puzzle
		const SudokuEngineState trySolve()
		{
			// Update the state of the engine
			this->updateState();

			// If the original puzzle was not modified, the hidden cells need to be shown
			if (this->_state == SudokuEngineState::NewGame)
			{
				// Check if the number of solutions is properly set
				assert(this->_solutions == 1);

				for (IndexType i = 0; i < boardSize; ++i)
				{
					for (IndexType j = 0; j < boardSize; ++j)
					{
						if (this->_filled[i][j] == 0)
						{
							this->_filled[i][j] = 1;
							++this->_numberOfFilledCells;
						}
					}
				}

				// Check if all the cells are filled
				assert(this->_numberOfFilledCells == numberOfCells);

				// Check if the solution is correct
				assert(this->noConflictsExist());

				// Change the engine state
				this->_state = SudokuEngineState::FilledValid;
			}
			// Else, the puzzle can be solved only if it has a unique solution
			else if (this->_state == SudokuEngineState::HasUniqueSolution)
			{
				// Check if the number of solutions is properly set
				assert(this->_solutions == 1);

				// In this case the puzzle is not complete
				assert(this->_numberOfFilledCells < numberOfCells);

				// Solve the current puzzle
				this->solvePuzzle();

				// Check if all the cells are filled
				assert(this->_numberOfFilledCells == numberOfCells);

				// Check if the number of solutions is still 1
				assert(this->_solutions == 1);

				// Check if the solution is correct
				assert(this->noConflictsExist());

				// Change the engine state
				this->_state = SudokuEngineState::FilledValid;
			}

			// Return current state
			return this->_state;
		}

	private:
		// Size of the board
		static const IndexType boardSize = sizeFactor * sizeFactor;

		// Number of cells on the board
		static const IndexType numberOfCells = boardSize * boardSize;

#ifdef USE_ITERATIVE_SOLVING_ALGORITHM

		// Stack for storing filled cells, cell index variable indicates the next free index
		IndexType rowIndexStack[numberOfCells];
		IndexType rowIndexStackIndex;
		IndexType columnIndexStack[numberOfCells];
		IndexType columnIndexStackIndex;
		IndexType valueStack[numberOfCells];
		IndexType valueStackIndex;

#endif

		// Values
		IndexType _value[boardSize][boardSize];

		// Filled state flags
		BooleanType _filled[boardSize][boardSize];

		// Number has been tried state flags
		BooleanType _tried[boardSize][boardSize][boardSize];

		// Number of tried values per cell
		IndexType _numberOfTried[boardSize][boardSize];

		// Random sequence of cells that will be hidden in that order
		IndexType _numbersToHide[numberOfCells];

		// Cache of possible candidates per cell
		IndexType _candidatesCache[boardSize];

		// Number of filled cells
		IndexType _numberOfFilledCells;

		// Number of solutions
		IndexType _solutions;

		// Current state of the engine
		SudokuEngineState _state;

		// Get next cell
		static void makeNextCell(IndexType & row, IndexType & column)
		{
			// Check if the cell is not the last on the board
			assert(!(row == boardSize && column == boardSize));

			// If this is not the last cell in a row
			if (column < boardSize - 1)
			{
				// Go to the next cell in a row
				++column;
			}
			// Else if it is the last cell in a row
			else
			{
				// Go to the first cell of the next row
				column = 0;
				++row;
			}

			// Check if the range is valid
			assert(row >= 0 && row < boardSize && column >= 0 && column < boardSize);

			return;
		}

		// Get previous cell
		static void makePreviousCell(IndexType & row, IndexType & column)
		{
			// Check if the cell is not the first on the board
			assert(!(row == 0 && column == 0));

			// If this is not the first cell in a row
			if (column > 0)
			{
				// Go to the previous cell in a row
				--column;
			}
			// Else if it is the first cell in a row
			else
			{
				// Go to the last cell of the previous row
				column = boardSize - 1;
				--row;
			}

			// Check if the cell index is in valid range
			assert(row >= 0 && row < boardSize && column >= 0 && column < boardSize);

			return;
		}

		// Initializate the board
		void initialize()
		{
			// Iterate through each cell
			for (IndexType i = 0; i < boardSize; ++i)
			{
				for (IndexType j = 0; j < boardSize; ++j)
				{
					// Reset the value
					this->_value[i][j] = 0;

					// Hide the cell
					this->_filled[i][j] = 0;

					// Reset the number of tried values
					this->_numberOfTried[i][j] = 0;

					// Reset the number tried flags
					for (IndexType k = 0; k < boardSize; ++k)
					{
						this->_tried[i][j][k] = 0;
					}
				}
			}

			// Reset the number of filled cells
			this->_numberOfFilledCells = 0;

			// Reset the number of solutions
			this->_solutions = 0;

			// Reset the state
			this->_state = SudokuEngineState::Empty;

			return;
		}

		// Initialize random sequence of cells to hide
		void initializeNumbersToHide()
		{
			for (IndexType i = 0; i < this->numberOfCells; ++i)
			{
				this->_numbersToHide[i] = i;
			}
		}

		// Copy the board
		void copy(const SudokuEngine& other)
		{
			// Iterate through each cell
			for (IndexType i = 0; i < boardSize; ++i)
			{
				for (IndexType j = 0; j < boardSize; ++j)
				{
					// Copy the cell value
					this->_value[i][j] = other._value[i][j];

					// Copy the cell state
					this->_filled[i][j] = other._filled[i][j];

					// Copy number of tried values
					this->_numberOfTried[i][j] = other._numberOfTried[i][j];

					// Copy random sequence of numbers to hide
					this->_numbersToHide[i * boardSize + j] = other._numbersToHide[i * boardSize + j];

					// Copy the cell tried values flags
					for (IndexType k = 0; k < boardSize; ++k)
					{
						this->_tried[i][j][k] = other._tried[i][j][k];
					}
				}
			}

			// Copy the number of filled cells
			this->_numberOfFilledCells = other._numberOfFilledCells;

			// Copy the number of solutions
			this->_solutions = other._solutions;

			// Copy state of the engine
			this->_state = other._state;

			return;
		}

		// Check if number is valid for a cell
		const bool checkNumber(const IndexType row, const IndexType column, const IndexType number) const
		{
			// Check if the method has been called for a hidden cell
			assert(this->_filled[row][column] == 0);

			// Iterate through each cell in a row
			for (IndexType i = 0; i < boardSize; ++i)
			{
				// Check if it contains the value
				if (this->_value[row][i] == number && this->_filled[row][i])
				{
					return false;
				}
			}

			// Iterate through each cell in a column
			for (IndexType i = 0; i < boardSize; ++i)
			{
				// Check if it contains the value
				if (this->_value[i][column] == number && this->_filled[i][column])
				{
					return false;
				}
			}

			// Row number of the first cell in the block
			const IndexType rBegin((row / sizeFactor) * sizeFactor);

			// Column number of the first cell in the block
			const IndexType cBegin((column / sizeFactor) * sizeFactor);

			// Row number after the last cell in the block
			const IndexType rEnd(rBegin + sizeFactor);

			// Column number after the last cell in the block
			const IndexType cEnd(cBegin + sizeFactor);

			// Iterate through each cell in the block
			for (IndexType i = rBegin; i < rEnd; ++i)
			{
				for (IndexType j = cBegin; j < cEnd; ++j)
				{
					// Check if it contains the value
					if ((this->_value[i][j] == number) && this->_filled[i][j])
					{
						return false;
					}
				}
			}

			// The number does not conflict with existing ones
			return true;
		}

		// Check if no two or more numbers are in the same row, column or block
		const bool noConflictsExist()
		{
			// If the board is empty, there can be no conflicts
			if (this->_numberOfFilledCells == 0)
			{
				return true;
			}

			// Temporary bool value indicating whether value of current cell is valid
			bool validValue(false);

			// Iterathe through each cell
			for (IndexType i = 0; i < boardSize; ++i)
			{
				for (IndexType j = 0; j < boardSize; ++j)
				{
					// If the cell is filled
					if (this->_filled[i][j])
					{
						// Hide it temporarily
						this->_filled[i][j] = 0;

						// Check if its value is allowed
						validValue = this->checkNumber(i, j, this->_value[i][j]);

						// Show the cell again
						this->_filled[i][j] = 1;

						// Return false immediately if the conflict was found
						if (!validValue)
						{
							return false;
						}
					}
				}
			}

			// No conflicts were found
			return true;
		}

		// Number of possible valid candidates for a cell
		const IndexType numberOfCandidates(const IndexType row, const IndexType column)
		{
			// Check if the cell is empty
			assert(this->_filled[row][column] == 0);

			// Number of candidates
			for (IndexType i = 0; i < this->boardSize; ++i)
			{
				this->_candidatesCache[i] = 1;
			}

			// Iterate through each cell in a row
			for (IndexType i = 0; i < this->boardSize; ++i)
			{
				// Check if cell in a row contains the value
				if (this->_filled[row][i])
				{
					this->_candidatesCache[this->_value[row][i] - 1] = 0;
				}

				// Check if cell in a column contains the value
				if (this->_filled[i][column])
				{
					this->_candidatesCache[this->_value[i][column] - 1] = 0;
				}
			}

			// Row number of the first cell in the block
			const IndexType rBegin((row / sizeFactor) * sizeFactor);

			// Column number of the first cell in the block
			const IndexType cBegin((column / sizeFactor) * sizeFactor);

			// Row number after the last cell in the block
			const IndexType rEnd(rBegin + sizeFactor);

			// Column number after the last cell in the block
			const IndexType cEnd(cBegin + sizeFactor);

			// Iterate through each cell in the block
			for (IndexType i = rBegin; i < rEnd; ++i)
			{
				for (IndexType j = cBegin; j < cEnd; ++j)
				{
					// Check if it contains the value
					if (this->_filled[i][j])
					{
						this->_candidatesCache[this->_value[i][j] - 1] = 0;
					}
				}
			}

			IndexType result = 0;
			for (IndexType i = 0; i < this->boardSize; ++i)
			{
				result += this->_candidatesCache[i];
			}

			return result;
		}

		// Find a cell with minimal number of possible variants
		const IndexType cellWithMinCandidates(IndexType & row, IndexType & column)
		{
			// Check if the method has not been called for a filled board
			assert(this->_numberOfFilledCells < numberOfCells);

			// Index of the current cell with minimal number of candidates
			IndexType r(0);
			IndexType c(0);

			// Current minimal number of candidates
			IndexType min(boardSize);

			// Iterathe through each cell
			for (IndexType i = 0; i < boardSize; ++i)
			{
				for (IndexType j = 0; j < boardSize; ++j)
				{
					// If the cell is filled, it doesn't have any candidates
					if (!this->_filled[i][j])
					{
						// Calculate the number of candidates for current cell
						IndexType variants(this->numberOfCandidates(i, j));

						// If it has only one candidate, return this cell
						if (variants == 1)
						{
							row = i;
							column = j;
							return variants;
						}
						// If the number of candidates in a new cell is smaller, save it as current cell with min candidates
						else if (variants < min)
						{
							min = variants;
							r = i;
							c = j;
						}
					}
				}
			}

			// Return the result
			row = r;
			column = c;

			// Return the minimal number of variants found
			return min;
		}

		// Fill the board with a valid combination
		void generateFullBoard()
		{
			// Check if the method is called for an empty board
			assert(this->_numberOfFilledCells == 0);

			// Current cell index
			IndexType currentRow(0);
			IndexType currentColumn(0);

			// Fill the next cell while the last cell has not been filled
			while (this->_numberOfFilledCells < numberOfCells)
			{
				// The last cell is not supposed to be filled at the moment
				assert(this->_filled[currentRow][currentColumn] == 0);

				// If not all numbers have been tried for the current cell
				if (this->_numberOfTried[currentRow][currentColumn] < boardSize)
				{
					// Check if the cell is empty
					assert(this->_filled[currentRow][currentColumn] == 0);

					// Find a new candidate that has not been tried yet
					IndexType candidate = 0;
					do
					{
						candidate = static_cast<IndexType>(rand()) % boardSize + 1;
					} while (this->_tried[currentRow][currentColumn][candidate - 1]);

					// Check if the candidate is in valid range
					assert(candidate > 0 && candidate <= boardSize);

					// Mark the cell as tried
					this->_tried[currentRow][currentColumn][candidate - 1] = 1;
					++(this->_numberOfTried[currentRow][currentColumn]);

					// If it is a possible candidate
					if (this->checkNumber(currentRow, currentColumn, candidate))
					{
						// Fill current cell with the value
						this->_value[currentRow][currentColumn] = candidate;
						this->_filled[currentRow][currentColumn] = 1;

						// Increase the counter of filled cells
						++(this->_numberOfFilledCells);

						// If it is not the last cell, go to the next cell
						if (this->_numberOfFilledCells < numberOfCells)
						{
							makeNextCell(currentRow, currentColumn);
						}
					}
				}
				// Else if all numbers have been tried for this cell
				else
				{
					// Reset current cell
					this->_value[currentRow][currentColumn] = 0;
					this->_filled[currentRow][currentColumn] = 0;
					this->_numberOfTried[currentRow][currentColumn] = 0;
					for (IndexType i = 0; i < boardSize; ++i)
					{
						this->_tried[currentRow][currentColumn][i] = 0;
					}

					// Decrease the counter of filled cells
					--(this->_numberOfFilledCells);

					// Check if the cell with no more candidates is not the first one
					assert(currentRow != 0 || currentColumn != 0);

					// Go back to the previous cell
					this->makePreviousCell(currentRow, currentColumn);

					// Clear the value because it is not a candidate
					this->_filled[currentRow][currentColumn] = 0;
				}
			}

			assert(this->_numberOfFilledCells == numberOfCells);

			// Clear all tried number flags
			for (IndexType i = 0; i < boardSize; ++i)
			{
				for (IndexType j = 0; j < boardSize; ++j)
				{
					this->_numberOfTried[i][j] = 0;

					for (IndexType k = 0; k < boardSize; ++k)
					{
						this->_tried[i][j][k] = 0;
					}
				}
			}

			// This is the unique solution
			this->_solutions = 1;

			// Change the engine state
			this->_state = SudokuEngineState::FilledValid;

			return;
		}

#ifdef USE_ITERATIVE_SOLVING_ALGORITHM

		// Solves the proposed puzzle
		void solvePuzzle()
		{
			// Of the board is filled completely, this already is a unique solution
			if (this->_numberOfFilledCells < numberOfCells)
			{
				// Reset the stack
				this->rowIndexStackIndex = 0;
				this->columnIndexStackIndex = 0;
				this->valueStackIndex = 0;

				// Current index
				IndexType currentRow(0);
				IndexType currentColumn(0);

				// Find the first cell for filling
				this->cellWithMinCandidates(currentRow, currentColumn);

				// Push the first cell into the stack
				this->rowIndexStack[this->rowIndexStackIndex++] = currentRow;
				this->columnIndexStack[this->columnIndexStackIndex++] = currentColumn;
				this->valueStack[this->valueStackIndex++] = this->_value[currentRow][currentColumn];

				// Indicates whether a break from the inner loop should also break the current iteration of the main loop
				bool breakToTheMainLoop(false);

				// Run the main loop until no more solutions remain
				do
				{
					// Check if all stack indexes are synchronized
					assert((this->valueStackIndex == this->rowIndexStackIndex) && (this->rowIndexStackIndex == this->columnIndexStackIndex));

					// Try all candidates for the cell
					for (IndexType i = 1; i <= boardSize; ++i)
					{
						// If this candidate has not been tried yet
						if (!(this->_tried[currentRow][currentColumn][i - 1]))
						{
							// If it is a possible candidate
							if (this->checkNumber(currentRow, currentColumn, i))
							{
								// Temporarily fill the cell with this candidate
								this->_value[currentRow][currentColumn] = i;
								this->_filled[currentRow][currentColumn] = 1;
								this->_tried[currentRow][currentColumn][i - 1] = 1;
								++(this->_numberOfFilledCells);

								// If all cells are filled
								if (this->_numberOfFilledCells == numberOfCells)
								{
									// Check if the puzzle has unique solution
									assert(this->_solutions == 1);

									// The puzzle has been solved
									return;
								}

								// Find the next cell with the least number of possible candidates
								this->cellWithMinCandidates(currentRow, currentColumn);

								// Push the cell into the stack
								this->rowIndexStack[this->rowIndexStackIndex++] = currentRow;
								this->columnIndexStack[this->columnIndexStackIndex++] = currentColumn;
								this->valueStack[this->valueStackIndex++] = this->_value[currentRow][currentColumn];

								// Back to the main loop and fill the next cell
								breakToTheMainLoop = true;
								break;
							}
							// If it is not a candidate
							else
							{
								// Mark it as tried
								this->_tried[currentRow][currentColumn][i - 1] = 1;
							}
						}
					}

					// Continue the main loop if needed
					if (breakToTheMainLoop)
					{
						breakToTheMainLoop = false;
						continue;
					}

					// All candidates have been tried

					// Reset the cell value
					this->_value[currentRow][currentColumn] = this->valueStack[this->valueStackIndex - 1];
					--this->valueStackIndex;

					// Reset the cell filled state
					this->_filled[currentRow][currentColumn] = 0;

					// Decrement the counter of filled cells
					--(this->_numberOfFilledCells);

					// Clear the tried flags for the cell
					for (IndexType i = 0; i < boardSize; ++i)
					{
						this->_tried[currentRow][currentColumn][i] = 0;
					}

					// Return to the previous cell
					--this->rowIndexStackIndex;
					--this->columnIndexStackIndex;

					// Update the current cell value if more cells remain in the stack
					if (this->rowIndexStackIndex > 0)
					{
						// Check if row index stack and row column stack are synchronized
						assert(this->columnIndexStackIndex > 0);

						currentRow = this->rowIndexStack[this->rowIndexStackIndex - 1];
						currentColumn = this->columnIndexStack[this->columnIndexStackIndex - 1];
					}

					// Clear the value because it is not a candidate
					this->_filled[currentRow][currentColumn] = 0;
				} while (this->_numberOfFilledCells < numberOfCells);

				// Check if all stack indexes are synchronized
				assert((this->valueStackIndex == this->rowIndexStackIndex) && (this->rowIndexStackIndex == this->columnIndexStackIndex));
			}

			// Check if all cells are filled
			assert(this->_numberOfFilledCells == numberOfCells);

			// Check if the puzzle has unique solution
			assert(this->_solutions == 1);

			return;
		}

		// Calculate the number of solutions of a puzzle (if more than one, stop calculation)
		const IndexType calculateSolutions()
		{
			// Check if the method has not been called for an empty board
			assert(this->_numberOfFilledCells > 0);

			// Check if the number of solutions has been reset before the method call
			assert(this->_solutions == 0);

			// Of the board is filled completely, this already is a unique solution
			if (this->_numberOfFilledCells == numberOfCells)
			{
				return 1;
			}

#ifndef NDEBUG

			// Remember the number of filled cells before computation
			const IndexType filledBeforeCall(this->_numberOfFilledCells);

#endif

			// Reset the stack
			this->rowIndexStackIndex = 0;
			this->columnIndexStackIndex = 0;
			this->valueStackIndex = 0;

			// Current index
			IndexType currentRow(0);
			IndexType currentColumn(0);

			// Find the first cell for filling
			this->cellWithMinCandidates(currentRow, currentColumn);

			// Push the first cell into the stack
			this->rowIndexStack[this->rowIndexStackIndex++] = currentRow;
			this->columnIndexStack[this->columnIndexStackIndex++] = currentColumn;
			this->valueStack[this->valueStackIndex++] = this->_value[currentRow][currentColumn];

			// Indicates whether a break from the inner loop should also break the current iteration of the main loop
			bool breakToTheMainLoop(false);

			// Run the main loop until no more solutions remain
			do
			{
				// Check if all stack indexes are synchronized
				assert((this->valueStackIndex == this->rowIndexStackIndex) && (this->rowIndexStackIndex == this->columnIndexStackIndex));

				// If the number of solution already exceeds 1, there's no need to continue
				if (this->_solutions > 1)
				{
					break;
				}

				// Otherwise continue filling the board

				// Try all candidates for the cell
				for (IndexType i = 1; i <= boardSize; ++i)
				{
					// If this candidate has not been tried yet
					if (!(this->_tried[currentRow][currentColumn][i - 1]))
					{
						// If it is a possible candidate
						if (this->checkNumber(currentRow, currentColumn, i))
						{
							// Temporarily fill the cell with this candidate
							this->_value[currentRow][currentColumn] = i;
							this->_filled[currentRow][currentColumn] = 1;
							this->_tried[currentRow][currentColumn][i - 1] = 1;
							++(this->_numberOfFilledCells);

							// If all cells are filled
							if (this->_numberOfFilledCells == numberOfCells)
							{
								// Increase the number of solutions
								++(this->_solutions);

								// Reset the last cell
								this->_value[currentRow][currentColumn] = this->valueStack[this->valueStackIndex - 1];
								this->_filled[currentRow][currentColumn] = 0;
								for (IndexType j = i; j < boardSize; ++j)
								{
									this->_tried[currentRow][currentColumn][j] = 1;
								}

								--(this->_numberOfFilledCells);

								// Break to the main loop
								breakToTheMainLoop = true;
								break;
							}

							// Find the next cell with the least number of possible candidates
							this->cellWithMinCandidates(currentRow, currentColumn);

							// Push the cell into the stack
							this->rowIndexStack[this->rowIndexStackIndex++] = currentRow;
							this->columnIndexStack[this->columnIndexStackIndex++] = currentColumn;
							this->valueStack[this->valueStackIndex++] = this->_value[currentRow][currentColumn];

							// Back to the main loop
							breakToTheMainLoop = true;
							break;
						}
						// If it is not a candidate
						else
						{
							// Mark it as tried
							this->_tried[currentRow][currentColumn][i - 1] = 1;
						}
					}
				}

				// Continue the main loop if needed
				if (breakToTheMainLoop)
				{
					breakToTheMainLoop = false;
					continue;
				}

				// All candidates have been tried

				// Reset the cell value
				this->_value[currentRow][currentColumn] = this->valueStack[this->valueStackIndex - 1];
				--this->valueStackIndex;

				// Reset the cell filled state
				this->_filled[currentRow][currentColumn] = 0;

				// Decrement the counter of filled cells
				--(this->_numberOfFilledCells);

				// Clear the tried flags for the cell
				for (IndexType i = 0; i < boardSize; ++i)
				{
					this->_tried[currentRow][currentColumn][i] = 0;
				}

				// Return to the previous cell
				--this->rowIndexStackIndex;
				--this->columnIndexStackIndex;

				// Update the current cell value if more cells remain in the stack
				if (this->rowIndexStackIndex > 0)
				{
					// Check if row index stack and row column stack are synchronized
					assert(this->columnIndexStackIndex > 0);

					currentRow = this->rowIndexStack[this->rowIndexStackIndex - 1];
					currentColumn = this->columnIndexStack[this->columnIndexStackIndex - 1];
				}

				// Clear the value because it is not a candidate
				this->_filled[currentRow][currentColumn] = 0;
			} while (this->valueStackIndex > 0);

			// Check if all stack indexes are synchronized
			assert((this->valueStackIndex == this->rowIndexStackIndex) && (this->rowIndexStackIndex == this->columnIndexStackIndex));

			// Reset all remaining cells to their initial state
			while (this->valueStackIndex > 0)
			{
				// Get current index
				currentRow = this->rowIndexStack[this->rowIndexStackIndex - 1];
				currentColumn = this->columnIndexStack[this->columnIndexStackIndex - 1];

				// Reset the cell value
				this->_value[currentRow][currentColumn] = this->valueStack[this->valueStackIndex - 1];
				--this->valueStackIndex;
				this->_filled[currentRow][currentColumn] = 0;
				--(this->_numberOfFilledCells);

				// Clear all tried number flags
				for (IndexType i = 0; i < boardSize; ++i)
				{
					this->_tried[currentRow][currentColumn][i] = 0;
				}

				// Return to the previous cell
				--this->rowIndexStackIndex;
				--this->columnIndexStackIndex;

				// Check if all stack indexes are synchronized
				assert((this->valueStackIndex == this->rowIndexStackIndex) && (this->rowIndexStackIndex == this->columnIndexStackIndex));
			}

			// The value was decremented extra time when the last element from the stack was removed
			++this->_numberOfFilledCells;

			// Check if number of filled cells has not changed
			assert(filledBeforeCall == this->_numberOfFilledCells);

			// Return the number of solutions found
			return this->_solutions;
		}

#else

		// Solves the proposed puzzle
		void solvePuzzle()
		{
			// If not all cells have been filled yet
			if (this->_numberOfFilledCells < numberOfCells)
			{
				// Find next free cell with minimal number of candidates
				IndexType minCellRow(0);
				IndexType minCellColumn(0);
				this->cellWithMinCandidates(minCellRow, minCellColumn);

				// Check all numbers for the cell
				for (IndexType i = 1; i <= boardSize; ++i)
				{
					// If the number is a possible candidate, try to fill the cell with it
					if (this->checkNumber(minCellRow, minCellColumn, i))
					{
						// Fill the cell
						this->_value[minCellRow][minCellColumn] = i;

						// Mark the cell as filled
						this->_filled[minCellRow][minCellColumn] = 1;

						++(this->_numberOfFilledCells);

						// Proceed to the next step
						this->solvePuzzle();

						// If the puzzle has been solved, exit immediately
						if (this->_numberOfFilledCells == numberOfCells)
						{
							break;
						}
						// The cell was not filled on this iteration
						else
						{
							this->_filled[minCellRow][minCellColumn] = 0;
							--(this->_numberOfFilledCells);
						}
					}
				}
			}

			return;
		}

		// Solve the game and calculate the number of solutions (if more than one, stop calculation)
		const IndexType calculateSolutions()
		{
			// If the number of solutions has exceeded 1, return
			if (this->_solutions > 1)
			{
				return this->_solutions;
			}

			// If the last cell has been filled before this call
			if (this->_numberOfFilledCells == numberOfCells)
			{
				// Increase the number of solutions
				++(this->_solutions);
			}
			else
			{
				// Find next free cell with minimal number of candidates
				IndexType minCellRow(0);
				IndexType minCellColumn(0);
				this->cellWithMinCandidates(minCellRow, minCellColumn);

				// Remember the original value
				IndexType originalValue = this->_value[minCellRow][minCellColumn];

				// Check all numbers for the cell
				for (IndexType i = 1; i <= boardSize; ++i)
				{
					// If the number is a possible candidate, try to fill the cell with it
					if (this->checkNumber(minCellRow, minCellColumn, i))
					{
						// Fill the cell
						this->_value[minCellRow][minCellColumn] = i;

						// Mark the cell as filled
						this->_filled[minCellRow][minCellColumn] = 1;

						++(this->_numberOfFilledCells);

						// Proceed to the next step
						this->calculateSolutions();

						// Reset the cell to its original state
						this->_value[minCellRow][minCellColumn] = originalValue;

						// Hide the call back
						this->_filled[minCellRow][minCellColumn] = 0;

						--(this->_numberOfFilledCells);

						// If found more than 1 solution, exit immediately
						if (this->_solutions > 1)
						{
							return this->_solutions;
						}
					}
				}
			}

			return this->_solutions;
		}

#endif

		// Hide the specified number of cells in a filled board
		const bool hideCells(const IndexType numberOfCellsToHide, const IndexType numberOfCellsToHideFirst)
		{
			// Check if the method has been called for a completely filled game board
			assert(this->_numberOfFilledCells == this->numberOfCells);

			// Check if the number of cells to hide parameter is valid
			assert(numberOfCellsToHide < this->numberOfCells);

			// Check if the number of cells to hide first is not greater than the number of cells to hide
			assert(numberOfCellsToHideFirst <= numberOfCellsToHide);

			// Randomly shuffle the sequence of numbers to hide
			std::random_shuffle<IndexType*>(&(this->_numbersToHide[0]), &(this->_numbersToHide[this->numberOfCells]));

			// Number of hidden cells
			IndexType hidden(0);

			// Random next cell
			IndexType randomValue(0);
			IndexType row(0);
			IndexType column(0);
			IndexType index(0);

			// Hide the first block of cells without checking for unique solution
			for (index = 0; hidden < numberOfCellsToHideFirst && index < this->numberOfCells; ++index)
			{
				// Get index of next random cell
				randomValue = this->_numbersToHide[index];
				row = randomValue / boardSize;
				column = randomValue % boardSize;

				// Hide the cell
				this->_filled[row][column] = 0;
				--(this->_numberOfFilledCells);
				++hidden;
			}

			// Index of the next unchecked random cell
			IndexType nextIndex(index);

			// Restore last previously hidden cells while multiple solutions remain
			while (this->_solutions = 0, this->calculateSolutions() > 1)
			{
				// Get index of next random cell
				randomValue = this->_numbersToHide[--index];
				row = randomValue / boardSize;
				column = randomValue % boardSize;

				// Restore the cell
				this->_filled[row][column] = 1;
				++(this->_numberOfFilledCells);
				--hidden;
			}

			// Check if the solution is unique at this point
			assert(this->_solutions == 1);

			// Hide remaining cells if possible
			for (; hidden < numberOfCellsToHide && nextIndex < this->numberOfCells; ++nextIndex)
			{
				// Get index of next random cell
				randomValue = this->_numbersToHide[nextIndex];
				row = randomValue / boardSize;
				column = randomValue % boardSize;

				// Hide the cell
				this->_filled[row][column] = 0;
				--(this->_numberOfFilledCells);

				// Reset the number of solutions
				this->_solutions = 0;

				// If the game has a unique solution
				if (this->calculateSolutions() == 1)
				{
					// Increase the counter and go to the next cell
					++hidden;
				}
				// If there are multiple solutions
				else
				{
					// Reset the cell and try another one
					this->_filled[row][column] = 1;
					++(this->_numberOfFilledCells);
					this->_solutions = 1;
				}
			}

			// Check if no extra cells have been hidden
			assert(hidden <= numberOfCellsToHide);

#ifndef NDEBUG

			// Check if the final puzzle has a unique solution
			this->_solutions = 0;
			assert(this->calculateSolutions() == 1);

#endif

			// The final puzzle always has a unique solution
			this->_solutions = 1;

			// Change the engine state
			this->_state = SudokuEngineState::NewGame;

			// Return true if and only if the required number of cells has been hidden
			return hidden == numberOfCellsToHide;
		}
	};

	// Print difficulty level
	std::ostream & operator <<(std::ostream & os, const DifficultyLevel & difficulty)
	{
		switch (difficulty)
		{
			case DifficultyLevel::VeryEasy:
				os << "Very easy";
				break;
			case DifficultyLevel::Easy:
				os << "Easy";
				break;
			case DifficultyLevel::Medium:
				os << "Medium";
				break;
			case DifficultyLevel::Hard:
				os << "Hard";
				break;
			case DifficultyLevel::VeryHard:
				os << "Very hard";
				break;
		}

		return os;
	}

	// Print engine state
	std::ostream & operator <<(std::ostream & os, const SudokuEngineState & state)
	{
		switch (state)
		{
			case SudokuEngineState::Empty:
				os << "Empty";
				break;
			case SudokuEngineState::BeingEdited:
				os << "Being edited";
				break;
			case SudokuEngineState::HasNoSolution:
				os << "Has no solution";
				break;
			case SudokuEngineState::HasUniqueSolution:
				os << "Has unique solution";
				break;
			case SudokuEngineState::HasMultipleSolutions:
				os << "Has multiple solutions";
				break;
			case SudokuEngineState::NewGame:
				os << "New game";
				break;
			case SudokuEngineState::FilledInvalid:
				os << "Filled invalid";
				break;
			case SudokuEngineState::FilledValid:
				os << "Filled valid";
				break;
		}

		return os;
	}

	// Print the board
	template <typename IndexType, typename BooleanType, IndexType sizeFactor>
	std::ostream & operator <<(std::ostream & os, const SudokuEngine<IndexType, BooleanType, sizeFactor> & engine)
	{
		os << "Current state: " << engine.currentState() << std::endl;
		os << "Total number of cells: " << (unsigned int) engine.numberOfBoardCells() << std::endl;
		os << "Number of filled cells: " << (unsigned int) engine.numberOfFilledCells() << std::endl;
		os << "Number of free cells: " << (unsigned int) engine.numberOfFreeCells() << std::endl << std::endl;

		for (IndexType i = 0; i < engine.sizeOfTheBoard(); ++i)
		{
			for (IndexType j = 0; j < engine.sizeOfTheBoard(); ++j)
			{
				std::cout << static_cast<unsigned int>(engine(i, j)) << ", ";
			}
			os << std::endl;
		}

		return os;
	}
}

#endif