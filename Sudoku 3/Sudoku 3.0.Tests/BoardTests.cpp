// Danylo Fitel 2026
// Unit tests for Board: the authoritative cell model and its invariants.

#include "Board.h"

using namespace System;
using namespace Sudoku_3_0;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace Sudoku_3_0_Tests
{
    [TestClass]
    public ref class BoardTests
    {
    private:
        literal int Cells = 81;

        static Board^ NewBoard() { return gcnew Board(Cells); }

    public:
        // ---- Construction ----

        [TestMethod]
        void NewBoard_IsAllEmptyAndEditable()
        {
            Board^ b = NewBoard();
            Assert::AreEqual((unsigned int)Cells, b->Count);
            Assert::AreEqual((unsigned int)0, b->FilledCount);
            for (unsigned int i = 0; i < b->Count; ++i)
            {
                Assert::AreEqual(0, (int)b->valueAt(i));
                Assert::IsTrue(b->kindAt(i) == CellKind::UserEmpty);
                Assert::IsTrue(b->isEmpty(i));
                Assert::IsTrue(b->isEditable(i));
                Assert::AreEqual(0, b->pencilMarksAt(i));
            }
        }

        // ---- setUserValue ----

        [TestMethod]
        void SetUserValue_Fills_AndMarksUserFilled()
        {
            Board^ b = NewBoard();
            b->setUserValue(10, 7);

            Assert::AreEqual(7, (int)b->valueAt(10));
            Assert::IsTrue(b->kindAt(10) == CellKind::UserFilled);
            Assert::IsFalse(b->isEmpty(10));
            Assert::IsTrue(b->isEditable(10));
            Assert::AreEqual((unsigned int)1, b->FilledCount);
        }

        [TestMethod]
        void SetUserValue_Filling_ClearsPencilMarks()
        {
            Board^ b = NewBoard();
            b->togglePencilMark(10, 3);
            b->togglePencilMark(10, 5);
            Assert::AreNotEqual(0, b->pencilMarksAt(10));

            b->setUserValue(10, 7);
            Assert::AreEqual(0, b->pencilMarksAt(10));
        }

        [TestMethod]
        void SetUserValue_Zero_Empties_AndDecrementsFilled()
        {
            Board^ b = NewBoard();
            b->setUserValue(10, 7);
            b->setUserValue(10, 0);

            Assert::AreEqual(0, (int)b->valueAt(10));
            Assert::IsTrue(b->kindAt(10) == CellKind::UserEmpty);
            Assert::AreEqual((unsigned int)0, b->FilledCount);
        }

        [TestMethod]
        void SetUserValue_Overwrite_KeepsFilledCountStable()
        {
            Board^ b = NewBoard();
            b->setUserValue(10, 7);
            b->setUserValue(10, 4); // overwrite, still filled
            Assert::AreEqual(4, (int)b->valueAt(10));
            Assert::AreEqual((unsigned int)1, b->FilledCount);
        }

        [TestMethod]
        [ExpectedException(ArgumentOutOfRangeException::typeid)]
        void SetUserValue_Throws_OnOutOfRange()
        {
            NewBoard()->setUserValue(0, 10);
        }

        // ---- Pencil marks ----

        [TestMethod]
        void TogglePencilMark_TogglesBit_OnEmptyEditableCell()
        {
            Board^ b = NewBoard();
            b->togglePencilMark(0, 4);
            Assert::AreEqual(1 << 4, b->pencilMarksAt(0));
            b->togglePencilMark(0, 4);
            Assert::AreEqual(0, b->pencilMarksAt(0));
        }

        [TestMethod]
        void TogglePencilMark_NoOp_OnFilledCell()
        {
            Board^ b = NewBoard();
            b->setUserValue(0, 5);
            b->togglePencilMark(0, 4);
            Assert::AreEqual(0, b->pencilMarksAt(0));
        }

        [TestMethod]
        void TogglePencilMark_NoOp_OnClueCell()
        {
            Board^ b = NewBoard();
            b->setClue(0, 5);
            b->togglePencilMark(0, 4);
            Assert::AreEqual(0, b->pencilMarksAt(0));
        }

        [TestMethod]
        void TogglePencilMark_IgnoresOutOfRangeDigit()
        {
            Board^ b = NewBoard();
            b->togglePencilMark(0, 0);
            b->togglePencilMark(0, 10);
            Assert::AreEqual(0, b->pencilMarksAt(0));
        }

        // ---- Clues / reveals / locking ----

        [TestMethod]
        void SetClue_IsFilledLockedAndCounts()
        {
            Board^ b = NewBoard();
            b->setClue(0, 6);
            Assert::AreEqual(6, (int)b->valueAt(0));
            Assert::IsTrue(b->kindAt(0) == CellKind::Clue);
            Assert::IsFalse(b->isEditable(0));
            Assert::AreEqual((unsigned int)1, b->FilledCount);
        }

        [TestMethod]
        [ExpectedException(ArgumentOutOfRangeException::typeid)]
        void SetClue_Throws_OnZero()
        {
            NewBoard()->setClue(0, 0);
        }

        [TestMethod]
        void Reveal_Hint_LocksWithValueAndClearsMarks()
        {
            Board^ b = NewBoard();
            b->togglePencilMark(0, 2);
            b->reveal(0, 8, CellKind::Hint);

            Assert::AreEqual(8, (int)b->valueAt(0));
            Assert::IsTrue(b->kindAt(0) == CellKind::Hint);
            Assert::IsFalse(b->isEditable(0));
            Assert::AreEqual(0, b->pencilMarksAt(0));
            Assert::AreEqual((unsigned int)1, b->FilledCount);
        }

        [TestMethod]
        [ExpectedException(ArgumentException::typeid)]
        void Reveal_Throws_OnNonRevealKind()
        {
            NewBoard()->reveal(0, 8, CellKind::UserFilled);
        }

        [TestMethod]
        void LockAsCorrect_KeepsValue_ChangesKind()
        {
            Board^ b = NewBoard();
            b->setUserValue(0, 9);
            b->lockAsCorrect(0);

            Assert::AreEqual(9, (int)b->valueAt(0));
            Assert::IsTrue(b->kindAt(0) == CellKind::Correct);
            Assert::IsFalse(b->isEditable(0));
            Assert::AreEqual((unsigned int)1, b->FilledCount);
        }

        [TestMethod]
        [ExpectedException(InvalidOperationException::typeid)]
        void LockAsCorrect_Throws_OnEmptyCell()
        {
            NewBoard()->lockAsCorrect(0);
        }

        // ---- Undo restore ----

        [TestMethod]
        void RestoreUserCell_RestoresValueAndMarks()
        {
            Board^ b = NewBoard();
            b->restoreUserCell(0, 3, 1 << 5);
            Assert::AreEqual(3, (int)b->valueAt(0));
            Assert::IsTrue(b->kindAt(0) == CellKind::UserFilled);
            // Restoring an empty cell yields UserEmpty and preserves marks
            b->restoreUserCell(1, 0, 1 << 2);
            Assert::IsTrue(b->kindAt(1) == CellKind::UserEmpty);
            Assert::AreEqual(1 << 2, b->pencilMarksAt(1));
        }

        // ---- Bulk operations ----

        [TestMethod]
        void ResetToClues_SetsCluesAndEmpties()
        {
            Board^ b = NewBoard();
            b->setUserValue(0, 5); // dirty state to be reset

            array<unsigned char>^ clues = gcnew array<unsigned char>(Cells);
            for (int i = 0; i < Cells; ++i)
                clues[i] = (i % 3 == 0) ? (unsigned char)(1 + (i % 9)) : (unsigned char)0;

            b->resetToClues(clues);

            unsigned int expectedFilled = 0;
            for (int i = 0; i < Cells; ++i)
            {
                if (clues[i] != 0)
                {
                    Assert::IsTrue(b->kindAt(i) == CellKind::Clue);
                    Assert::AreEqual((int)clues[i], (int)b->valueAt(i));
                    ++expectedFilled;
                }
                else
                {
                    Assert::IsTrue(b->kindAt(i) == CellKind::UserEmpty);
                }
            }
            Assert::AreEqual(expectedFilled, b->FilledCount);
        }

        [TestMethod]
        void ClearToEmpty_ResetsEverything()
        {
            Board^ b = NewBoard();
            b->setClue(0, 5);
            b->setUserValue(1, 6);
            b->togglePencilMark(2, 3);

            b->clearToEmpty();

            Assert::AreEqual((unsigned int)0, b->FilledCount);
            for (unsigned int i = 0; i < b->Count; ++i)
            {
                Assert::IsTrue(b->kindAt(i) == CellKind::UserEmpty);
                Assert::AreEqual(0, b->pencilMarksAt(i));
            }
        }

        // ---- Serialization helpers ----

        [TestMethod]
        void CopyStates_MapsKindsToCodes()
        {
            Board^ b = NewBoard();
            b->setClue(0, 5);        // 0
            b->setUserValue(2, 6);   // 2
            b->reveal(3, 7, CellKind::Hint); // 4

            array<unsigned char>^ states = b->copyStates();
            Assert::AreEqual(0, (int)states[0]);
            Assert::AreEqual(1, (int)states[1]);
            Assert::AreEqual(2, (int)states[2]);
            Assert::AreEqual(4, (int)states[3]);
        }

        [TestMethod]
        void CopyValues_IsDefensiveCopy()
        {
            Board^ b = NewBoard();
            b->setUserValue(0, 5);
            array<unsigned char>^ copy = b->copyValues();
            copy[0] = 9;
            Assert::AreEqual(5, (int)b->valueAt(0)); // board unaffected
        }

        [TestMethod]
        void RestoreFrom_RebuildsBoardAndFilledCount()
        {
            Board^ source = NewBoard();
            source->setClue(0, 4);
            source->setUserValue(1, 5);
            source->reveal(2, 6, CellKind::Solved);
            source->togglePencilMark(3, 7);

            Board^ target = NewBoard();
            target->restoreFrom(source->copyValues(), source->copyStates(), source->copyPencilMarks());

            Assert::AreEqual(source->FilledCount, target->FilledCount);
            for (unsigned int i = 0; i < target->Count; ++i)
            {
                Assert::AreEqual((int)source->valueAt(i), (int)target->valueAt(i));
                Assert::IsTrue(source->kindAt(i) == target->kindAt(i));
                Assert::AreEqual(source->pencilMarksAt(i), target->pencilMarksAt(i));
            }
        }
    };
}
