// Danylo Fitel 2026
// Persistent user settings, stored in the Windows registry under
// HKEY_CURRENT_USER\Software\Sudoku_3.
//
// Every method is defensive: read failures fall back to safe defaults, write failures
// are silently ignored (settings are never worth crashing over), and loaded values are
// validated before use. Callers are expected to read once at startup and write only
// when a value actually changes, so registry traffic stays minimal.

#pragma once

#include "Language.h"

namespace Sudoku_3_0
{
    ref class Settings abstract sealed
    {
    private:
        static System::String^ SubKeyPath = L"Software\\Sudoku_3";
        static System::String^ LanguageValueName = L"Language";
        static System::String^ DifficultyValueName = L"Difficulty";
        static System::String^ WinStreakValueName = L"WinStreak";
        static System::String^ WindowLeftValueName = L"WindowLeft";
        static System::String^ WindowTopValueName = L"WindowTop";

        static const Language DefaultLanguage = Language::English;
        static const unsigned int DefaultDifficulty = 2; // Medium

        // Reads an integer value. Returns true and sets result only if the value exists
        // and is convertible; false on any failure.
        static bool TryReadInt(System::String^ name, int% result)
        {
            try
            {
                Microsoft::Win32::RegistryKey^ key =
                    Microsoft::Win32::Registry::CurrentUser->OpenSubKey(SubKeyPath);
                if (key == nullptr)
                    return false;

                System::Object^ raw = key->GetValue(name);
                key->Close();

                if (raw == nullptr)
                    return false;

                result = System::Convert::ToInt32(raw);
                return true;
            }
            catch (System::Exception^)
            {
                return false;
            }
        }

        // Writes an integer value. Failures are ignored, as settings are not critical.
        static void WriteInt(System::String^ name, int value)
        {
            try
            {
                Microsoft::Win32::RegistryKey^ key =
                    Microsoft::Win32::Registry::CurrentUser->CreateSubKey(SubKeyPath);
                if (key != nullptr)
                {
                    key->SetValue(name, value);
                    key->Close();
                }
            }
            catch (System::Exception^)
            {
                // Ignore: losing a preference write must never disturb the game.
            }
        }

    public:
        // ---- UI language ----

        static Language LoadLanguage()
        {
            int stored = 0;
            if (TryReadInt(LanguageValueName, stored))
            {
                if (stored == static_cast<int>(Language::English))   return Language::English;
                if (stored == static_cast<int>(Language::Ukrainian)) return Language::Ukrainian;
            }
            return DefaultLanguage;
        }

        static void SaveLanguage(Language lang)
        {
            WriteInt(LanguageValueName, static_cast<int>(lang));
        }

        // ---- Preferred difficulty (0=VeryEasy .. 4=VeryHard) ----

        static unsigned int LoadDifficulty()
        {
            int stored = 0;
            if (TryReadInt(DifficultyValueName, stored) && stored >= 0 && stored <= 4)
                return static_cast<unsigned int>(stored);
            return DefaultDifficulty;
        }

        static void SaveDifficulty(unsigned int difficulty)
        {
            if (difficulty <= 4)
                WriteInt(DifficultyValueName, static_cast<int>(difficulty));
        }

        // ---- Win streak ----

        static unsigned int LoadWinStreak()
        {
            int stored = 0;
            if (TryReadInt(WinStreakValueName, stored) && stored >= 0)
                return static_cast<unsigned int>(stored);
            return 0;
        }

        static void SaveWinStreak(unsigned int streak)
        {
            WriteInt(WinStreakValueName, static_cast<int>(streak));
        }

        // ---- Window position ----

        // Returns true only if both coordinates were stored and readable.
        // Callers must still validate the position against the current screen layout.
        static bool TryLoadWindowPosition(int% left, int% top)
        {
            int storedLeft = 0;
            int storedTop = 0;
            if (!TryReadInt(WindowLeftValueName, storedLeft) ||
                !TryReadInt(WindowTopValueName, storedTop))
            {
                return false;
            }
            left = storedLeft;
            top = storedTop;
            return true;
        }

        static void SaveWindowPosition(int left, int top)
        {
            WriteInt(WindowLeftValueName, left);
            WriteInt(WindowTopValueName, top);
        }
    };
}
