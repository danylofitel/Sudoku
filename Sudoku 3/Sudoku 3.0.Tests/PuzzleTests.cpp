// Danylo Fitel 2026
// Unit tests for Puzzle (immutable snapshot: validation + defensive copy).

#include "Puzzle.h"

using namespace System;
using namespace Sudoku_3_0;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace Sudoku_3_0_Tests
{
    [TestClass]
    public ref class PuzzleTests
    {
    private:
        static array<unsigned char>^ MakeArray(int length, unsigned char fill)
        {
            array<unsigned char>^ a = gcnew array<unsigned char>(length);
            for (int i = 0; i < length; ++i)
                a[i] = fill;
            return a;
        }

    public:
        [TestMethod]
        void Constructor_KeepsProvidedValues()
        {
            array<unsigned char>^ clues = MakeArray(81, 0);
            array<unsigned char>^ solution = MakeArray(81, 5);
            clues[0] = 7;

            Puzzle^ p = gcnew Puzzle(clues, solution);

            Assert::AreEqual(7, (int)p->clues[0]);
            Assert::AreEqual(5, (int)p->solution[80]);
        }

        [TestMethod]
        void Constructor_DefensivelyCopies_Clues()
        {
            array<unsigned char>^ clues = MakeArray(81, 0);
            array<unsigned char>^ solution = MakeArray(81, 5);

            Puzzle^ p = gcnew Puzzle(clues, solution);
            clues[0] = 9; // mutate the caller's array after construction

            Assert::AreEqual(0, (int)p->clues[0]); // snapshot must be unaffected
        }

        [TestMethod]
        void Constructor_DefensivelyCopies_Solution()
        {
            array<unsigned char>^ clues = MakeArray(81, 0);
            array<unsigned char>^ solution = MakeArray(81, 5);

            Puzzle^ p = gcnew Puzzle(clues, solution);
            solution[0] = 9;

            Assert::AreEqual(5, (int)p->solution[0]);
        }

        [TestMethod]
        [ExpectedException(ArgumentNullException::typeid)]
        void Constructor_Throws_OnNullClues()
        {
            gcnew Puzzle(nullptr, MakeArray(81, 5));
        }

        [TestMethod]
        [ExpectedException(ArgumentNullException::typeid)]
        void Constructor_Throws_OnNullSolution()
        {
            gcnew Puzzle(MakeArray(81, 0), nullptr);
        }

        [TestMethod]
        [ExpectedException(ArgumentException::typeid)]
        void Constructor_Throws_OnLengthMismatch()
        {
            gcnew Puzzle(MakeArray(80, 0), MakeArray(81, 5));
        }
    };
}
