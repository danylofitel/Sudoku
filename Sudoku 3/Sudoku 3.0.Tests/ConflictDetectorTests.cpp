// Danylo Fitel 2026
// Unit tests for ConflictDetector: pure Sudoku conflict logic over a Board.

#include "ConflictDetector.h"

using namespace System;
using namespace Sudoku_3_0;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace Sudoku_3_0_Tests
{
    [TestClass]
    public ref class ConflictDetectorTests
    {
    private:
        literal int Cells = 81;
        static Board^ NewBoard() { return gcnew Board(Cells); }
        static ConflictDetector^ DetectorFor(Board^ board) { return gcnew ConflictDetector(board, 3); }

    public:
        [TestMethod]
        void EmptyBoard_HasNoConflicts()
        {
            Board^ b = NewBoard();
            ConflictDetector^ d = DetectorFor(b);
            for (unsigned int i = 0; i < (unsigned int)Cells; ++i)
                Assert::IsFalse(d->hasConflict(i));
        }

        [TestMethod]
        void RowDuplicate_Conflicts()
        {
            Board^ b = NewBoard();
            b->setUserValue(0, 5);
            b->setUserValue(1, 5); // same row (0)
            ConflictDetector^ d = DetectorFor(b);
            Assert::IsTrue(d->hasConflict(0));
            Assert::IsTrue(d->hasConflict(1));
        }

        [TestMethod]
        void ColumnDuplicate_Conflicts()
        {
            Board^ b = NewBoard();
            b->setUserValue(0, 7);
            b->setUserValue(9, 7); // same column (0)
            ConflictDetector^ d = DetectorFor(b);
            Assert::IsTrue(d->hasConflict(0));
            Assert::IsTrue(d->hasConflict(9));
        }

        [TestMethod]
        void BlockDuplicate_Conflicts()
        {
            Board^ b = NewBoard();
            b->setUserValue(0, 3);
            b->setUserValue(10, 3); // both in top-left block, different row and column
            ConflictDetector^ d = DetectorFor(b);
            Assert::IsTrue(d->hasConflict(0));
            Assert::IsTrue(d->hasConflict(10));
        }

        [TestMethod]
        void UnrelatedCells_DoNotConflict()
        {
            Board^ b = NewBoard();
            b->setUserValue(0, 4);
            b->setUserValue(80, 4); // different row, column, and block
            ConflictDetector^ d = DetectorFor(b);
            Assert::IsFalse(d->hasConflict(0));
            Assert::IsFalse(d->hasConflict(80));
        }

        [TestMethod]
        void EmptyCell_NeverConflicts()
        {
            Board^ b = NewBoard();
            b->setUserValue(0, 5);
            b->setUserValue(1, 5);
            ConflictDetector^ d = DetectorFor(b);
            Assert::IsFalse(d->hasConflict(2)); // empty cell in the conflicted row
        }

        [TestMethod]
        void GetBlockedDigits_ReflectsPeers()
        {
            Board^ b = NewBoard();
            b->setUserValue(0, 5); // a row peer of cell 1
            ConflictDetector^ d = DetectorFor(b);
            int blocked = d->getBlockedDigits(1);
            Assert::AreEqual(1 << 5, blocked & (1 << 5)); // digit 5 blocked
            Assert::AreEqual(0, blocked & (1 << 6));       // digit 6 not blocked
        }

        [TestMethod]
        void PeersOf_IncludesRowColBlock_ExcludesSelfAndUnrelated()
        {
            ConflictDetector^ d = DetectorFor(NewBoard());
            System::Collections::Generic::List<unsigned int>^ peers =
                gcnew System::Collections::Generic::List<unsigned int>(d->peersOf(0));

            Assert::IsTrue(peers->Contains(1));   // same row
            Assert::IsTrue(peers->Contains(9));   // same column
            Assert::IsTrue(peers->Contains(10));  // same block
            Assert::IsFalse(peers->Contains(0));  // self excluded
            Assert::IsFalse(peers->Contains(80)); // unrelated cell
        }

        [TestMethod]
        [ExpectedException(ArgumentNullException::typeid)]
        void Constructor_Throws_OnNullBoard()
        {
            gcnew ConflictDetector(nullptr, 3);
        }

        [TestMethod]
        [ExpectedException(ArgumentException::typeid)]
        void Constructor_Throws_OnWrongSizedBoard()
        {
            gcnew ConflictDetector(gcnew Board(16), 3); // 16 cells != expected 81
        }
    };
}
