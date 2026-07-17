// Danylo Fitel 2013
// Persists the user's language choice in the Windows registry.
// Key: HKEY_CURRENT_USER\Software\Sudoku, value: "Language" (DWORD)

#pragma once

#include "Strings.h"

namespace Sudoku_3_0
{
    ref class LanguagePreference abstract sealed
    {
    private:
        static System::String^ SubKeyPath = L"Software\\Sudoku_3";
        static System::String^ ValueName = L"Language";

    public:
        // Writes the selected language to the registry.
        static void Save(Language lang)
        {
            Microsoft::Win32::RegistryKey^ regKey =
                Microsoft::Win32::Registry::CurrentUser->CreateSubKey(SubKeyPath);
            if (regKey != nullptr)
            {
                regKey->SetValue(ValueName, (int)static_cast<unsigned int>(lang));
                regKey->Close();
            }
        }

        // Reads the language from the registry.
        // Returns Language::English if no value has been saved yet or the stored
        // value does not correspond to a known language.
        static Language Load()
        {
            try
            {
                Microsoft::Win32::RegistryKey^ regKey =
                    Microsoft::Win32::Registry::CurrentUser->OpenSubKey(SubKeyPath);
                if (regKey == nullptr)
                    return Language::English;

                System::Object^ raw = regKey->GetValue(ValueName);
                regKey->Close();

                if (raw == nullptr)
                    return Language::English;

                unsigned int stored = (unsigned int)System::Convert::ToInt32(raw);
                if (stored == static_cast<unsigned int>(Language::Ukrainian))
                    return Language::Ukrainian;

                return Language::English;
            }
            catch (...)
            {
                return Language::English;
            }
        }
    };
}
