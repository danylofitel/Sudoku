// Danylo Fitel 2026

#pragma once

#include "ClipboardPuzzleFormatter.h"
#include "ConflictDetector.h"
#include "GameMode.h"
#include "GameSession.h"
#include "GameTimer.h"
#include "Numbers.h"
#include "PlayerStats.h"
#include "SavedGame.h"
#include "SavedGameMapper.h"
#include "SaveGameStore.h"
#include "Settings.h"
#include "Strings.h"
#include "SudokuEngine.h"
#include "UndoManager.h"
#include "WindowDragger.h"

namespace Sudoku_3_0
{
    using namespace System;
    using namespace System::IO;
    using namespace System::Drawing;
    using namespace System::Windows::Forms;

    /// <summary>
    /// Sudoku game form
    /// </summary>
    public ref class SudokuForm : public System::Windows::Forms::Form
    {
    public:
        // startupFilePath: a .sdk3 file to open on launch (e.g. passed by the shell when a save
        // is double-clicked), or nullptr to resume the auto-save / start a new game.
        SudokuForm(System::String^ startupFilePath)
        {
            this->startupFilePath = startupFilePath;
            InitializeComponent();
            this->initialize();
        }

    protected:
        ~SudokuForm()
        {
            delete engine;
            engine = nullptr;

            // Font and StringFormat are IDisposable wrappers around native GDI/GDI+ handles.
            // They are created lazily in cell_Paint and are not part of the Form's component
            // container, so nothing else disposes them - delete releases their native handles
            // here rather than leaving it to the finalizer.
            delete pencilFont;
            pencilFont = nullptr;
            delete pencilFormat;
            pencilFormat = nullptr;

            // ToolTip is a Component we create ourselves (not in the designer's container),
            // so nothing else disposes it.
            delete buttonToolTips;
            buttonToolTips = nullptr;
        }

        !SudokuForm()
        {
            delete engine;
            engine = nullptr;
        }

        // Set of standard colors
    private: static const System::Drawing::Color defaultColor = Color::Black;
    private: static const System::Drawing::Color correctColor = Color::ForestGreen;
    private: static const System::Drawing::Color hintColor = Color::Orange;
    private: static const System::Drawing::Color giveUpColor = Color::Red;
    private: static const System::Drawing::Color solveColor = Color::DarkCyan;
    private: static const System::Drawing::Color defaultBackColor = SystemColors::Menu;
    private: static const System::Drawing::Color activeButtonColor = Color::Orange;
           // Conflict-highlight backgrounds: bright red on an editable cell, softer coral on a
           // locked one (a clue/hint/reveal cannot be changed, so its conflict is only informative)
    private: static const System::Drawing::Color conflictBackColor = Color::Red;
    private: static const System::Drawing::Color conflictBackColorImmutable = Color::LightCoral;

           // Size of the board: a classic 9x9 grid of 3x3 blocks. These are fixed compile-time
           // constants (the engine and layout are built for this size).
    private: static const unsigned int sizeFactor = 3;
    private: static const unsigned int boardSize = sizeFactor * sizeFactor;   // 9
    private: static const unsigned int numberOfCells = boardSize * boardSize; // 81

           // Sudoku engine
    private: SudokuGameEngine::SudokuEngine<>* engine;

           // Access to buttons by their numbers
    private: array<System::Windows::Forms::Button^>^ cells;

           // Reverse lookup map from cell button to its 0-based index; built once in initializeCells()
    private: System::Collections::Generic::Dictionary<System::Windows::Forms::Button^, int>^ cellIndex;

           // Cell buttons
    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::Button^ button2;
    private: System::Windows::Forms::Button^ button3;
    private: System::Windows::Forms::Button^ button4;
    private: System::Windows::Forms::Button^ button5;
    private: System::Windows::Forms::Button^ button6;
    private: System::Windows::Forms::Button^ button7;
    private: System::Windows::Forms::Button^ button8;
    private: System::Windows::Forms::Button^ button9;
    private: System::Windows::Forms::Button^ button10;
    private: System::Windows::Forms::Button^ button11;
    private: System::Windows::Forms::Button^ button12;
    private: System::Windows::Forms::Button^ button13;
    private: System::Windows::Forms::Button^ button14;
    private: System::Windows::Forms::Button^ button15;
    private: System::Windows::Forms::Button^ button16;
    private: System::Windows::Forms::Button^ button17;
    private: System::Windows::Forms::Button^ button18;
    private: System::Windows::Forms::Button^ button19;
    private: System::Windows::Forms::Button^ button20;
    private: System::Windows::Forms::Button^ button21;
    private: System::Windows::Forms::Button^ button22;
    private: System::Windows::Forms::Button^ button23;
    private: System::Windows::Forms::Button^ button24;
    private: System::Windows::Forms::Button^ button25;
    private: System::Windows::Forms::Button^ button26;
    private: System::Windows::Forms::Button^ button27;
    private: System::Windows::Forms::Button^ button28;
    private: System::Windows::Forms::Button^ button29;
    private: System::Windows::Forms::Button^ button30;
    private: System::Windows::Forms::Button^ button31;
    private: System::Windows::Forms::Button^ button32;
    private: System::Windows::Forms::Button^ button33;
    private: System::Windows::Forms::Button^ button34;
    private: System::Windows::Forms::Button^ button35;
    private: System::Windows::Forms::Button^ button36;
    private: System::Windows::Forms::Button^ button37;
    private: System::Windows::Forms::Button^ button38;
    private: System::Windows::Forms::Button^ button39;
    private: System::Windows::Forms::Button^ button40;
    private: System::Windows::Forms::Button^ button41;
    private: System::Windows::Forms::Button^ button42;
    private: System::Windows::Forms::Button^ button43;
    private: System::Windows::Forms::Button^ button44;
    private: System::Windows::Forms::Button^ button45;
    private: System::Windows::Forms::Button^ button46;
    private: System::Windows::Forms::Button^ button47;
    private: System::Windows::Forms::Button^ button48;
    private: System::Windows::Forms::Button^ button49;
    private: System::Windows::Forms::Button^ button50;
    private: System::Windows::Forms::Button^ button51;
    private: System::Windows::Forms::Button^ button52;
    private: System::Windows::Forms::Button^ button53;
    private: System::Windows::Forms::Button^ button54;
    private: System::Windows::Forms::Button^ button55;
    private: System::Windows::Forms::Button^ button56;
    private: System::Windows::Forms::Button^ button57;
    private: System::Windows::Forms::Button^ button58;
    private: System::Windows::Forms::Button^ button59;
    private: System::Windows::Forms::Button^ button60;
    private: System::Windows::Forms::Button^ button61;
    private: System::Windows::Forms::Button^ button62;
    private: System::Windows::Forms::Button^ button63;
    private: System::Windows::Forms::Button^ button64;
    private: System::Windows::Forms::Button^ button65;
    private: System::Windows::Forms::Button^ button66;
    private: System::Windows::Forms::Button^ button67;
    private: System::Windows::Forms::Button^ button68;
    private: System::Windows::Forms::Button^ button69;
    private: System::Windows::Forms::Button^ button70;
    private: System::Windows::Forms::Button^ button71;
    private: System::Windows::Forms::Button^ button72;
    private: System::Windows::Forms::Button^ button73;
    private: System::Windows::Forms::Button^ button74;
    private: System::Windows::Forms::Button^ button75;
    private: System::Windows::Forms::Button^ button76;
    private: System::Windows::Forms::Button^ button77;
    private: System::Windows::Forms::Button^ button78;
    private: System::Windows::Forms::Button^ button79;
    private: System::Windows::Forms::Button^ button80;
    private: System::Windows::Forms::Button^ button81;

           // Control elements
    private: System::Windows::Forms::Label^ timerLabel;
    private: System::Windows::Forms::Timer^ clockTimer;
    private: System::Windows::Forms::ComboBox^ difficultyComboBox;
    private: System::Windows::Forms::Button^ newGameButton;
    private: System::Windows::Forms::Button^ restartButton;
    private: System::Windows::Forms::Button^ hintButton;
    private: System::Windows::Forms::Button^ fixButton;
    private: System::Windows::Forms::Button^ giveUpButton;
    private: System::Windows::Forms::Button^ customPuzzleButton;
    private: System::Windows::Forms::Button^ solveButton;
    private: System::Windows::Forms::Button^ undoButton;
    private: System::Windows::Forms::Button^ pencilButton;
    private: System::Windows::Forms::Button^ clipboardButton;
    private: System::Windows::Forms::Button^ buttonMinimize;
    private: System::Windows::Forms::Button^ buttonClose;

           // Menu elements
    private: System::Windows::Forms::MenuStrip^ menuStrip;
    private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ saveToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ minimizeToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ exitToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ gameToolStripMenuItem;

    private: System::Windows::Forms::ToolStripMenuItem^ newGameToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ undoToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ restartToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ hintToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ fixToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ giveUpToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ customPuzzleToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ copyPuzzleToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ pastePuzzleToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ copySolutionToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ solveToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ pencilToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ optionsToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ difficultyToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ languageToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ candidatesToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ candidatesNoneToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ candidatesCurrentCellToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ candidatesAllCellsToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ englishToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ ukrainianToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ veryEasyToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ easyToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ mediumToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ hardToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ veryHardToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ helpToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ aboutToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ rulesToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ featuresToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ hintsAndTipsToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ keyboardToolStripMenuItem;
    private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator1;
    private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator2;

           // Dialogs
    private: System::Windows::Forms::SaveFileDialog^ saveGameDialog;
    private: System::Windows::Forms::OpenFileDialog^ openGameDialog;

           // Numbers form
    private: Sudoku_3_0::Numbers^ numbersForm;

           // Active game session state (mode, difficulty, counters, pencil marks, etc.)
    private: GameSession^ session;

           // Cross-game statistics that persist for the lifetime of the application
    private: PlayerStats^ playerStats;

           // Undo manager
    private: UndoManager^ undoManager;

           // Conflict detector
    private: ConflictDetector^ conflicts;

           // Time spent on the current puzzle (an on-screen display can later poll Elapsed)
    private: GameTimer^ gameTimer;

           // Board interaction state (view state, never persisted): whether the next cell action
           // pencils a mark or reveals a hint, and which cell the mouse is currently over.
    private: bool pencilMode;
    private: bool hintMode;
    private: int hoveredCellIndex;

           // Active UI language
    private: Language currentLanguage;

           // Difficulty index that backs the combo box and is used as the next-game preference (0-4).
           // Distinct from session->difficulty, which records the loaded puzzle's actual difficulty.
    private: unsigned int selectedDifficulty;

           // Mirror of the persisted candidate-display level (None / CurrentCell / AllCells).
           // Gates the candidate ghost in cell_Paint; chosen via the Options > Candidates submenu.
    private: CandidateDisplay candidateDisplay;

           // Window dragging
    private: WindowDragger^ dragger;

           // .sdk3 file to open at launch (from the command line / shell), or nullptr
    private: System::String^ startupFilePath;

           // Cached resources for painting pencil marks. The font is rebuilt only when the
           // cell size (and hence the derived point size) changes; the format is created once.
    private: System::Drawing::Font^ pencilFont;
    private: float pencilFontSize;
    private: System::Drawing::StringFormat^ pencilFormat;
    private: System::ComponentModel::IContainer^ components;

           // Hover tooltips for the side-panel buttons, showing the full localized action name
           // and description (also useful where a translated caption is wider than its button)
    private: System::Windows::Forms::ToolTip^ buttonToolTips;

#pragma region Windows Form Designer generated code

           void InitializeComponent(void)
           {
               this->components = (gcnew System::ComponentModel::Container());
               this->button1 = (gcnew System::Windows::Forms::Button());
               this->button2 = (gcnew System::Windows::Forms::Button());
               this->button3 = (gcnew System::Windows::Forms::Button());
               this->button4 = (gcnew System::Windows::Forms::Button());
               this->button5 = (gcnew System::Windows::Forms::Button());
               this->button6 = (gcnew System::Windows::Forms::Button());
               this->button7 = (gcnew System::Windows::Forms::Button());
               this->button8 = (gcnew System::Windows::Forms::Button());
               this->button9 = (gcnew System::Windows::Forms::Button());
               this->button10 = (gcnew System::Windows::Forms::Button());
               this->button11 = (gcnew System::Windows::Forms::Button());
               this->button12 = (gcnew System::Windows::Forms::Button());
               this->button13 = (gcnew System::Windows::Forms::Button());
               this->button14 = (gcnew System::Windows::Forms::Button());
               this->button15 = (gcnew System::Windows::Forms::Button());
               this->button16 = (gcnew System::Windows::Forms::Button());
               this->button17 = (gcnew System::Windows::Forms::Button());
               this->button18 = (gcnew System::Windows::Forms::Button());
               this->button19 = (gcnew System::Windows::Forms::Button());
               this->button20 = (gcnew System::Windows::Forms::Button());
               this->button21 = (gcnew System::Windows::Forms::Button());
               this->button22 = (gcnew System::Windows::Forms::Button());
               this->button23 = (gcnew System::Windows::Forms::Button());
               this->button24 = (gcnew System::Windows::Forms::Button());
               this->button25 = (gcnew System::Windows::Forms::Button());
               this->button26 = (gcnew System::Windows::Forms::Button());
               this->button27 = (gcnew System::Windows::Forms::Button());
               this->button28 = (gcnew System::Windows::Forms::Button());
               this->button29 = (gcnew System::Windows::Forms::Button());
               this->button30 = (gcnew System::Windows::Forms::Button());
               this->button31 = (gcnew System::Windows::Forms::Button());
               this->button32 = (gcnew System::Windows::Forms::Button());
               this->button33 = (gcnew System::Windows::Forms::Button());
               this->button34 = (gcnew System::Windows::Forms::Button());
               this->button35 = (gcnew System::Windows::Forms::Button());
               this->button36 = (gcnew System::Windows::Forms::Button());
               this->button37 = (gcnew System::Windows::Forms::Button());
               this->button38 = (gcnew System::Windows::Forms::Button());
               this->button39 = (gcnew System::Windows::Forms::Button());
               this->button40 = (gcnew System::Windows::Forms::Button());
               this->button41 = (gcnew System::Windows::Forms::Button());
               this->button42 = (gcnew System::Windows::Forms::Button());
               this->button43 = (gcnew System::Windows::Forms::Button());
               this->button44 = (gcnew System::Windows::Forms::Button());
               this->button45 = (gcnew System::Windows::Forms::Button());
               this->button46 = (gcnew System::Windows::Forms::Button());
               this->button47 = (gcnew System::Windows::Forms::Button());
               this->button48 = (gcnew System::Windows::Forms::Button());
               this->button49 = (gcnew System::Windows::Forms::Button());
               this->button50 = (gcnew System::Windows::Forms::Button());
               this->button51 = (gcnew System::Windows::Forms::Button());
               this->button52 = (gcnew System::Windows::Forms::Button());
               this->button53 = (gcnew System::Windows::Forms::Button());
               this->button54 = (gcnew System::Windows::Forms::Button());
               this->button55 = (gcnew System::Windows::Forms::Button());
               this->button56 = (gcnew System::Windows::Forms::Button());
               this->button57 = (gcnew System::Windows::Forms::Button());
               this->button58 = (gcnew System::Windows::Forms::Button());
               this->button59 = (gcnew System::Windows::Forms::Button());
               this->button60 = (gcnew System::Windows::Forms::Button());
               this->button61 = (gcnew System::Windows::Forms::Button());
               this->button62 = (gcnew System::Windows::Forms::Button());
               this->button63 = (gcnew System::Windows::Forms::Button());
               this->button64 = (gcnew System::Windows::Forms::Button());
               this->button65 = (gcnew System::Windows::Forms::Button());
               this->button66 = (gcnew System::Windows::Forms::Button());
               this->button67 = (gcnew System::Windows::Forms::Button());
               this->button68 = (gcnew System::Windows::Forms::Button());
               this->button69 = (gcnew System::Windows::Forms::Button());
               this->button70 = (gcnew System::Windows::Forms::Button());
               this->button71 = (gcnew System::Windows::Forms::Button());
               this->button72 = (gcnew System::Windows::Forms::Button());
               this->button73 = (gcnew System::Windows::Forms::Button());
               this->button74 = (gcnew System::Windows::Forms::Button());
               this->button75 = (gcnew System::Windows::Forms::Button());
               this->button76 = (gcnew System::Windows::Forms::Button());
               this->button77 = (gcnew System::Windows::Forms::Button());
               this->button78 = (gcnew System::Windows::Forms::Button());
               this->button79 = (gcnew System::Windows::Forms::Button());
               this->button80 = (gcnew System::Windows::Forms::Button());
               this->button81 = (gcnew System::Windows::Forms::Button());
               this->buttonMinimize = (gcnew System::Windows::Forms::Button());
               this->buttonClose = (gcnew System::Windows::Forms::Button());
               this->timerLabel = (gcnew System::Windows::Forms::Label());
               this->clockTimer = (gcnew System::Windows::Forms::Timer(this->components));
               this->difficultyComboBox = (gcnew System::Windows::Forms::ComboBox());
               this->newGameButton = (gcnew System::Windows::Forms::Button());
               this->restartButton = (gcnew System::Windows::Forms::Button());
               this->hintButton = (gcnew System::Windows::Forms::Button());
               this->fixButton = (gcnew System::Windows::Forms::Button());
               this->giveUpButton = (gcnew System::Windows::Forms::Button());
               this->customPuzzleButton = (gcnew System::Windows::Forms::Button());
               this->solveButton = (gcnew System::Windows::Forms::Button());
               this->undoButton = (gcnew System::Windows::Forms::Button());
               this->pencilButton = (gcnew System::Windows::Forms::Button());
               this->saveGameDialog = (gcnew System::Windows::Forms::SaveFileDialog());
               this->openGameDialog = (gcnew System::Windows::Forms::OpenFileDialog());
               this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
               this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
               this->minimizeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->gameToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->newGameToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->restartToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->pencilToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->hintToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->fixToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->giveUpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->undoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->customPuzzleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->solveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
               this->copyPuzzleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->pastePuzzleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->copySolutionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->languageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->englishToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->ukrainianToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->difficultyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->veryEasyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->easyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->mediumToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->hardToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->veryHardToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->candidatesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->candidatesNoneToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->candidatesCurrentCellToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->candidatesAllCellsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->rulesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->featuresToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->hintsAndTipsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->keyboardToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->clipboardButton = (gcnew System::Windows::Forms::Button());
               this->menuStrip->SuspendLayout();
               this->SuspendLayout();
               // 
               // button1
               // 
               this->button1->BackColor = System::Drawing::SystemColors::Menu;
               this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button1->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button1->Location = System::Drawing::Point(48, 54);
               this->button1->Margin = System::Windows::Forms::Padding(4);
               this->button1->Name = L"button1";
               this->button1->Size = System::Drawing::Size(62, 62);
               this->button1->TabIndex = 3;
               this->button1->UseVisualStyleBackColor = false;
               this->button1->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button1->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button2
               // 
               this->button2->BackColor = System::Drawing::SystemColors::Menu;
               this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button2->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button2->Location = System::Drawing::Point(114, 54);
               this->button2->Margin = System::Windows::Forms::Padding(4);
               this->button2->Name = L"button2";
               this->button2->Size = System::Drawing::Size(62, 62);
               this->button2->TabIndex = 4;
               this->button2->UseVisualStyleBackColor = false;
               this->button2->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button2->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button3
               // 
               this->button3->BackColor = System::Drawing::SystemColors::Menu;
               this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button3->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button3->Location = System::Drawing::Point(180, 54);
               this->button3->Margin = System::Windows::Forms::Padding(4);
               this->button3->Name = L"button3";
               this->button3->Size = System::Drawing::Size(62, 62);
               this->button3->TabIndex = 5;
               this->button3->UseVisualStyleBackColor = false;
               this->button3->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button3->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button3->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button4
               // 
               this->button4->BackColor = System::Drawing::SystemColors::Menu;
               this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button4->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button4->Location = System::Drawing::Point(254, 54);
               this->button4->Margin = System::Windows::Forms::Padding(4);
               this->button4->Name = L"button4";
               this->button4->Size = System::Drawing::Size(62, 62);
               this->button4->TabIndex = 6;
               this->button4->UseVisualStyleBackColor = false;
               this->button4->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button4->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button4->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button4->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button5
               // 
               this->button5->BackColor = System::Drawing::SystemColors::Menu;
               this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button5->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button5->Location = System::Drawing::Point(320, 54);
               this->button5->Margin = System::Windows::Forms::Padding(4);
               this->button5->Name = L"button5";
               this->button5->Size = System::Drawing::Size(62, 62);
               this->button5->TabIndex = 7;
               this->button5->UseVisualStyleBackColor = false;
               this->button5->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button5->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button5->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button5->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button6
               // 
               this->button6->BackColor = System::Drawing::SystemColors::Menu;
               this->button6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button6->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button6->Location = System::Drawing::Point(386, 54);
               this->button6->Margin = System::Windows::Forms::Padding(4);
               this->button6->Name = L"button6";
               this->button6->Size = System::Drawing::Size(62, 62);
               this->button6->TabIndex = 8;
               this->button6->UseVisualStyleBackColor = false;
               this->button6->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button6->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button6->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button6->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button7
               // 
               this->button7->BackColor = System::Drawing::SystemColors::Menu;
               this->button7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button7->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button7->Location = System::Drawing::Point(460, 54);
               this->button7->Margin = System::Windows::Forms::Padding(4);
               this->button7->Name = L"button7";
               this->button7->Size = System::Drawing::Size(62, 62);
               this->button7->TabIndex = 9;
               this->button7->UseVisualStyleBackColor = false;
               this->button7->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button7->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button7->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button7->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button8
               // 
               this->button8->BackColor = System::Drawing::SystemColors::Menu;
               this->button8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button8->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button8->Location = System::Drawing::Point(526, 54);
               this->button8->Margin = System::Windows::Forms::Padding(4);
               this->button8->Name = L"button8";
               this->button8->Size = System::Drawing::Size(62, 62);
               this->button8->TabIndex = 10;
               this->button8->UseVisualStyleBackColor = false;
               this->button8->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button8->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button8->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button8->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button9
               // 
               this->button9->BackColor = System::Drawing::SystemColors::Menu;
               this->button9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button9->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button9->Location = System::Drawing::Point(592, 54);
               this->button9->Margin = System::Windows::Forms::Padding(4);
               this->button9->Name = L"button9";
               this->button9->Size = System::Drawing::Size(62, 62);
               this->button9->TabIndex = 11;
               this->button9->UseVisualStyleBackColor = false;
               this->button9->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button9->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button9->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button9->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button10
               // 
               this->button10->BackColor = System::Drawing::SystemColors::Menu;
               this->button10->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button10->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button10->Location = System::Drawing::Point(48, 120);
               this->button10->Margin = System::Windows::Forms::Padding(4);
               this->button10->Name = L"button10";
               this->button10->Size = System::Drawing::Size(62, 62);
               this->button10->TabIndex = 12;
               this->button10->UseVisualStyleBackColor = false;
               this->button10->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button10->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button10->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button10->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button11
               // 
               this->button11->BackColor = System::Drawing::SystemColors::Menu;
               this->button11->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button11->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button11->Location = System::Drawing::Point(114, 120);
               this->button11->Margin = System::Windows::Forms::Padding(4);
               this->button11->Name = L"button11";
               this->button11->Size = System::Drawing::Size(62, 62);
               this->button11->TabIndex = 13;
               this->button11->UseVisualStyleBackColor = false;
               this->button11->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button11->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button11->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button11->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button12
               // 
               this->button12->BackColor = System::Drawing::SystemColors::Menu;
               this->button12->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button12->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button12->Location = System::Drawing::Point(180, 120);
               this->button12->Margin = System::Windows::Forms::Padding(4);
               this->button12->Name = L"button12";
               this->button12->Size = System::Drawing::Size(62, 62);
               this->button12->TabIndex = 14;
               this->button12->UseVisualStyleBackColor = false;
               this->button12->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button12->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button12->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button12->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button13
               // 
               this->button13->BackColor = System::Drawing::SystemColors::Menu;
               this->button13->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button13->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button13->Location = System::Drawing::Point(254, 120);
               this->button13->Margin = System::Windows::Forms::Padding(4);
               this->button13->Name = L"button13";
               this->button13->Size = System::Drawing::Size(62, 62);
               this->button13->TabIndex = 15;
               this->button13->UseVisualStyleBackColor = false;
               this->button13->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button13->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button13->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button13->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button14
               // 
               this->button14->BackColor = System::Drawing::SystemColors::Menu;
               this->button14->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button14->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button14->Location = System::Drawing::Point(320, 120);
               this->button14->Margin = System::Windows::Forms::Padding(4);
               this->button14->Name = L"button14";
               this->button14->Size = System::Drawing::Size(62, 62);
               this->button14->TabIndex = 16;
               this->button14->UseVisualStyleBackColor = false;
               this->button14->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button14->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button14->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button14->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button15
               // 
               this->button15->BackColor = System::Drawing::SystemColors::Menu;
               this->button15->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button15->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button15->Location = System::Drawing::Point(386, 120);
               this->button15->Margin = System::Windows::Forms::Padding(4);
               this->button15->Name = L"button15";
               this->button15->Size = System::Drawing::Size(62, 62);
               this->button15->TabIndex = 17;
               this->button15->UseVisualStyleBackColor = false;
               this->button15->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button15->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button15->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button15->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button16
               // 
               this->button16->BackColor = System::Drawing::SystemColors::Menu;
               this->button16->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button16->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button16->Location = System::Drawing::Point(460, 120);
               this->button16->Margin = System::Windows::Forms::Padding(4);
               this->button16->Name = L"button16";
               this->button16->Size = System::Drawing::Size(62, 62);
               this->button16->TabIndex = 18;
               this->button16->UseVisualStyleBackColor = false;
               this->button16->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button16->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button16->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button16->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button17
               // 
               this->button17->BackColor = System::Drawing::SystemColors::Menu;
               this->button17->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button17->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button17->Location = System::Drawing::Point(526, 120);
               this->button17->Margin = System::Windows::Forms::Padding(4);
               this->button17->Name = L"button17";
               this->button17->Size = System::Drawing::Size(62, 62);
               this->button17->TabIndex = 19;
               this->button17->UseVisualStyleBackColor = false;
               this->button17->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button17->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button17->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button17->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button18
               // 
               this->button18->BackColor = System::Drawing::SystemColors::Menu;
               this->button18->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button18->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button18->Location = System::Drawing::Point(592, 120);
               this->button18->Margin = System::Windows::Forms::Padding(4);
               this->button18->Name = L"button18";
               this->button18->Size = System::Drawing::Size(62, 62);
               this->button18->TabIndex = 20;
               this->button18->UseVisualStyleBackColor = false;
               this->button18->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button18->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button18->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button18->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button19
               // 
               this->button19->BackColor = System::Drawing::SystemColors::Menu;
               this->button19->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button19->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button19->Location = System::Drawing::Point(48, 186);
               this->button19->Margin = System::Windows::Forms::Padding(4);
               this->button19->Name = L"button19";
               this->button19->Size = System::Drawing::Size(62, 62);
               this->button19->TabIndex = 21;
               this->button19->UseVisualStyleBackColor = false;
               this->button19->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button19->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button19->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button19->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button20
               // 
               this->button20->BackColor = System::Drawing::SystemColors::Menu;
               this->button20->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button20->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button20->Location = System::Drawing::Point(114, 186);
               this->button20->Margin = System::Windows::Forms::Padding(4);
               this->button20->Name = L"button20";
               this->button20->Size = System::Drawing::Size(62, 62);
               this->button20->TabIndex = 22;
               this->button20->UseVisualStyleBackColor = false;
               this->button20->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button20->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button20->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button20->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button21
               // 
               this->button21->BackColor = System::Drawing::SystemColors::Menu;
               this->button21->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button21->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button21->Location = System::Drawing::Point(180, 186);
               this->button21->Margin = System::Windows::Forms::Padding(4);
               this->button21->Name = L"button21";
               this->button21->Size = System::Drawing::Size(62, 62);
               this->button21->TabIndex = 23;
               this->button21->UseVisualStyleBackColor = false;
               this->button21->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button21->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button21->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button21->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button22
               // 
               this->button22->BackColor = System::Drawing::SystemColors::Menu;
               this->button22->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button22->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button22->Location = System::Drawing::Point(254, 186);
               this->button22->Margin = System::Windows::Forms::Padding(4);
               this->button22->Name = L"button22";
               this->button22->Size = System::Drawing::Size(62, 62);
               this->button22->TabIndex = 24;
               this->button22->UseVisualStyleBackColor = false;
               this->button22->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button22->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button22->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button22->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button23
               // 
               this->button23->BackColor = System::Drawing::SystemColors::Menu;
               this->button23->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button23->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button23->Location = System::Drawing::Point(320, 186);
               this->button23->Margin = System::Windows::Forms::Padding(4);
               this->button23->Name = L"button23";
               this->button23->Size = System::Drawing::Size(62, 62);
               this->button23->TabIndex = 25;
               this->button23->UseVisualStyleBackColor = false;
               this->button23->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button23->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button23->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button23->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button24
               // 
               this->button24->BackColor = System::Drawing::SystemColors::Menu;
               this->button24->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button24->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button24->Location = System::Drawing::Point(386, 186);
               this->button24->Margin = System::Windows::Forms::Padding(4);
               this->button24->Name = L"button24";
               this->button24->Size = System::Drawing::Size(62, 62);
               this->button24->TabIndex = 26;
               this->button24->UseVisualStyleBackColor = false;
               this->button24->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button24->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button24->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button24->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button25
               // 
               this->button25->BackColor = System::Drawing::SystemColors::Menu;
               this->button25->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button25->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button25->Location = System::Drawing::Point(460, 186);
               this->button25->Margin = System::Windows::Forms::Padding(4);
               this->button25->Name = L"button25";
               this->button25->Size = System::Drawing::Size(62, 62);
               this->button25->TabIndex = 27;
               this->button25->UseVisualStyleBackColor = false;
               this->button25->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button25->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button25->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button25->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button26
               // 
               this->button26->BackColor = System::Drawing::SystemColors::Menu;
               this->button26->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button26->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button26->Location = System::Drawing::Point(526, 186);
               this->button26->Margin = System::Windows::Forms::Padding(4);
               this->button26->Name = L"button26";
               this->button26->Size = System::Drawing::Size(62, 62);
               this->button26->TabIndex = 28;
               this->button26->UseVisualStyleBackColor = false;
               this->button26->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button26->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button26->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button26->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button27
               // 
               this->button27->BackColor = System::Drawing::SystemColors::Menu;
               this->button27->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button27->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button27->Location = System::Drawing::Point(592, 186);
               this->button27->Margin = System::Windows::Forms::Padding(4);
               this->button27->Name = L"button27";
               this->button27->Size = System::Drawing::Size(62, 62);
               this->button27->TabIndex = 29;
               this->button27->UseVisualStyleBackColor = false;
               this->button27->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button27->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button27->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button27->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button28
               // 
               this->button28->BackColor = System::Drawing::SystemColors::Menu;
               this->button28->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button28->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button28->Location = System::Drawing::Point(48, 262);
               this->button28->Margin = System::Windows::Forms::Padding(4);
               this->button28->Name = L"button28";
               this->button28->Size = System::Drawing::Size(62, 62);
               this->button28->TabIndex = 30;
               this->button28->UseVisualStyleBackColor = false;
               this->button28->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button28->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button28->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button28->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button29
               // 
               this->button29->BackColor = System::Drawing::SystemColors::Menu;
               this->button29->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button29->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button29->Location = System::Drawing::Point(114, 262);
               this->button29->Margin = System::Windows::Forms::Padding(4);
               this->button29->Name = L"button29";
               this->button29->Size = System::Drawing::Size(62, 62);
               this->button29->TabIndex = 31;
               this->button29->UseVisualStyleBackColor = false;
               this->button29->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button29->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button29->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button29->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button30
               // 
               this->button30->BackColor = System::Drawing::SystemColors::Menu;
               this->button30->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button30->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button30->Location = System::Drawing::Point(180, 262);
               this->button30->Margin = System::Windows::Forms::Padding(4);
               this->button30->Name = L"button30";
               this->button30->Size = System::Drawing::Size(62, 62);
               this->button30->TabIndex = 32;
               this->button30->UseVisualStyleBackColor = false;
               this->button30->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button30->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button30->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button30->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button31
               // 
               this->button31->BackColor = System::Drawing::SystemColors::Menu;
               this->button31->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button31->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button31->Location = System::Drawing::Point(254, 262);
               this->button31->Margin = System::Windows::Forms::Padding(4);
               this->button31->Name = L"button31";
               this->button31->Size = System::Drawing::Size(62, 62);
               this->button31->TabIndex = 33;
               this->button31->UseVisualStyleBackColor = false;
               this->button31->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button31->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button31->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button31->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button32
               // 
               this->button32->BackColor = System::Drawing::SystemColors::Menu;
               this->button32->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button32->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button32->Location = System::Drawing::Point(320, 262);
               this->button32->Margin = System::Windows::Forms::Padding(4);
               this->button32->Name = L"button32";
               this->button32->Size = System::Drawing::Size(62, 62);
               this->button32->TabIndex = 34;
               this->button32->UseVisualStyleBackColor = false;
               this->button32->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button32->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button32->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button32->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button33
               // 
               this->button33->BackColor = System::Drawing::SystemColors::Menu;
               this->button33->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button33->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button33->Location = System::Drawing::Point(386, 262);
               this->button33->Margin = System::Windows::Forms::Padding(4);
               this->button33->Name = L"button33";
               this->button33->Size = System::Drawing::Size(62, 62);
               this->button33->TabIndex = 35;
               this->button33->UseVisualStyleBackColor = false;
               this->button33->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button33->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button33->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button33->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button34
               // 
               this->button34->BackColor = System::Drawing::SystemColors::Menu;
               this->button34->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button34->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button34->Location = System::Drawing::Point(460, 262);
               this->button34->Margin = System::Windows::Forms::Padding(4);
               this->button34->Name = L"button34";
               this->button34->Size = System::Drawing::Size(62, 62);
               this->button34->TabIndex = 36;
               this->button34->UseVisualStyleBackColor = false;
               this->button34->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button34->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button34->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button34->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button35
               // 
               this->button35->BackColor = System::Drawing::SystemColors::Menu;
               this->button35->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button35->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button35->Location = System::Drawing::Point(526, 262);
               this->button35->Margin = System::Windows::Forms::Padding(4);
               this->button35->Name = L"button35";
               this->button35->Size = System::Drawing::Size(62, 62);
               this->button35->TabIndex = 37;
               this->button35->UseVisualStyleBackColor = false;
               this->button35->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button35->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button35->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button35->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button36
               // 
               this->button36->BackColor = System::Drawing::SystemColors::Menu;
               this->button36->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button36->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button36->Location = System::Drawing::Point(592, 262);
               this->button36->Margin = System::Windows::Forms::Padding(4);
               this->button36->Name = L"button36";
               this->button36->Size = System::Drawing::Size(62, 62);
               this->button36->TabIndex = 38;
               this->button36->UseVisualStyleBackColor = false;
               this->button36->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button36->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button36->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button36->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button37
               // 
               this->button37->BackColor = System::Drawing::SystemColors::Menu;
               this->button37->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button37->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button37->Location = System::Drawing::Point(48, 328);
               this->button37->Margin = System::Windows::Forms::Padding(4);
               this->button37->Name = L"button37";
               this->button37->Size = System::Drawing::Size(62, 62);
               this->button37->TabIndex = 39;
               this->button37->UseVisualStyleBackColor = false;
               this->button37->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button37->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button37->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button37->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button38
               // 
               this->button38->BackColor = System::Drawing::SystemColors::Menu;
               this->button38->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button38->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button38->Location = System::Drawing::Point(114, 328);
               this->button38->Margin = System::Windows::Forms::Padding(4);
               this->button38->Name = L"button38";
               this->button38->Size = System::Drawing::Size(62, 62);
               this->button38->TabIndex = 40;
               this->button38->UseVisualStyleBackColor = false;
               this->button38->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button38->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button38->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button38->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button39
               // 
               this->button39->BackColor = System::Drawing::SystemColors::Menu;
               this->button39->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button39->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button39->Location = System::Drawing::Point(180, 328);
               this->button39->Margin = System::Windows::Forms::Padding(4);
               this->button39->Name = L"button39";
               this->button39->Size = System::Drawing::Size(62, 62);
               this->button39->TabIndex = 41;
               this->button39->UseVisualStyleBackColor = false;
               this->button39->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button39->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button39->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button39->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button40
               // 
               this->button40->BackColor = System::Drawing::SystemColors::Menu;
               this->button40->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button40->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button40->Location = System::Drawing::Point(254, 328);
               this->button40->Margin = System::Windows::Forms::Padding(4);
               this->button40->Name = L"button40";
               this->button40->Size = System::Drawing::Size(62, 62);
               this->button40->TabIndex = 42;
               this->button40->UseVisualStyleBackColor = false;
               this->button40->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button40->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button40->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button40->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button41
               // 
               this->button41->BackColor = System::Drawing::SystemColors::Menu;
               this->button41->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button41->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button41->Location = System::Drawing::Point(320, 328);
               this->button41->Margin = System::Windows::Forms::Padding(4);
               this->button41->Name = L"button41";
               this->button41->Size = System::Drawing::Size(62, 62);
               this->button41->TabIndex = 43;
               this->button41->UseVisualStyleBackColor = false;
               this->button41->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button41->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button41->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button41->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button42
               // 
               this->button42->BackColor = System::Drawing::SystemColors::Menu;
               this->button42->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button42->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button42->Location = System::Drawing::Point(386, 328);
               this->button42->Margin = System::Windows::Forms::Padding(4);
               this->button42->Name = L"button42";
               this->button42->Size = System::Drawing::Size(62, 62);
               this->button42->TabIndex = 44;
               this->button42->UseVisualStyleBackColor = false;
               this->button42->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button42->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button42->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button42->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button43
               // 
               this->button43->BackColor = System::Drawing::SystemColors::Menu;
               this->button43->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button43->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button43->Location = System::Drawing::Point(460, 328);
               this->button43->Margin = System::Windows::Forms::Padding(4);
               this->button43->Name = L"button43";
               this->button43->Size = System::Drawing::Size(62, 62);
               this->button43->TabIndex = 45;
               this->button43->UseVisualStyleBackColor = false;
               this->button43->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button43->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button43->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button43->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button44
               // 
               this->button44->BackColor = System::Drawing::SystemColors::Menu;
               this->button44->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button44->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button44->Location = System::Drawing::Point(526, 328);
               this->button44->Margin = System::Windows::Forms::Padding(4);
               this->button44->Name = L"button44";
               this->button44->Size = System::Drawing::Size(62, 62);
               this->button44->TabIndex = 46;
               this->button44->UseVisualStyleBackColor = false;
               this->button44->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button44->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button44->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button44->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button45
               // 
               this->button45->BackColor = System::Drawing::SystemColors::Menu;
               this->button45->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button45->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button45->Location = System::Drawing::Point(592, 328);
               this->button45->Margin = System::Windows::Forms::Padding(4);
               this->button45->Name = L"button45";
               this->button45->Size = System::Drawing::Size(62, 62);
               this->button45->TabIndex = 47;
               this->button45->UseVisualStyleBackColor = false;
               this->button45->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button45->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button45->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button45->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button46
               // 
               this->button46->BackColor = System::Drawing::SystemColors::Menu;
               this->button46->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button46->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button46->Location = System::Drawing::Point(48, 394);
               this->button46->Margin = System::Windows::Forms::Padding(4);
               this->button46->Name = L"button46";
               this->button46->Size = System::Drawing::Size(62, 62);
               this->button46->TabIndex = 48;
               this->button46->UseVisualStyleBackColor = false;
               this->button46->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button46->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button46->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button46->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button47
               // 
               this->button47->BackColor = System::Drawing::SystemColors::Menu;
               this->button47->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button47->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button47->Location = System::Drawing::Point(114, 394);
               this->button47->Margin = System::Windows::Forms::Padding(4);
               this->button47->Name = L"button47";
               this->button47->Size = System::Drawing::Size(62, 62);
               this->button47->TabIndex = 49;
               this->button47->UseVisualStyleBackColor = false;
               this->button47->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button47->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button47->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button47->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button48
               // 
               this->button48->BackColor = System::Drawing::SystemColors::Menu;
               this->button48->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button48->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button48->Location = System::Drawing::Point(180, 394);
               this->button48->Margin = System::Windows::Forms::Padding(4);
               this->button48->Name = L"button48";
               this->button48->Size = System::Drawing::Size(62, 62);
               this->button48->TabIndex = 50;
               this->button48->UseVisualStyleBackColor = false;
               this->button48->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button48->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button48->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button48->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button49
               // 
               this->button49->BackColor = System::Drawing::SystemColors::Menu;
               this->button49->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button49->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button49->Location = System::Drawing::Point(254, 394);
               this->button49->Margin = System::Windows::Forms::Padding(4);
               this->button49->Name = L"button49";
               this->button49->Size = System::Drawing::Size(62, 62);
               this->button49->TabIndex = 51;
               this->button49->UseVisualStyleBackColor = false;
               this->button49->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button49->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button49->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button49->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button50
               // 
               this->button50->BackColor = System::Drawing::SystemColors::Menu;
               this->button50->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button50->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button50->Location = System::Drawing::Point(320, 394);
               this->button50->Margin = System::Windows::Forms::Padding(4);
               this->button50->Name = L"button50";
               this->button50->Size = System::Drawing::Size(62, 62);
               this->button50->TabIndex = 52;
               this->button50->UseVisualStyleBackColor = false;
               this->button50->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button50->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button50->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button50->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button51
               // 
               this->button51->BackColor = System::Drawing::SystemColors::Menu;
               this->button51->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button51->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button51->Location = System::Drawing::Point(386, 394);
               this->button51->Margin = System::Windows::Forms::Padding(4);
               this->button51->Name = L"button51";
               this->button51->Size = System::Drawing::Size(62, 62);
               this->button51->TabIndex = 53;
               this->button51->UseVisualStyleBackColor = false;
               this->button51->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button51->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button51->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button51->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button52
               // 
               this->button52->BackColor = System::Drawing::SystemColors::Menu;
               this->button52->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button52->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button52->Location = System::Drawing::Point(460, 394);
               this->button52->Margin = System::Windows::Forms::Padding(4);
               this->button52->Name = L"button52";
               this->button52->Size = System::Drawing::Size(62, 62);
               this->button52->TabIndex = 54;
               this->button52->UseVisualStyleBackColor = false;
               this->button52->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button52->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button52->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button52->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button53
               // 
               this->button53->BackColor = System::Drawing::SystemColors::Menu;
               this->button53->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button53->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button53->Location = System::Drawing::Point(526, 394);
               this->button53->Margin = System::Windows::Forms::Padding(4);
               this->button53->Name = L"button53";
               this->button53->Size = System::Drawing::Size(62, 62);
               this->button53->TabIndex = 55;
               this->button53->UseVisualStyleBackColor = false;
               this->button53->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button53->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button53->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button53->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button54
               // 
               this->button54->BackColor = System::Drawing::SystemColors::Menu;
               this->button54->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button54->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button54->Location = System::Drawing::Point(592, 394);
               this->button54->Margin = System::Windows::Forms::Padding(4);
               this->button54->Name = L"button54";
               this->button54->Size = System::Drawing::Size(62, 62);
               this->button54->TabIndex = 56;
               this->button54->UseVisualStyleBackColor = false;
               this->button54->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button54->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button54->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button54->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button55
               // 
               this->button55->BackColor = System::Drawing::SystemColors::Menu;
               this->button55->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button55->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button55->Location = System::Drawing::Point(48, 470);
               this->button55->Margin = System::Windows::Forms::Padding(4);
               this->button55->Name = L"button55";
               this->button55->Size = System::Drawing::Size(62, 62);
               this->button55->TabIndex = 57;
               this->button55->UseVisualStyleBackColor = false;
               this->button55->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button55->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button55->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button55->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button56
               // 
               this->button56->BackColor = System::Drawing::SystemColors::Menu;
               this->button56->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button56->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button56->Location = System::Drawing::Point(114, 470);
               this->button56->Margin = System::Windows::Forms::Padding(4);
               this->button56->Name = L"button56";
               this->button56->Size = System::Drawing::Size(62, 62);
               this->button56->TabIndex = 58;
               this->button56->UseVisualStyleBackColor = false;
               this->button56->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button56->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button56->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button56->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button57
               // 
               this->button57->BackColor = System::Drawing::SystemColors::Menu;
               this->button57->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button57->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button57->Location = System::Drawing::Point(180, 470);
               this->button57->Margin = System::Windows::Forms::Padding(4);
               this->button57->Name = L"button57";
               this->button57->Size = System::Drawing::Size(62, 62);
               this->button57->TabIndex = 59;
               this->button57->UseVisualStyleBackColor = false;
               this->button57->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button57->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button57->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button57->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button58
               // 
               this->button58->BackColor = System::Drawing::SystemColors::Menu;
               this->button58->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button58->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button58->Location = System::Drawing::Point(254, 470);
               this->button58->Margin = System::Windows::Forms::Padding(4);
               this->button58->Name = L"button58";
               this->button58->Size = System::Drawing::Size(62, 62);
               this->button58->TabIndex = 60;
               this->button58->UseVisualStyleBackColor = false;
               this->button58->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button58->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button58->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button58->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button59
               // 
               this->button59->BackColor = System::Drawing::SystemColors::Menu;
               this->button59->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button59->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button59->Location = System::Drawing::Point(320, 470);
               this->button59->Margin = System::Windows::Forms::Padding(4);
               this->button59->Name = L"button59";
               this->button59->Size = System::Drawing::Size(62, 62);
               this->button59->TabIndex = 61;
               this->button59->UseVisualStyleBackColor = false;
               this->button59->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button59->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button59->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button59->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button60
               // 
               this->button60->BackColor = System::Drawing::SystemColors::Menu;
               this->button60->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button60->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button60->Location = System::Drawing::Point(386, 470);
               this->button60->Margin = System::Windows::Forms::Padding(4);
               this->button60->Name = L"button60";
               this->button60->Size = System::Drawing::Size(62, 62);
               this->button60->TabIndex = 62;
               this->button60->UseVisualStyleBackColor = false;
               this->button60->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button60->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button60->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button60->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button61
               // 
               this->button61->BackColor = System::Drawing::SystemColors::Menu;
               this->button61->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button61->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button61->Location = System::Drawing::Point(460, 470);
               this->button61->Margin = System::Windows::Forms::Padding(4);
               this->button61->Name = L"button61";
               this->button61->Size = System::Drawing::Size(62, 62);
               this->button61->TabIndex = 63;
               this->button61->UseVisualStyleBackColor = false;
               this->button61->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button61->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button61->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button61->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button62
               // 
               this->button62->BackColor = System::Drawing::SystemColors::Menu;
               this->button62->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button62->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button62->Location = System::Drawing::Point(526, 470);
               this->button62->Margin = System::Windows::Forms::Padding(4);
               this->button62->Name = L"button62";
               this->button62->Size = System::Drawing::Size(62, 62);
               this->button62->TabIndex = 64;
               this->button62->UseVisualStyleBackColor = false;
               this->button62->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button62->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button62->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button62->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button63
               // 
               this->button63->BackColor = System::Drawing::SystemColors::Menu;
               this->button63->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button63->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button63->Location = System::Drawing::Point(592, 470);
               this->button63->Margin = System::Windows::Forms::Padding(4);
               this->button63->Name = L"button63";
               this->button63->Size = System::Drawing::Size(62, 62);
               this->button63->TabIndex = 65;
               this->button63->UseVisualStyleBackColor = false;
               this->button63->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button63->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button63->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button63->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button64
               // 
               this->button64->BackColor = System::Drawing::SystemColors::Menu;
               this->button64->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button64->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button64->Location = System::Drawing::Point(48, 536);
               this->button64->Margin = System::Windows::Forms::Padding(4);
               this->button64->Name = L"button64";
               this->button64->Size = System::Drawing::Size(62, 62);
               this->button64->TabIndex = 66;
               this->button64->UseVisualStyleBackColor = false;
               this->button64->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button64->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button64->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button64->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button65
               // 
               this->button65->BackColor = System::Drawing::SystemColors::Menu;
               this->button65->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button65->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button65->Location = System::Drawing::Point(114, 536);
               this->button65->Margin = System::Windows::Forms::Padding(4);
               this->button65->Name = L"button65";
               this->button65->Size = System::Drawing::Size(62, 62);
               this->button65->TabIndex = 67;
               this->button65->UseVisualStyleBackColor = false;
               this->button65->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button65->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button65->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button65->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button66
               // 
               this->button66->BackColor = System::Drawing::SystemColors::Menu;
               this->button66->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button66->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button66->Location = System::Drawing::Point(180, 536);
               this->button66->Margin = System::Windows::Forms::Padding(4);
               this->button66->Name = L"button66";
               this->button66->Size = System::Drawing::Size(62, 62);
               this->button66->TabIndex = 68;
               this->button66->UseVisualStyleBackColor = false;
               this->button66->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button66->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button66->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button66->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button67
               // 
               this->button67->BackColor = System::Drawing::SystemColors::Menu;
               this->button67->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button67->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button67->Location = System::Drawing::Point(254, 536);
               this->button67->Margin = System::Windows::Forms::Padding(4);
               this->button67->Name = L"button67";
               this->button67->Size = System::Drawing::Size(62, 62);
               this->button67->TabIndex = 69;
               this->button67->UseVisualStyleBackColor = false;
               this->button67->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button67->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button67->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button67->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button68
               // 
               this->button68->BackColor = System::Drawing::SystemColors::Menu;
               this->button68->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button68->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button68->Location = System::Drawing::Point(320, 536);
               this->button68->Margin = System::Windows::Forms::Padding(4);
               this->button68->Name = L"button68";
               this->button68->Size = System::Drawing::Size(62, 62);
               this->button68->TabIndex = 70;
               this->button68->UseVisualStyleBackColor = false;
               this->button68->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button68->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button68->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button68->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button69
               // 
               this->button69->BackColor = System::Drawing::SystemColors::Menu;
               this->button69->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button69->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button69->Location = System::Drawing::Point(386, 536);
               this->button69->Margin = System::Windows::Forms::Padding(4);
               this->button69->Name = L"button69";
               this->button69->Size = System::Drawing::Size(62, 62);
               this->button69->TabIndex = 71;
               this->button69->UseVisualStyleBackColor = false;
               this->button69->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button69->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button69->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button69->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button70
               // 
               this->button70->BackColor = System::Drawing::SystemColors::Menu;
               this->button70->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button70->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button70->Location = System::Drawing::Point(460, 536);
               this->button70->Margin = System::Windows::Forms::Padding(4);
               this->button70->Name = L"button70";
               this->button70->Size = System::Drawing::Size(62, 62);
               this->button70->TabIndex = 72;
               this->button70->UseVisualStyleBackColor = false;
               this->button70->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button70->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button70->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button70->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button71
               // 
               this->button71->BackColor = System::Drawing::SystemColors::Menu;
               this->button71->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button71->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button71->Location = System::Drawing::Point(526, 536);
               this->button71->Margin = System::Windows::Forms::Padding(4);
               this->button71->Name = L"button71";
               this->button71->Size = System::Drawing::Size(62, 62);
               this->button71->TabIndex = 73;
               this->button71->UseVisualStyleBackColor = false;
               this->button71->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button71->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button71->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button71->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button72
               // 
               this->button72->BackColor = System::Drawing::SystemColors::Menu;
               this->button72->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button72->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button72->Location = System::Drawing::Point(592, 536);
               this->button72->Margin = System::Windows::Forms::Padding(4);
               this->button72->Name = L"button72";
               this->button72->Size = System::Drawing::Size(62, 62);
               this->button72->TabIndex = 74;
               this->button72->UseVisualStyleBackColor = false;
               this->button72->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button72->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button72->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button72->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button73
               // 
               this->button73->BackColor = System::Drawing::SystemColors::Menu;
               this->button73->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button73->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button73->Location = System::Drawing::Point(48, 602);
               this->button73->Margin = System::Windows::Forms::Padding(4);
               this->button73->Name = L"button73";
               this->button73->Size = System::Drawing::Size(62, 62);
               this->button73->TabIndex = 75;
               this->button73->UseVisualStyleBackColor = false;
               this->button73->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button73->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button73->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button73->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button74
               // 
               this->button74->BackColor = System::Drawing::SystemColors::Menu;
               this->button74->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button74->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button74->Location = System::Drawing::Point(114, 602);
               this->button74->Margin = System::Windows::Forms::Padding(4);
               this->button74->Name = L"button74";
               this->button74->Size = System::Drawing::Size(62, 62);
               this->button74->TabIndex = 76;
               this->button74->UseVisualStyleBackColor = false;
               this->button74->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button74->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button74->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button74->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button75
               // 
               this->button75->BackColor = System::Drawing::SystemColors::Menu;
               this->button75->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button75->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button75->Location = System::Drawing::Point(180, 602);
               this->button75->Margin = System::Windows::Forms::Padding(4);
               this->button75->Name = L"button75";
               this->button75->Size = System::Drawing::Size(62, 62);
               this->button75->TabIndex = 77;
               this->button75->UseVisualStyleBackColor = false;
               this->button75->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button75->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button75->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button75->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button76
               // 
               this->button76->BackColor = System::Drawing::SystemColors::Menu;
               this->button76->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button76->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button76->Location = System::Drawing::Point(254, 602);
               this->button76->Margin = System::Windows::Forms::Padding(4);
               this->button76->Name = L"button76";
               this->button76->Size = System::Drawing::Size(62, 62);
               this->button76->TabIndex = 78;
               this->button76->UseVisualStyleBackColor = false;
               this->button76->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button76->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button76->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button76->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button77
               // 
               this->button77->BackColor = System::Drawing::SystemColors::Menu;
               this->button77->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button77->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button77->Location = System::Drawing::Point(320, 602);
               this->button77->Margin = System::Windows::Forms::Padding(4);
               this->button77->Name = L"button77";
               this->button77->Size = System::Drawing::Size(62, 62);
               this->button77->TabIndex = 79;
               this->button77->UseVisualStyleBackColor = false;
               this->button77->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button77->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button77->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button77->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button78
               // 
               this->button78->BackColor = System::Drawing::SystemColors::Menu;
               this->button78->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button78->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button78->Location = System::Drawing::Point(386, 602);
               this->button78->Margin = System::Windows::Forms::Padding(4);
               this->button78->Name = L"button78";
               this->button78->Size = System::Drawing::Size(62, 62);
               this->button78->TabIndex = 80;
               this->button78->UseVisualStyleBackColor = false;
               this->button78->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button78->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button78->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button78->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button79
               // 
               this->button79->BackColor = System::Drawing::SystemColors::Menu;
               this->button79->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button79->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button79->Location = System::Drawing::Point(460, 602);
               this->button79->Margin = System::Windows::Forms::Padding(4);
               this->button79->Name = L"button79";
               this->button79->Size = System::Drawing::Size(62, 62);
               this->button79->TabIndex = 81;
               this->button79->UseVisualStyleBackColor = false;
               this->button79->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button79->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button79->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button79->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button80
               // 
               this->button80->BackColor = System::Drawing::SystemColors::Menu;
               this->button80->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button80->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button80->Location = System::Drawing::Point(526, 602);
               this->button80->Margin = System::Windows::Forms::Padding(4);
               this->button80->Name = L"button80";
               this->button80->Size = System::Drawing::Size(62, 62);
               this->button80->TabIndex = 82;
               this->button80->UseVisualStyleBackColor = false;
               this->button80->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button80->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button80->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button80->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // button81
               // 
               this->button81->BackColor = System::Drawing::SystemColors::Menu;
               this->button81->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->button81->Font = (gcnew System::Drawing::Font(L"Cambria", 26, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->button81->Location = System::Drawing::Point(592, 602);
               this->button81->Margin = System::Windows::Forms::Padding(4);
               this->button81->Name = L"button81";
               this->button81->Size = System::Drawing::Size(62, 62);
               this->button81->TabIndex = 83;
               this->button81->UseVisualStyleBackColor = false;
               this->button81->Click += gcnew System::EventHandler(this, &SudokuForm::cell_Click);
               this->button81->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SudokuForm::buttonKeyDown);
               this->button81->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
               this->button81->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SudokuForm::buttonPreviewKeyDown);
               // 
               // buttonMinimize
               // 
               this->buttonMinimize->FlatAppearance->BorderSize = 0;
               this->buttonMinimize->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->buttonMinimize->Font = (gcnew System::Drawing::Font(L"Calibri", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->buttonMinimize->Location = System::Drawing::Point(890, 0);
               this->buttonMinimize->Margin = System::Windows::Forms::Padding(0);
               this->buttonMinimize->Name = L"buttonMinimize";
               this->buttonMinimize->Size = System::Drawing::Size(50, 50);
               this->buttonMinimize->TabIndex = 84;
               this->buttonMinimize->TabStop = false;
               this->buttonMinimize->Text = L"—";
               this->buttonMinimize->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
               this->buttonMinimize->UseVisualStyleBackColor = true;
               this->buttonMinimize->Click += gcnew System::EventHandler(this, &SudokuForm::buttonMinimize_Click);
               // 
               // buttonClose
               // 
               this->buttonClose->FlatAppearance->BorderSize = 0;
               this->buttonClose->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->buttonClose->Font = (gcnew System::Drawing::Font(L"Calibri", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->buttonClose->Location = System::Drawing::Point(940, 0);
               this->buttonClose->Margin = System::Windows::Forms::Padding(0);
               this->buttonClose->Name = L"buttonClose";
               this->buttonClose->Size = System::Drawing::Size(50, 50);
               this->buttonClose->TabIndex = 85;
               this->buttonClose->TabStop = false;
               this->buttonClose->Text = L"✕";
               this->buttonClose->UseVisualStyleBackColor = true;
               this->buttonClose->Click += gcnew System::EventHandler(this, &SudokuForm::buttonClose_Click);
               // 
               // timerLabel
               // 
               this->timerLabel->BackColor = System::Drawing::SystemColors::Menu;
               this->timerLabel->Font = (gcnew System::Drawing::Font(L"Calibri", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->timerLabel->Location = System::Drawing::Point(701, 54);
               this->timerLabel->Name = L"timerLabel";
               this->timerLabel->Size = System::Drawing::Size(240, 49);
               this->timerLabel->TabIndex = 84;
               this->timerLabel->Text = L"0:00";
               this->timerLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
               this->timerLabel->Click += gcnew System::EventHandler(this, &SudokuForm::timerLabel_Click);
               this->timerLabel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SudokuForm::timerLabel_MouseDown);
               this->timerLabel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &SudokuForm::timerLabel_MouseMove);
               this->timerLabel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &SudokuForm::timerLabel_MouseUp);
               // 
               // clockTimer
               // 
               this->clockTimer->Enabled = true;
               this->clockTimer->Interval = 250;
               this->clockTimer->Tick += gcnew System::EventHandler(this, &SudokuForm::clockTimer_Tick);
               // 
               // difficultyComboBox
               // 
               this->difficultyComboBox->BackColor = System::Drawing::SystemColors::Menu;
               this->difficultyComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
               this->difficultyComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->difficultyComboBox->Font = (gcnew System::Drawing::Font(L"Calibri", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->difficultyComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
                   L"Very Easy", L"Easy", L"Medium", L"Hard",
                       L"Very Hard"
               });
               this->difficultyComboBox->Location = System::Drawing::Point(701, 111);
               this->difficultyComboBox->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->difficultyComboBox->Name = L"difficultyComboBox";
               this->difficultyComboBox->Size = System::Drawing::Size(240, 43);
               this->difficultyComboBox->TabIndex = 86;
               this->difficultyComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &SudokuForm::difficultyComboBox_SelectedIndexChanged);
               this->difficultyComboBox->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SudokuForm::difficultyComboBox_MouseDown);
               // 
               // newGameButton
               // 
               this->newGameButton->BackColor = System::Drawing::SystemColors::Menu;
               this->newGameButton->FlatAppearance->BorderSize = 0;
               this->newGameButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->newGameButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->newGameButton->Location = System::Drawing::Point(701, 162);
               this->newGameButton->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->newGameButton->Name = L"newGameButton";
               this->newGameButton->Size = System::Drawing::Size(240, 43);
               this->newGameButton->TabIndex = 87;
               this->newGameButton->Text = L"New Game";
               this->newGameButton->UseVisualStyleBackColor = false;
               this->newGameButton->Click += gcnew System::EventHandler(this, &SudokuForm::newGameButton_Click);
               // 
               // restartButton
               // 
               this->restartButton->BackColor = System::Drawing::SystemColors::Menu;
               this->restartButton->FlatAppearance->BorderSize = 0;
               this->restartButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->restartButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->restartButton->Location = System::Drawing::Point(701, 213);
               this->restartButton->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->restartButton->Name = L"restartButton";
               this->restartButton->Size = System::Drawing::Size(240, 43);
               this->restartButton->TabIndex = 88;
               this->restartButton->Text = L"Restart";
               this->restartButton->UseVisualStyleBackColor = false;
               this->restartButton->Click += gcnew System::EventHandler(this, &SudokuForm::restartButton_Click);
               // 
               // hintButton
               // 
               this->hintButton->BackColor = System::Drawing::SystemColors::Menu;
               this->hintButton->FlatAppearance->BorderSize = 0;
               this->hintButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->hintButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->hintButton->Location = System::Drawing::Point(701, 315);
               this->hintButton->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->hintButton->Name = L"hintButton";
               this->hintButton->Size = System::Drawing::Size(240, 43);
               this->hintButton->TabIndex = 90;
               this->hintButton->Text = L"Hint";
               this->hintButton->UseVisualStyleBackColor = false;
               this->hintButton->Click += gcnew System::EventHandler(this, &SudokuForm::hintButton_Click);
               // 
               // fixButton
               // 
               this->fixButton->BackColor = System::Drawing::SystemColors::Menu;
               this->fixButton->FlatAppearance->BorderSize = 0;
               this->fixButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->fixButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->fixButton->Location = System::Drawing::Point(701, 366);
               this->fixButton->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->fixButton->Name = L"fixButton";
               this->fixButton->Size = System::Drawing::Size(240, 43);
               this->fixButton->TabIndex = 91;
               this->fixButton->Text = L"Fix";
               this->fixButton->UseVisualStyleBackColor = false;
               this->fixButton->Click += gcnew System::EventHandler(this, &SudokuForm::fixButton_Click);
               // 
               // giveUpButton
               // 
               this->giveUpButton->BackColor = System::Drawing::SystemColors::Menu;
               this->giveUpButton->FlatAppearance->BorderSize = 0;
               this->giveUpButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->giveUpButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->giveUpButton->Location = System::Drawing::Point(701, 417);
               this->giveUpButton->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->giveUpButton->Name = L"giveUpButton";
               this->giveUpButton->Size = System::Drawing::Size(240, 43);
               this->giveUpButton->TabIndex = 92;
               this->giveUpButton->Text = L"Give Up";
               this->giveUpButton->UseVisualStyleBackColor = false;
               this->giveUpButton->Click += gcnew System::EventHandler(this, &SudokuForm::giveUpButton_Click);
               // 
               // customPuzzleButton
               // 
               this->customPuzzleButton->BackColor = System::Drawing::SystemColors::Menu;
               this->customPuzzleButton->FlatAppearance->BorderSize = 0;
               this->customPuzzleButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->customPuzzleButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->customPuzzleButton->Location = System::Drawing::Point(701, 519);
               this->customPuzzleButton->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->customPuzzleButton->Name = L"customPuzzleButton";
               this->customPuzzleButton->Size = System::Drawing::Size(240, 43);
               this->customPuzzleButton->TabIndex = 94;
               this->customPuzzleButton->Text = L"Enter Puzzle";
               this->customPuzzleButton->UseVisualStyleBackColor = false;
               this->customPuzzleButton->Click += gcnew System::EventHandler(this, &SudokuForm::customPuzzleButton_Click);
               // 
               // solveButton
               // 
               this->solveButton->BackColor = System::Drawing::SystemColors::Menu;
               this->solveButton->FlatAppearance->BorderSize = 0;
               this->solveButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->solveButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->solveButton->Location = System::Drawing::Point(701, 570);
               this->solveButton->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->solveButton->Name = L"solveButton";
               this->solveButton->Size = System::Drawing::Size(240, 43);
               this->solveButton->TabIndex = 95;
               this->solveButton->Text = L"Solve Puzzle";
               this->solveButton->UseVisualStyleBackColor = false;
               this->solveButton->Click += gcnew System::EventHandler(this, &SudokuForm::solveButton_Click);
               // 
               // undoButton
               // 
               this->undoButton->BackColor = System::Drawing::SystemColors::Menu;
               this->undoButton->FlatAppearance->BorderSize = 0;
               this->undoButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->undoButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->undoButton->Location = System::Drawing::Point(701, 468);
               this->undoButton->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->undoButton->Name = L"undoButton";
               this->undoButton->Size = System::Drawing::Size(240, 43);
               this->undoButton->TabIndex = 93;
               this->undoButton->Text = L"Undo";
               this->undoButton->UseVisualStyleBackColor = false;
               this->undoButton->Click += gcnew System::EventHandler(this, &SudokuForm::undoButton_Click);
               // 
               // pencilButton
               // 
               this->pencilButton->BackColor = System::Drawing::SystemColors::Menu;
               this->pencilButton->FlatAppearance->BorderSize = 0;
               this->pencilButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->pencilButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->pencilButton->Location = System::Drawing::Point(701, 264);
               this->pencilButton->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->pencilButton->Name = L"pencilButton";
               this->pencilButton->Size = System::Drawing::Size(240, 43);
               this->pencilButton->TabIndex = 89;
               this->pencilButton->Text = L"Pencil";
               this->pencilButton->UseVisualStyleBackColor = false;
               this->pencilButton->Click += gcnew System::EventHandler(this, &SudokuForm::pencilButton_Click);
               // 
               // saveGameDialog
               // 
               this->saveGameDialog->DefaultExt = L"sdk3";
               this->saveGameDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &SudokuForm::saveGameDialog_FileOk);
               // 
               // openGameDialog
               // 
               this->openGameDialog->DefaultExt = L"sdk3";
               this->openGameDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &SudokuForm::openGameDialog_FileOk);
               // 
               // menuStrip
               // 
               this->menuStrip->AccessibleRole = System::Windows::Forms::AccessibleRole::MenuBar;
               this->menuStrip->AllowMerge = false;
               this->menuStrip->BackColor = System::Drawing::SystemColors::ButtonFace;
               this->menuStrip->GripMargin = System::Windows::Forms::Padding(2, 2, 0, 2);
               this->menuStrip->ImageScalingSize = System::Drawing::Size(24, 24);
               this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
                   this->fileToolStripMenuItem,
                       this->gameToolStripMenuItem, this->optionsToolStripMenuItem, this->helpToolStripMenuItem
               });
               this->menuStrip->Location = System::Drawing::Point(0, 0);
               this->menuStrip->Name = L"menuStrip";
               this->menuStrip->Size = System::Drawing::Size(990, 36);
               this->menuStrip->TabIndex = 0;
               this->menuStrip->Text = L"menuStrip";
               this->menuStrip->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &SudokuForm::menuStrip_ItemClicked);
               this->menuStrip->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SudokuForm::menuStrip_MouseDown);
               this->menuStrip->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &SudokuForm::menuStrip_MouseMove);
               this->menuStrip->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &SudokuForm::menuStrip_MouseUp);
               // 
               // fileToolStripMenuItem
               // 
               this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
                   this->saveToolStripMenuItem,
                       this->openToolStripMenuItem, this->toolStripSeparator1, this->minimizeToolStripMenuItem, this->exitToolStripMenuItem
               });
               this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
               this->fileToolStripMenuItem->Size = System::Drawing::Size(54, 32);
               this->fileToolStripMenuItem->Text = L"File";
               // 
               // saveToolStripMenuItem
               // 
               this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
               this->saveToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
               this->saveToolStripMenuItem->Size = System::Drawing::Size(252, 34);
               this->saveToolStripMenuItem->Text = L"Save";
               this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::saveToolStripMenuItem_Click);
               // 
               // openToolStripMenuItem
               // 
               this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
               this->openToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
               this->openToolStripMenuItem->Size = System::Drawing::Size(252, 34);
               this->openToolStripMenuItem->Text = L"Open";
               this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::openToolStripMenuItem_Click);
               // 
               // toolStripSeparator1
               // 
               this->toolStripSeparator1->Name = L"toolStripSeparator1";
               this->toolStripSeparator1->Size = System::Drawing::Size(249, 6);
               // 
               // minimizeToolStripMenuItem
               // 
               this->minimizeToolStripMenuItem->Name = L"minimizeToolStripMenuItem";
               this->minimizeToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::M));
               this->minimizeToolStripMenuItem->Size = System::Drawing::Size(252, 34);
               this->minimizeToolStripMenuItem->Text = L"Minimize";
               this->minimizeToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::minimizeToolStripMenuItem_Click);
               // 
               // exitToolStripMenuItem
               // 
               this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
               this->exitToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Q));
               this->exitToolStripMenuItem->Size = System::Drawing::Size(252, 34);
               this->exitToolStripMenuItem->Text = L"Quit";
               this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::exitToolStripMenuItem_Click);
               // 
               // gameToolStripMenuItem
               // 
               this->gameToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(13) {
                   this->newGameToolStripMenuItem,
                       this->restartToolStripMenuItem, this->pencilToolStripMenuItem, this->hintToolStripMenuItem, this->fixToolStripMenuItem, this->giveUpToolStripMenuItem,
                       this->undoToolStripMenuItem, this->customPuzzleToolStripMenuItem, this->solveToolStripMenuItem, this->toolStripSeparator2, this->copyPuzzleToolStripMenuItem,
                       this->pastePuzzleToolStripMenuItem, this->copySolutionToolStripMenuItem
               });
               this->gameToolStripMenuItem->Name = L"gameToolStripMenuItem";
               this->gameToolStripMenuItem->Size = System::Drawing::Size(74, 32);
               this->gameToolStripMenuItem->Text = L"Game";
               // 
               // newGameToolStripMenuItem
               // 
               this->newGameToolStripMenuItem->Name = L"newGameToolStripMenuItem";
               this->newGameToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
               this->newGameToolStripMenuItem->Size = System::Drawing::Size(337, 34);
               this->newGameToolStripMenuItem->Text = L"New Game";
               this->newGameToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::newGameToolStripMenuItem_Click);
               // 
               // restartToolStripMenuItem
               // 
               this->restartToolStripMenuItem->Name = L"restartToolStripMenuItem";
               this->restartToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::R));
               this->restartToolStripMenuItem->Size = System::Drawing::Size(337, 34);
               this->restartToolStripMenuItem->Text = L"Restart";
               this->restartToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::restartToolStripMenuItem_Click);
               // 
               // pencilToolStripMenuItem
               // 
               this->pencilToolStripMenuItem->Name = L"pencilToolStripMenuItem";
               this->pencilToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::P));
               this->pencilToolStripMenuItem->Size = System::Drawing::Size(337, 34);
               this->pencilToolStripMenuItem->Text = L"Pencil";
               this->pencilToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::pencilToolStripMenuItem_Click);
               // 
               // hintToolStripMenuItem
               // 
               this->hintToolStripMenuItem->Name = L"hintToolStripMenuItem";
               this->hintToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::H));
               this->hintToolStripMenuItem->Size = System::Drawing::Size(337, 34);
               this->hintToolStripMenuItem->Text = L"Hint";
               this->hintToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::hintToolStripMenuItem_Click);
               // 
               // fixToolStripMenuItem
               // 
               this->fixToolStripMenuItem->Name = L"fixToolStripMenuItem";
               this->fixToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::F));
               this->fixToolStripMenuItem->Size = System::Drawing::Size(337, 34);
               this->fixToolStripMenuItem->Text = L"Fix";
               this->fixToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::fixToolStripMenuItem_Click);
               // 
               // giveUpToolStripMenuItem
               // 
               this->giveUpToolStripMenuItem->Name = L"giveUpToolStripMenuItem";
               this->giveUpToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::G));
               this->giveUpToolStripMenuItem->Size = System::Drawing::Size(337, 34);
               this->giveUpToolStripMenuItem->Text = L"Give Up";
               this->giveUpToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::giveUpToolStripMenuItem_Click);
               // 
               // undoToolStripMenuItem
               // 
               this->undoToolStripMenuItem->Name = L"undoToolStripMenuItem";
               this->undoToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Z));
               this->undoToolStripMenuItem->Size = System::Drawing::Size(337, 34);
               this->undoToolStripMenuItem->Text = L"Undo";
               this->undoToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::undoToolStripMenuItem_Click);
               // 
               // customPuzzleToolStripMenuItem
               // 
               this->customPuzzleToolStripMenuItem->Name = L"customPuzzleToolStripMenuItem";
               this->customPuzzleToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::E));
               this->customPuzzleToolStripMenuItem->Size = System::Drawing::Size(337, 34);
               this->customPuzzleToolStripMenuItem->Text = L"Enter Puzzle";
               this->customPuzzleToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::customPuzzleToolStripMenuItem_Click);
               // 
               // solveToolStripMenuItem
               // 
               this->solveToolStripMenuItem->Name = L"solveToolStripMenuItem";
               this->solveToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::L));
               this->solveToolStripMenuItem->Size = System::Drawing::Size(337, 34);
               this->solveToolStripMenuItem->Text = L"Solve";
               this->solveToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::solveToolStripMenuItem_Click);
               // 
               // toolStripSeparator2
               // 
               this->toolStripSeparator2->Name = L"toolStripSeparator2";
               this->toolStripSeparator2->Size = System::Drawing::Size(334, 6);
               // 
               // copyPuzzleToolStripMenuItem
               // 
               this->copyPuzzleToolStripMenuItem->Enabled = false;
               this->copyPuzzleToolStripMenuItem->Name = L"copyPuzzleToolStripMenuItem";
               this->copyPuzzleToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::C));
               this->copyPuzzleToolStripMenuItem->Size = System::Drawing::Size(337, 34);
               this->copyPuzzleToolStripMenuItem->Text = L"Copy Puzzle";
               this->copyPuzzleToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::copyPuzzleToolStripMenuItem_Click);
               // 
               // pastePuzzleToolStripMenuItem
               // 
               this->pastePuzzleToolStripMenuItem->Enabled = false;
               this->pastePuzzleToolStripMenuItem->Name = L"pastePuzzleToolStripMenuItem";
               this->pastePuzzleToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::V));
               this->pastePuzzleToolStripMenuItem->Size = System::Drawing::Size(337, 34);
               this->pastePuzzleToolStripMenuItem->Text = L"Paste Puzzle";
               this->pastePuzzleToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::pastePuzzleToolStripMenuItem_Click);
               // 
               // copySolutionToolStripMenuItem
               // 
               this->copySolutionToolStripMenuItem->Enabled = false;
               this->copySolutionToolStripMenuItem->Name = L"copySolutionToolStripMenuItem";
               this->copySolutionToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift)
                   | System::Windows::Forms::Keys::C));
               this->copySolutionToolStripMenuItem->Size = System::Drawing::Size(337, 34);
               this->copySolutionToolStripMenuItem->Text = L"Copy Solution";
               this->copySolutionToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::copySolutionToolStripMenuItem_Click);
               // 
               // optionsToolStripMenuItem
               // 
               this->optionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
                   this->languageToolStripMenuItem,
                       this->difficultyToolStripMenuItem, this->candidatesToolStripMenuItem
               });
               this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
               this->optionsToolStripMenuItem->Size = System::Drawing::Size(92, 32);
               this->optionsToolStripMenuItem->Text = L"Options";
               // 
               // languageToolStripMenuItem
               // 
               this->languageToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
                   this->englishToolStripMenuItem,
                       this->ukrainianToolStripMenuItem
               });
               this->languageToolStripMenuItem->Name = L"languageToolStripMenuItem";
               this->languageToolStripMenuItem->Size = System::Drawing::Size(202, 34);
               this->languageToolStripMenuItem->Text = L"Language";
               // 
               // englishToolStripMenuItem
               // 
               this->englishToolStripMenuItem->Name = L"englishToolStripMenuItem";
               this->englishToolStripMenuItem->Size = System::Drawing::Size(202, 34);
               this->englishToolStripMenuItem->Text = L"English";
               this->englishToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::englishToolStripMenuItem_Click);
               // 
               // ukrainianToolStripMenuItem
               // 
               this->ukrainianToolStripMenuItem->Name = L"ukrainianToolStripMenuItem";
               this->ukrainianToolStripMenuItem->Size = System::Drawing::Size(202, 34);
               this->ukrainianToolStripMenuItem->Text = L"Українська";
               this->ukrainianToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::ukrainianToolStripMenuItem_Click);
               // 
               // difficultyToolStripMenuItem
               // 
               this->difficultyToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
                   this->veryEasyToolStripMenuItem,
                       this->easyToolStripMenuItem, this->mediumToolStripMenuItem, this->hardToolStripMenuItem, this->veryHardToolStripMenuItem
               });
               this->difficultyToolStripMenuItem->Name = L"difficultyToolStripMenuItem";
               this->difficultyToolStripMenuItem->Size = System::Drawing::Size(202, 34);
               this->difficultyToolStripMenuItem->Text = L"Difficulty";
               // 
               // veryEasyToolStripMenuItem
               // 
               this->veryEasyToolStripMenuItem->Name = L"veryEasyToolStripMenuItem";
               this->veryEasyToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D1));
               this->veryEasyToolStripMenuItem->Size = System::Drawing::Size(253, 34);
               this->veryEasyToolStripMenuItem->Text = L"Very Easy";
               this->veryEasyToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::veryEasyToolStripMenuItem_Click);
               // 
               // easyToolStripMenuItem
               // 
               this->easyToolStripMenuItem->Name = L"easyToolStripMenuItem";
               this->easyToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D2));
               this->easyToolStripMenuItem->Size = System::Drawing::Size(253, 34);
               this->easyToolStripMenuItem->Text = L"Easy";
               this->easyToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::easyToolStripMenuItem_Click);
               // 
               // mediumToolStripMenuItem
               // 
               this->mediumToolStripMenuItem->Name = L"mediumToolStripMenuItem";
               this->mediumToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D3));
               this->mediumToolStripMenuItem->Size = System::Drawing::Size(253, 34);
               this->mediumToolStripMenuItem->Text = L"Medium";
               this->mediumToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::mediumToolStripMenuItem_Click);
               // 
               // hardToolStripMenuItem
               // 
               this->hardToolStripMenuItem->Name = L"hardToolStripMenuItem";
               this->hardToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D4));
               this->hardToolStripMenuItem->Size = System::Drawing::Size(253, 34);
               this->hardToolStripMenuItem->Text = L"Hard";
               this->hardToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::hardToolStripMenuItem_Click);
               // 
               // veryHardToolStripMenuItem
               // 
               this->veryHardToolStripMenuItem->Name = L"veryHardToolStripMenuItem";
               this->veryHardToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D5));
               this->veryHardToolStripMenuItem->Size = System::Drawing::Size(253, 34);
               this->veryHardToolStripMenuItem->Text = L"Very Hard";
               this->veryHardToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::veryHardToolStripMenuItem_Click);
               // 
               // candidatesToolStripMenuItem
               // 
               this->candidatesToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
                   this->candidatesNoneToolStripMenuItem,
                       this->candidatesCurrentCellToolStripMenuItem, this->candidatesAllCellsToolStripMenuItem
               });
               this->candidatesToolStripMenuItem->Name = L"candidatesToolStripMenuItem";
               this->candidatesToolStripMenuItem->Size = System::Drawing::Size(202, 34);
               this->candidatesToolStripMenuItem->Text = L"Candidates";
               // 
               // candidatesNoneToolStripMenuItem
               // 
               this->candidatesNoneToolStripMenuItem->Name = L"candidatesNoneToolStripMenuItem";
               this->candidatesNoneToolStripMenuItem->Size = System::Drawing::Size(202, 34);
               this->candidatesNoneToolStripMenuItem->Text = L"None";
               this->candidatesNoneToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::candidatesNoneToolStripMenuItem_Click);
               // 
               // candidatesCurrentCellToolStripMenuItem
               // 
               this->candidatesCurrentCellToolStripMenuItem->Name = L"candidatesCurrentCellToolStripMenuItem";
               this->candidatesCurrentCellToolStripMenuItem->Size = System::Drawing::Size(202, 34);
               this->candidatesCurrentCellToolStripMenuItem->Text = L"Current cell";
               this->candidatesCurrentCellToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::candidatesCurrentCellToolStripMenuItem_Click);
               // 
               // candidatesAllCellsToolStripMenuItem
               // 
               this->candidatesAllCellsToolStripMenuItem->Name = L"candidatesAllCellsToolStripMenuItem";
               this->candidatesAllCellsToolStripMenuItem->Size = System::Drawing::Size(202, 34);
               this->candidatesAllCellsToolStripMenuItem->Text = L"All cells";
               this->candidatesAllCellsToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::candidatesAllCellsToolStripMenuItem_Click);
               // 
               // helpToolStripMenuItem
               // 
               this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
                   this->aboutToolStripMenuItem,
                       this->rulesToolStripMenuItem, this->featuresToolStripMenuItem, this->hintsAndTipsToolStripMenuItem, this->keyboardToolStripMenuItem
               });
               this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
               this->helpToolStripMenuItem->Size = System::Drawing::Size(65, 32);
               this->helpToolStripMenuItem->Text = L"Help";
               // 
               // aboutToolStripMenuItem
               // 
               this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
               this->aboutToolStripMenuItem->ShowShortcutKeys = false;
               this->aboutToolStripMenuItem->Size = System::Drawing::Size(218, 34);
               this->aboutToolStripMenuItem->Text = L"About";
               this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::aboutToolStripMenuItem_Click);
               // 
               // rulesToolStripMenuItem
               // 
               this->rulesToolStripMenuItem->Name = L"rulesToolStripMenuItem";
               this->rulesToolStripMenuItem->ShowShortcutKeys = false;
               this->rulesToolStripMenuItem->Size = System::Drawing::Size(218, 34);
               this->rulesToolStripMenuItem->Text = L"Rules";
               this->rulesToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::rulesToolStripMenuItem_Click);
               // 
               // featuresToolStripMenuItem
               // 
               this->featuresToolStripMenuItem->Name = L"featuresToolStripMenuItem";
               this->featuresToolStripMenuItem->ShowShortcutKeys = false;
               this->featuresToolStripMenuItem->Size = System::Drawing::Size(218, 34);
               this->featuresToolStripMenuItem->Text = L"Features";
               this->featuresToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::featuresToolStripMenuItem_Click);
               // 
               // hintsAndTipsToolStripMenuItem
               // 
               this->hintsAndTipsToolStripMenuItem->Name = L"hintsAndTipsToolStripMenuItem";
               this->hintsAndTipsToolStripMenuItem->ShowShortcutKeys = false;
               this->hintsAndTipsToolStripMenuItem->Size = System::Drawing::Size(218, 34);
               this->hintsAndTipsToolStripMenuItem->Text = L"Hints And Tips";
               this->hintsAndTipsToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::hintsAndTipsToolStripMenuItem_Click);
               // 
               // keyboardToolStripMenuItem
               // 
               this->keyboardToolStripMenuItem->Name = L"keyboardToolStripMenuItem";
               this->keyboardToolStripMenuItem->ShowShortcutKeys = false;
               this->keyboardToolStripMenuItem->Size = System::Drawing::Size(218, 34);
               this->keyboardToolStripMenuItem->Text = L"Keyboard";
               this->keyboardToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::keyboardToolStripMenuItem_Click);
               // 
               // clipboardButton
               // 
               this->clipboardButton->BackColor = System::Drawing::SystemColors::Menu;
               this->clipboardButton->Enabled = false;
               this->clipboardButton->FlatAppearance->BorderSize = 0;
               this->clipboardButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->clipboardButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->clipboardButton->Location = System::Drawing::Point(701, 621);
               this->clipboardButton->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->clipboardButton->Name = L"clipboardButton";
               this->clipboardButton->Size = System::Drawing::Size(240, 43);
               this->clipboardButton->TabIndex = 96;
               this->clipboardButton->Text = L"Copy Puzzle";
               this->clipboardButton->UseVisualStyleBackColor = false;
               this->clipboardButton->Click += gcnew System::EventHandler(this, &SudokuForm::clipboardButton_Click);
               // 
               // SudokuForm
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->AutoValidate = System::Windows::Forms::AutoValidate::EnablePreventFocusChange;
               this->BackColor = System::Drawing::SystemColors::Menu;
               this->ClientSize = System::Drawing::Size(990, 700);
               this->Controls->Add(this->clipboardButton);
               this->Controls->Add(this->pencilButton);
               this->Controls->Add(this->undoButton);
               this->Controls->Add(this->solveButton);
               this->Controls->Add(this->customPuzzleButton);
               this->Controls->Add(this->giveUpButton);
               this->Controls->Add(this->fixButton);
               this->Controls->Add(this->hintButton);
               this->Controls->Add(this->restartButton);
               this->Controls->Add(this->newGameButton);
               this->Controls->Add(this->difficultyComboBox);
               this->Controls->Add(this->timerLabel);
               this->Controls->Add(this->buttonClose);
               this->Controls->Add(this->buttonMinimize);
               this->Controls->Add(this->button81);
               this->Controls->Add(this->button80);
               this->Controls->Add(this->button79);
               this->Controls->Add(this->button78);
               this->Controls->Add(this->button77);
               this->Controls->Add(this->button76);
               this->Controls->Add(this->button75);
               this->Controls->Add(this->button74);
               this->Controls->Add(this->button73);
               this->Controls->Add(this->button72);
               this->Controls->Add(this->button71);
               this->Controls->Add(this->button70);
               this->Controls->Add(this->button69);
               this->Controls->Add(this->button68);
               this->Controls->Add(this->button67);
               this->Controls->Add(this->button66);
               this->Controls->Add(this->button65);
               this->Controls->Add(this->button64);
               this->Controls->Add(this->button63);
               this->Controls->Add(this->button62);
               this->Controls->Add(this->button61);
               this->Controls->Add(this->button60);
               this->Controls->Add(this->button59);
               this->Controls->Add(this->button58);
               this->Controls->Add(this->button57);
               this->Controls->Add(this->button56);
               this->Controls->Add(this->button55);
               this->Controls->Add(this->button54);
               this->Controls->Add(this->button53);
               this->Controls->Add(this->button52);
               this->Controls->Add(this->button51);
               this->Controls->Add(this->button50);
               this->Controls->Add(this->button49);
               this->Controls->Add(this->button48);
               this->Controls->Add(this->button47);
               this->Controls->Add(this->button46);
               this->Controls->Add(this->button45);
               this->Controls->Add(this->button44);
               this->Controls->Add(this->button43);
               this->Controls->Add(this->button42);
               this->Controls->Add(this->button41);
               this->Controls->Add(this->button40);
               this->Controls->Add(this->button39);
               this->Controls->Add(this->button38);
               this->Controls->Add(this->button37);
               this->Controls->Add(this->button34);
               this->Controls->Add(this->button35);
               this->Controls->Add(this->button36);
               this->Controls->Add(this->button31);
               this->Controls->Add(this->button32);
               this->Controls->Add(this->button33);
               this->Controls->Add(this->button30);
               this->Controls->Add(this->button29);
               this->Controls->Add(this->button28);
               this->Controls->Add(this->button27);
               this->Controls->Add(this->button26);
               this->Controls->Add(this->button25);
               this->Controls->Add(this->button24);
               this->Controls->Add(this->button23);
               this->Controls->Add(this->button22);
               this->Controls->Add(this->button21);
               this->Controls->Add(this->button20);
               this->Controls->Add(this->button19);
               this->Controls->Add(this->button18);
               this->Controls->Add(this->button17);
               this->Controls->Add(this->button16);
               this->Controls->Add(this->button15);
               this->Controls->Add(this->button14);
               this->Controls->Add(this->button13);
               this->Controls->Add(this->button12);
               this->Controls->Add(this->button11);
               this->Controls->Add(this->button10);
               this->Controls->Add(this->button9);
               this->Controls->Add(this->button8);
               this->Controls->Add(this->button7);
               this->Controls->Add(this->button6);
               this->Controls->Add(this->button5);
               this->Controls->Add(this->button4);
               this->Controls->Add(this->button3);
               this->Controls->Add(this->button2);
               this->Controls->Add(this->button1);
               this->Controls->Add(this->menuStrip);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
               this->MainMenuStrip = this->menuStrip;
               this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->MaximizeBox = false;
               this->MaximumSize = System::Drawing::Size(990, 700);
               this->MinimumSize = System::Drawing::Size(990, 700);
               this->Name = L"SudokuForm";
               this->ShowIcon = false;
               this->Text = L"Sudoku 3.0";
               this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SudokuForm::SudokuForm_MouseDown);
               this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &SudokuForm::SudokuForm_MouseMove);
               this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &SudokuForm::SudokuForm_MouseUp);
               this->menuStrip->ResumeLayout(false);
               this->menuStrip->PerformLayout();
               this->ResumeLayout(false);
               this->PerformLayout();

           }

#pragma endregion

           // Show notification
    private: void showNotification(System::String^ message)
    {
        MessageBox::Show(message, Strings::Get(StringId::DialogTitleSudoku, this->currentLanguage), MessageBoxButtons::OK, MessageBoxIcon::None);
    }

    private: void setGameControls(bool gameActive, bool restartActive, bool solveActive)
    {
        this->restartButton->Enabled = restartActive;
        this->restartToolStripMenuItem->Enabled = restartActive;
        this->pencilButton->Enabled = gameActive;
        this->pencilToolStripMenuItem->Enabled = gameActive;
        this->hintButton->Enabled = gameActive;
        this->hintToolStripMenuItem->Enabled = gameActive;
        this->fixButton->Enabled = gameActive;
        this->fixToolStripMenuItem->Enabled = gameActive;
        this->giveUpButton->Enabled = gameActive;
        this->giveUpToolStripMenuItem->Enabled = gameActive;
        this->solveButton->Enabled = solveActive;
        this->solveToolStripMenuItem->Enabled = solveActive;
    }

    private: bool isGameFinished()
    {
        if (this->session->mode == GameMode::Game)   return !this->giveUpButton->Enabled;
        if (this->session->mode == GameMode::Solver) return !this->solveButton->Enabled;
        return false;
    }

    private: System::String^ difficultyName(unsigned int d)
    {
        switch (d)
        {
        case 0: return Strings::Get(StringId::DifficultyVeryEasy, this->currentLanguage);
        case 1: return Strings::Get(StringId::DifficultyEasy, this->currentLanguage);
        case 2: return Strings::Get(StringId::DifficultyMedium, this->currentLanguage);
        case 3: return Strings::Get(StringId::DifficultyHard, this->currentLanguage);
        case 4: return Strings::Get(StringId::DifficultyVeryHard, this->currentLanguage);
        default: return Strings::Get(StringId::DifficultyMedium, this->currentLanguage);
        }
    }

           // Initialize sudoku engine
    private: void initialize()
    {
        // Initialize engine
        this->engine = new SudokuGameEngine::SudokuEngine<>();

        // Initialize numbers form
        this->numbersForm = gcnew Sudoku_3_0::Numbers();
        this->numbersForm->Left = this->Left;
        this->numbersForm->Top = this->Top;
        this->numbersForm->setChoiceDelegate(gcnew choiceAction(this, &SudokuForm::choiceMade));
        // Show then immediately hide the form once at startup. This runs its full first
        // layout/show pass so AutoScaleMode applies DPI scaling and Width/Height reflect the
        // final on-screen size. cell_Click relies on those sizes to center the form
        // over a cell, so without this the very first popup would be mispositioned.
        // (CreateControl() alone only makes the handle and is not enough.)
        this->numbersForm->Visible = true;
        this->numbersForm->Visible = false;

        // Initialize dragging
        this->dragger = gcnew WindowDragger(this);

        // Initialize cells
        this->cells = gcnew array<System::Windows::Forms::Button^>(this->numberOfCells);
        this->initializeCells();

        // Initialize the form
        this->session = gcnew GameSession(this->numberOfCells);
        this->playerStats = gcnew PlayerStats();
        this->undoManager = gcnew UndoManager(gcnew System::Action(this, &SudokuForm::syncUndoControls));
        this->syncUndoControls(); // initial state, now that undoManager is assigned
        this->conflicts = gcnew ConflictDetector(this->session->board, this->sizeFactor);
        this->gameTimer = gcnew GameTimer();

        // No cell is hovered until the mouse enters one (MouseEnter/Leave keep this current).
        this->hoveredCellIndex = -1;

        // Restore the win streak and clean win streak earned in previous runs
        this->playerStats->winStreak = Settings::LoadWinStreak();
        this->playerStats->cleanWinStreak = Settings::LoadCleanWinStreak();

        // Restore the candidate-display preference and reflect it in the Options menu checkmarks.
        this->candidateDisplay = Settings::LoadCandidateDisplay();
        this->updateCandidateMenuChecks();

        // Restore the preferred difficulty. selectedDifficulty is set BEFORE the combo box
        // index so that difficultyComboBox_SelectedIndexChanged sees an unchanged value and
        // does not write it straight back to the registry.
        this->selectedDifficulty = Settings::LoadDifficulty();
        this->difficultyComboBox->SelectedIndex = this->selectedDifficulty;
        this->updateDifficultyMenuChecks();

        // Restore the last window position if one was stored and it is still (at least
        // partially) on a visible screen; otherwise keep the default placement.
        int storedLeft = 0;
        int storedTop = 0;
        if (Settings::TryLoadWindowPosition(storedLeft, storedTop))
        {
            System::Drawing::Rectangle bounds(storedLeft, storedTop, this->Width, this->Height);
            for each (Screen ^ screen in Screen::AllScreens)
            {
                if (screen->WorkingArea.IntersectsWith(bounds))
                {
                    this->StartPosition = FormStartPosition::Manual;
                    this->Location = System::Drawing::Point(storedLeft, storedTop);
                    break;
                }
            }
        }

        // Initialize button tooltips (texts are assigned by setLanguage below).
        // Longer auto-pop delay: the descriptions are full sentences.
        this->buttonToolTips = gcnew System::Windows::Forms::ToolTip();
        this->buttonToolTips->AutoPopDelay = 10000;
        this->buttonToolTips->InitialDelay = 500;
        this->buttonToolTips->ReshowDelay = 100;

        // Restore the language the user last chose; falls back to English on first run.
        // persist = false: this value came straight from the registry, no need to write it back.
        this->setLanguage(Settings::LoadLanguage(), false);

        // Wire Paint, MouseEnter, MouseLeave, and MouseClick events for each cell
        for each (System::Windows::Forms::Button ^ cell in this->cells)
        {
            cell->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &SudokuForm::cell_Paint);
            cell->MouseEnter += gcnew System::EventHandler(this, &SudokuForm::cell_MouseEnter);
            cell->MouseLeave += gcnew System::EventHandler(this, &SudokuForm::cell_MouseLeave);
            cell->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &SudokuForm::cell_MouseClick);
            cell->GotFocus += gcnew System::EventHandler(this, &SudokuForm::cell_FocusChanged);
            cell->LostFocus += gcnew System::EventHandler(this, &SudokuForm::cell_FocusChanged);
        }

        // Startup priority:
        //   1. a .sdk3 file passed on the command line / by the shell (open it, report errors)
        //   2. otherwise resume the session auto-saved when the app last closed
        //   3. otherwise start a new game at the restored preferred difficulty
        bool started = false;
        if (this->startupFilePath != nullptr && this->startupFilePath->Length > 0)
            started = this->loadGameFromFile(this->startupFilePath);

        if (!started && !this->tryResumeAutoSave())
            this->newGame(this->difficultyLevelFromIndex(this->selectedDifficulty));
    }

           // Apply the given language to all UI controls and update the language menu checkmarks.
           // Pass persist = false to apply without writing back to the registry (e.g. when the
           // language was just loaded from it at startup).
    private: void setLanguage(Language lang, bool persist)
    {
        this->currentLanguage = lang;
        if (persist)
            Settings::SaveLanguage(lang);

        // Window title
        this->Text = Strings::Get(StringId::WindowTitle, lang);

        // Buttons
        this->newGameButton->Text = Strings::Get(StringId::ButtonNewGame, lang);
        this->restartButton->Text = Strings::Get(StringId::ButtonRestart, lang);
        this->hintButton->Text = Strings::Get(StringId::ButtonHint, lang);
        this->fixButton->Text = Strings::Get(StringId::ButtonFix, lang);
        this->giveUpButton->Text = Strings::Get(StringId::ButtonGiveUp, lang);
        this->customPuzzleButton->Text = Strings::Get(StringId::ButtonEnterPuzzle, lang);
        this->solveButton->Text = Strings::Get(StringId::ButtonSolve, lang);
        this->undoButton->Text = Strings::Get(StringId::ButtonUndo, lang);
        this->pencilButton->Text = Strings::Get(StringId::ButtonPencil, lang);

        // Keep the timer and the difficulty dropdown self-describing
        // via accessible name (screen readers) and a hover tooltip (sighted users). The timer
        // carries its own tooltip; hiding it in Solver mode suppresses that tooltip automatically.
        this->difficultyComboBox->AccessibleName = Strings::Get(StringId::LabelDifficulty, lang);
        this->buttonToolTips->SetToolTip(this->difficultyComboBox, Strings::Get(StringId::LabelDifficulty, lang));
        this->buttonToolTips->SetToolTip(this->timerLabel, Strings::Get(StringId::TooltipTimer, lang));

        // Difficulty combo items
        this->difficultyComboBox->Items->Clear();
        this->difficultyComboBox->Items->Add(Strings::Get(StringId::DifficultyVeryEasy, lang));
        this->difficultyComboBox->Items->Add(Strings::Get(StringId::DifficultyEasy, lang));
        this->difficultyComboBox->Items->Add(Strings::Get(StringId::DifficultyMedium, lang));
        this->difficultyComboBox->Items->Add(Strings::Get(StringId::DifficultyHard, lang));
        this->difficultyComboBox->Items->Add(Strings::Get(StringId::DifficultyVeryHard, lang));
        this->difficultyComboBox->SelectedIndex = this->selectedDifficulty;

        // Menu: File
        this->fileToolStripMenuItem->Text = Strings::Get(StringId::MenuFile, lang);
        this->saveToolStripMenuItem->Text = Strings::Get(StringId::MenuSave, lang);
        this->openToolStripMenuItem->Text = Strings::Get(StringId::MenuOpen, lang);
        this->minimizeToolStripMenuItem->Text = Strings::Get(StringId::MenuMinimize, lang);
        this->exitToolStripMenuItem->Text = Strings::Get(StringId::MenuExit, lang);

        // Menu: Game
        this->gameToolStripMenuItem->Text = Strings::Get(StringId::MenuGame, lang);
        this->newGameToolStripMenuItem->Text = Strings::Get(StringId::MenuNewGame, lang);
        this->restartToolStripMenuItem->Text = Strings::Get(StringId::MenuRestart, lang);
        this->pencilToolStripMenuItem->Text = Strings::Get(StringId::MenuPencil, lang);
        this->hintToolStripMenuItem->Text = Strings::Get(StringId::MenuHint, lang);
        this->fixToolStripMenuItem->Text = Strings::Get(StringId::MenuFix, lang);
        this->giveUpToolStripMenuItem->Text = Strings::Get(StringId::MenuGiveUp, lang);
        this->undoToolStripMenuItem->Text = Strings::Get(StringId::MenuUndo, lang);
        this->customPuzzleToolStripMenuItem->Text = Strings::Get(StringId::MenuEnterPuzzle, lang);
        this->solveToolStripMenuItem->Text = Strings::Get(StringId::MenuSolve, lang);

        // Button tooltips (the clipboard button's tooltip is state-dependent and is
        // set by updateClipboardControls below)
        this->updateButtonTooltips();
        this->updateClipboardControls();

        // Menu: Options
        this->optionsToolStripMenuItem->Text = Strings::Get(StringId::MenuOptions, lang);
        this->difficultyToolStripMenuItem->Text = Strings::Get(StringId::MenuDifficulty, lang);
        this->veryEasyToolStripMenuItem->Text = Strings::Get(StringId::DifficultyVeryEasy, lang);
        this->easyToolStripMenuItem->Text = Strings::Get(StringId::DifficultyEasy, lang);
        this->mediumToolStripMenuItem->Text = Strings::Get(StringId::DifficultyMedium, lang);
        this->hardToolStripMenuItem->Text = Strings::Get(StringId::DifficultyHard, lang);
        this->veryHardToolStripMenuItem->Text = Strings::Get(StringId::DifficultyVeryHard, lang);
        this->languageToolStripMenuItem->Text = Strings::Get(StringId::MenuLanguage, lang);
        this->englishToolStripMenuItem->Text = Strings::Get(StringId::MenuLanguageEnglish, lang);
        this->ukrainianToolStripMenuItem->Text = Strings::Get(StringId::MenuLanguageUkrainian, lang);
        this->candidatesToolStripMenuItem->Text = Strings::Get(StringId::MenuCandidates, lang);
        this->candidatesNoneToolStripMenuItem->Text = Strings::Get(StringId::CandidateLevelNone, lang);
        this->candidatesCurrentCellToolStripMenuItem->Text = Strings::Get(StringId::CandidateLevelCurrentCell, lang);
        this->candidatesAllCellsToolStripMenuItem->Text = Strings::Get(StringId::CandidateLevelAllCells, lang);

        // Menu: Help
        this->helpToolStripMenuItem->Text = Strings::Get(StringId::MenuHelp, lang);
        this->aboutToolStripMenuItem->Text = Strings::Get(StringId::MenuAbout, lang);
        this->rulesToolStripMenuItem->Text = Strings::Get(StringId::MenuRules, lang);
        this->featuresToolStripMenuItem->Text = Strings::Get(StringId::MenuFeatures, lang);
        this->hintsAndTipsToolStripMenuItem->Text = Strings::Get(StringId::MenuHintsAndTips, lang);
        this->keyboardToolStripMenuItem->Text = Strings::Get(StringId::MenuKeyboard, lang);

        // Language menu checkmarks
        this->englishToolStripMenuItem->Checked = (lang == Language::English);
        this->ukrainianToolStripMenuItem->Checked = (lang == Language::Ukrainian);

        // File dialogs
        this->saveGameDialog->Title = Strings::Get(StringId::DialogTitleSave, lang);
        this->saveGameDialog->Filter = Strings::Get(StringId::FileDialogFilter, lang);
        this->openGameDialog->Title = Strings::Get(StringId::MenuOpen, lang);
        this->openGameDialog->Filter = Strings::Get(StringId::FileDialogFilter, lang);

        // Numbers form
        this->numbersForm->setLanguage(lang);
    }

    private: void englishToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->setLanguage(Language::English, true);
    }

    private: void ukrainianToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->setLanguage(Language::Ukrainian, true);
    }

    private: void candidatesNoneToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->setCandidateDisplay(CandidateDisplay::None);
    }

    private: void candidatesCurrentCellToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->setCandidateDisplay(CandidateDisplay::CurrentCell);
    }

    private: void candidatesAllCellsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->setCandidateDisplay(CandidateDisplay::AllCells);
    }

           // Changes the candidate-display level. Turning assistance ON (from None) first warns
           // that it forfeits the clean-win badge and clean streak, and does nothing if cancelled;
           // moving between non-None levels or back to None is silent.
    private: void setCandidateDisplay(CandidateDisplay level)
    {
        if (level == this->candidateDisplay)
            return;

        if (this->candidateDisplay == CandidateDisplay::None && level != CandidateDisplay::None)
        {
            System::Windows::Forms::DialogResult confirm = MessageBox::Show(
                Strings::Get(StringId::DialogCandidatesPrompt, this->currentLanguage),
                Strings::Get(StringId::DialogTitleCandidates, this->currentLanguage),
                MessageBoxButtons::YesNo,
                MessageBoxIcon::Warning);
            if (confirm != System::Windows::Forms::DialogResult::Yes)
                return;
        }

        this->candidateDisplay = level;
        Settings::SaveCandidateDisplay(level);
        this->updateCandidateMenuChecks();
        this->recordCandidateLevel(level); // taint the in-progress game with this level

        // Repaint so the candidate ghost appears, moves, or disappears immediately.
        this->renderAll();
    }

           // Reflects the selected candidate level as a checkmark in the Options > Candidates submenu.
    private: void updateCandidateMenuChecks()
    {
        this->candidatesNoneToolStripMenuItem->Checked = (this->candidateDisplay == CandidateDisplay::None);
        this->candidatesCurrentCellToolStripMenuItem->Checked = (this->candidateDisplay == CandidateDisplay::CurrentCell);
        this->candidatesAllCellsToolStripMenuItem->Checked = (this->candidateDisplay == CandidateDisplay::AllCells);
    }

           // Records that the in-progress game was played with at least this candidate level.
           // No-op once the game is finished, so its recorded assist level stays frozen (and a
           // later setting change cannot retroactively taint a completed game).
    private: void recordCandidateLevel(CandidateDisplay level)
    {
        if (this->isGameFinished()) return;
        if (level > this->session->maxCandidateAssist)
            this->session->maxCandidateAssist = level;
    }

           // Localized name of a candidate-display level, for the end-of-game stats line.
    private: System::String^ candidateLevelName(CandidateDisplay level)
    {
        StringId id;
        switch (level)
        {
        case CandidateDisplay::CurrentCell: id = StringId::CandidateLevelCurrentCell; break;
        case CandidateDisplay::AllCells:    id = StringId::CandidateLevelAllCells; break;
        default:                            id = StringId::CandidateLevelNone; break;
        }
        return Strings::Get(id, this->currentLanguage);
    }

    private: void initializeCells()
    {
        this->cells[80] = this->button81;
        this->cells[79] = this->button80;
        this->cells[78] = this->button79;
        this->cells[77] = this->button78;
        this->cells[76] = this->button77;
        this->cells[75] = this->button76;
        this->cells[74] = this->button75;
        this->cells[73] = this->button74;
        this->cells[72] = this->button73;
        this->cells[71] = this->button72;
        this->cells[70] = this->button71;
        this->cells[69] = this->button70;
        this->cells[68] = this->button69;
        this->cells[67] = this->button68;
        this->cells[66] = this->button67;
        this->cells[65] = this->button66;
        this->cells[64] = this->button65;
        this->cells[63] = this->button64;
        this->cells[62] = this->button63;
        this->cells[61] = this->button62;
        this->cells[60] = this->button61;
        this->cells[59] = this->button60;
        this->cells[58] = this->button59;
        this->cells[57] = this->button58;
        this->cells[56] = this->button57;
        this->cells[55] = this->button56;
        this->cells[54] = this->button55;
        this->cells[53] = this->button54;
        this->cells[52] = this->button53;
        this->cells[51] = this->button52;
        this->cells[50] = this->button51;
        this->cells[49] = this->button50;
        this->cells[48] = this->button49;
        this->cells[47] = this->button48;
        this->cells[46] = this->button47;
        this->cells[45] = this->button46;
        this->cells[44] = this->button45;
        this->cells[43] = this->button44;
        this->cells[42] = this->button43;
        this->cells[41] = this->button42;
        this->cells[40] = this->button41;
        this->cells[39] = this->button40;
        this->cells[38] = this->button39;
        this->cells[37] = this->button38;
        this->cells[36] = this->button37;
        this->cells[35] = this->button36;
        this->cells[34] = this->button35;
        this->cells[33] = this->button34;
        this->cells[32] = this->button33;
        this->cells[31] = this->button32;
        this->cells[30] = this->button31;
        this->cells[29] = this->button30;
        this->cells[28] = this->button29;
        this->cells[27] = this->button28;
        this->cells[26] = this->button27;
        this->cells[25] = this->button26;
        this->cells[24] = this->button25;
        this->cells[23] = this->button24;
        this->cells[22] = this->button23;
        this->cells[21] = this->button22;
        this->cells[20] = this->button21;
        this->cells[19] = this->button20;
        this->cells[18] = this->button19;
        this->cells[17] = this->button18;
        this->cells[16] = this->button17;
        this->cells[15] = this->button16;
        this->cells[14] = this->button15;
        this->cells[13] = this->button14;
        this->cells[12] = this->button13;
        this->cells[11] = this->button12;
        this->cells[10] = this->button11;
        this->cells[9] = this->button10;
        this->cells[8] = this->button9;
        this->cells[7] = this->button8;
        this->cells[6] = this->button7;
        this->cells[5] = this->button6;
        this->cells[4] = this->button5;
        this->cells[3] = this->button4;
        this->cells[2] = this->button3;
        this->cells[1] = this->button2;
        this->cells[0] = this->button1;

        this->cellIndex = gcnew System::Collections::Generic::Dictionary<System::Windows::Forms::Button^, int>();
        for (int i = 0; i < (int)this->numberOfCells; ++i)
            this->cellIndex[this->cells[i]] = i;
    }

           // Get cell button by its coordinates
    private: System::Windows::Forms::Button^ getButton(const unsigned int row, const unsigned int column)
    {
        return this->cells[this->boardSize * row + column];
    }

           // Maps a cell's kind to the text color used to render it.
    private: System::Drawing::Color colorForKind(CellKind kind)
    {
        switch (kind)
        {
        case CellKind::Correct: return correctColor;
        case CellKind::Hint:    return hintColor;
        case CellKind::GivenUp: return giveUpColor;
        case CellKind::Solved:  return solveColor;
        default:                return defaultColor; // Clue, UserEmpty, UserFilled
        }
    }

           // Projects one board cell fully onto its button: text, fore color, enabled state, and
           // conflict background. Invalidates so cell_Paint repaints any pencil marks.
    private: void projectCell(unsigned int index)
    {
        Board^ board = this->session->board;
        System::Windows::Forms::Button^ cell = this->cells[index];

        unsigned char value = board->valueAt(index);
        cell->Text = value == 0 ? String::Empty : ((int)value).ToString();
        cell->ForeColor = this->colorForKind(board->kindAt(index));
        cell->Enabled = board->isEditable(index);
        cell->BackColor = this->conflicts->hasConflict(index)
            ? (board->isEditable(index) ? conflictBackColor : conflictBackColorImmutable)
            : defaultBackColor;
        cell->Invalidate();
    }

           // Renders a single cell after a change, plus its peers (whose conflict state may have
           // changed as a result). Conflict detection reads the board model, so partial-render
           // ordering is never an issue.
    private: void renderCell(unsigned int index)
    {
        this->projectCell(index);
        for each (unsigned int peer in this->conflicts->peersOf(index))
            this->projectCell(peer);
    }

           // Re-projects the entire board.
    private: void renderAll()
    {
        for (unsigned int i = 0; i < this->numberOfCells; ++i)
            this->projectCell(i);
    }

           // Clears the board model to empty editable cells and re-renders.
    private: void clearBoard()
    {
        this->session->board->clearToEmpty();
        this->renderAll();
    }

           // Resets the board to its initial clue state from session->puzzle.
    private: void resetBoardToClues()
    {
        this->session->board->resetToClues(this->session->puzzle->clues);
        this->renderAll();
    }

           // Fill the engine with the values currently on the board.
    private: void fillEngine()
    {
        unsigned int index = 0;
        for (unsigned char i = 0; i < boardSize; ++i)
        {
            for (unsigned char j = 0; j < boardSize; ++j)
            {
                unsigned char value = this->session->board->valueAt(index);
                if (value == 0)
                {
                    this->engine->setFilled(i, j, false);
                }
                else
                {
                    this->engine->setFilled(i, j, true);
                    this->engine->setCellValue(i, j, value);
                }

                ++index;
            }
        }
    }

           // Start a new game
    private: void newGame(const SudokuGameEngine::DifficultyLevel difficulty)
    {
        // Generate a new puzzle
        this->engine->newGame(difficulty);

        // Capture the immutable puzzle snapshot before any session state changes
        array<unsigned char>^ clues = gcnew array<unsigned char>(this->numberOfCells);
        array<unsigned char>^ solution = gcnew array<unsigned char>(this->numberOfCells);
        for (unsigned int idx = 0; idx < this->numberOfCells; ++idx)
        {
            unsigned char i = (unsigned char)(idx / this->boardSize);
            unsigned char j = (unsigned char)(idx % this->boardSize);
            solution[idx] = (unsigned char)this->engine->getCellValue(i, j);
            clues[idx] = this->engine->getFilled(i, j) ? solution[idx] : (unsigned char)0;
        }

        // Map difficulty enum to index and reset all per-game session state atomically
        unsigned int difficultyIndex = 0;
        switch (difficulty)
        {
        case SudokuGameEngine::DifficultyLevel::VeryEasy: difficultyIndex = 0; break;
        case SudokuGameEngine::DifficultyLevel::Easy:     difficultyIndex = 1; break;
        case SudokuGameEngine::DifficultyLevel::Medium:   difficultyIndex = 2; break;
        case SudokuGameEngine::DifficultyLevel::Hard:     difficultyIndex = 3; break;
        case SudokuGameEngine::DifficultyLevel::VeryHard: difficultyIndex = 4; break;
        }
        this->session->startNewGame(difficultyIndex);
        this->session->puzzle = gcnew Puzzle(clues, solution);

        // Prepare the board (resetBoardToClues re-renders and highlights conflicts)
        this->resetBoardToClues();
        this->undoManager->clear();
        this->gameTimer->restart();
        this->setGameControls(true, true, false);
        this->recordCandidateLevel(this->candidateDisplay); // this game is played under the current level
        this->updateClipboardControls();

        // Move focus to the first editable cell
        for each (Button ^ cell in this->cells)
        {
            if (cell->Enabled)
            {
                cell->Focus();
                break;
            }
        }
    }

           // Check if the solution is correct: every editable (user) cell must hold its solution value.
    private: const bool checkSolution()
    {
        for (unsigned int index = 0; index < this->numberOfCells; ++index)
        {
            if (this->session->board->isEditable(index) &&
                this->session->board->valueAt(index) != this->session->puzzle->solution[index])
            {
                return false;
            }
        }
        return true;
    }

           // Check if the game has been finished
           // Locks all correctly-filled user cells, updates win streak, and resets UI controls.
           // Called once when the puzzle is detected as solved.
    private: void applyWin()
    {
        for (unsigned int i = 0; i < this->numberOfCells; ++i)
        {
            if (this->session->board->isEditable(i))
                this->session->board->lockAsCorrect(i);
        }
        this->renderAll();

        this->clearActiveModes();
        this->setGameControls(false, true, false);
        this->undoManager->clear();

        // Freeze the play time before the win message reads it
        this->gameTimer->stop();

        // A win advances the win streak; the clean streak advances only if the win was clean.
        unsigned int previousWin = this->playerStats->winStreak;
        unsigned int previousClean = this->playerStats->cleanWinStreak;
        this->playerStats->recordWin(this->session->isClean());
        this->persistStreaks(previousWin, previousClean);
    }

           // Persists the two streaks, writing each to the registry only when it actually changed
           // (e.g. a give-up while both are already 0 writes nothing).
    private: void persistStreaks(unsigned int previousWin, unsigned int previousClean)
    {
        if (this->playerStats->winStreak != previousWin)
            Settings::SaveWinStreak(this->playerStats->winStreak);
        if (this->playerStats->cleanWinStreak != previousClean)
            Settings::SaveCleanWinStreak(this->playerStats->cleanWinStreak);
    }

           // A win counts as "mostly hints" - barely better than giving up - once hint reveals
           // reach this share of the cells the player had to fill.
    private: literal int MostlyHintsThresholdPercent = 90;

           // Presentation policy: was this win carried mostly by hint reveals? Reads the session's
           // factual counts and applies the threshold above (kept here, in the view, rather than in
           // the session data model).
    private: bool wonMostlyByHints()
    {
        int fillable = (int)this->numberOfCells - this->session->clueCount();
        return fillable > 0
            && this->session->hintCount() * 100 >= fillable * MostlyHintsThresholdPercent;
    }

           // Builds the end-of-game message: a headline line, then each per-puzzle statistic on
           // its own line. Shown both on a win and after a give-up.
    private: System::String^ buildEndMessage(bool won)
    {
        System::String^ headline;
        if (won)
        {
            if (this->session->isClean())
            {
                headline = Strings::Get(StringId::EndWinClean, this->currentLanguage);
            }
            else
            {
                // If hints revealed almost the whole board, this "win" is barely better than
                // giving up - deflate the message instead of celebrating.
                StringId headlineId = this->wonMostlyByHints()
                    ? StringId::EndWinMostlyHints : StringId::EndWin;
                headline = Strings::Get(headlineId, this->currentLanguage);
            }
        }
        else
        {
            headline = Strings::Get(StringId::EndGiveUp, this->currentLanguage);
        }

        System::String^ msg = headline + "\n\n";
        msg += Strings::Get(StringId::StatDifficulty, this->currentLanguage) + this->difficultyName(this->session->difficulty)
            + " " + System::String::Format(Strings::Get(StringId::StatClues, this->currentLanguage), this->session->clueCount()) + "\n";
        msg += Strings::Get(StringId::StatTime, this->currentLanguage) + this->formatElapsed(this->gameTimer->Elapsed) + "\n";
        msg += Strings::Get(StringId::StatRestarts, this->currentLanguage) + this->session->numberOfRestarts + "\n";
        msg += Strings::Get(StringId::StatHints, this->currentLanguage) + this->session->numberOfHints + "\n";
        msg += Strings::Get(StringId::StatFixes, this->currentLanguage) + this->session->numberOfFixes + "\n";
        msg += Strings::Get(StringId::StatGiveUps, this->currentLanguage) + this->session->numberOfGiveUps + "\n";
        msg += Strings::Get(StringId::StatCandidateHelp, this->currentLanguage)
            + this->candidateLevelName(this->session->maxCandidateAssist);

        // Win streaks are cross-game stats; show each only on a win, and only once it is a streak.
        if (won && this->playerStats->winStreak > 1)
            msg += "\n" + Strings::Get(StringId::StatWinStreak, this->currentLanguage) + this->playerStats->winStreak;
        if (won && this->playerStats->cleanWinStreak > 1)
            msg += "\n" + Strings::Get(StringId::StatCleanWinStreak, this->currentLanguage) + this->playerStats->cleanWinStreak;

        return msg;
    }

           // Formats an elapsed play time as m:ss, or h:mm:ss once it reaches an hour
    private: System::String^ formatElapsed(System::TimeSpan elapsed)
    {
        if (elapsed.TotalHours >= 1.0)
        {
            return System::String::Format("{0}:{1:00}:{2:00}",
                (int)elapsed.TotalHours, elapsed.Minutes, elapsed.Seconds);
        }
        return System::String::Format("{0}:{1:00}", elapsed.Minutes, elapsed.Seconds);
    }

           // Checks if the board is fully and correctly filled; triggers win flow if so.
           // Only meaningful in Game mode: Solver mode has no win condition and session->puzzle
           // may not be set (or may be stale from a prior game) while the user is still entering.
    private: void checkGameState()
    {
        if (this->session->mode != GameMode::Game) return;

        if (this->session->board->FilledCount == this->numberOfCells && this->checkSolution())
        {
            this->applyWin();
            this->showNotification(this->buildEndMessage(true));
        }
    }

           // Handles a click on any of the 81 cell buttons. Every cell is wired to this one
           // handler in initialize(); the clicked cell is identified from the sender.
    private: void cell_Click(System::Object^ sender, System::EventArgs^ e)
    {
        int index;
        if (!this->cellIndex->TryGetValue(safe_cast<System::Windows::Forms::Button^>(sender), index)) return;

        this->closeHelperForms();

        // The button that has been clicked
        System::Windows::Forms::Button^ currentButton = this->cells[index];

        // In pencil mode, mouse clicks are handled by cell_MouseClick (zone hit-test);
        // a plain button Click in pencil mode means the user clicked outside a digit zone
        // or used keyboard - keyboard path goes through choiceMade directly, so just return.
        if (this->pencilMode && currentButton->Enabled && !this->hintMode)
            return;

        // If this is a hint option, reveal the cell's solution value
        if (this->hintMode)
        {
            this->undoManager->push(index, this->session->board->valueAt(index), this->session->board->pencilMarksAt(index));
            this->session->board->reveal(index, this->session->puzzle->solution[index], CellKind::Hint);
            ++(this->session->numberOfHints);
            this->renderCell(index);

            this->checkGameState();
        }
        // Else show the numbers form
        else
        {
            // Center the numbers form over the clicked cell,
            // clamped so it stays fully within the cell grid
            int boardLeft = this->Left + this->cells[0]->Left;
            int boardTop = this->Top + this->cells[0]->Top;
            int boardRight = this->Left + this->cells[this->numberOfCells - 1]->Right;
            int boardBottom = this->Top + this->cells[this->numberOfCells - 1]->Bottom;

            int left = this->Left + currentButton->Left + (currentButton->Width - this->numbersForm->Width) / 2;
            int top = this->Top + currentButton->Top + (currentButton->Height - this->numbersForm->Height) / 2;

            left = Math::Max(boardLeft, Math::Min(left, boardRight - this->numbersForm->Width));
            top = Math::Max(boardTop, Math::Min(top, boardBottom - this->numbersForm->Height));

            // Show the number choice form
            this->numbersForm->Left = left;
            this->numbersForm->Top = top;
            this->numbersForm->setPencilMode(this->pencilMode && currentButton->Enabled);
            // The numbers form uses 1-based cell numbers and echoes it back via choiceMade.
            this->numbersForm->setCellNumber(index + 1);
            this->numbersForm->Visible = true;
            this->numbersForm->Activate();
        }
    }

           // A delegate method called by the numbers form when a choice has been made
    public: void choiceMade(
        const unsigned int cellNumber,
        const unsigned int choice)
    {
        this->closeHelperForms();
        unsigned int index = cellNumber - 1;
        Board^ board = this->session->board;

        // Pencil mode: toggle a mark bit only, never touch the cell value
        if (this->pencilMode && board->isEditable(index))
        {
            if (choice >= 1 && choice <= 9)
            {
                this->undoManager->push(index, this->session->board->valueAt(index), board->pencilMarksAt(index));
                board->togglePencilMark(index, (int)choice);
                this->renderCell(index);
            }
            return;
        }

        // Ignore no-op edits - picking the value the cell already holds, or clearing an
        // already-empty cell - so they never create a redundant undo entry.
        if ((unsigned char)choice == board->valueAt(index))
            return;

        this->undoManager->push(index, this->session->board->valueAt(index), board->pencilMarksAt(index));
        board->setUserValue(index, (unsigned char)choice);
        this->renderCell(index);
        this->checkGameState();
    }

    private: void restoreCell(unsigned int index, unsigned char previousValue, int previousMarks)
    {
        // Undo always restores an editable user cell (value + pencil marks); Board derives the kind.
        this->session->board->restoreUserCell(index, previousValue, previousMarks);
        this->renderCell(index);
    }

           // Keeps the Undo button and menu item in sync with the undo stack. Wired as the
           // UndoManager's change callback, so it fires on every push/batch/pop/clear.
    private: void syncUndoControls()
    {
        this->undoButton->Enabled = this->undoManager->canUndo;
        this->undoToolStripMenuItem->Enabled = this->undoManager->canUndo;
    }

    private: void performUndo()
    {
        auto entries = this->undoManager->popOperation();
        if (entries->Count == 0) return;

        System::Windows::Forms::Button^ lastCell = nullptr;
        for each (auto entry in entries)
        {
            this->restoreCell(entry->cellIndex, entry->previousValue, entry->previousPencilMarks);
            lastCell = this->cells[entry->cellIndex];
        }
        if (lastCell != nullptr)
        {
            lastCell->Focus();
        }
    }

    private: void undoToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->performUndo();
    }

    private: void undoButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->performUndo();
    }

    private: void pencilToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (!this->pencilToolStripMenuItem->Enabled) return;
        this->setPencilMode(!this->pencilMode);
    }

    private: void setPencilMode(bool active)
    {
        if (active) { this->hintMode = false; this->hintButton->ForeColor = defaultColor; }
        this->pencilMode = active;
        this->pencilButton->ForeColor = active ? activeButtonColor : defaultColor;

        // Refresh the focused cell so its candidate ghost appears/disappears immediately on toggle
        // (e.g. Ctrl+P while a cell is keyboard-selected).
        if (this->ActiveControl != nullptr) this->ActiveControl->Invalidate();
    }

           // Set hint mode; deactivates pencil mode so both cannot be active simultaneously
    private: void setHintMode(bool active)
    {
        if (active) { this->pencilMode = false; this->pencilButton->ForeColor = defaultColor; }
        this->hintMode = active;
        this->hintButton->ForeColor = active ? activeButtonColor : defaultColor;
    }

           // Deactivates both pencil and hint mode; call at every state transition
    private: void clearActiveModes()
    {
        this->setPencilMode(false);
        this->setHintMode(false);
    }

    private: void pencilButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->setPencilMode(!this->pencilMode);
    }

           // Paints pencil marks
    private: void cell_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
    {
        System::Windows::Forms::Button^ cell = safe_cast<System::Windows::Forms::Button^>(sender);
        int idx;
        if (!this->cellIndex->TryGetValue(cell, idx) || cell->Text->Length > 0) return;

        // Candidate-ghost visibility is driven purely by the CandidateDisplay level (independent
        // of pencil mode, which only governs input): None never shows, CurrentCell shows on the
        // hovered/focused cell, AllCells shows on every empty cell.
        bool showCandidates = cell->Enabled &&
            (this->candidateDisplay == CandidateDisplay::AllCells ||
                (this->candidateDisplay == CandidateDisplay::CurrentCell
                    && (idx == this->hoveredCellIndex || cell->Focused)));

        int pencilMarks = this->session->board->pencilMarksAt(idx);
        if (pencilMarks == 0 && !showCandidates) return;

        System::Drawing::Graphics^ g = e->Graphics;
        float w = (float)cell->ClientSize.Width;
        float h = (float)cell->ClientSize.Height;
        float pad = Math::Max(2.0f, Math::Min(w, h) * 0.04f);
        float cw = (w - 2.0f * pad) / 3.0f;
        float ch = (h - 2.0f * pad) / 3.0f;

        // Reuse cached rendering resources, rebuilding the font only when the size changes.
        float fontSize = Math::Max(6.0f, Math::Min(cw, ch) * 0.55f);
        if (this->pencilFont == nullptr || this->pencilFontSize != fontSize)
        {
            delete this->pencilFont;
            this->pencilFont = gcnew System::Drawing::Font("Calibri", fontSize,
                System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
            this->pencilFontSize = fontSize;
        }
        if (this->pencilFormat == nullptr)
        {
            this->pencilFormat = gcnew System::Drawing::StringFormat();
            this->pencilFormat->LineAlignment = System::Drawing::StringAlignment::Center;
        }
        System::Drawing::Font^ font = this->pencilFont;
        System::Drawing::StringFormat^ sf = this->pencilFormat;

        // Pre-compute which digits are blocked by a filled peer
        int blockedBits = this->conflicts->getBlockedDigits((unsigned int)idx);

        for (int d = 1; d <= 9; ++d)
        {
            bool isMarked = (pencilMarks & (1 << d)) != 0;
            bool isConflict = (blockedBits & (1 << d)) != 0;

            System::Drawing::Brush^ brush;
            if (isMarked)
                brush = isConflict ? System::Drawing::Brushes::Red : System::Drawing::Brushes::Black;
            else if (showCandidates && !isConflict)
                brush = System::Drawing::Brushes::DarkGray;
            else
                continue;

            int col3 = (d - 1) % 3;
            int row3 = (d - 1) / 3;
            float x = pad + col3 * cw;
            float y = pad + row3 * ch;
            System::Drawing::RectangleF rect(x, y, cw, ch);
            g->DrawString(d.ToString(), font, brush, rect, sf);
        }
    }

           // Navigate focus to the nearest enabled cell in a given direction, wrapping around
    private: void navigateCell(int currentIndex, int rowDelta, int colDelta)
    {
        int row = currentIndex / (int)boardSize;
        int col = currentIndex % (int)boardSize;

        for (int steps = 1; steps < (int)boardSize; ++steps)
        {
            int newRow = ((row + rowDelta * steps) % (int)boardSize + (int)boardSize) % (int)boardSize;
            int newCol = ((col + colDelta * steps) % (int)boardSize + (int)boardSize) % (int)boardSize;
            int newIndex = newRow * (int)boardSize + newCol;

            if (this->cells[newIndex]->Enabled)
            {
                this->cells[newIndex]->Focus();
                return;
            }
        }
    }

    private: void buttonPreviewKeyDown(System::Object^ sender, System::Windows::Forms::PreviewKeyDownEventArgs^ e)
    {
        if (e->KeyCode == Keys::Up || e->KeyCode == Keys::Down ||
            e->KeyCode == Keys::Left || e->KeyCode == Keys::Right)
        {
            e->IsInputKey = true;
        }
    }

    private: void buttonKeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
    {
        int index;
        if (!this->cellIndex->TryGetValue(safe_cast<Button^>(sender), index)) return;

        switch (e->KeyCode)
        {
        case Keys::Up:
            this->navigateCell(index, -1, 0);
            e->Handled = true;
            break;
        case Keys::Down:
            this->navigateCell(index, 1, 0);
            e->Handled = true;
            break;
        case Keys::Left:
            this->navigateCell(index, 0, -1);
            e->Handled = true;
            break;
        case Keys::Right:
            this->navigateCell(index, 0, 1);
            e->Handled = true;
            break;
        case Keys::Delete:
            if (!this->hintMode)
            {
                this->choiceMade(index + 1, 0);
                e->Handled = true;
            }
            break;
        case Keys::P:
            if (e->Control && this->pencilButton->Enabled)
            {
                this->setPencilMode(!this->pencilMode);
                e->Handled = true;
                e->SuppressKeyPress = true;
            }
            break;
        default:
            // Suppress all Ctrl+key combinations so their KeyChar (e.g. Ctrl+H -> '\b')
            // does not reach buttonKeyPress and get misinterpreted as a digit/clear action.
            if (e->Control)
            {
                e->Handled = true;
                e->SuppressKeyPress = true;
            }
            break;
        }
    }

           // Pencil-mode hover: track which cell is under the mouse for ghost-mark rendering
    private: void cell_MouseEnter(System::Object^ sender, System::EventArgs^ e)
    {
        int idx;
        if (!this->cellIndex->TryGetValue(safe_cast<Button^>(sender), idx)) return;
        this->hoveredCellIndex = idx;
        if (this->pencilMode && this->cells[idx]->Enabled && this->cells[idx]->Text->Length == 0)
            this->cells[idx]->Invalidate();
    }

    private: void cell_MouseLeave(System::Object^ sender, System::EventArgs^ e)
    {
        int idx;
        if (!this->cellIndex->TryGetValue(safe_cast<Button^>(sender), idx)) return;
        if (this->hoveredCellIndex == idx)
            this->hoveredCellIndex = -1;
        if (this->pencilMode && this->cells[idx]->Enabled && this->cells[idx]->Text->Length == 0)
            this->cells[idx]->Invalidate();
    }

           // Pencil-mode keyboard selection: the focused cell shows candidate ghost marks, so
           // repaint it as focus enters or leaves it (wired to both GotFocus and LostFocus).
    private: void cell_FocusChanged(System::Object^ sender, System::EventArgs^ e)
    {
        if (!this->pencilMode) return;
        Button^ cell = safe_cast<Button^>(sender);
        if (cell->Enabled && cell->Text->Length == 0)
            cell->Invalidate();
    }

           // Pencil-mode mouse click: hit-test which digit zone was clicked and toggle that mark
    private: void cell_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        if (!this->pencilMode || this->hintMode) return;

        Button^ cell = safe_cast<Button^>(sender);
        int idx;
        if (!this->cellIndex->TryGetValue(cell, idx) || !cell->Enabled || cell->Text->Length > 0) return;

        float w = (float)cell->ClientSize.Width;
        float h = (float)cell->ClientSize.Height;
        float pad = Math::Max(2.0f, Math::Min(w, h) * 0.04f);
        float cw = (w - 2.0f * pad) / 3.0f;
        float ch = (h - 2.0f * pad) / 3.0f;

        float relX = e->X - pad;
        float relY = e->Y - pad;
        if (relX < 0 || relY < 0 || relX >= cw * 3.0f || relY >= ch * 3.0f) return;

        int col3 = (int)(relX / cw);
        int row3 = (int)(relY / ch);
        int digit = row3 * 3 + col3 + 1;
        if (digit < 1 || digit > 9) return;

        this->undoManager->push(idx, this->session->board->valueAt(idx), this->session->board->pencilMarksAt(idx));
        this->session->board->togglePencilMark(idx, digit);
        this->renderCell(idx);
    }

           // Offer to save the current session before it is discarded.
           // Returns true if the action should proceed, false if the user cancelled.
    private: bool promptSaveIfNeeded()
    {
        System::Windows::Forms::DialogResult result = MessageBox::Show(
            Strings::Get(StringId::DialogSavePrompt, this->currentLanguage),
            Strings::Get(StringId::DialogTitleSave, this->currentLanguage),
            MessageBoxButtons::YesNoCancel,
            MessageBoxIcon::Question);

        if (result == System::Windows::Forms::DialogResult::Yes)
        {
            this->showSaveGameDialog();
        }
        else if (result == System::Windows::Forms::DialogResult::Cancel)
        {
            return false;
        }
        return true;
    }

           // Close the numbers form if it is open
    private: void closeHelperForms()
    {
        // Close numbers form
        this->numbersForm->Visible = false;
    }

           // Maps a 0-based difficulty index (combo box / settings) to the engine's enum
    private: SudokuGameEngine::DifficultyLevel difficultyLevelFromIndex(unsigned int index)
    {
        switch (index)
        {
        case 0:  return SudokuGameEngine::DifficultyLevel::VeryEasy;
        case 1:  return SudokuGameEngine::DifficultyLevel::Easy;
        case 2:  return SudokuGameEngine::DifficultyLevel::Medium;
        case 3:  return SudokuGameEngine::DifficultyLevel::Hard;
        case 4:  return SudokuGameEngine::DifficultyLevel::VeryHard;
        default: return SudokuGameEngine::DifficultyLevel::Medium;
        }
    }

    private: void newGameButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (!this->promptSaveIfNeeded()) return;
        this->closeHelperForms();
        this->clearActiveModes();

        this->newGame(this->difficultyLevelFromIndex(this->selectedDifficulty));
    }

    private: void restartButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        System::Windows::Forms::DialogResult confirm = MessageBox::Show(
            Strings::Get(StringId::DialogRestartPrompt, this->currentLanguage),
            Strings::Get(StringId::DialogTitleRestart, this->currentLanguage),
            MessageBoxButtons::OKCancel,
            MessageBoxIcon::None);

        if (confirm != System::Windows::Forms::DialogResult::OK)
        {
            return;
        }

        this->closeHelperForms();
        this->clearActiveModes();

        ++this->session->numberOfRestarts;
        this->undoManager->clear();
        // Timing is cumulative across restarts of the same puzzle; this also resumes
        // the timer when restarting after a win or a give-up froze it
        this->gameTimer->resume();

        // Restore the board to its initial clue state (re-renders and re-highlights).
        this->resetBoardToClues();

        this->setGameControls(true, true, false);
        // numberOfGiveUps is intentionally NOT reset: once the user has seen the solution,
        // no re-prompt is needed and a win after restart still counts as a post-give-up win.
    }

    private: void hintButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->closeHelperForms();
        this->setHintMode(!this->hintMode);
    }

    private: void fixButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->closeHelperForms();

        // Confirm only the first time Fix is used on this puzzle
        if (this->session->numberOfFixes == 0)
        {
            System::Windows::Forms::DialogResult confirm = MessageBox::Show(
                Strings::Get(StringId::DialogFixPrompt, this->currentLanguage),
                Strings::Get(StringId::DialogTitleFix, this->currentLanguage),
                MessageBoxButtons::OKCancel,
                MessageBoxIcon::None);

            if (confirm != System::Windows::Forms::DialogResult::OK)
            {
                return;
            }
        }

        ++this->session->numberOfFixes;

        Board^ board = this->session->board;
        bool anyFixed = false;

        for (unsigned int index = 0; index < this->numberOfCells; ++index)
        {
            // A user-filled cell whose value contradicts the solution
            if (board->isEditable(index) && board->valueAt(index) != 0 &&
                board->valueAt(index) != this->session->puzzle->solution[index])
            {
                if (!anyFixed)
                {
                    this->undoManager->beginBatch();
                    anyFixed = true;
                }

                this->undoManager->push(index, this->session->board->valueAt(index), board->pencilMarksAt(index));
                board->setUserValue(index, 0);
                this->renderCell(index);
            }
        }

        if (anyFixed)
        {
            this->undoManager->endBatch();
        }
    }

    private: void giveUpButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        // Confirm only the first time the user gives up on this puzzle
        if (this->session->numberOfGiveUps == 0)
        {
            System::Windows::Forms::DialogResult confirm = MessageBox::Show(
                Strings::Get(StringId::DialogGiveUpPrompt, this->currentLanguage),
                Strings::Get(StringId::DialogTitleGiveUp, this->currentLanguage),
                MessageBoxButtons::YesNo,
                MessageBoxIcon::None);

            if (confirm != System::Windows::Forms::DialogResult::Yes)
            {
                return;
            }
        }

        this->closeHelperForms();
        this->clearActiveModes();

        ++this->session->numberOfGiveUps;
        unsigned int previousWin = this->playerStats->winStreak;
        unsigned int previousClean = this->playerStats->cleanWinStreak;
        this->playerStats->recordGiveUp();
        this->persistStreaks(previousWin, previousClean);

        // Reveal the solution in every editable cell.
        for (unsigned int index = 0; index < this->numberOfCells; ++index)
        {
            if (this->session->board->isEditable(index))
                this->session->board->reveal(index, this->session->puzzle->solution[index], CellKind::GivenUp);
        }
        this->renderAll();

        this->setGameControls(false, true, false);
        this->undoManager->clear();
        this->gameTimer->stop();

        this->showNotification(this->buildEndMessage(false));
    }

           // Assigns localized hover tooltips (full action name + description, the same
           // Feature* strings the Features dialog is composed of) to the side-panel buttons.
           // The clipboard button is state-dependent and handled in updateClipboardControls().
    private: void updateButtonTooltips()
    {
        this->buttonToolTips->SetToolTip(this->newGameButton, Strings::Get(StringId::FeatureNewGame, this->currentLanguage));
        this->buttonToolTips->SetToolTip(this->restartButton, Strings::Get(StringId::FeatureRestart, this->currentLanguage));
        this->buttonToolTips->SetToolTip(this->pencilButton, Strings::Get(StringId::FeaturePencil, this->currentLanguage));
        this->buttonToolTips->SetToolTip(this->hintButton, Strings::Get(StringId::FeatureHint, this->currentLanguage));
        this->buttonToolTips->SetToolTip(this->fixButton, Strings::Get(StringId::FeatureFix, this->currentLanguage));
        this->buttonToolTips->SetToolTip(this->giveUpButton, Strings::Get(StringId::FeatureGiveUp, this->currentLanguage));
        this->buttonToolTips->SetToolTip(this->undoButton, Strings::Get(StringId::FeatureUndo, this->currentLanguage));
        this->buttonToolTips->SetToolTip(this->customPuzzleButton, Strings::Get(StringId::FeatureEnterPuzzle, this->currentLanguage));
        this->buttonToolTips->SetToolTip(this->solveButton, Strings::Get(StringId::FeatureSolve, this->currentLanguage));
    }

           // Single source of truth for the clipboard button and its three menu items. Exactly one
           // clipboard action is available at a time, driven purely by session state, so it stays
           // correct no matter how we reached the state (new game, solve, paste, or file load):
           //   Game mode            -> Copy Puzzle   (share the clues)
           //   Solver, solved       -> Copy Solution (share the found solution)
           //   Solver, being entered-> Paste Puzzle  (load clues from the clipboard)
    private: void updateClipboardControls()
    {
        // Refresh labels every call so a language change is reflected too.
        this->copyPuzzleToolStripMenuItem->Text = Strings::Get(StringId::MenuCopyPuzzle, this->currentLanguage);
        this->pastePuzzleToolStripMenuItem->Text = Strings::Get(StringId::MenuPastePuzzle, this->currentLanguage);
        this->copySolutionToolStripMenuItem->Text = Strings::Get(StringId::MenuCopySolution, this->currentLanguage);

        bool inGame = this->session->mode == GameMode::Game;
        bool solverSolved = !inGame && this->session->puzzle != nullptr;
        bool solverEntering = !inGame && this->session->puzzle == nullptr;

        this->copyPuzzleToolStripMenuItem->Enabled = inGame;
        this->pastePuzzleToolStripMenuItem->Enabled = solverEntering;
        this->copySolutionToolStripMenuItem->Enabled = solverSolved;

        StringId buttonLabel = inGame ? StringId::ButtonCopyPuzzle
            : solverSolved ? StringId::ButtonCopySolution
            : StringId::ButtonPastePuzzle;
        this->clipboardButton->Text = Strings::Get(buttonLabel, this->currentLanguage);
        this->clipboardButton->Enabled = true;

        // Tooltip follows the active action; also shows the full caption when the
        // localized text is too wide to fit on the button
        StringId buttonTooltip = inGame ? StringId::FeatureCopyPuzzle
            : solverSolved ? StringId::FeatureCopySolution
            : StringId::FeaturePastePuzzle;
        this->buttonToolTips->SetToolTip(this->clipboardButton, Strings::Get(buttonTooltip, this->currentLanguage));
    }

    private: void copyPuzzleToClipboard()
    {
        // Always copies the original clues, never the solution.
        System::Windows::Forms::Clipboard::SetText(
            ClipboardPuzzleFormatter::Encode(this->session->puzzle->clues));
    }

    private: void copySolutionToClipboard()
    {
        // Copies the full solution of a solved custom puzzle.
        System::Windows::Forms::Clipboard::SetText(
            ClipboardPuzzleFormatter::Encode(this->session->puzzle->solution));
    }

    private: void pastePuzzleFromClipboard()
    {
        System::String^ raw = System::Windows::Forms::Clipboard::ContainsText()
            ? System::Windows::Forms::Clipboard::GetText()
            : gcnew System::String(L"");

        array<unsigned char>^ digits = ClipboardPuzzleFormatter::Decode(raw, (int)this->numberOfCells);
        if (digits == nullptr)
        {
            this->showNotification(Strings::Get(StringId::NotifyInvalidPuzzleString, this->currentLanguage));
            return;
        }

        this->engine->clear();
        this->session->board->clearToEmpty();
        this->undoManager->clear();
        this->gameTimer->restart();
        this->session->puzzle = nullptr;  // no valid puzzle until Solve succeeds

        for (unsigned int i = 0; i < this->numberOfCells; ++i)
        {
            if (digits[i] >= 1 && digits[i] <= 9)
                this->session->board->setUserValue(i, digits[i]);
        }

        this->renderAll();
    }

    private: void clipboardButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (this->copyPuzzleToolStripMenuItem->Enabled)
            this->copyPuzzleToClipboard();
        else if (this->pastePuzzleToolStripMenuItem->Enabled)
            this->pastePuzzleFromClipboard();
        else if (this->copySolutionToolStripMenuItem->Enabled)
            this->copySolutionToClipboard();
    }

    private: void copyPuzzleToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (this->copyPuzzleToolStripMenuItem->Enabled)
            this->copyPuzzleToClipboard();
    }

    private: void pastePuzzleToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (this->pastePuzzleToolStripMenuItem->Enabled)
            this->pastePuzzleFromClipboard();
    }

    private: void copySolutionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (this->copySolutionToolStripMenuItem->Enabled)
            this->copySolutionToClipboard();
    }

    private: void customPuzzleButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (!this->promptSaveIfNeeded()) return;
        this->closeHelperForms();
        this->clearActiveModes();

        this->engine->clear();
        // Resets the board, counters, and mode to Solver (puzzle stays nullptr until Solve).
        this->session->startCustomPuzzle();
        this->renderAll();

        this->undoManager->clear();
        this->gameTimer->restart();
        this->setGameControls(false, false, true);
        this->recordCandidateLevel(this->candidateDisplay); // this session is played under the current level
        this->updateClipboardControls();
    }

    private: void solveButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->closeHelperForms();
        this->clearActiveModes();

        this->fillEngine();
        this->engine->trySolve();

        if (engine->currentState() == SudokuGameEngine::SudokuEngineState::FilledValid)
        {
            // Capture the puzzle snapshot: clues are whatever was pre-filled, solution comes from the engine
            array<unsigned char>^ clues = gcnew array<unsigned char>(this->numberOfCells);
            array<unsigned char>^ solution = gcnew array<unsigned char>(this->numberOfCells);
            for (unsigned int idx = 0; idx < this->numberOfCells; ++idx)
            {
                solution[idx] = (unsigned char)this->engine->getCellValue(
                    (unsigned char)(idx / this->boardSize),
                    (unsigned char)(idx % this->boardSize));
                // A cell that already had a value before Solve was pressed is a clue
                clues[idx] = this->session->board->valueAt(idx) != 0 ? solution[idx] : (unsigned char)0;
            }
            this->session->puzzle = gcnew Puzzle(clues, solution);

            // Lock the pre-filled cells as clues; fill the rest from the solution.
            for (unsigned int index = 0; index < this->numberOfCells; ++index)
            {
                if (this->session->board->valueAt(index) == 0)
                    this->session->board->reveal(index, solution[index], CellKind::Solved);
                else
                    this->session->board->setClue(index, solution[index]);
            }
            this->renderAll();

            this->solveButton->Enabled = false;
            this->solveToolStripMenuItem->Enabled = false;
            // The puzzle now has a solution, so the clipboard offers Copy Solution instead of Paste.
            this->updateClipboardControls();
            this->undoManager->clear();
            this->gameTimer->stop();
        }
        else if (engine->currentState() == SudokuGameEngine::SudokuEngineState::HasMultipleSolutions)
        {
            this->showNotification(Strings::Get(StringId::NotifyMultipleSolutions, this->currentLanguage));
        }
        else if (
            engine->currentState() == SudokuGameEngine::SudokuEngineState::HasNoSolution ||
            engine->currentState() == SudokuGameEngine::SudokuEngineState::FilledInvalid)
        {
            this->showNotification(Strings::Get(StringId::NotifyNoSolution, this->currentLanguage));
        }
        else if (engine->currentState() == SudokuGameEngine::SudokuEngineState::Empty)
        {
            this->showNotification(Strings::Get(StringId::NotifyBoardEmpty, this->currentLanguage));
        }
    }

    private: void menuStrip_ItemClicked(System::Object^ sender, System::Windows::Forms::ToolStripItemClickedEventArgs^ e)
    {
        this->closeHelperForms();
    }

           // Shows the save dialog with a fresh date-and-time-based file name suggestion.
           // Local time on purpose (file names should match the user's clock), and with '-'
           // in the time part since ':' is not allowed in Windows file names.
    private: void showSaveGameDialog()
    {
        this->saveGameDialog->FileName = "Sudoku " + System::DateTime::Now.ToString("yyyy-MM-dd HH-mm");
        this->saveGameDialog->ShowDialog();
    }

    private: void saveToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        // A session is always saveable: a game, a solved custom puzzle, or a custom puzzle
        // still being entered (which is recoverable from its cell values alone).
        this->showSaveGameDialog();
    }

    private: void openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (!this->promptSaveIfNeeded()) return;
        this->openGameDialog->ShowDialog();
    }

    private: void minimizeToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->closeHelperForms();
        this->buttonMinimize_Click(sender, e);
    }

    private: void exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->closeHelperForms();
        this->buttonClose_Click(sender, e);
    }

    private: void newGameToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (this->newGameButton->Enabled)
        {
            this->newGameButton_Click(sender, e);
        }
    }

    private: void restartToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (this->restartButton->Enabled)
        {
            this->restartButton_Click(sender, e);
        }
    }

    private: void hintToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (this->hintButton->Enabled)
        {
            this->hintButton_Click(sender, e);
        }
    }

    private: void fixToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (this->fixButton->Enabled)
        {
            this->fixButton_Click(sender, e);
        }
    }

    private: void giveUpToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (this->giveUpButton->Enabled)
        {
            this->giveUpButton_Click(sender, e);
        }
    }

    private: void customPuzzleToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (this->customPuzzleButton->Enabled)
        {
            this->customPuzzleButton_Click(sender, e);
        }
    }

    private: void solveToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (this->solveButton->Enabled)
        {
            this->solveButton_Click(sender, e);
        }
    }

    private: void veryEasyToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->difficultyComboBox->SelectedIndex = 0;
        this->difficultyComboBox->Select();
    }

    private: void easyToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->difficultyComboBox->SelectedIndex = 1;
        this->difficultyComboBox->Select();
    }

    private: void mediumToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->difficultyComboBox->SelectedIndex = 2;
        this->difficultyComboBox->Select();
    }

    private: void hardToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->difficultyComboBox->SelectedIndex = 3;
        this->difficultyComboBox->Select();
    }

    private: void veryHardToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->difficultyComboBox->SelectedIndex = 4;
        this->difficultyComboBox->Select();
    }

    private: void aboutToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        System::String^ text = Strings::Get(StringId::DialogAboutText, this->currentLanguage);

        System::String^ build = this->buildStamp();
        if (build->Length > 0)
            text += "\n\n" + Strings::Get(StringId::DialogBuildLabel, this->currentLanguage) + build;

        MessageBox::Show(
            text,
            Strings::Get(StringId::DialogTitleAbout, this->currentLanguage),
            MessageBoxButtons::OK,
            MessageBoxIcon::None);
    }

           // Reads the UTC build stamp baked into the assembly (AssemblyInformationalVersion,
           // set from BuildInfo.h at build time). Returns an empty string if unavailable.
    private: System::String^ buildStamp()
    {
        System::Reflection::Assembly^ assembly = System::Reflection::Assembly::GetExecutingAssembly();
        System::Reflection::AssemblyInformationalVersionAttribute^ attribute =
            safe_cast<System::Reflection::AssemblyInformationalVersionAttribute^>(
                System::Attribute::GetCustomAttribute(
                    assembly, System::Reflection::AssemblyInformationalVersionAttribute::typeid));
        return attribute != nullptr ? attribute->InformationalVersion : System::String::Empty;
    }

    private: void rulesToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        MessageBox::Show(
            Strings::Get(StringId::DialogRulesText, this->currentLanguage),
            Strings::Get(StringId::DialogTitleRules, this->currentLanguage),
            MessageBoxButtons::OK,
            MessageBoxIcon::None);
    }

    private: void featuresToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        MessageBox::Show(
            Strings::Get(StringId::DialogFeaturesText, this->currentLanguage),
            Strings::Get(StringId::DialogTitleFeatures, this->currentLanguage),
            MessageBoxButtons::OK,
            MessageBoxIcon::None);
    }

    private: void hintsAndTipsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        MessageBox::Show(
            Strings::Get(StringId::DialogHintsAndTipsText, this->currentLanguage),
            Strings::Get(StringId::DialogTitleHintsAndTips, this->currentLanguage),
            MessageBoxButtons::OK,
            MessageBoxIcon::None);
    }

    private: void keyboardToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        MessageBox::Show(
            Strings::Get(StringId::DialogKeyboardText, this->currentLanguage),
            Strings::Get(StringId::DialogTitleKeyboard, this->currentLanguage),
            MessageBoxButtons::OK,
            MessageBoxIcon::None);
    }

    private: void difficultyComboBox_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        this->closeHelperForms();
    }

           // Single choke point for difficulty changes: the menu items, startup restore, and
           // save-file loads all set the combo index, which funnels through here.
    private: void difficultyComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
    {
        // Index is -1 transiently while setLanguage rebuilds the combo items
        if (this->difficultyComboBox->SelectedIndex < 0) return;

        unsigned int newDifficulty = (unsigned int)this->difficultyComboBox->SelectedIndex;

        // Persist only on an actual change, so re-selections (startup restore, language
        // switch re-populating the combo) do not cause redundant registry writes
        if (newDifficulty != this->selectedDifficulty)
        {
            this->selectedDifficulty = newDifficulty;
            Settings::SaveDifficulty(newDifficulty);
        }

        this->updateDifficultyMenuChecks();
    }

           // Reflects the selected difficulty in the Options menu, like the language checkmarks
    private: void updateDifficultyMenuChecks()
    {
        this->veryEasyToolStripMenuItem->Checked = (this->selectedDifficulty == 0);
        this->easyToolStripMenuItem->Checked = (this->selectedDifficulty == 1);
        this->mediumToolStripMenuItem->Checked = (this->selectedDifficulty == 2);
        this->hardToolStripMenuItem->Checked = (this->selectedDifficulty == 3);
        this->veryHardToolStripMenuItem->Checked = (this->selectedDifficulty == 4);
    }

    private: void buttonMinimize_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->closeHelperForms();

        this->WindowState = FormWindowState::Minimized;
    }

           // Pause the play timer while minimized and resume when restored, so time away from the
           // board is not counted. Only resumes if the game is still in progress (a finished game's
           // timer is already stopped and must stay so).
    protected: virtual void OnResize(System::EventArgs^ e) override
    {
        Form::OnResize(e);

        if (this->gameTimer == nullptr) return; // may fire during construction

        if (this->WindowState == FormWindowState::Minimized)
            this->gameTimer->stop();
        else if (this->WindowState == FormWindowState::Normal && !this->isGameFinished())
            this->gameTimer->resume();
    }

    private: void buttonClose_Click(System::Object^ sender, System::EventArgs^ e)
    {
        // The save prompt and shutdown work live in OnFormClosing, so every close
        // path (this button, menu Exit, Alt+F4, taskbar close, OS shutdown) is covered.
        this->Close();
    }

           // Single choke point for closing the application, no matter how it was initiated.
    protected: virtual void OnFormClosing(System::Windows::Forms::FormClosingEventArgs^ e) override
    {
        // Auto-save the session for a silent resume on the next launch; only if that
        // fails do we fall back to asking the user to save manually.
        if (!this->tryAutoSave() && !this->promptSaveIfNeeded())
        {
            e->Cancel = true;
            return;
        }

        this->closeHelperForms();

        // Remember where the window was, but never a minimized position (-32000, -32000)
        if (this->WindowState == FormWindowState::Normal)
            Settings::SaveWindowPosition(this->Left, this->Top);

        Form::OnFormClosing(e);
    }

    private: void SudokuForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        this->closeHelperForms();
        this->dragger->onMouseDown(e);
    }

    private: void SudokuForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        this->dragger->onMouseMove(e);
    }

    private: void SudokuForm_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        this->closeHelperForms();
        this->dragger->onMouseUp();
    }

    private: void menuStrip_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        this->SudokuForm_MouseDown(sender, e);
    }

    private: void menuStrip_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        this->SudokuForm_MouseMove(sender, e);
    }

    private: void menuStrip_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        this->SudokuForm_MouseUp(sender, e);
    }

    private: void timerLabel_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        this->SudokuForm_MouseDown(sender, e);
    }

    private: void timerLabel_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        this->SudokuForm_MouseMove(sender, e);
    }

    private: void timerLabel_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        this->SudokuForm_MouseUp(sender, e);
    }

           // Ticks a few times a second to refresh the elapsed-time readout. The display simply
           // mirrors gameTimer->Elapsed, so it freezes automatically whenever the clock is paused
           // (minimize) or stopped (game over) without any extra coordination.
    private: System::Void clockTimer_Tick(System::Object^ sender, System::EventArgs^ e)
    {
        this->updateTimerDisplay();
    }

    private: void updateTimerDisplay()
    {
        if (this->gameTimer == nullptr) return; // ticks can fire before the timer is constructed

        // Enter Puzzle (Solver) mode is not a timed challenge, so the clock is hidden there.
        // Hiding also suppresses its tooltip (a hidden control gets no hover), which matches how
        // disabled buttons behave. The clock keeps running under the hood regardless.
        bool solver = (this->session->mode == GameMode::Solver);
        this->timerLabel->Visible = !solver;
        if (solver) return;

        System::String^ text = this->formatElapsed(this->gameTimer->Elapsed);
        if (!this->timerLabel->Text->Equals(text)) // only repaint when the shown second changes
            this->timerLabel->Text = text;
    }

    private: void buttonKeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
    {
        if (this->hintMode) return;

        unsigned int choice = 0;
        if (e->KeyChar >= '1' && e->KeyChar <= '9')
            choice = e->KeyChar - '0';
        else if (e->KeyChar == '\b' || e->KeyChar == '0')
            choice = 0;
        else
            return; // includes bare 'p'/'P' (Ctrl+P is handled in buttonKeyDown) and other keys

        int index;
        if (!this->cellIndex->TryGetValue(safe_cast<Button^>(sender), index)) return;

        // choiceMade ignores no-op edits itself, so there is no need to pre-compute a change flag.
        this->choiceMade(index + 1, choice);
    }

           // Serializes the current game state (any state is saveable) to the given file.
           // Returns true on success, false on any failure - reporting is up to the caller.
    private: bool saveGameToFile(System::String^ path)
    {
        // gameFinished (from the controls) and elapsedSeconds (from the timer) are the only two
        // pieces the session does not own; the mapper builds the rest of the snapshot.
        SavedGame^ game = SavedGameMapper::Capture(
            this->session, this->isGameFinished(), (unsigned int)this->gameTimer->Elapsed.TotalSeconds);

        try
        {
            SaveGameStore::Save(path, game);
            return true;
        }
        catch (System::Exception^)
        {
            return false;
        }
    }

    private: void saveGameDialog_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e)
    {
        if (!this->saveGameToFile(this->saveGameDialog->FileName))
        {
            this->showNotification(Strings::Get(StringId::NotifyFileSaveError, this->currentLanguage));
        }
    }

           // Loads and applies a save file the user explicitly asked for (Open dialog or a
           // command-line / shell file argument), reporting any failure. Returns true on success.
    private: bool loadGameFromFile(System::String^ path)
    {
        SavedGame^ save = nullptr;
        try
        {
            save = SaveGameStore::Load(path, this->numberOfCells);
        }
        catch (UnsupportedSaveVersionException^ ex)
        {
            this->showNotification(
                Strings::Get(StringId::NotifyUnsupportedVersion, this->currentLanguage) + ex->FileVersion);
            return false;
        }
        catch (System::Exception^)
        {
            this->showNotification(Strings::Get(StringId::NotifyFileLoadError, this->currentLanguage));
            return false;
        }

        try
        {
            this->applyLoadedGame(save);
            return true;
        }
        catch (System::Exception^)
        {
            this->showNotification(Strings::Get(StringId::NotifyFileLoadError, this->currentLanguage));
            return false;
        }
    }

    private: void openGameDialog_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e)
    {
        this->loadGameFromFile(this->openGameDialog->FileName);
    }

           // Applies a validated SavedGame to the session, board, and controls. Throws on any
           // failure; callers decide whether that is reported (explicit Open) or silently
           // recovered from (auto-save resume).
    private: void applyLoadedGame(SavedGame^ save)
    {
        this->engine->clear();
        this->clearActiveModes();
        this->undoManager->clear();

        // Restore all session and board data from the save (pure data mapping).
        SavedGameMapper::Restore(save, this->session);

        // Everything below is UI that follows from the restored state.
        this->difficultyComboBox->SelectedIndex = save->difficulty;
        this->setGameControls(
            this->session->mode == GameMode::Game && !save->gameFinished,
            this->session->mode == GameMode::Game,
            this->session->mode == GameMode::Solver && !save->gameFinished);

        // Resuming an unfinished game means continuing to play it under the current setting,
        // so that level counts too (recordCandidateLevel is a no-op once the game is finished).
        this->recordCandidateLevel(this->candidateDisplay);

        this->renderAll();

        // Clipboard controls follow from the restored session state: a solved custom puzzle
        // (puzzle snapshot present) offers Copy Solution, an in-progress one offers Paste.
        this->updateClipboardControls();

        // Restore the play time; it only keeps ticking while the game is still playable.
        this->gameTimer->restore(System::TimeSpan::FromSeconds((double)save->elapsedSeconds));
        if (!save->gameFinished)
            this->gameTimer->resume();
    }

           // Full path of the auto-save file, in the user's local (non-roaming) app data folder:
           // machine-local app state the user does not manage by hand belongs there, not in
           // Documents (user files) or next to the executable (write-protected).
    private: System::String^ autoSavePath()
    {
        return System::IO::Path::Combine(
            System::Environment::GetFolderPath(System::Environment::SpecialFolder::LocalApplicationData),
            "Sudoku 3", "autosave.sdk3");
    }

           // Attempts to auto-save the current session on exit. Returns true on success;
           // failures are silent - the caller falls back to the interactive save prompt.
    private: bool tryAutoSave()
    {
        try
        {
            System::String^ path = this->autoSavePath();
            System::IO::Directory::CreateDirectory(System::IO::Path::GetDirectoryName(path));
            return this->saveGameToFile(path);
        }
        catch (System::Exception^)
        {
            return false;
        }
    }

           // Attempts to resume the session auto-saved when the app last closed.
           // Returns true on success. Failures are silent: no auto-save simply means starting
           // fresh, and an unreadable one is deleted so it cannot fail again next launch.
    private: bool tryResumeAutoSave()
    {
        System::String^ path = this->autoSavePath();
        try
        {
            if (!System::IO::File::Exists(path))
                return false;

            SavedGame^ save = SaveGameStore::Load(path, this->numberOfCells);
            this->applyLoadedGame(save);
            return true;
        }
        catch (System::Exception^)
        {
            try { System::IO::File::Delete(path); }
            catch (System::Exception^) { /* leave it; next launch will try again */ }
            return false;
        }
    }
    private: System::Void timerLabel_Click(System::Object^ sender, System::EventArgs^ e) {}
    };
}
