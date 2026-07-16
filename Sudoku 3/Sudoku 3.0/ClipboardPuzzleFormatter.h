// Danylo Fitel 2013

#pragma once

namespace Sudoku_3_0
{
    // Encoder/decoder for the clipboard puzzle string format.
    // Format: exactly numberOfCells ASCII digit characters ('0'-'9').
    // '0' means empty; '1'-'9' are filled cell values.
    // On input, '.' is also accepted as an alias for '0' to support
    // puzzles copied from other applications.
    ref class ClipboardPuzzleFormatter abstract sealed
    {
    public:
        // Encodes a digit array into a puzzle string.
        // digits[i] must be 0-9; 0 means empty.
        static System::String^ Encode(array<unsigned char>^ digits)
        {
            System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder(digits->Length);
            for each (unsigned char d in digits)
                sb->Append((wchar_t)(L'0' + d));
            return sb->ToString();
        }

        // Decodes a raw string into a digit array of the expected length.
        // Accepts '0'-'9' and '.' (treated as '0'); all other characters are skipped.
        // Returns nullptr if the number of extracted digits != expectedLength.
        static array<unsigned char>^ Decode(System::String^ text, int expectedLength)
        {
            array<unsigned char>^ digits = gcnew array<unsigned char>(expectedLength);
            int count = 0;
            for each (wchar_t c in text)
            {
                if (count == expectedLength) break;
                if (c >= L'0' && c <= L'9')
                    digits[count++] = (unsigned char)(c - L'0');
                else if (c == L'.')
                    digits[count++] = 0;
            }
            return count == expectedLength ? digits : nullptr;
        }
    };
}
