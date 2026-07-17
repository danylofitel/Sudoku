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
        static const Language DefaultLanguage = Language::English;
        static System::String^ SubKeyPath = L"Software\\Sudoku_3";
        static System::String^ ValueName = L"Language";

    public:
        // Writes the selected language to the registry.
        static void Save(Language lang)
        {
            try
            {
                Microsoft::Win32::RegistryKey^ regKey =
                    Microsoft::Win32::Registry::CurrentUser->CreateSubKey(SubKeyPath);
                if (regKey != nullptr)
                {
                    regKey->SetValue(ValueName, (int)static_cast<unsigned int>(lang));
                    regKey->Close();
                }
            }
            catch (...)
            {
                // Ignore errors, as this is not critical.
            }
        }

        // Reads the language from the registry.
        // Returns default language if no value has been saved yet or the stored
        // value does not correspond to a known language.
        static Language Load()
        {
            try
            {
                Microsoft::Win32::RegistryKey^ regKey =
                    Microsoft::Win32::Registry::CurrentUser->OpenSubKey(SubKeyPath);
                if (regKey == nullptr)
                    return DefaultLanguage;

                System::Object^ raw = regKey->GetValue(ValueName);
                regKey->Close();

                if (raw == nullptr)
                    return DefaultLanguage;

                unsigned int stored = (unsigned int)System::Convert::ToInt32(raw);
                if (stored == static_cast<unsigned int>(Language::English))
                    return Language::English;
                if (stored == static_cast<unsigned int>(Language::Ukrainian))
                    return Language::Ukrainian;

                return DefaultLanguage;
            }
            catch (...)
            {
                // Ignore errors, as this is not critical.
                return DefaultLanguage;
            }
        }
    };
}
