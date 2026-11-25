// Danylo Fitel 2026
// All of the app's fonts centralized in one place: the two families and the font each role uses.
// Both families ship with Windows Vista and later. A font a machine lacks is silently replaced
// by a substitute, usually a wider one, which clips labels sized for the intended font.
// Menus, tooltips and message boxes keep the Windows UI font and are not configured here.

#pragma once

namespace Sudoku_3_0
{
    public ref class Fonts abstract sealed
    {
    public:
        // Serif face for the digits players place, on the board and on the number pad
        literal System::String^ DigitFamily = L"Cambria";
        // Sans face for all other text
        literal System::String^ TextFamily = L"Calibri";

        // Shared fonts, one per role. Controls may share a Font, and these live as long as the
        // app, so they are never disposed. Sizes are in points at the form's design DPI (main
        // form 144, number pad 96); DPI auto-scaling keeps them in proportion to the controls.

        // ---- Main form ----
        static initonly System::Drawing::Font^ CellDigit = Digit(26);
        static initonly System::Drawing::Font^ ButtonText = Text(14);
        static initonly System::Drawing::Font^ TimerText = Text(20);
        // The title bar's minimize and close glyphs ("—" and "✕")
        static initonly System::Drawing::Font^ MinimizeGlyph = Text(20);
        static initonly System::Drawing::Font^ CloseGlyph = Text(18);

        // ---- Number pad ----
        static initonly System::Drawing::Font^ PadDigit = Digit(24);
        // Largest size for the Clear and Cancel labels, which shrink from it to fit their buttons
        literal float PadLabelMaxSize = 14.25F;

        // Factories for fonts sized at run time. The caller owns the font and disposes it.

        // Label text at a size in points
        static System::Drawing::Font^ Text(float points)
        {
            return gcnew System::Drawing::Font(TextFamily, points,
                System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
        }

        // Pencil marks, sized in pixels from the cell's pixel size so they stay in proportion
        // to the cell at every display scaling. (A size in points would be scaled by the
        // display a second time, shrinking the marks at lower scalings.)
        static System::Drawing::Font^ PencilMark(float pixels)
        {
            return gcnew System::Drawing::Font(TextFamily, pixels,
                System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel);
        }

    private:
        static System::Drawing::Font^ Digit(float points)
        {
            return gcnew System::Drawing::Font(DigitFamily, points,
                System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point);
        }
    };
}
