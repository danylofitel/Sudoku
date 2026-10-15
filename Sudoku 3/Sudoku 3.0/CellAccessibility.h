// Danylo Fitel 2026

#pragma once

#include "Board.h"

namespace Sudoku_3_0
{
    // The localized words a cell's screen-reader name is built from. The form fills this from
    // Strings (so every translation stays in Strings.h); tests can pass plain texts directly.
    ref class CellNameTexts
    {
    public:
        System::String^ position;    // format with {0} = row, {1} = column (1-based)
        System::String^ empty;
        System::String^ pencilMarks; // format with {0} = the marked digits, e.g. "1 4"
        System::String^ clue;
        System::String^ hint;
        System::String^ correct;
        System::String^ givenUp;
        System::String^ solved;
        System::String^ conflict;
    };

    // Builds the accessible name a screen reader announces for a board cell, e.g.
    //   "Row 3, column 5: empty, pencil marks 1 4"
    //   "Row 1, column 2: 7, hint, conflict"
    // A cell's button shows only its digit (pencil marks are painted, not text), so without this
    // a screen reader would announce just "7" or nothing at all. UI-free, so it is unit-testable.
    ref class CellAccessibility abstract sealed
    {
    public:
        static System::String^ Describe(Board^ board, unsigned int index, unsigned int boardSize,
            bool hasConflict, CellNameTexts^ texts)
        {
            System::Text::StringBuilder^ name = gcnew System::Text::StringBuilder();
            name->AppendFormat(texts->position, index / boardSize + 1, index % boardSize + 1);
            name->Append(L": ");

            unsigned char value = board->valueAt(index);
            if (value == 0)
            {
                name->Append(texts->empty);

                int marks = board->pencilMarksAt(index);
                if (marks != 0)
                {
                    System::Text::StringBuilder^ digits = gcnew System::Text::StringBuilder();
                    for (int digit = 1; digit <= 9; ++digit)
                    {
                        if ((marks & (1 << digit)) == 0) continue;
                        if (digits->Length > 0) digits->Append(L' ');
                        digits->Append(digit);
                    }
                    name->Append(L", ")->AppendFormat(texts->pencilMarks, digits->ToString());
                }
            }
            else
            {
                name->Append((int)value);

                // How the digit got there; a plain user entry needs no label
                System::String^ kind = KindLabel(board->kindAt(index), texts);
                if (kind != nullptr)
                    name->Append(L", ")->Append(kind);
            }

            if (hasConflict)
                name->Append(L", ")->Append(texts->conflict);

            return name->ToString();
        }

    private:
        static System::String^ KindLabel(CellKind kind, CellNameTexts^ texts)
        {
            switch (kind)
            {
            case CellKind::Clue:    return texts->clue;
            case CellKind::Hint:    return texts->hint;
            case CellKind::Correct: return texts->correct;
            case CellKind::GivenUp: return texts->givenUp;
            case CellKind::Solved:  return texts->solved;
            default:                return nullptr; // UserEmpty, UserFilled
            }
        }
    };
}
