// Danylo Fitel 2026

#include "stdafx.h"
#include "Sudoku 3.0.h"

using namespace Sudoku_3_0;

[STAThreadAttribute]
int main(array<System::String^>^ args)
{
    // Enabling Windows XP visual effects before any controls are created
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Route UI-thread exceptions to the catch below instead of the default
    // ThreadException dialog, so any crash shows one friendly localized message.
    Application::SetUnhandledExceptionMode(UnhandledExceptionMode::ThrowException);

    try
    {
        // Create the main window and run it
        Application::Run(gcnew SudokuForm());
    }
    catch (System::Exception^ ex)
    {
        Language lang = Settings::LoadLanguage();
        MessageBox::Show(
            Strings::Get(StringId::NotifyUnexpectedError, lang) + ex->Message,
            Strings::Get(StringId::WindowTitle, lang),
            MessageBoxButtons::OK,
            MessageBoxIcon::Error);
        return 1;
    }

    return 0;
}
