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

    // First command-line argument, if any, is a save file to open on launch (e.g. from a
    // .sdk3 file association). Note: .NET args do NOT include the executable path, so args[0]
    // is the first real argument.
    System::String^ startupFile = (args != nullptr && args->Length > 0) ? args[0] : nullptr;

    try
    {
        // Create the main window and run it
        Application::Run(gcnew SudokuForm(startupFile));
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
