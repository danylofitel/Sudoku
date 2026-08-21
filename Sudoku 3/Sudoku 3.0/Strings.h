// Danylo Fitel 2026
// All translatable UI strings centralized in one place.
// To add a new language: add a value to Language, then add a column to every Get() call below.
// To add a new string: add a value to StringId, then add cases in the Get() function.

#pragma once

#include "Language.h"
#include "BuildInfo.h" // generated at build time; defines SUDOKU_COPYRIGHT_YEAR_W

namespace Sudoku_3_0
{
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
        TooltipTimer,
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
        MenuCandidates,
        CandidateLevelNone,
        CandidateLevelCurrentCell,
        CandidateLevelAllCells,

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
        DialogTitleCandidates,

        // ---- Dialogs: messages ----
        DialogSavePrompt,
        DialogRestartPrompt,
        DialogFixPrompt,
        DialogGiveUpPrompt,
        DialogCandidatesPrompt,
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
        NotifyUnexpectedError,

        // ---- File dialogs ----
        FileDialogFilter,

        // ---- Numbers form ----
        ButtonClear,
        ButtonCancel,

        // ---- End-of-game message ----
        EndWin,          // headline: won with assists
        EndWinClean,     // headline: won with no hints/fixes/give-ups
        EndWinMostlyHints, // headline: "won", but hints revealed almost the whole board
        EndGiveUp,       // headline: gave up
        StatDifficulty,
        StatClues,       // parenthetical clue count appended to the difficulty line ("{0}" = count)
        StatTime,
        StatRestarts,
        StatHints,
        StatFixes,
        StatGiveUps,
        StatCandidateHelp,   // "Candidate help: " followed by a CandidateLevel* name
        StatWinStreak,
        StatCleanWinStreak,

        // ---- Clipboard puzzle ----
        ButtonPastePuzzle,
        ButtonCopyPuzzle,
        ButtonCopySolution,
        MenuPastePuzzle,
        MenuCopyPuzzle,
        MenuCopySolution,
        NotifyInvalidPuzzleString,

        // ---- Feature descriptions ----
        // One "Name - what it does" line per action; used as button tooltips and
        // composed into DialogFeaturesText so the two can never drift apart.
        FeatureNewGame,
        FeatureRestart,
        FeaturePencil,
        FeatureHint,
        FeatureFix,
        FeatureGiveUp,
        FeatureUndo,
        FeatureEnterPuzzle,
        FeatureSolve,
        FeatureCopyPuzzle,
        FeaturePastePuzzle,
        FeatureCopySolution,
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
            case StringId::TooltipTimer:
                switch (lang) {
                case Language::Ukrainian: return L"Час, витрачений на поточну задачу";
                default:                 return L"Time spent on current puzzle";
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
            case StringId::MenuCandidates:
                switch (lang) {
                case Language::Ukrainian: return L"Кандидати";
                default:                 return L"Candidates";
                }
            case StringId::CandidateLevelNone:
                switch (lang) {
                case Language::Ukrainian: return L"Немає";
                default:                 return L"None";
                }
            case StringId::CandidateLevelCurrentCell:
                switch (lang) {
                case Language::Ukrainian: return L"Поточна клітинка";
                default:                 return L"Current cell";
                }
            case StringId::CandidateLevelAllCells:
                switch (lang) {
                case Language::Ukrainian: return L"Усі клітинки";
                default:                 return L"All cells";
                }

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
            case StringId::DialogTitleCandidates:
                switch (lang) {
                case Language::Ukrainian: return L"Показувати кандидатів";
                default:                 return L"Show Candidates";
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
                case Language::Ukrainian: return L"Ви впевнені, що хочете здатися?\nЦе позбавить вас можливості чистої перемоги в цій задачі та обнулить вашу серію перемог.";
                default:                 return L"Are you sure you want to give up?\nThis will disqualify you from a clean win on this puzzle and reset your win streak.";
                }
            case StringId::DialogCandidatesPrompt:
                switch (lang) {
                case Language::Ukrainian: return L"Показ кандидатів вважається підказкою. Будь-яка задача, яку ви розв'яжете з увімкненим показом, не зарахується як чиста перемога, і вашу серію чистих перемог буде обнулено.\n\nУвімкнути показ кандидатів?";
                default:                 return L"Showing candidates counts as assistance. Any puzzle you solve while it is on will not count as a clean win, and your clean win streak will reset.\n\nEnable candidate display?";
                }
            case StringId::DialogAboutText:
                switch (lang) {
                case Language::Ukrainian: return L"Судоку 3.0\n\n© 2013–" SUDOKU_COPYRIGHT_YEAR_W L" Фітель Данило\nУсі права захищені";
                default:                 return L"Sudoku 3.0\n\n© 2013–" SUDOKU_COPYRIGHT_YEAR_W L" Danylo Fitel\nAll rights reserved";
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
                // Composed from the per-action Feature* strings (also used as button tooltips)
                return Get(StringId::FeatureNewGame, lang) + L"\n"
                    + Get(StringId::FeatureRestart, lang) + L"\n"
                    + Get(StringId::FeaturePencil, lang) + L"\n"
                    + Get(StringId::FeatureHint, lang) + L"\n"
                    + Get(StringId::FeatureFix, lang) + L"\n"
                    + Get(StringId::FeatureGiveUp, lang) + L"\n"
                    + Get(StringId::FeatureUndo, lang) + L"\n"
                    + Get(StringId::FeatureEnterPuzzle, lang) + L"\n"
                    + Get(StringId::FeatureSolve, lang) + L"\n"
                    + Get(StringId::FeatureCopyPuzzle, lang) + L"\n"
                    + Get(StringId::FeaturePastePuzzle, lang) + L"\n"
                    + Get(StringId::FeatureCopySolution, lang);
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
            case StringId::NotifyUnexpectedError:
                switch (lang) {
                case Language::Ukrainian: return L"Сталася неочікувана помилка, і застосунок буде закрито.\n\n";
                default:                 return L"An unexpected error occurred and the application must close.\n\n";
                }

                // ---- File dialogs ----
            case StringId::FileDialogFilter:
                switch (lang) {
                case Language::Ukrainian: return L"Збереження судоку (*.sdk3)|*.sdk3|Усі файли (*.*)|*.*";
                default:                 return L"Sudoku save (*.sdk3)|*.sdk3|All files (*.*)|*.*";
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

                // ---- End-of-game message ----
            case StringId::EndWin:
                switch (lang) {
                case Language::Ukrainian: return L"Вітаємо! Задачу розв'язано!";
                default:                 return L"Congratulations! You solved the puzzle!";
                }
            case StringId::EndWinClean:
                switch (lang) {
                case Language::Ukrainian: return L"Вітаємо! Бездоганна перемога!";
                default:                 return L"Congratulations! A flawless win!";
                }
            case StringId::EndWinMostlyHints:
                switch (lang) {
                case Language::Ukrainian: return L"Задачу завершено, але майже всю роботу зробили підказки — навряд чи краще, ніж здатися.";
                default:                 return L"Puzzle finished, but hints did almost all the work — hardly better than giving up.";
                }
            case StringId::EndGiveUp:
                switch (lang) {
                case Language::Ukrainian: return L"Ви здалися. Ось розв'язок.";
                default:                 return L"You gave up. Here is the solution.";
                }
            case StringId::StatDifficulty:
                switch (lang) {
                case Language::Ukrainian: return L"Складність: ";
                default:                 return L"Difficulty: ";
                }
            case StringId::StatClues:
                switch (lang) {
                case Language::Ukrainian: return L"({0} підказок)";
                default:                 return L"({0} clues)";
                }
            case StringId::StatTime:
                switch (lang) {
                case Language::Ukrainian: return L"Витрачено часу: ";
                default:                 return L"Time taken: ";
                }
            case StringId::StatRestarts:
                switch (lang) {
                case Language::Ukrainian: return L"Перезапусків: ";
                default:                 return L"Restarts: ";
                }
            case StringId::StatHints:
                switch (lang) {
                case Language::Ukrainian: return L"Підказок: ";
                default:                 return L"Hints: ";
                }
            case StringId::StatFixes:
                switch (lang) {
                case Language::Ukrainian: return L"Виправлень: ";
                default:                 return L"Fixes: ";
                }
            case StringId::StatGiveUps:
                switch (lang) {
                case Language::Ukrainian: return L"Капітуляцій: ";
                default:                 return L"Give-ups: ";
                }
            case StringId::StatCandidateHelp:
                switch (lang) {
                case Language::Ukrainian: return L"Показ кандидатів: ";
                default:                 return L"Candidate help: ";
                }
            case StringId::StatWinStreak:
                switch (lang) {
                case Language::Ukrainian: return L"Серія перемог: ";
                default:                 return L"Win streak: ";
                }
            case StringId::StatCleanWinStreak:
                switch (lang) {
                case Language::Ukrainian: return L"Серія чистих перемог: ";
                default:                 return L"Clean win streak: ";
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

                // ---- Feature descriptions (Features dialog lines & button tooltips) ----
            case StringId::FeatureNewGame:
                switch (lang) {
                case Language::Ukrainian: return L"Нова гра — розпочати нову гру";
                default:                 return L"New Game - start a new game";
                }
            case StringId::FeatureRestart:
                switch (lang) {
                case Language::Ukrainian: return L"Спочатку — перезапустити поточну гру";
                default:                 return L"Restart - restart the current game";
                }
            case StringId::FeaturePencil:
                switch (lang) {
                case Language::Ukrainian: return L"Олівець — увімкнути або вимкнути режим олівця для позначок";
                default:                 return L"Pencil - toggle pencil mode to add or remove pencil marks";
                }
            case StringId::FeatureHint:
                switch (lang) {
                case Language::Ukrainian: return L"Підказка — увімкнути або вимкнути режим підказок для відкриття прихованих клітинок";
                default:                 return L"Hint - toggle hint mode to reveal hidden cells";
                }
            case StringId::FeatureFix:
                switch (lang) {
                case Language::Ukrainian: return L"Виправити — видалити всі неправильні здогади";
                default:                 return L"Fix - remove all incorrect guesses";
                }
            case StringId::FeatureGiveUp:
                switch (lang) {
                case Language::Ukrainian: return L"Здатися — показати розв'язок поточної задачі";
                default:                 return L"Give Up - show the solution to the current puzzle";
                }
            case StringId::FeatureUndo:
                switch (lang) {
                case Language::Ukrainian: return L"Відмінити — скасувати останній хід або групу ходів";
                default:                 return L"Undo - undo the last move or batch of moves";
                }
            case StringId::FeatureEnterPuzzle:
                switch (lang) {
                case Language::Ukrainian: return L"Ввести задачу — ввести власну задачу судоку";
                default:                 return L"Enter Puzzle - enter a custom sudoku puzzle";
                }
            case StringId::FeatureSolve:
                switch (lang) {
                case Language::Ukrainian: return L"Розв'язати задачу — розв'язати власну задачу судоку";
                default:                 return L"Solve Puzzle - solve a custom sudoku puzzle";
                }
            case StringId::FeatureCopyPuzzle:
                switch (lang) {
                case Language::Ukrainian: return L"Скопіювати задачу — скопіювати поточну задачу в буфер обміну";
                default:                 return L"Copy Puzzle - copy the current puzzle to the clipboard";
                }
            case StringId::FeaturePastePuzzle:
                switch (lang) {
                case Language::Ukrainian: return L"Вставити задачу — завантажити задачу з буфера обміну";
                default:                 return L"Paste Puzzle - load a puzzle from the clipboard";
                }
            case StringId::FeatureCopySolution:
                switch (lang) {
                case Language::Ukrainian: return L"Скопіювати розв'язок — скопіювати розв'язок власної задачі в буфер обміну";
                default:                 return L"Copy Solution - copy the solution of a solved custom puzzle to the clipboard";
                }

            default:
                return L"";
            }
        }
    };
}
