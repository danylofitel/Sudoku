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

    SudokuForm^ form = nullptr;
    try
    {
        // Create the main window and run it
        form = gcnew SudokuForm(startupFile);
        Application::Run(form);
    }
    catch (System::Exception^ ex)
    {
        // Auto-save normally runs only on a clean exit, so try to keep the game first. The form
        // saves only a game that passes the load checks; otherwise the last auto-save stands.
        bool saved = form != nullptr && form->trySaveAfterCrash();

        Language lang = Settings::LoadLanguage();
        System::String^ message = Strings::Get(StringId::NotifyUnexpectedError, lang);
        if (saved)
            message += Strings::Get(StringId::NotifyGameSavedAfterError, lang);
        MessageBox::Show(
            message + ex->Message,
            Strings::Get(StringId::WindowTitle, lang),
            MessageBoxButtons::OK,
            MessageBoxIcon::Error);
        return 1;
    }

    return 0;
}
