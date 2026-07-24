// Danylo Fitel 2026
// Unit tests for ClipboardPuzzleFormatter (pure encode/decode; no UI, no I/O).

#include "ClipboardPuzzleFormatter.h"

using namespace System;
using namespace Sudoku_3_0;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace Sudoku_3_0_Tests
{
    [TestClass]
    public ref class ClipboardPuzzleFormatterTests
    {
    public:
        [TestMethod]
        void Encode_ProducesOneDigitPerCell()
        {
            array<unsigned char>^ digits = gcnew array<unsigned char>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            String^ expected = "0123456789";
            Assert::AreEqual(expected, ClipboardPuzzleFormatter::Encode(digits));
        }

        [TestMethod]
        void Decode_RoundTripsEncode()
        {
            array<unsigned char>^ digits = gcnew array<unsigned char>(81);
            for (int i = 0; i < 81; ++i)
                digits[i] = (unsigned char)(i % 10);

            array<unsigned char>^ decoded = ClipboardPuzzleFormatter::Decode(
                ClipboardPuzzleFormatter::Encode(digits), 81);

            Assert::IsNotNull(decoded);
            for (int i = 0; i < 81; ++i)
                Assert::AreEqual((int)digits[i], (int)decoded[i]);
        }

        [TestMethod]
        void Decode_TreatsDotAsZero()
        {
            array<unsigned char>^ decoded = ClipboardPuzzleFormatter::Decode(gcnew String('.', 81), 81);

            Assert::IsNotNull(decoded);
            for (int i = 0; i < 81; ++i)
                Assert::AreEqual(0, (int)decoded[i]);
        }

        [TestMethod]
        void Decode_SkipsWhitespaceBetweenDigits()
        {
            // 81 digits separated by spaces (as if copied from a grid layout)
            System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder();
            for (int i = 0; i < 81; ++i)
            {
                sb->Append((wchar_t)(L'1' + (i % 9)));
                sb->Append(L' ');
            }

            array<unsigned char>^ decoded = ClipboardPuzzleFormatter::Decode(sb->ToString(), 81);

            Assert::IsNotNull(decoded);
            Assert::AreEqual(1, (int)decoded[0]);
            Assert::AreEqual(9, (int)decoded[8]);
        }

        [TestMethod]
        void Decode_ReturnsNull_WhenTooFewDigits()
        {
            Assert::IsNull(ClipboardPuzzleFormatter::Decode("123", 81));
        }

        [TestMethod]
        void Decode_StopsAtExpectedLength_WhenTooManyDigits()
        {
            array<unsigned char>^ decoded = ClipboardPuzzleFormatter::Decode(gcnew String('5', 200), 81);

            Assert::IsNotNull(decoded);
            Assert::AreEqual(81, decoded->Length);
        }

        [TestMethod]
        void Decode_ReturnsNull_ForEmptyString()
        {
            Assert::IsNull(ClipboardPuzzleFormatter::Decode("", 81));
        }
    };
}
