// Danylo Fitel 2026
// Unit tests for CellAccessibility: the screen-reader name announced for each board cell.

#include "CellAccessibility.h"

using namespace System;
using namespace Sudoku_3_0;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace Sudoku_3_0_Tests
{
    [TestClass]
    public ref class CellAccessibilityTests
    {
    private:
        literal int Cells = 81;
        literal int Size = 9;

        static CellNameTexts^ English()
        {
            CellNameTexts^ t = gcnew CellNameTexts();
            t->position = "Row {0}, column {1}";
            t->empty = "empty";
            t->pencilMarks = "pencil marks {0}";
            t->clue = "clue";
            t->hint = "hint";
            t->correct = "correct";
            t->givenUp = "revealed";
            t->solved = "solved";
            t->conflict = "conflict";
            return t;
        }

        static String^ Describe(Board^ b, unsigned int index, bool conflict)
        {
            return CellAccessibility::Describe(b, index, Size, conflict, English());
        }

    public:
        [TestMethod]
        void EmptyCell_NamesPositionAndEmpty()
        {
            Assert::AreEqual("Row 1, column 1: empty", Describe(gcnew Board(Cells), 0, false));
        }

        [TestMethod]
        void Position_IsOneBasedRowThenColumn()
        {
            // Index 23 is the 3rd row (index 2), 6th column (index 5)
            Assert::AreEqual("Row 3, column 6: empty", Describe(gcnew Board(Cells), 23, false));
            Assert::AreEqual("Row 9, column 9: empty", Describe(gcnew Board(Cells), 80, false));
        }

        [TestMethod]
        void EmptyCell_ListsPencilMarksInOrder()
        {
            Board^ b = gcnew Board(Cells);
            b->togglePencilMark(4, 9);
            b->togglePencilMark(4, 1);
            b->togglePencilMark(4, 4);
            Assert::AreEqual("Row 1, column 5: empty, pencil marks 1 4 9", Describe(b, 4, false));
        }

        [TestMethod]
        void UserEntry_IsJustTheDigit()
        {
            Board^ b = gcnew Board(Cells);
            b->setUserValue(10, 7);
            Assert::AreEqual("Row 2, column 2: 7", Describe(b, 10, false));
        }

        [TestMethod]
        void LockedCells_NameHowTheDigitGotThere()
        {
            Board^ b = gcnew Board(Cells);
            b->setClue(0, 1);
            b->reveal(1, 2, CellKind::Hint);
            b->reveal(2, 3, CellKind::GivenUp);
            b->reveal(3, 4, CellKind::Solved);
            b->setUserValue(5, 6);
            b->lockAsCorrect(5);

            Assert::AreEqual("Row 1, column 1: 1, clue", Describe(b, 0, false));
            Assert::AreEqual("Row 1, column 2: 2, hint", Describe(b, 1, false));
            Assert::AreEqual("Row 1, column 3: 3, revealed", Describe(b, 2, false));
            Assert::AreEqual("Row 1, column 4: 4, solved", Describe(b, 3, false));
            Assert::AreEqual("Row 1, column 6: 6, correct", Describe(b, 5, false));
        }

        [TestMethod]
        void Conflict_IsAnnouncedLast()
        {
            Board^ b = gcnew Board(Cells);
            b->setUserValue(10, 7);
            b->setClue(11, 7);
            Assert::AreEqual("Row 2, column 2: 7, conflict", Describe(b, 10, true));
            Assert::AreEqual("Row 2, column 3: 7, clue, conflict", Describe(b, 11, true));
        }

        [TestMethod]
        void UsesTheGivenLanguage()
        {
            CellNameTexts^ t = English();
            // Wide literals, as in Strings.h: narrow ones would pass through the 1252 code page
            t->position = L"Рядок {0}, стовпець {1}";
            t->empty = L"порожня";
            Assert::AreEqual(L"Рядок 1, стовпець 1: порожня",
                CellAccessibility::Describe(gcnew Board(Cells), 0, Size, false, t));
        }
    };
}
