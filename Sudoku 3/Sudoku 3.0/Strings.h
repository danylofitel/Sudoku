// Danylo Fitel 2013
// All translatable UI strings centralized in one place.
// To add a new language: add a value to Language, then add a column to every Get() call below.
// To add a new string: add a value to StringId, then add cases in the Get() function.

#pragma once

namespace Sudoku_3_0
{
    enum class Language : unsigned int
    {
        English = 0,
        Ukrainian = 1,
    };

    enum class StringId : unsigned int
    {
        // ---- Window title ----
        WindowTitle,

        // ---- Buttons ----
        ButtonNewGame,
        ButtonRestart,
        ButtonHint,
        ButtonFix,
        ButtonGiveUp,
        ButtonEnterPuzzle,
        ButtonSolve,
        ButtonUndo,
        ButtonPencil,

        // ---- Difficulty label & combo items ----
        LabelDifficulty,
        DifficultyVeryEasy,
        DifficultyEasy,
        DifficultyMedium,
        DifficultyHard,
        DifficultyVeryHard,

        // ---- Menu: File ----
        MenuFile,
        MenuSave,
        MenuOpen,
        MenuMinimize,
        MenuExit,

        // ---- Menu: Game ----
        MenuGame,
        MenuNewGame,
        MenuRestart,
        MenuPencil,
        MenuHint,
        MenuFix,
        MenuGiveUp,
        MenuEnterPuzzle,
        MenuSolve,
        MenuUndo,

        // ---- Menu: Options ----
        MenuOptions,
        MenuDifficulty,
        MenuLanguage,
        MenuLanguageEnglish,
        MenuLanguageUkrainian,

        // ---- Menu: Help ----
        MenuHelp,
        MenuAbout,
        MenuRules,
        MenuFeatures,
        MenuHintsAndTips,
        MenuKeyboard,

        // ---- Dialogs: titles ----
        DialogTitleSudoku,
        DialogTitleSave,
        DialogTitleRestart,
        DialogTitleFix,
        DialogTitleGiveUp,
        DialogTitleAbout,
        DialogTitleRules,
        DialogTitleFeatures,
        DialogTitleHintsAndTips,
        DialogTitleKeyboard,

        // ---- Dialogs: messages ----
        DialogSavePrompt,
        DialogRestartPrompt,
        DialogFixPrompt,
        DialogGiveUpPrompt,
        DialogAboutText,
        DialogBuildLabel,
        DialogRulesText,
        DialogFeaturesText,
        DialogHintsAndTipsText,
        DialogKeyboardText,

        // ---- Notifications ----
        NotifyMultipleSolutions,
        NotifyNoSolution,
        NotifyBoardEmpty,
        NotifyFileSaveError,
        NotifyFileLoadError,
        NotifyUnsupportedVersion,

        // ---- Numbers form ----
        ButtonClear,
        ButtonCancel,

        // ---- Win messages ----
        WinClean,
        WinWithAssists,
        WinAfterGiveUp,
        WinDifficulty,
        WinStreak,
        WinAssistHint,
        WinAssistHints,
        WinAssistFix,
        WinAssistFixes,
        WinAssistUsing,
        WinAssistAnd,

        // ---- Clipboard puzzle ----
        ButtonPastePuzzle,
        ButtonCopyPuzzle,
        ButtonCopySolution,
        MenuPastePuzzle,
        MenuCopyPuzzle,
        MenuCopySolution,
        NotifyInvalidPuzzleString,
    };

    ref class Strings abstract sealed
    {
    public:
        static System::String^ Get(StringId id, Language lang)
        {
            switch (id)
            {
                // ---- Window title ----
            case StringId::WindowTitle:
                switch (lang) {
                case Language::Ukrainian: return L"Судоку 3.0";
                default:                 return L"Sudoku 3.0";
                }

                // ---- Buttons ----
            case StringId::ButtonNewGame:
                switch (lang) {
                case Language::Ukrainian: return L"Нова гра";
                default:                 return L"New Game";
                }
            case StringId::ButtonRestart:
                switch (lang) {
                case Language::Ukrainian: return L"Спочатку";
                default:                 return L"Restart";
                }
            case StringId::ButtonHint:
                switch (lang) {
                case Language::Ukrainian: return L"Підказка";
                default:                 return L"Hint";
                }
            case StringId::ButtonFix:
                switch (lang) {
                case Language::Ukrainian: return L"Виправити";
                default:                 return L"Fix";
                }
            case StringId::ButtonGiveUp:
                switch (lang) {
                case Language::Ukrainian: return L"Здатися";
                default:                 return L"Give Up";
                }
            case StringId::ButtonEnterPuzzle:
                switch (lang) {
                case Language::Ukrainian: return L"Ввести задачу";
                default:                 return L"Enter Puzzle";
                }
            case StringId::ButtonSolve:
                switch (lang) {
                case Language::Ukrainian: return L"Розв'язати задачу";
                default:                 return L"Solve Puzzle";
                }
            case StringId::ButtonUndo:
                switch (lang) {
                case Language::Ukrainian: return L"Відмінити";
                default:                 return L"Undo";
                }
            case StringId::ButtonPencil:
                switch (lang) {
                case Language::Ukrainian: return L"Олівець";
                default:                 return L"Pencil";
                }

                // ---- Difficulty label & combo ----
            case StringId::LabelDifficulty:
                switch (lang) {
                case Language::Ukrainian: return L"Складність";
                default:                 return L"Difficulty";
                }
            case StringId::DifficultyVeryEasy:
                switch (lang) {
                case Language::Ukrainian: return L"Дуже легко";
                default:                 return L"Very Easy";
                }
            case StringId::DifficultyEasy:
                switch (lang) {
                case Language::Ukrainian: return L"Легко";
                default:                 return L"Easy";
                }
            case StringId::DifficultyMedium:
                switch (lang) {
                case Language::Ukrainian: return L"Середньо";
                default:                 return L"Medium";
                }
            case StringId::DifficultyHard:
                switch (lang) {
                case Language::Ukrainian: return L"Важко";
                default:                 return L"Hard";
                }
            case StringId::DifficultyVeryHard:
                switch (lang) {
                case Language::Ukrainian: return L"Дуже важко";
                default:                 return L"Very Hard";
                }

                // ---- Menu: File ----
            case StringId::MenuFile:
                switch (lang) {
                case Language::Ukrainian: return L"Файл";
                default:                 return L"File";
                }
            case StringId::MenuSave:
                switch (lang) {
                case Language::Ukrainian: return L"Зберегти";
                default:                 return L"Save";
                }
            case StringId::MenuOpen:
                switch (lang) {
                case Language::Ukrainian: return L"Відкрити";
                default:                 return L"Open";
                }
            case StringId::MenuMinimize:
                switch (lang) {
                case Language::Ukrainian: return L"Мінімізувати";
                default:                 return L"Minimize";
                }
            case StringId::MenuExit:
                switch (lang) {
                case Language::Ukrainian: return L"Вийти";
                default:                 return L"Exit";
                }

                // ---- Menu: Game ----
            case StringId::MenuGame:
                switch (lang) {
                case Language::Ukrainian: return L"Гра";
                default:                 return L"Game";
                }
            case StringId::MenuNewGame:
                switch (lang) {
                case Language::Ukrainian: return L"Нова гра";
                default:                 return L"New Game";
                }
            case StringId::MenuRestart:
                switch (lang) {
                case Language::Ukrainian: return L"Спочатку";
                default:                 return L"Restart";
                }
            case StringId::MenuPencil:
                switch (lang) {
                case Language::Ukrainian: return L"Олівець";
                default:                 return L"Pencil";
                }
            case StringId::MenuHint:
                switch (lang) {
                case Language::Ukrainian: return L"Підказка";
                default:                 return L"Hint";
                }
            case StringId::MenuFix:
                switch (lang) {
                case Language::Ukrainian: return L"Виправити";
                default:                 return L"Fix";
                }
            case StringId::MenuGiveUp:
                switch (lang) {
                case Language::Ukrainian: return L"Здатися";
                default:                 return L"Give Up";
                }
            case StringId::MenuEnterPuzzle:
                switch (lang) {
                case Language::Ukrainian: return L"Ввести задачу";
                default:                 return L"Enter Puzzle";
                }
            case StringId::MenuSolve:
                switch (lang) {
                case Language::Ukrainian: return L"Розв'язати задачу";
                default:                 return L"Solve Puzzle";
                }
            case StringId::MenuUndo:
                switch (lang) {
                case Language::Ukrainian: return L"Відмінити";
                default:                 return L"Undo";
                }

                // ---- Menu: Options ----
            case StringId::MenuOptions:
                switch (lang) {
                case Language::Ukrainian: return L"Параметри";
                default:                 return L"Options";
                }
            case StringId::MenuDifficulty:
                switch (lang) {
                case Language::Ukrainian: return L"Складність";
                default:                 return L"Difficulty";
                }
            case StringId::MenuLanguage:
                switch (lang) {
                case Language::Ukrainian: return L"Мова";
                default:                 return L"Language";
                }
            case StringId::MenuLanguageEnglish:
                return L"English";
            case StringId::MenuLanguageUkrainian:
                return L"Українська";

                // ---- Menu: Help ----
            case StringId::MenuHelp:
                switch (lang) {
                case Language::Ukrainian: return L"Довідка";
                default:                 return L"Help";
                }
            case StringId::MenuAbout:
                switch (lang) {
                case Language::Ukrainian: return L"Про гру";
                default:                 return L"About";
                }
            case StringId::MenuRules:
                switch (lang) {
                case Language::Ukrainian: return L"Правила";
                default:                 return L"Rules";
                }
            case StringId::MenuFeatures:
                switch (lang) {
                case Language::Ukrainian: return L"Можливості";
                default:                 return L"Features";
                }
            case StringId::MenuHintsAndTips:
                switch (lang) {
                case Language::Ukrainian: return L"Поради";
                default:                 return L"Hints And Tips";
                }
            case StringId::MenuKeyboard:
                switch (lang) {
                case Language::Ukrainian: return L"Клавіатура";
                default:                 return L"Keyboard";
                }

                // ---- Dialog titles ----
            case StringId::DialogTitleSudoku:
                switch (lang) {
                case Language::Ukrainian: return L"Судоку";
                default:                 return L"Sudoku";
                }
            case StringId::DialogTitleSave:
                switch (lang) {
                case Language::Ukrainian: return L"Зберегти гру";
                default:                 return L"Save Game";
                }
            case StringId::DialogTitleRestart:
                switch (lang) {
                case Language::Ukrainian: return L"Спочатку";
                default:                 return L"Restart";
                }
            case StringId::DialogTitleFix:
                switch (lang) {
                case Language::Ukrainian: return L"Виправити";
                default:                 return L"Fix";
                }
            case StringId::DialogTitleGiveUp:
                switch (lang) {
                case Language::Ukrainian: return L"Здатися";
                default:                 return L"Give Up";
                }
            case StringId::DialogTitleAbout:
                switch (lang) {
                case Language::Ukrainian: return L"Про гру";
                default:                 return L"About";
                }
            case StringId::DialogTitleRules:
                switch (lang) {
                case Language::Ukrainian: return L"Правила";
                default:                 return L"Rules";
                }
            case StringId::DialogTitleFeatures:
                switch (lang) {
                case Language::Ukrainian: return L"Можливості";
                default:                 return L"Features";
                }
            case StringId::DialogTitleHintsAndTips:
                switch (lang) {
                case Language::Ukrainian: return L"Поради";
                default:                 return L"Hints And Tips";
                }
            case StringId::DialogTitleKeyboard:
                switch (lang) {
                case Language::Ukrainian: return L"Клавіатура";
                default:                 return L"Keyboard";
                }

                // ---- Dialog messages ----
            case StringId::DialogSavePrompt:
                switch (lang) {
                case Language::Ukrainian: return L"Бажаєте зберегти поточну гру?";
                default:                 return L"Do you want to save the current game?";
                }
            case StringId::DialogRestartPrompt:
                switch (lang) {
                case Language::Ukrainian: return L"Ви впевнені, що хочете почати спочатку?\nВесь ваш прогрес у цій задачі буде втрачено.";
                default:                 return L"Are you sure you want to restart?\nAll your progress on this puzzle will be lost.";
                }
            case StringId::DialogFixPrompt:
                switch (lang) {
                case Language::Ukrainian: return L"Виправлення очистить усі клітинки, значення яких суперечать розв'язку.\nЦе позбавить вас можливості чистої перемоги в цій задачі.";
                default:                 return L"Fix will clear all cells whose values conflict with the solution.\nThis will disqualify you from a clean win on this puzzle.";
                }
            case StringId::DialogGiveUpPrompt:
                switch (lang) {
                case Language::Ukrainian: return L"Ви впевнені, що хочете здатися?\nЦе позбавить вас можливості чистої перемоги в цій задачі.";
                default:                 return L"Are you sure you want to give up?\nThis will disqualify you from a clean win on this puzzle.";
                }
            case StringId::DialogAboutText:
                switch (lang) {
                case Language::Ukrainian: return L"Судоку 3.0\n\nУсі права захищені";
                default:                 return L"Sudoku 3.0\n\nAll rights reserved";
                }
            case StringId::DialogBuildLabel:
                switch (lang) {
                case Language::Ukrainian: return L"Збірка: ";
                default:                 return L"Build: ";
                }
            case StringId::DialogRulesText:
                switch (lang) {
                case Language::Ukrainian:
                    return L"Розв'язати задачу судоку може бути непросто, але правила гри досить прості.\n\n"
                        L"Судоку — це сітка дев'ять на дев'ять клітинок, розділена на дев'ять підсіток або «регіонів» розміром три на три клітинки.\n\n"
                        L"Мета судоку — вписати цифру від 1 до 9 у кожну клітинку так, "
                        L"щоб кожен горизонтальний рядок, вертикальний стовпець і регіон містили кожну цифру рівно по одному разу.\n\n"
                        L"Задача судоку має лише один розв'язок.";
                default:
                    return L"Solving a sudoku puzzle can be rather tricky, but the rules of the game are quite simple.\n\n"
                        L"A sudoku puzzle is a grid of nine by nine squares or cells, that has been subdivided into "
                        L"nine subgrids or \"regions\" of three by three cells.\n\n"
                        L"The objective of sudoku is to enter a digit from 1 through 9 in each cell, in such a way "
                        L"that each horizontal row, vertical column and region contains each digit exactly once.\n\n"
                        L"A sudoku puzzle has only one solution.";
                }
            case StringId::DialogFeaturesText:
                switch (lang) {
                case Language::Ukrainian:
                    return L"Нова гра — розпочати нову гру\n"
                        L"Спочатку — перезапустити поточну гру\n"
                        L"Олівець — увімкнути або вимкнути режим олівця для позначок\n"
                        L"Підказка — увімкнути або вимкнути режим підказок для відкриття прихованих клітинок\n"
                        L"Виправити — видалити всі неправильні здогади\n"
                        L"Здатися — показати розв'язок поточної задачі\n"
                        L"Відмінити — скасувати останній хід або групу ходів\n"
                        L"Ввести задачу — ввести власну задачу судоку\n"
                        L"Розв'язати задачу — розв'язати власну задачу судоку\n"
                        L"Скопіювати задачу — скопіювати поточну задачу в буфер обміну\n"
                        L"Вставити задачу — завантажити задачу з буфера обміну\n"
                        L"Скопіювати розв'язок — скопіювати розв'язок власної задачі в буфер обміну";
                default:
                    return L"New Game - start a new game\n"
                        L"Restart - restart the current game\n"
                        L"Pencil - toggle pencil mode to add or remove pencil marks\n"
                        L"Hint - toggle hint mode to reveal hidden cells\n"
                        L"Fix - remove all incorrect guesses\n"
                        L"Give Up - show the solution to the current puzzle\n"
                        L"Undo - undo the last move or batch of moves\n"
                        L"Enter Puzzle - enter a custom sudoku puzzle\n"
                        L"Solve Puzzle - solve a custom sudoku puzzle\n"
                        L"Copy Puzzle - copy the current puzzle to the clipboard\n"
                        L"Paste Puzzle - load a puzzle from the clipboard\n"
                        L"Copy Solution - copy the solution of a solved custom puzzle to the clipboard";
                }
            case StringId::DialogHintsAndTipsText:
                switch (lang) {
                case Language::Ukrainian:
                    return L"Ви можете зберегти гру в будь-який момент і відкрити її пізніше\n\n"
                        L"Натисніть на будь-яку клітинку, яку хочете заповнити, щоб побачити варіанти\n\n"
                        L"Якщо введена вами цифра підсвічена червоним -\n"
                        L"вона конфліктує з наявними цифрами\n\n"
                        L"Натисніть кнопку «Підказка», щоб увімкнути режим підказок\n"
                        L"Натисніть і утримуйте, щоб перетягнути вікно";
                default:
                    return L"You can save the game anytime and open it later\n\n"
                        L"Click on any cell you want to fill to see the options\n\n"
                        L"If the number you entered is highlighted in red -\n"
                        L"it conflicts with existing numbers\n\n"
                        L"Click the Hint button to toggle hint mode\n"
                        L"Press and hold anywhere to drag the window";
                }
            case StringId::DialogKeyboardText:
                switch (lang) {
                case Language::Ukrainian:
                    return L"Гра повністю підтримує клавіатуру\n\n"
                        L"Натисніть Tab, щоб вибрати клітинки\n"
                        L"Використовуйте Tab або клавіші зі стрілками для навігації між клітинками\n"
                        L"Натисніть Enter або Пробіл, щоб відкрити вибір числа для клітинки\n"
                        L"Натисніть Backspace або Delete, щоб очистити вибрану клітинку\n"
                        L"Натисніть цифрову клавішу для швидкого заповнення клітинки\n\n"
                        L"Усі кнопки мають гарячі клавіші\n"
                        L"Список гарячих клавіш можна переглянути в головному меню";
                default:
                    return L"The game has full keyboard support\n\n"
                        L"Press Tab to select cells\n"
                        L"Use Tab or arrow keys to navigate between cells\n"
                        L"Press Enter or Space to open the number selection for a cell\n"
                        L"Press Backspace or Delete to clear the selected cell\n"
                        L"Press a number key to quickly fill the cell\n\n"
                        L"All buttons have hotkeys\n"
                        L"You can see the list of hotkeys in the main menu";
                }

                // ---- Notifications ----
            case StringId::NotifyMultipleSolutions:
                switch (lang) {
                case Language::Ukrainian: return L"Задача має кілька розв'язків!";
                default:                 return L"The puzzle has multiple solutions!";
                }
            case StringId::NotifyNoSolution:
                switch (lang) {
                case Language::Ukrainian: return L"Задача не має розв'язку!";
                default:                 return L"The puzzle has no solution!";
                }
            case StringId::NotifyBoardEmpty:
                switch (lang) {
                case Language::Ukrainian: return L"Поле порожнє!";
                default:                 return L"The board is empty!";
                }
            case StringId::NotifyFileSaveError:
                switch (lang) {
                case Language::Ukrainian: return L"Не вдалося записати файл!";
                default:                 return L"Could not write the file!";
                }
            case StringId::NotifyFileLoadError:
                switch (lang) {
                case Language::Ukrainian: return L"Файл збереження пошкоджено і не може бути завантажено.";
                default:                 return L"The save file is corrupted and could not be loaded.";
                }
            case StringId::NotifyUnsupportedVersion:
                switch (lang) {
                case Language::Ukrainian: return L"Це збереження створено новішою версією Судоку і не може бути відкрите. Версія збереження: ";
                default:                 return L"This save was created by a newer version of Sudoku and cannot be opened. Save version: ";
                }

                // ---- Numbers form ----
            case StringId::ButtonClear:
                switch (lang) {
                case Language::Ukrainian: return L"Стерти";
                default:                 return L"Clear";
                }
            case StringId::ButtonCancel:
                switch (lang) {
                case Language::Ukrainian: return L"Скасувати";
                default:                 return L"Cancel";
                }

                // ---- Win messages ----
            case StringId::WinClean:
                switch (lang) {
                case Language::Ukrainian: return L"Вітаємо! Ви виграли без підказок і виправлень!";
                default:                 return L"Congratulations! You won without any hints or fixes!";
                }
            case StringId::WinWithAssists:
                switch (lang) {
                case Language::Ukrainian: return L"Ви завершили гру";
                default:                 return L"You beat the game";
                }
            case StringId::WinAfterGiveUp:
                switch (lang) {
                case Language::Ukrainian: return L"Ви завершили задачу після того, як здалися";
                default:                 return L"You completed the puzzle after giving up";
                }
            case StringId::WinDifficulty:
                switch (lang) {
                case Language::Ukrainian: return L"\n\nСкладність: ";
                default:                 return L"\n\nDifficulty: ";
                }
            case StringId::WinStreak:
                switch (lang) {
                case Language::Ukrainian: return L"\nСерія перемог: ";
                default:                 return L"\nWin streak: ";
                }
            case StringId::WinAssistHint:
                switch (lang) {
                case Language::Ukrainian: return L"1 підказку";
                default:                 return L"1 hint";
                }
            case StringId::WinAssistHints:
                switch (lang) {
                case Language::Ukrainian: return L"підказки(-ок)";
                default:                 return L"hints";
                }
            case StringId::WinAssistFix:
                switch (lang) {
                case Language::Ukrainian: return L"1 виправлення";
                default:                 return L"1 fix";
                }
            case StringId::WinAssistFixes:
                switch (lang) {
                case Language::Ukrainian: return L"виправлень(-ня)";
                default:                 return L"fixes";
                }
            case StringId::WinAssistUsing:
                switch (lang) {
                case Language::Ukrainian: return L" використавши ";
                default:                 return L" using ";
                }
            case StringId::WinAssistAnd:
                switch (lang) {
                case Language::Ukrainian: return L" та ";
                default:                 return L" and ";
                }

                // ---- Clipboard puzzle ----
            case StringId::ButtonPastePuzzle:
                switch (lang) {
                case Language::Ukrainian: return L"Вставити задачу";
                default:                 return L"Paste Puzzle";
                }
            case StringId::ButtonCopyPuzzle:
                switch (lang) {
                case Language::Ukrainian: return L"Скопіювати задачу";
                default:                 return L"Copy Puzzle";
                }
            case StringId::ButtonCopySolution:
                switch (lang) {
                case Language::Ukrainian: return L"Скопіювати розв'язок";
                default:                 return L"Copy Solution";
                }
            case StringId::MenuPastePuzzle:
                switch (lang) {
                case Language::Ukrainian: return L"Вставити задачу";
                default:                 return L"Paste Puzzle";
                }
            case StringId::MenuCopyPuzzle:
                switch (lang) {
                case Language::Ukrainian: return L"Скопіювати задачу";
                default:                 return L"Copy Puzzle";
                }
            case StringId::MenuCopySolution:
                switch (lang) {
                case Language::Ukrainian: return L"Скопіювати розв'язок";
                default:                 return L"Copy Solution";
                }
            case StringId::NotifyInvalidPuzzleString:
                switch (lang) {
                case Language::Ukrainian: return L"Неправильний рядок! Потрібно 81 цифру (1-9 або 0/крапка для порожніх).";
                default:                 return L"Invalid puzzle string! Expected 81 digits (1-9 or 0/dot for empty cells).";
                }

            default:
                return L"";
            }
        }
    };
}
