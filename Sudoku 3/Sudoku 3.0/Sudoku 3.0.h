// Danylo Fitel 2013

#pragma once

#include "Numbers.h"
#include "SavedGame.h"
#include "SudokuEngine.h"
#include "Strings.h"

namespace Sudoku_3_0
{
    using namespace System;
    using namespace System::IO;
    using namespace System::Drawing;
    using namespace System::Runtime::Serialization::Formatters::Binary;
    using namespace System::Windows::Forms;

    // Active game mode
    enum class GameMode : unsigned int
    {
        None = 0, // No active game (initial state or finished)
        Game = 1, // Standard puzzle game session
        Solver = 2, // Custom puzzle solver session
    };

    /// <summary>
    /// Sudoku game form
    /// </summary>
    public ref class SudokuForm : public System::Windows::Forms::Form
    {
    public:
        SudokuForm(void) : sizeFactor(3), boardSize(sizeFactor * sizeFactor), numberOfCells(boardSize * boardSize)
        {
            InitializeComponent();
            this->initialize();
        }

    protected:
        ~SudokuForm()
        {
            delete engine;
            engine = nullptr;
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
    private: static const System::Drawing::Color hintButtonColor = Color::Orange;
    private: static const System::Drawing::Color giveUpColor = Color::Red;
    private: static const System::Drawing::Color solveColor = Color::DarkCyan;
    private: static const System::Drawing::Color defaultBackColor = SystemColors::Menu;
    private: static const System::Drawing::Color conflictBackColor = Color::Red;
    private: static const System::Drawing::Color conflictBackColorImmutable = Color::LightCoral;

           // Size of the board
    private: const unsigned int sizeFactor;
    private: const unsigned int boardSize;
    private: const unsigned int numberOfCells;

           // Sudoku engine
    private: SudokuGameEngine::SudokuEngine<>* engine;

           // Access to buttons by their numbers
    private: array<System::Windows::Forms::Button^>^ cells;

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
    private: System::Windows::Forms::Label^ difficultyLabel;
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
    private: System::Windows::Forms::ToolStripMenuItem^ solveToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ pencilToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ optionsToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ difficultyToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ languageToolStripMenuItem;
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

           // Dialogs
    private: System::Windows::Forms::SaveFileDialog^ saveGameDialog;
    private: System::Windows::Forms::OpenFileDialog^ openGameDialog;

           // Numbers form
    private: Sudoku_3_0::Numbers^ numbersForm;

           // Numbers form active
    private: bool numbersFormActive;

           // Number of filled cells
    private: unsigned int numberOfFilledCells;

           // State of the hint
    private: bool isHint;

           // Number of hints used so far
    private: unsigned int numberOfHints;

           // Number of times Fix was used so far
    private: unsigned int numberOfFixes;

           // Active game mode
    private: GameMode gameMode;

           // Difficulty level of current puzzle
    private: unsigned int currentDifficulty;

           // Whether the user has given up at least once on this puzzle
    private: bool hasGivenUp;

           // Whether the user has used Fix at least once on this puzzle
    private: bool hasUsedFix;

           // Session-only win streak (resets to zero on give-up or start of new game)
    private: unsigned int winStreak;

           // Undo stack: each entry is (cellIndex, previousText, previousPencilMarks).
           // Atomic batch operations (e.g. Fix) are bracketed by two sentinel entries
           // (cellIndex == undoGroupSentinel): one pushed first (bottom) and one pushed last (top).
    private: System::Collections::Generic::Stack<System::Tuple<unsigned int, System::String^, int>^>^ undoStack;

           // Sentinel cellIndex value marking a batch boundary in the undo stack
    private: static const unsigned int undoGroupSentinel = UINT_MAX;

           // Active UI language
    private: Language currentLanguage;

           // Pencil mark bitmask per cell: bit N set means digit N is marked (bits 1-9)
    private: array<int>^ pencilMarks;

           // Whether pencil mode is active
    private: bool pencilMode;

           // Dragging state
    private: bool dragging;
    private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator1;
    private: Point offset;

#pragma region Windows Form Designer generated code

           void InitializeComponent(void)
           {
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
               this->difficultyLabel = (gcnew System::Windows::Forms::Label());
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
               this->customPuzzleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->copyPuzzleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->pastePuzzleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->solveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->undoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->difficultyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->veryEasyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->easyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->mediumToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->hardToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->veryHardToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->languageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->englishToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->ukrainianToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
               this->button1->Click += gcnew System::EventHandler(this, &SudokuForm::button1_Click);
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
               this->button2->Click += gcnew System::EventHandler(this, &SudokuForm::button2_Click);
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
               this->button3->Click += gcnew System::EventHandler(this, &SudokuForm::button3_Click);
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
               this->button4->Click += gcnew System::EventHandler(this, &SudokuForm::button4_Click);
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
               this->button5->Click += gcnew System::EventHandler(this, &SudokuForm::button5_Click);
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
               this->button6->Click += gcnew System::EventHandler(this, &SudokuForm::button6_Click);
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
               this->button7->Click += gcnew System::EventHandler(this, &SudokuForm::button7_Click);
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
               this->button8->Click += gcnew System::EventHandler(this, &SudokuForm::button8_Click);
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
               this->button9->Click += gcnew System::EventHandler(this, &SudokuForm::button9_Click);
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
               this->button10->Click += gcnew System::EventHandler(this, &SudokuForm::button10_Click);
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
               this->button11->Click += gcnew System::EventHandler(this, &SudokuForm::button11_Click);
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
               this->button12->Click += gcnew System::EventHandler(this, &SudokuForm::button12_Click);
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
               this->button13->Click += gcnew System::EventHandler(this, &SudokuForm::button13_Click);
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
               this->button14->Click += gcnew System::EventHandler(this, &SudokuForm::button14_Click);
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
               this->button15->Click += gcnew System::EventHandler(this, &SudokuForm::button15_Click);
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
               this->button16->Click += gcnew System::EventHandler(this, &SudokuForm::button16_Click);
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
               this->button17->Click += gcnew System::EventHandler(this, &SudokuForm::button17_Click);
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
               this->button18->Click += gcnew System::EventHandler(this, &SudokuForm::button18_Click);
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
               this->button19->Click += gcnew System::EventHandler(this, &SudokuForm::button19_Click);
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
               this->button20->Click += gcnew System::EventHandler(this, &SudokuForm::button20_Click);
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
               this->button21->Click += gcnew System::EventHandler(this, &SudokuForm::button21_Click);
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
               this->button22->Click += gcnew System::EventHandler(this, &SudokuForm::button22_Click);
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
               this->button23->Click += gcnew System::EventHandler(this, &SudokuForm::button23_Click);
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
               this->button24->Click += gcnew System::EventHandler(this, &SudokuForm::button24_Click);
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
               this->button25->Click += gcnew System::EventHandler(this, &SudokuForm::button25_Click);
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
               this->button26->Click += gcnew System::EventHandler(this, &SudokuForm::button26_Click);
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
               this->button27->Click += gcnew System::EventHandler(this, &SudokuForm::button27_Click);
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
               this->button28->Click += gcnew System::EventHandler(this, &SudokuForm::button28_Click);
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
               this->button29->Click += gcnew System::EventHandler(this, &SudokuForm::button29_Click);
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
               this->button30->Click += gcnew System::EventHandler(this, &SudokuForm::button30_Click);
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
               this->button31->Click += gcnew System::EventHandler(this, &SudokuForm::button31_Click);
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
               this->button32->Click += gcnew System::EventHandler(this, &SudokuForm::button32_Click);
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
               this->button33->Click += gcnew System::EventHandler(this, &SudokuForm::button33_Click);
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
               this->button34->Click += gcnew System::EventHandler(this, &SudokuForm::button34_Click);
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
               this->button35->Click += gcnew System::EventHandler(this, &SudokuForm::button35_Click);
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
               this->button36->Click += gcnew System::EventHandler(this, &SudokuForm::button36_Click);
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
               this->button37->Click += gcnew System::EventHandler(this, &SudokuForm::button37_Click);
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
               this->button38->Click += gcnew System::EventHandler(this, &SudokuForm::button38_Click);
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
               this->button39->Click += gcnew System::EventHandler(this, &SudokuForm::button39_Click);
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
               this->button40->Click += gcnew System::EventHandler(this, &SudokuForm::button40_Click);
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
               this->button41->Click += gcnew System::EventHandler(this, &SudokuForm::button41_Click);
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
               this->button42->Click += gcnew System::EventHandler(this, &SudokuForm::button42_Click);
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
               this->button43->Click += gcnew System::EventHandler(this, &SudokuForm::button43_Click);
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
               this->button44->Click += gcnew System::EventHandler(this, &SudokuForm::button44_Click);
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
               this->button45->Click += gcnew System::EventHandler(this, &SudokuForm::button45_Click);
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
               this->button46->Click += gcnew System::EventHandler(this, &SudokuForm::button46_Click);
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
               this->button47->Click += gcnew System::EventHandler(this, &SudokuForm::button47_Click);
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
               this->button48->Click += gcnew System::EventHandler(this, &SudokuForm::button48_Click);
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
               this->button49->Click += gcnew System::EventHandler(this, &SudokuForm::button49_Click);
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
               this->button50->Click += gcnew System::EventHandler(this, &SudokuForm::button50_Click);
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
               this->button51->Click += gcnew System::EventHandler(this, &SudokuForm::button51_Click);
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
               this->button52->Click += gcnew System::EventHandler(this, &SudokuForm::button52_Click);
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
               this->button53->Click += gcnew System::EventHandler(this, &SudokuForm::button53_Click);
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
               this->button54->Click += gcnew System::EventHandler(this, &SudokuForm::button54_Click);
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
               this->button55->Click += gcnew System::EventHandler(this, &SudokuForm::button55_Click);
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
               this->button56->Click += gcnew System::EventHandler(this, &SudokuForm::button56_Click);
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
               this->button57->Click += gcnew System::EventHandler(this, &SudokuForm::button57_Click);
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
               this->button58->Click += gcnew System::EventHandler(this, &SudokuForm::button58_Click);
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
               this->button59->Click += gcnew System::EventHandler(this, &SudokuForm::button59_Click);
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
               this->button60->Click += gcnew System::EventHandler(this, &SudokuForm::button60_Click);
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
               this->button61->Click += gcnew System::EventHandler(this, &SudokuForm::button61_Click);
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
               this->button62->Click += gcnew System::EventHandler(this, &SudokuForm::button62_Click);
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
               this->button63->Click += gcnew System::EventHandler(this, &SudokuForm::button63_Click);
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
               this->button64->Click += gcnew System::EventHandler(this, &SudokuForm::button64_Click);
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
               this->button65->Click += gcnew System::EventHandler(this, &SudokuForm::button65_Click);
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
               this->button66->Click += gcnew System::EventHandler(this, &SudokuForm::button66_Click);
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
               this->button67->Click += gcnew System::EventHandler(this, &SudokuForm::button67_Click);
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
               this->button68->Click += gcnew System::EventHandler(this, &SudokuForm::button68_Click);
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
               this->button69->Click += gcnew System::EventHandler(this, &SudokuForm::button69_Click);
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
               this->button70->Click += gcnew System::EventHandler(this, &SudokuForm::button70_Click);
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
               this->button71->Click += gcnew System::EventHandler(this, &SudokuForm::button71_Click);
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
               this->button72->Click += gcnew System::EventHandler(this, &SudokuForm::button72_Click);
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
               this->button73->Click += gcnew System::EventHandler(this, &SudokuForm::button73_Click);
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
               this->button74->Click += gcnew System::EventHandler(this, &SudokuForm::button74_Click);
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
               this->button75->Click += gcnew System::EventHandler(this, &SudokuForm::button75_Click);
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
               this->button76->Click += gcnew System::EventHandler(this, &SudokuForm::button76_Click);
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
               this->button77->Click += gcnew System::EventHandler(this, &SudokuForm::button77_Click);
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
               this->button78->Click += gcnew System::EventHandler(this, &SudokuForm::button78_Click);
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
               this->button79->Click += gcnew System::EventHandler(this, &SudokuForm::button79_Click);
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
               this->button80->Click += gcnew System::EventHandler(this, &SudokuForm::button80_Click);
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
               this->button81->Click += gcnew System::EventHandler(this, &SudokuForm::button81_Click);
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
               // difficultyLabel
               // 
               this->difficultyLabel->AutoSize = true;
               this->difficultyLabel->BackColor = System::Drawing::SystemColors::Menu;
               this->difficultyLabel->Font = (gcnew System::Drawing::Font(L"Calibri", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(0)));
               this->difficultyLabel->Location = System::Drawing::Point(760, 54);
               this->difficultyLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
               this->difficultyLabel->Name = L"difficultyLabel";
               this->difficultyLabel->Size = System::Drawing::Size(116, 35);
               this->difficultyLabel->TabIndex = 84;
               this->difficultyLabel->Text = L"Difficulty";
               this->difficultyLabel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SudokuForm::difficultyLabel_MouseDown);
               this->difficultyLabel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &SudokuForm::difficultyLabel_MouseMove);
               this->difficultyLabel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &SudokuForm::difficultyLabel_MouseUp);
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
               this->difficultyComboBox->Location = System::Drawing::Point(701, 100);
               this->difficultyComboBox->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->difficultyComboBox->Name = L"difficultyComboBox";
               this->difficultyComboBox->Size = System::Drawing::Size(240, 43);
               this->difficultyComboBox->TabIndex = 86;
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
               this->hintButton->TabIndex = 89;
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
               this->fixButton->TabIndex = 90;
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
               this->giveUpButton->TabIndex = 91;
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
               this->customPuzzleButton->Location = System::Drawing::Point(701, 468);
               this->customPuzzleButton->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->customPuzzleButton->Name = L"customPuzzleButton";
               this->customPuzzleButton->Size = System::Drawing::Size(240, 43);
               this->customPuzzleButton->TabIndex = 93;
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
               this->solveButton->Location = System::Drawing::Point(701, 519);
               this->solveButton->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->solveButton->Name = L"solveButton";
               this->solveButton->Size = System::Drawing::Size(240, 43);
               this->solveButton->TabIndex = 94;
               this->solveButton->Text = L"Solve";
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
               this->undoButton->Location = System::Drawing::Point(701, 570);
               this->undoButton->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->undoButton->Name = L"undoButton";
               this->undoButton->Size = System::Drawing::Size(240, 43);
               this->undoButton->TabIndex = 96;
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
               this->pencilButton->TabIndex = 95;
               this->pencilButton->Text = L"Pencil";
               this->pencilButton->UseVisualStyleBackColor = false;
               this->pencilButton->Click += gcnew System::EventHandler(this, &SudokuForm::pencilButton_Click);
               // 
               // saveGameDialog
               // 
               this->saveGameDialog->DefaultExt = L"sdk3";
               this->saveGameDialog->Title = L"Current game";
               this->saveGameDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &SudokuForm::saveGameDialog_FileOk);
               // 
               // openGameDialog
               // 
               this->openGameDialog->FileName = L"openFileDialog";
               this->openGameDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &SudokuForm::openGameDialog_FileOk);
               // 
               // menuStrip
               // 
               this->menuStrip->AccessibleRole = System::Windows::Forms::AccessibleRole::MenuBar;
               this->menuStrip->AllowMerge = false;
               this->menuStrip->BackColor = System::Drawing::SystemColors::ButtonFace;
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
               this->gameToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(11) {
                   this->newGameToolStripMenuItem,
                       this->restartToolStripMenuItem, this->pencilToolStripMenuItem, this->hintToolStripMenuItem, this->fixToolStripMenuItem, this->giveUpToolStripMenuItem,
                       this->customPuzzleToolStripMenuItem, this->copyPuzzleToolStripMenuItem, this->pastePuzzleToolStripMenuItem, this->solveToolStripMenuItem,
                       this->undoToolStripMenuItem
               });
               this->gameToolStripMenuItem->Name = L"gameToolStripMenuItem";
               this->gameToolStripMenuItem->Size = System::Drawing::Size(74, 32);
               this->gameToolStripMenuItem->Text = L"Game";
               // 
               // newGameToolStripMenuItem
               // 
               this->newGameToolStripMenuItem->Name = L"newGameToolStripMenuItem";
               this->newGameToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
               this->newGameToolStripMenuItem->Size = System::Drawing::Size(272, 34);
               this->newGameToolStripMenuItem->Text = L"New Game";
               this->newGameToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::newGameToolStripMenuItem_Click);
               // 
               // restartToolStripMenuItem
               // 
               this->restartToolStripMenuItem->Name = L"restartToolStripMenuItem";
               this->restartToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::R));
               this->restartToolStripMenuItem->Size = System::Drawing::Size(272, 34);
               this->restartToolStripMenuItem->Text = L"Restart";
               this->restartToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::restartToolStripMenuItem_Click);
               // 
               // pencilToolStripMenuItem
               // 
               this->pencilToolStripMenuItem->Name = L"pencilToolStripMenuItem";
               this->pencilToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::P));
               this->pencilToolStripMenuItem->Size = System::Drawing::Size(272, 34);
               this->pencilToolStripMenuItem->Text = L"Pencil";
               this->pencilToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::pencilToolStripMenuItem_Click);
               // 
               // hintToolStripMenuItem
               // 
               this->hintToolStripMenuItem->Name = L"hintToolStripMenuItem";
               this->hintToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::H));
               this->hintToolStripMenuItem->Size = System::Drawing::Size(272, 34);
               this->hintToolStripMenuItem->Text = L"Hint";
               this->hintToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::hintToolStripMenuItem_Click);
               // 
               // fixToolStripMenuItem
               // 
               this->fixToolStripMenuItem->Name = L"fixToolStripMenuItem";
               this->fixToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::F));
               this->fixToolStripMenuItem->Size = System::Drawing::Size(272, 34);
               this->fixToolStripMenuItem->Text = L"Fix";
               this->fixToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::fixToolStripMenuItem_Click);
               // 
               // giveUpToolStripMenuItem
               // 
               this->giveUpToolStripMenuItem->Name = L"giveUpToolStripMenuItem";
               this->giveUpToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::G));
               this->giveUpToolStripMenuItem->Size = System::Drawing::Size(272, 34);
               this->giveUpToolStripMenuItem->Text = L"Give Up";
               this->giveUpToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::giveUpToolStripMenuItem_Click);
               // 
               // customPuzzleToolStripMenuItem
               // 
               this->customPuzzleToolStripMenuItem->Name = L"customPuzzleToolStripMenuItem";
               this->customPuzzleToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::E));
               this->customPuzzleToolStripMenuItem->Size = System::Drawing::Size(272, 34);
               this->customPuzzleToolStripMenuItem->Text = L"Enter Puzzle";
               this->customPuzzleToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::customPuzzleToolStripMenuItem_Click);
               // 
               // copyPuzzleToolStripMenuItem
               // 
               this->copyPuzzleToolStripMenuItem->Enabled = false;
               this->copyPuzzleToolStripMenuItem->Name = L"copyPuzzleToolStripMenuItem";
               this->copyPuzzleToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::C));
               this->copyPuzzleToolStripMenuItem->Size = System::Drawing::Size(272, 34);
               this->copyPuzzleToolStripMenuItem->Text = L"Copy Puzzle";
               this->copyPuzzleToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::copyPuzzleToolStripMenuItem_Click);
               // 
               // pastePuzzleToolStripMenuItem
               // 
               this->pastePuzzleToolStripMenuItem->Enabled = false;
               this->pastePuzzleToolStripMenuItem->Name = L"pastePuzzleToolStripMenuItem";
               this->pastePuzzleToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::V));
               this->pastePuzzleToolStripMenuItem->Size = System::Drawing::Size(272, 34);
               this->pastePuzzleToolStripMenuItem->Text = L"Paste Puzzle";
               this->pastePuzzleToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::pastePuzzleToolStripMenuItem_Click);
               // 
               // solveToolStripMenuItem
               // 
               this->solveToolStripMenuItem->Name = L"solveToolStripMenuItem";
               this->solveToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::L));
               this->solveToolStripMenuItem->Size = System::Drawing::Size(272, 34);
               this->solveToolStripMenuItem->Text = L"Solve";
               this->solveToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::solveToolStripMenuItem_Click);
               // 
               // undoToolStripMenuItem
               // 
               this->undoToolStripMenuItem->Name = L"undoToolStripMenuItem";
               this->undoToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Z));
               this->undoToolStripMenuItem->Size = System::Drawing::Size(272, 34);
               this->undoToolStripMenuItem->Text = L"Undo";
               this->undoToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::undoToolStripMenuItem_Click);
               // 
               // optionsToolStripMenuItem
               // 
               this->optionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
                   this->difficultyToolStripMenuItem,
                       this->languageToolStripMenuItem
               });
               this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
               this->optionsToolStripMenuItem->Size = System::Drawing::Size(92, 32);
               this->optionsToolStripMenuItem->Text = L"Options";
               // 
               // difficultyToolStripMenuItem
               // 
               this->difficultyToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
                   this->veryEasyToolStripMenuItem,
                       this->easyToolStripMenuItem, this->mediumToolStripMenuItem, this->hardToolStripMenuItem, this->veryHardToolStripMenuItem
               });
               this->difficultyToolStripMenuItem->Name = L"difficultyToolStripMenuItem";
               this->difficultyToolStripMenuItem->Size = System::Drawing::Size(191, 34);
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
               // languageToolStripMenuItem
               // 
               this->languageToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
                   this->englishToolStripMenuItem,
                       this->ukrainianToolStripMenuItem
               });
               this->languageToolStripMenuItem->Name = L"languageToolStripMenuItem";
               this->languageToolStripMenuItem->Size = System::Drawing::Size(191, 34);
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
               this->clipboardButton->TabIndex = 97;
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
               this->Controls->Add(this->difficultyLabel);
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

    private: void setGameControls(bool hint, bool fix, bool giveUp, bool solve)
    {
        this->hintButton->Enabled = hint;
        this->fixButton->Enabled = fix;
        this->giveUpButton->Enabled = giveUp;
        this->solveButton->Enabled = solve;
        this->pencilButton->Enabled = hint;
        this->hintToolStripMenuItem->Enabled = hint;
        this->fixToolStripMenuItem->Enabled = fix;
        this->giveUpToolStripMenuItem->Enabled = giveUp;
        this->solveToolStripMenuItem->Enabled = solve;
        this->pencilToolStripMenuItem->Enabled = hint;
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
        this->numbersForm->Visible = true;
        this->numbersForm->Visible = false;

        // Initialize dragging state
        this->dragging = false;
        this->offset = this->Location;

        // Initialize cells
        this->cells = gcnew array<System::Windows::Forms::Button^>(this->numberOfCells);
        this->initializeCells();

        // Initialize the form
        this->numbersFormActive = false;
        this->numberOfFilledCells = 0;
        this->isHint = false;
        this->numberOfHints = 0;
        this->numberOfFixes = 0;
        this->hasGivenUp = false;
        this->hasUsedFix = false;
        this->winStreak = 0;
        this->pencilMarks = gcnew array<int>(this->numberOfCells);
        this->pencilMode = false;
        this->undoStack = gcnew System::Collections::Generic::Stack<System::Tuple<unsigned int, System::String^, int>^>();
        this->gameMode = GameMode::None;
        this->currentDifficulty = 2;
        this->currentLanguage = Language::English;
        this->difficultyComboBox->SelectedIndex = currentDifficulty;
        this->applyLanguage();

        // Wire Paint events for pencil marks on each cell
        for each (System::Windows::Forms::Button ^ cell in this->cells)
        {
            cell->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &SudokuForm::cell_Paint);
        }

        // Start a new game
        this->newGame(SudokuGameEngine::DifficultyLevel::Medium);
    }

           // Apply the current language to all UI controls and update the language menu checkmarks
    private: void applyLanguage()
    {
        Language lang = this->currentLanguage;

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

        // Difficulty label
        this->difficultyLabel->Text = Strings::Get(StringId::LabelDifficulty, lang);

        // Difficulty combo items
        int sel = this->difficultyComboBox->SelectedIndex;
        this->difficultyComboBox->Items->Clear();
        this->difficultyComboBox->Items->Add(Strings::Get(StringId::DifficultyVeryEasy, lang));
        this->difficultyComboBox->Items->Add(Strings::Get(StringId::DifficultyEasy, lang));
        this->difficultyComboBox->Items->Add(Strings::Get(StringId::DifficultyMedium, lang));
        this->difficultyComboBox->Items->Add(Strings::Get(StringId::DifficultyHard, lang));
        this->difficultyComboBox->Items->Add(Strings::Get(StringId::DifficultyVeryHard, lang));
        this->difficultyComboBox->SelectedIndex = sel >= 0 ? sel : 2;

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
        this->customPuzzleToolStripMenuItem->Text = Strings::Get(StringId::MenuEnterPuzzle, lang);
        this->solveToolStripMenuItem->Text = Strings::Get(StringId::MenuSolve, lang);
        this->undoToolStripMenuItem->Text = Strings::Get(StringId::MenuUndo, lang);
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

        // Numbers form
        this->numbersForm->setLanguage(lang);
    }

    private: void englishToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->currentLanguage = Language::English;
        this->applyLanguage();
    }

    private: void ukrainianToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->currentLanguage = Language::Ukrainian;
        this->applyLanguage();
    }

           void initializeCells()
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
           }

           // Get cell button by its coordinates
    private: System::Windows::Forms::Button^ getButton(const unsigned int row, const unsigned int column)
    {
        return this->cells[this->boardSize * row + column];
    }

           // Clear the board
    private: void clearBoard(const bool enableCells)
    {
        this->numberOfFilledCells = 0;

        unsigned int index = 0;
        for (unsigned char i = 0; i < boardSize; ++i)
        {
            for (unsigned char j = 0; j < boardSize; ++j)
            {
                System::Windows::Forms::Button^ cell = this->cells[index];
                cell->Text = String::Empty;
                cell->ForeColor = defaultColor;
                cell->BackColor = defaultBackColor;
                cell->Enabled = enableCells;
                this->pencilMarks[index] = 0;
                ++index;
            }
        }
    }

           // Fill the board with values from the engine
    private: void fillBoardFromEngine(const bool showHiddenCells)
    {
        this->numberOfFilledCells = this->engine->numberOfFilledCells();

        unsigned int index = 0;
        for (unsigned char i = 0; i < boardSize; ++i)
        {
            for (unsigned char j = 0; j < boardSize; ++j)
            {
                System::Windows::Forms::Button^ cell = this->cells[index];
                if (showHiddenCells)
                {
                    cell->Text = ((int)engine->getCellValue(i, j)).ToString();
                }
                else
                {
                    if (engine->getFilled(i, j))
                    {
                        cell->Text = ((int)engine->operator()(i, j)).ToString();
                    }
                    else
                    {
                        cell->Text = String::Empty;
                        cell->Invalidate(); // clear any stale pencil marks painted by cell_Paint
                    }
                }

                cell->ForeColor = defaultColor;
                cell->Enabled = !engine->getFilled(i, j);
                ++index;
            }
        }
    }

           // Fill the engine with values entered by user
    private: void fillEngine()
    {
        unsigned int index = 0;
        for (unsigned char i = 0; i < boardSize; ++i)
        {
            for (unsigned char j = 0; j < boardSize; ++j)
            {
                if (cells[index]->Text->Length == 0)
                {
                    this->engine->setFilled(i, j, false);
                }
                else
                {
                    this->engine->setFilled(i, j, true);
                    this->engine->setCellValue(i, j, int::Parse(this->cells[index]->Text));
                }

                ++index;
            }
        }
    }

           // Start a new game
    private: void newGame(const SudokuGameEngine::DifficultyLevel difficulty)
    {
        // Create a new puzzle
        this->engine->newGame(difficulty);

        // Set current difficulty value
        switch (difficulty)
        {
        case SudokuGameEngine::DifficultyLevel::VeryEasy:
            this->currentDifficulty = 0;
            break;
        case SudokuGameEngine::DifficultyLevel::Easy:
            this->currentDifficulty = 1;
            break;
        case SudokuGameEngine::DifficultyLevel::Medium:
            this->currentDifficulty = 2;
            break;
        case SudokuGameEngine::DifficultyLevel::Hard:
            this->currentDifficulty = 3;
            break;
        case SudokuGameEngine::DifficultyLevel::VeryHard:
            this->currentDifficulty = 4;
            break;
        }

        // Prepare the board
        this->fillBoardFromEngine(false);
        this->gameMode = GameMode::Game;
        this->numberOfHints = 0;
        this->numberOfFixes = 0;
        this->hasGivenUp = false;
        this->hasUsedFix = false;
        this->undoStack->Clear();
        this->undoToolStripMenuItem->Enabled = false;
        this->undoButton->Enabled = false;
        this->restartButton->Enabled = true;
        this->setGameControls(true, true, true, false);
        this->updateClipboardControls();
        for (unsigned int i = 0; i < this->numberOfCells; ++i)
        {
            this->pencilMarks[i] = 0;
        }

        this->setPencilMode(false);

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

           // Check if the solution is correct
    private: const bool checkSolution()
    {
        unsigned int index = 0;
        for (unsigned char i = 0; i < this->boardSize; ++i)
        {
            for (unsigned char j = 0; j < this->boardSize; ++j)
            {
                System::Windows::Forms::Button^ cell = this->cells[index];
                if (cell->Enabled)
                {
                    if (!cell->Text->Equals(((int)this->engine->getCellValue(i, j)).ToString()))
                    {
                        return false;
                    }
                }
                ++index;
            }
        }
        return true;
    }

           // Check if the game has been finished
    private: void checkGameState()
    {
        if (this->numberOfFilledCells == this->numberOfCells)
        {
            if (this->checkSolution())
            {
                for (unsigned int i = 0; i < this->numberOfCells; ++i)
                {
                    if (this->cells[i]->Enabled)
                    {
                        this->cells[i]->Enabled = false;
                        this->cells[i]->ForeColor = correctColor;
                    }
                }

                this->disableHint();
                this->difficultyComboBox->SelectedIndex = this->currentDifficulty;
                this->setGameControls(false, false, false, false);
                this->setPencilMode(false);
                this->undoStack->Clear();
                this->undoToolStripMenuItem->Enabled = false;
                this->undoButton->Enabled = false;

                if (!this->hasGivenUp)
                {
                    ++this->winStreak;
                }
                else
                {
                    this->winStreak = 0;
                }

                System::String^ msg = "";

                bool clean = !this->hasGivenUp && this->numberOfHints == 0 && this->numberOfFixes == 0;

                if (clean)
                {
                    msg += Strings::Get(StringId::WinClean, this->currentLanguage);
                }
                else if (!this->hasGivenUp)
                {
                    msg += Strings::Get(StringId::WinWithAssists, this->currentLanguage);
                    System::Collections::Generic::List<System::String^>^ assists = gcnew System::Collections::Generic::List<System::String^>();
                    if (this->numberOfHints == 1) assists->Add(Strings::Get(StringId::WinAssistHint, this->currentLanguage));
                    else if (this->numberOfHints > 1) assists->Add(this->numberOfHints + Strings::Get(StringId::WinAssistHints, this->currentLanguage));
                    if (this->numberOfFixes == 1) assists->Add(Strings::Get(StringId::WinAssistFix, this->currentLanguage));
                    else if (this->numberOfFixes > 1) assists->Add(this->numberOfFixes + Strings::Get(StringId::WinAssistFixes, this->currentLanguage));
                    msg += " using " + System::String::Join(" and ", assists) + "!";
                }
                else
                {
                    msg += Strings::Get(StringId::WinAfterGiveUp, this->currentLanguage);
                    System::Collections::Generic::List<System::String^>^ assists = gcnew System::Collections::Generic::List<System::String^>();
                    if (this->numberOfHints == 1) assists->Add(Strings::Get(StringId::WinAssistHint, this->currentLanguage));
                    else if (this->numberOfHints > 1) assists->Add(this->numberOfHints + Strings::Get(StringId::WinAssistHints, this->currentLanguage));
                    if (this->numberOfFixes == 1) assists->Add(Strings::Get(StringId::WinAssistFix, this->currentLanguage));
                    else if (this->numberOfFixes > 1) assists->Add(this->numberOfFixes + Strings::Get(StringId::WinAssistFixes, this->currentLanguage));
                    if (assists->Count > 0)
                        msg += ", using " + System::String::Join(" and ", assists);
                    msg += ".";
                }

                msg += Strings::Get(StringId::WinDifficulty, this->currentLanguage) + this->difficultyName(this->currentDifficulty);
                if (this->winStreak > 1)
                {
                    msg += Strings::Get(StringId::WinStreak, this->currentLanguage) + this->winStreak;
                }

                this->showNotification(msg);
            }
        }
    }

           // Perform action when a cell has been chosen
    private: void cellButtonClicked(
        const unsigned int number,
        System::Object^ sender,
        System::EventArgs^ e)
    {
        this->closeHelperForms();

        // The button that has been clicked
        System::Windows::Forms::Button^ currentButton = this->cells[number - 1];

        // If this is a hint option, show the cell value
        if (this->isHint)
        {
            // Push undo entry before applying hint (saves text, marks, and hints delta)
            this->undoStack->Push(gcnew System::Tuple<unsigned int, System::String^, int>(
                number - 1, currentButton->Text, this->pencilMarks[number - 1]));
            this->undoToolStripMenuItem->Enabled = true;
            this->undoButton->Enabled = true;

            if (currentButton->Text->Length == 0)
            {
                ++(this->numberOfFilledCells);
            }

            currentButton->Text =
                ((int)this->engine->getCellValue(
                    ((number - 1) / this->boardSize),
                    ((number - 1) % this->boardSize))).ToString();
            currentButton->BackColor = defaultBackColor;
            currentButton->Enabled = false;
            currentButton->ForeColor = hintColor;
            ++(this->numberOfHints);
            this->revalidatePeers(number - 1);

            this->checkGameState();
        }
        // Else show the numbers form
        else
        {
            // Location of the numbers window
            int left(this->Left), top(this->Top);

            left += currentButton->Left;

            if (number <= this->numberOfCells / 3)
            {
                top += currentButton->Top;
            }
            else if (number <= this->numberOfCells * 2 / 3)
            {
                top += currentButton->Top + currentButton->Height - this->numbersForm->Height / 2;
            }
            else
            {
                top += currentButton->Top + currentButton->Height - this->numbersForm->Height;
            }

            // Show the number choice form
            this->numbersForm->Left = left;
            this->numbersForm->Top = top;
            this->numbersForm->setPencilMode(this->pencilMode && currentButton->Enabled);
            this->numbersForm->setCellNumber(number);
            this->numbersForm->Visible = true;
            this->numbersForm->Activate();

            // Change the form state
            this->numbersFormActive = true;
        }
    }

           // A delegate method called by the numbers form when a choice has been made
    public: void choiceMade(
        const unsigned int cellNumber,
        const bool changed,
        const unsigned int choice)
    {
        this->closeHelperForms();
        System::Windows::Forms::Button^ cell = this->cells[cellNumber - 1];

        // Pencil mode: toggle mark bit only, never touch the cell value
        if (this->pencilMode && cell->Enabled)
        {
            if (choice >= 1 && choice <= 9)
            {
                this->undoStack->Push(gcnew System::Tuple<unsigned int, System::String^, int>(
                    cellNumber - 1, cell->Text, this->pencilMarks[cellNumber - 1]));
                this->undoToolStripMenuItem->Enabled = true;
                this->undoButton->Enabled = true;
                this->pencilMarks[cellNumber - 1] ^= (1 << (int)choice);
                cell->Invalidate();
            }
            return;
        }

        if (changed)
        {
            // No-op: clearing an already-empty cell
            if (cell->Text->Length == 0 && choice == 0)
            {
                return;
            }

            this->undoToolStripMenuItem->Enabled = true;
            this->undoButton->Enabled = true;
            if (cell->Text->Length == 0)
            {
                if (choice != 0)
                {
                    auto sentinel = gcnew System::Tuple<unsigned int, System::String^, int>(undoGroupSentinel, System::String::Empty, 0);
                    this->undoStack->Push(sentinel);
                    this->undoStack->Push(gcnew System::Tuple<unsigned int, System::String^, int>(
                        cellNumber - 1, cell->Text, this->pencilMarks[cellNumber - 1]));
                    this->clearPeerPencilMarkWithUndo(cellNumber - 1, choice);
                    this->undoStack->Push(sentinel);
                    cell->Text = choice.ToString();
                    ++(this->numberOfFilledCells);
                    cell->Invalidate();
                    this->highlightCellConflict(cellNumber - 1);
                    this->revalidatePeers(cellNumber - 1);
                }
            }
            else
            {
                if (choice == 0)
                {
                    this->undoStack->Push(gcnew System::Tuple<unsigned int, System::String^, int>(
                        cellNumber - 1, cell->Text, this->pencilMarks[cellNumber - 1]));
                    cell->Text = String::Empty;
                    --(this->numberOfFilledCells);
                    cell->BackColor = defaultBackColor;
                    cell->Invalidate();
                    this->revalidatePeers(cellNumber - 1);
                }
                else
                {
                    auto sentinel = gcnew System::Tuple<unsigned int, System::String^, int>(undoGroupSentinel, System::String::Empty, 0);
                    this->undoStack->Push(sentinel);
                    this->undoStack->Push(gcnew System::Tuple<unsigned int, System::String^, int>(
                        cellNumber - 1, cell->Text, this->pencilMarks[cellNumber - 1]));
                    this->clearPeerPencilMarkWithUndo(cellNumber - 1, choice);
                    this->undoStack->Push(sentinel);
                    cell->Text = choice.ToString();
                    cell->Invalidate();
                    this->highlightCellConflict(cellNumber - 1);
                    this->revalidatePeers(cellNumber - 1);
                }
            }

            this->checkGameState();
        }
        else
        {
            this->highlightCellConflict(cellNumber - 1);
        }
    }

    private: void restoreCell(unsigned int index, System::String^ previousText, int previousMarks)
    {
        System::Windows::Forms::Button^ cell = this->cells[index];

        if (cell->Text->Length > 0 && previousText->Length == 0)
        {
            --(this->numberOfFilledCells);
        }
        else if (cell->Text->Length == 0 && previousText->Length > 0)
        {
            ++(this->numberOfFilledCells);
        }

        cell->Text = previousText;
        cell->Enabled = true;
        this->pencilMarks[index] = previousMarks;
        cell->ForeColor = defaultColor;
        cell->BackColor = defaultBackColor;
        cell->Invalidate();
        this->highlightCellConflict(index);
        this->revalidatePeers(index);
    }

    private: void performUndo()
    {
        if (this->undoStack->Count == 0) return;

        auto top = this->undoStack->Pop();

        if (top->Item1 == undoGroupSentinel)
        {
            // Batch undo: pop and restore all entries until the bottom sentinel
            System::Windows::Forms::Button^ lastCell = nullptr;
            while (this->undoStack->Count > 0)
            {
                auto entry = this->undoStack->Pop();
                if (entry->Item1 == undoGroupSentinel)
                {
                    break; // bottom sentinel reached
                }
                this->restoreCell(entry->Item1, entry->Item2, entry->Item3);
                lastCell = this->cells[entry->Item1];
            }
            if (lastCell != nullptr)
            {
                lastCell->Focus();
            }
        }
        else
        {
            // Single-cell undo
            this->restoreCell(top->Item1, top->Item2, top->Item3);
            this->cells[top->Item1]->Focus();
        }

        this->undoToolStripMenuItem->Enabled = this->undoStack->Count > 0;
        this->undoButton->Enabled = this->undoStack->Count > 0;
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
        this->setPencilMode(!this->pencilMode);
    }

    private: void setPencilMode(bool active)
    {
        if (active)
        {
            // Deactivate hint mode so both modes cannot be active simultaneously
            this->isHint = false;
            this->hintButton->ForeColor = defaultColor;
        }
        this->pencilMode = active;
        this->pencilButton->ForeColor = active ? hintButtonColor : defaultColor;
    }

    private: void pencilButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->setPencilMode(!this->pencilMode);
    }

           // Returns true if cellNumber has a conflict with any peer in its row, column, or block
    private: bool cellHasConflict(const unsigned int cellNumber)
    {
        if (this->cells[cellNumber]->Text->Length == 0)
        {
            return false;
        }

        const unsigned int rowIndex = cellNumber / this->boardSize;
        const unsigned int columnIndex = cellNumber % this->boardSize;

        unsigned int row = rowIndex * this->boardSize;
        unsigned int column = columnIndex;

        while (row < this->numberOfCells && column < this->numberOfCells)
        {
            if (row != cellNumber && this->cells[row]->Text->Equals(this->cells[cellNumber]->Text))
            {
                return true;
            }

            if (column != cellNumber && this->cells[column]->Text->Equals(this->cells[cellNumber]->Text))
            {
                return true;
            }

            row += 1;
            column += this->boardSize;
        }

        const unsigned int rBegin((rowIndex / this->sizeFactor) * this->sizeFactor);
        const unsigned int cBegin((columnIndex / this->sizeFactor) * this->sizeFactor);
        const unsigned int rEnd(rBegin + this->sizeFactor);
        const unsigned int cEnd(cBegin + this->sizeFactor);

        for (unsigned int i = rBegin; i < rEnd; ++i)
        {
            for (unsigned int j = cBegin; j < cEnd; ++j)
            {
                const unsigned int peer = i * this->boardSize + j;
                if (peer != cellNumber && this->cells[peer]->Text->Equals(this->cells[cellNumber]->Text))
                {
                    return true;
                }
            }
        }

        return false;
    }

           // Updates the background color of cellNumber to reflect its current conflict state
    private: void highlightCellConflict(const unsigned int cellNumber)
    {
        if (this->cellHasConflict(cellNumber))
        {
            this->cells[cellNumber]->BackColor = this->cells[cellNumber]->Enabled ? conflictBackColor : conflictBackColorImmutable;
        }
        else
        {
            this->cells[cellNumber]->BackColor = defaultBackColor;
        }
    }

           // Re-evaluates conflict highlighting for every cell on the board
    private: void revalidateAllCells()
    {
        for (unsigned int i = 0; i < this->numberOfCells; ++i)
        {
            this->highlightCellConflict(i);
        }
    }

           // Re-evaluates conflict highlighting for all peers of cellNumber
    private: void revalidatePeers(const unsigned int cellNumber)
    {
        const unsigned int rowIndex = cellNumber / this->boardSize;
        const unsigned int columnIndex = cellNumber % this->boardSize;

        unsigned int row = rowIndex * this->boardSize;
        unsigned int column = columnIndex;

        while (row < this->numberOfCells && column < this->numberOfCells)
        {
            if (row != cellNumber)
            {
                this->highlightCellConflict(row);
            }

            if (column != cellNumber && column != row)
            {
                this->highlightCellConflict(column);
            }

            row += 1;
            column += this->boardSize;
        }

        const unsigned int rBegin((rowIndex / this->sizeFactor) * this->sizeFactor);
        const unsigned int cBegin((columnIndex / this->sizeFactor) * this->sizeFactor);
        const unsigned int rEnd(rBegin + this->sizeFactor);
        const unsigned int cEnd(cBegin + this->sizeFactor);

        for (unsigned int i = rBegin; i < rEnd; ++i)
        {
            for (unsigned int j = cBegin; j < cEnd; ++j)
            {
                const unsigned int peer = i * this->boardSize + j;
                if (peer != cellNumber)
                {
                    this->highlightCellConflict(peer);
                }
            }
        }
    }

           // Clears the given digit from the pencil marks of all peers of cellNumber and repaints them.
           // Also pushes each modified peer's previous state onto the undo stack.
    private: void clearPeerPencilMarkWithUndo(const unsigned int cellNumber, const unsigned int digit)
    {
        const int bit = 1 << (int)digit;
        const unsigned int rowIndex = cellNumber / this->boardSize;
        const unsigned int columnIndex = cellNumber % this->boardSize;

        unsigned int row = rowIndex * this->boardSize;
        unsigned int col = columnIndex;
        while (row < this->numberOfCells && col < this->numberOfCells)
        {
            if (row != cellNumber && (this->pencilMarks[row] & bit))
            {
                this->undoStack->Push(gcnew System::Tuple<unsigned int, System::String^, int>(
                    row, this->cells[row]->Text, this->pencilMarks[row]));
                this->pencilMarks[row] &= ~bit;
                this->cells[row]->Invalidate();
            }
            if (col != cellNumber && col != row && (this->pencilMarks[col] & bit))
            {
                this->undoStack->Push(gcnew System::Tuple<unsigned int, System::String^, int>(
                    col, this->cells[col]->Text, this->pencilMarks[col]));
                this->pencilMarks[col] &= ~bit;
                this->cells[col]->Invalidate();
            }
            row += 1;
            col += this->boardSize;
        }

        const unsigned int rBegin((rowIndex / this->sizeFactor) * this->sizeFactor);
        const unsigned int cBegin((columnIndex / this->sizeFactor) * this->sizeFactor);
        for (unsigned int i = rBegin; i < rBegin + this->sizeFactor; ++i)
        {
            for (unsigned int j = cBegin; j < cBegin + this->sizeFactor; ++j)
            {
                const unsigned int peer = i * this->boardSize + j;
                if (peer != cellNumber && (this->pencilMarks[peer] & bit))
                {
                    this->undoStack->Push(gcnew System::Tuple<unsigned int, System::String^, int>(
                        peer, this->cells[peer]->Text, this->pencilMarks[peer]));
                    this->pencilMarks[peer] &= ~bit;
                    this->cells[peer]->Invalidate();
                }
            }
        }
    }

           // Clears the given digit from the pencil marks of all peers of cellNumber and repaints them
    private: void clearPeerPencilMark(const unsigned int cellNumber, const unsigned int digit)
    {
        const int bit = 1 << (int)digit;
        const unsigned int rowIndex = cellNumber / this->boardSize;
        const unsigned int columnIndex = cellNumber % this->boardSize;

        // Row and column peers
        unsigned int row = rowIndex * this->boardSize;
        unsigned int col = columnIndex;
        while (row < this->numberOfCells && col < this->numberOfCells)
        {
            if (row != cellNumber && (this->pencilMarks[row] & bit))
            {
                this->pencilMarks[row] &= ~bit;
                this->cells[row]->Invalidate();
            }
            if (col != cellNumber && col != row && (this->pencilMarks[col] & bit))
            {
                this->pencilMarks[col] &= ~bit;
                this->cells[col]->Invalidate();
            }
            row += 1;
            col += this->boardSize;
        }

        // Box peers
        const unsigned int rBegin((rowIndex / this->sizeFactor) * this->sizeFactor);
        const unsigned int cBegin((columnIndex / this->sizeFactor) * this->sizeFactor);
        for (unsigned int i = rBegin; i < rBegin + this->sizeFactor; ++i)
        {
            for (unsigned int j = cBegin; j < cBegin + this->sizeFactor; ++j)
            {
                const unsigned int peer = i * this->boardSize + j;
                if (peer != cellNumber && (this->pencilMarks[peer] & bit))
                {
                    this->pencilMarks[peer] &= ~bit;
                    this->cells[peer]->Invalidate();
                }
            }
        }
    }

           // Paints pencil marks into a cell using a 3x3 mini-grid layout
    private: void cell_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
    {
        System::Windows::Forms::Button^ cell = safe_cast<System::Windows::Forms::Button^>(sender);
        int idx = array<System::Windows::Forms::Button^>::IndexOf(this->cells, cell);
        if (idx < 0 || this->pencilMarks[idx] == 0 || cell->Text->Length > 0)
            return;

        System::Drawing::Graphics^ g = e->Graphics;
        float w = (float)cell->ClientSize.Width;
        float h = (float)cell->ClientSize.Height;
        float pad = Math::Max(2.0f, Math::Min(w, h) * 0.04f);
        float cw = (w - 2.0f * pad) / 3.0f;
        float ch = (h - 2.0f * pad) / 3.0f;

        System::Drawing::Font^ font = gcnew System::Drawing::Font("Calibri", Math::Max(6.0f, Math::Min(cw, ch) * 0.55f),
            System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point);
        System::Drawing::Brush^ brush = System::Drawing::Brushes::DimGray;

        for (int d = 1; d <= 9; ++d)
        {
            if (this->pencilMarks[idx] & (1 << d))
            {
                int col3 = (d - 1) % 3;
                int row3 = (d - 1) / 3;
                float x = pad + col3 * cw;
                float y = pad + row3 * ch;
                System::Drawing::RectangleF rect(x, y, cw, ch);
                System::Drawing::StringFormat^ sf = gcnew System::Drawing::StringFormat();
                sf->Alignment = System::Drawing::StringAlignment::Center;
                sf->LineAlignment = System::Drawing::StringAlignment::Center;
                g->DrawString(d.ToString(), font, brush, rect, sf);
            }
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
        int index = array<Button^>::IndexOf(this->cells, safe_cast<Button^>(sender));
        if (index < 0) return;

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
            if (!this->isHint)
            {
                Button^ btn = safe_cast<Button^>(sender);
                bool changed = btn->Text->Length != 0;
                this->choiceMade(index + 1, changed, 0);
                e->Handled = true;
            }
            break;
        case Keys::P:
            if (e->Control)
            {
                this->setPencilMode(!this->pencilMode);
                e->Handled = true;
                e->SuppressKeyPress = true;
            }
            break;
        }
    }

           // Prompt the user to save if a saveable game is in progress.
           // Returns true if the action should proceed, false if it was cancelled.
    private: bool promptSaveIfNeeded()
    {
        if (this->gameMode == GameMode::Game || this->gameMode == GameMode::Solver)
        {
            System::Windows::Forms::DialogResult result = MessageBox::Show(
                Strings::Get(StringId::DialogSavePrompt, this->currentLanguage),
                Strings::Get(StringId::DialogTitleSave, this->currentLanguage),
                MessageBoxButtons::YesNoCancel,
                MessageBoxIcon::Question);

            if (result == System::Windows::Forms::DialogResult::Yes)
            {
                this->saveGameDialog->ShowDialog();
            }
            else if (result == System::Windows::Forms::DialogResult::Cancel)
            {
                return false;
            }
        }
        return true;
    }

           // Close the numbers form if it is open
    private: void closeHelperForms()
    {
        // Close numbers form
        this->numbersForm->Visible = false;
        this->numbersFormActive = false;

    }

           // Enable hint mode (deactivates pencil mode so both cannot be active simultaneously)
    private: void enableHint()
    {
        this->setPencilMode(false);
        this->isHint = true;
        this->hintButton->ForeColor = hintButtonColor;
    }

           // Disable hint mode
    private: void disableHint()
    {
        this->isHint = false;
        this->hintButton->ForeColor = defaultColor;
    }

    private: void newGameButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (!this->promptSaveIfNeeded()) return;
        this->closeHelperForms();
        this->disableHint();

        SudokuGameEngine::DifficultyLevel difficulty(SudokuGameEngine::DifficultyLevel::Medium);
        switch (this->difficultyComboBox->SelectedIndex)
        {
        case 0:
            difficulty = SudokuGameEngine::DifficultyLevel::VeryEasy;
            break;
        case 1:
            difficulty = SudokuGameEngine::DifficultyLevel::Easy;
            break;
        case 2:
            difficulty = SudokuGameEngine::DifficultyLevel::Medium;
            break;
        case 3:
            difficulty = SudokuGameEngine::DifficultyLevel::Hard;
            break;
        case 4:
            difficulty = SudokuGameEngine::DifficultyLevel::VeryHard;
            break;
        }

        this->newGame(difficulty);
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
        this->disableHint();

        this->undoStack->Clear();
        this->undoToolStripMenuItem->Enabled = false;
        this->undoButton->Enabled = false;
        this->numberOfFilledCells = 0;

        // Fill the board, using the engine as the authoritative source for which cells are clues
        unsigned int index = 0;
        for (unsigned char i = 0; i < boardSize; ++i)
        {
            for (unsigned char j = 0; j < boardSize; ++j)
            {
                Button^ cell = this->cells[index];
                if (this->engine->getFilled(i, j))
                {
                    // Clue cell: keep text, restore clean appearance
                    ++this->numberOfFilledCells;
                    cell->Enabled = false;
                    cell->ForeColor = defaultColor;
                    cell->BackColor = defaultBackColor;
                }
                else
                {
                    // User cell: clear everything
                    cell->Text = System::String::Empty;
                    cell->ForeColor = defaultColor;
                    cell->BackColor = defaultBackColor;
                    cell->Enabled = true;
                    this->pencilMarks[index] = 0;
                    cell->Invalidate();
                }
                ++index;
            }
        }

        this->difficultyComboBox->SelectedIndex = this->currentDifficulty;
        this->setGameControls(true, true, true, false);
        this->setPencilMode(false);
    }

    private: void hintButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->closeHelperForms();

        if (this->isHint)
        {
            this->disableHint();
        }
        else
        {
            this->enableHint();
        }
    }

    private: void fixButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->closeHelperForms();

        if (!this->hasUsedFix)
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

            this->hasUsedFix = true;
        }

        ++this->numberOfFixes;

        auto sentinel = gcnew System::Tuple<unsigned int, System::String^, int>(undoGroupSentinel, System::String::Empty, 0);
        bool anyFixed = false;

        unsigned int index = 0;
        for (unsigned int i = 0; i < this->boardSize; ++i)
            for (unsigned int j = 0; j < this->boardSize; ++j)
            {
                if (this->cells[index]->Enabled &&
                    !this->cells[index]->Text->Equals(String::Empty) &&
                    !this->cells[index]->Text->Equals(((int)this->engine->getCellValue(i, j)).ToString()))
                {
                    if (!anyFixed)
                    {
                        // Push bottom sentinel before the first fixed-cell entry
                        this->undoStack->Push(sentinel);
                        anyFixed = true;
                    }

                    this->undoStack->Push(gcnew System::Tuple<unsigned int, System::String^, int>(
                        index, this->cells[index]->Text, this->pencilMarks[index]));

                    this->cells[index]->Text = "";
                    this->cells[index]->BackColor = defaultBackColor;
                    --(this->numberOfFilledCells);
                }

                ++index;
            }

        if (anyFixed)
        {
            // Push top sentinel to mark the end of the batch
            this->undoStack->Push(sentinel);
            this->undoToolStripMenuItem->Enabled = true;
            this->undoButton->Enabled = true;
        }

        this->revalidateAllCells();
    }

    private: void giveUpButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (!this->hasGivenUp)
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
        this->disableHint();

        this->hasGivenUp = true;
        this->winStreak = 0;

        unsigned int index = 0;
        for (unsigned char i = 0; i < boardSize; ++i)
        {
            for (unsigned char j = 0; j < boardSize; ++j)
            {
                System::Windows::Forms::Button^ cell = this->cells[index];
                if (cell->Enabled)
                {
                    if (cell->Text->Length == 0)
                    {
                        ++this->numberOfFilledCells;
                    }

                    cell->Text = ((int)engine->getCellValue(i, j)).ToString();
                    cell->BackColor = defaultBackColor;
                    cell->ForeColor = giveUpColor;
                    cell->Enabled = false;
                }

                ++index;
            }
        }

        this->difficultyComboBox->SelectedIndex = this->currentDifficulty;
        this->setGameControls(false, false, false, false);
        this->undoStack->Clear();
        this->undoToolStripMenuItem->Enabled = false;
        this->undoButton->Enabled = false;
        this->revalidateAllCells();
    }

    private: void updateClipboardControls()
    {
        if (this->gameMode == GameMode::Game)
        {
            this->clipboardButton->Text = Strings::Get(StringId::ButtonCopyPuzzle, this->currentLanguage);
            this->clipboardButton->Enabled = true;
            this->copyPuzzleToolStripMenuItem->Text = Strings::Get(StringId::MenuCopyPuzzle, this->currentLanguage);
            this->copyPuzzleToolStripMenuItem->Enabled = true;
            this->pastePuzzleToolStripMenuItem->Text = Strings::Get(StringId::MenuPastePuzzle, this->currentLanguage);
            this->pastePuzzleToolStripMenuItem->Enabled = false;
        }
        else if (this->gameMode == GameMode::Solver)
        {
            this->clipboardButton->Text = Strings::Get(StringId::ButtonPastePuzzle, this->currentLanguage);
            this->clipboardButton->Enabled = true;
            this->pastePuzzleToolStripMenuItem->Text = Strings::Get(StringId::MenuPastePuzzle, this->currentLanguage);
            this->pastePuzzleToolStripMenuItem->Enabled = true;
            this->copyPuzzleToolStripMenuItem->Text = Strings::Get(StringId::MenuCopyPuzzle, this->currentLanguage);
            this->copyPuzzleToolStripMenuItem->Enabled = false;
        }
        else
        {
            this->clipboardButton->Text = Strings::Get(StringId::ButtonCopyPuzzle, this->currentLanguage);
            this->clipboardButton->Enabled = false;
            this->copyPuzzleToolStripMenuItem->Text = Strings::Get(StringId::MenuCopyPuzzle, this->currentLanguage);
            this->copyPuzzleToolStripMenuItem->Enabled = false;
            this->pastePuzzleToolStripMenuItem->Text = Strings::Get(StringId::MenuPastePuzzle, this->currentLanguage);
            this->pastePuzzleToolStripMenuItem->Enabled = false;
        }
    }

    private: void copyPuzzleToClipboard()
    {
        System::String^ s = gcnew System::String(L"");
        for (unsigned char i = 0; i < boardSize; ++i)
        {
            for (unsigned char j = 0; j < boardSize; ++j)
            {
                if (engine->getFilled(i, j))
                    s += ((int)engine->getCellValue(i, j)).ToString();
                else
                    s += L"0";
            }
        }
        System::Windows::Forms::Clipboard::SetText(s);
    }

    private: void pastePuzzleFromClipboard()
    {
        System::String^ raw = System::Windows::Forms::Clipboard::ContainsText()
            ? System::Windows::Forms::Clipboard::GetText()
            : gcnew System::String(L"");

        // Extract digits, treating '.' as '0'
        System::String^ digits = gcnew System::String(L"");
        for each (wchar_t c in raw)
        {
            if (c >= L'0' && c <= L'9')
                digits += c.ToString();
            else if (c == L'.')
                digits += L"0";
        }

        if (digits->Length != (int)(this->numberOfCells))
        {
            this->showNotification(Strings::Get(StringId::NotifyInvalidPuzzleString, this->currentLanguage));
            return;
        }

        this->engine->clear();
        this->clearBoard(true);
        this->undoStack->Clear();
        this->undoToolStripMenuItem->Enabled = false;
        this->undoButton->Enabled = false;

        for (int i = 0; i < (int)(this->numberOfCells); ++i)
        {
            int digit = int::Parse(digits[i].ToString());
            if (digit >= 1 && digit <= 9)
            {
                this->cells[i]->Text = digit.ToString();
                this->cells[i]->ForeColor = defaultColor;
                ++this->numberOfFilledCells;
            }
        }

        this->revalidateAllCells();
    }

    private: void clipboardButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (this->gameMode == GameMode::Game)
            this->copyPuzzleToClipboard();
        else if (this->gameMode == GameMode::Solver)
            this->pastePuzzleFromClipboard();
    }

    private: void copyPuzzleToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (this->gameMode == GameMode::Game)
            this->copyPuzzleToClipboard();
    }

    private: void pastePuzzleToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (this->gameMode == GameMode::Solver)
            this->pastePuzzleFromClipboard();
    }

    private: void customPuzzleButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (!this->promptSaveIfNeeded()) return;
        this->closeHelperForms();
        this->disableHint();

        this->engine->clear();
        this->clearBoard(true);

        this->gameMode = GameMode::Solver;
        this->restartButton->Enabled = false;
        this->undoStack->Clear();
        this->undoToolStripMenuItem->Enabled = false;
        this->undoButton->Enabled = false;
        this->setGameControls(false, false, false, true);
        this->updateClipboardControls();
    }

    private: void solveButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->closeHelperForms();
        this->disableHint();

        this->fillEngine();
        this->engine->trySolve();

        if (engine->currentState() == SudokuGameEngine::SudokuEngineState::FilledValid)
        {
            unsigned int index = 0;
            for (unsigned char i = 0; i < boardSize; ++i)
            {
                for (unsigned char j = 0; j < boardSize; ++j)
                {
                    System::Windows::Forms::Button^ cell = this->cells[index];
                    if (cell->Text->Length == 0)
                    {
                        ++this->numberOfFilledCells;
                        cell->Text = ((int)engine->getCellValue(i, j)).ToString();
                        cell->ForeColor = solveColor;
                    }

                    cell->Enabled = false;
                    ++index;
                }
            }

            this->solveButton->Enabled = false;
            this->solveToolStripMenuItem->Enabled = false;
            this->clipboardButton->Enabled = false;
            this->pastePuzzleToolStripMenuItem->Enabled = false;
            this->undoStack->Clear();
            this->undoToolStripMenuItem->Enabled = false;
            this->undoButton->Enabled = false;
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

    private: void saveToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (this->gameMode == GameMode::Game || this->gameMode == GameMode::Solver)
        {
            this->saveGameDialog->ShowDialog();
        }
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
        MessageBox::Show(
            Strings::Get(StringId::DialogAboutText, this->currentLanguage),
            Strings::Get(StringId::DialogTitleAbout, this->currentLanguage),
            MessageBoxButtons::OK,
            MessageBoxIcon::None);
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

    private: void button1_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(1, sender, e);
    }

    private: void button2_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(2, sender, e);
    }

    private: void button3_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(3, sender, e);
    }

    private: void button4_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(4, sender, e);
    }

    private: void button5_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(5, sender, e);
    }

    private: void button6_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(6, sender, e);
    }

    private: void button7_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(7, sender, e);
    }

    private: void button8_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(8, sender, e);
    }

    private: void button9_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(9, sender, e);
    }

    private: void button10_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(10, sender, e);
    }

    private: void button11_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(11, sender, e);
    }

    private: void button12_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(12, sender, e);
    }

    private: void button13_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(13, sender, e);
    }

    private: void button14_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(14, sender, e);
    }

    private: void button15_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(15, sender, e);
    }

    private: void button16_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(16, sender, e);
    }

    private: void button17_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(17, sender, e);
    }

    private: void button18_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(18, sender, e);
    }

    private: void button19_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(19, sender, e);
    }

    private: void button20_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(20, sender, e);
    }

    private: void button21_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(21, sender, e);
    }

    private: void button22_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(22, sender, e);
    }

    private: void button23_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(23, sender, e);
    }

    private: void button24_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(24, sender, e);
    }

    private: void button25_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(25, sender, e);
    }

    private: void button26_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(26, sender, e);
    }

    private: void button27_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(27, sender, e);
    }

    private: void button28_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(28, sender, e);
    }

    private: void button29_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(29, sender, e);
    }

    private: void button30_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(30, sender, e);
    }

    private: void button31_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(31, sender, e);
    }

    private: void button32_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(32, sender, e);
    }

    private: void button33_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(33, sender, e);
    }

    private: void button34_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(34, sender, e);
    }

    private: void button35_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(35, sender, e);
    }

    private: void button36_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(36, sender, e);
    }

    private: void button37_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(37, sender, e);
    }

    private: void button38_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(38, sender, e);
    }

    private: void button39_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(39, sender, e);
    }

    private: void button40_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(40, sender, e);
    }

    private: void button41_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(41, sender, e);
    }

    private: void button42_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(42, sender, e);
    }

    private: void button43_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(43, sender, e);
    }

    private: void button44_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(44, sender, e);
    }

    private: void button45_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(45, sender, e);
    }

    private: void button46_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(46, sender, e);
    }

    private: void button47_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(47, sender, e);
    }

    private: void button48_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(48, sender, e);
    }

    private: void button49_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(49, sender, e);
    }

    private: void button50_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(50, sender, e);
    }

    private: void button51_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(51, sender, e);
    }

    private: void button52_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(52, sender, e);
    }

    private: void button53_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(53, sender, e);
    }

    private: void button54_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(54, sender, e);
    }

    private: void button55_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(55, sender, e);
    }

    private: void button56_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(56, sender, e);
    }

    private: void button57_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(57, sender, e);
    }

    private: void button58_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(58, sender, e);
    }

    private: void button59_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(59, sender, e);
    }

    private: void button60_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(60, sender, e);
    }

    private: void button61_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(61, sender, e);
    }

    private: void button62_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(62, sender, e);
    }

    private: void button63_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(63, sender, e);
    }

    private: void button64_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(64, sender, e);
    }

    private: void button65_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(65, sender, e);
    }

    private: void button66_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(66, sender, e);
    }

    private: void button67_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(67, sender, e);
    }

    private: void button68_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(68, sender, e);
    }

    private: void button69_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(69, sender, e);
    }

    private: void button70_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(70, sender, e);
    }

    private: void button71_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(71, sender, e);
    }

    private: void button72_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(72, sender, e);
    }

    private: void button73_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(73, sender, e);
    }

    private: void button74_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(74, sender, e);
    }

    private: void button75_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(75, sender, e);
    }

    private: void button76_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(76, sender, e);
    }

    private: void button77_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(77, sender, e);
    }

    private: void button78_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(78, sender, e);
    }

    private: void button79_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(79, sender, e);
    }

    private: void button80_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(80, sender, e);
    }

    private: void button81_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->cellButtonClicked(81, sender, e);
    }

    private: void difficultyComboBox_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        this->closeHelperForms();
    }

    private: void buttonMinimize_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->closeHelperForms();

        this->WindowState = FormWindowState::Minimized;
    }

    private: void buttonClose_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (!this->promptSaveIfNeeded()) return;
        this->closeHelperForms();

        this->Close();
    }

    private: void SudokuForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        this->closeHelperForms();

        this->dragging = true;
        this->offset = Point(e->X, e->Y);
    }

    private: void SudokuForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        if (this->dragging)
        {
            Point currentScreenPos = PointToScreen(e->Location);
            Location = Point(currentScreenPos.X - this->offset.X, currentScreenPos.Y - this->offset.Y);
        }
    }

    private: void SudokuForm_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        this->closeHelperForms();
        this->dragging = false;
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

    private: void difficultyLabel_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        this->SudokuForm_MouseDown(sender, e);
    }

    private: void difficultyLabel_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        this->SudokuForm_MouseMove(sender, e);
    }

    private: void difficultyLabel_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        this->SudokuForm_MouseUp(sender, e);
    }

    private: void buttonKeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
    {
        if (!this->isHint)
        {
            unsigned int choice = 0;
            if (e->KeyChar >= '1' && e->KeyChar <= '9')
            {
                choice = e->KeyChar - '0';
            }
            else if (e->KeyChar == '\b' || e->KeyChar == '0')
            {
                choice = 0;
            }
            else if (e->KeyChar == 'p' || e->KeyChar == 'P')
            {
                // Ctrl+P is handled in buttonKeyDown; ignore bare P here
                return;
            }
            else
            {
                return;
            }

            int buttonIndex = array<Button^>::IndexOf(this->cells, ((Button^)sender)) + 1;

            bool changed = false;
            if (((Button^)sender)->Text->Length == 0 && choice != 0 ||
                ((Button^)sender)->Text->Length != 0 && choice == 0)
            {
                changed = true;
            }
            else if (choice != 0 && !((Button^)sender)->Text->Equals(choice.ToString()))
            {
                changed = true;
            }

            this->choiceMade(buttonIndex, changed, choice);
        }
    }

    private: void saveGameDialog_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e)
    {
        SavedGame^ save = gcnew SavedGame();
        save->sizeFactor = this->engine->sizeOfTheBlock();
        save->difficulty = this->currentDifficulty;
        save->numberOfHints = this->numberOfHints;
        save->numberOfFixes = this->numberOfFixes;
        save->hasGivenUp = this->hasGivenUp;
        save->hasUsedFix = this->hasUsedFix;
        save->gameMode = static_cast<unsigned int>(this->gameMode);
        if (this->gameMode == GameMode::Game)
        {
            save->gameFinished = !this->giveUpButton->Enabled;
        }
        else
        {
            save->gameFinished = !this->solveButton->Enabled;
        }
        save->value = gcnew String("");
        save->state = gcnew String("");
        save->pencilMarks = gcnew String("");

        unsigned int index = 0;
        for (unsigned int i = 0; i < this->engine->sizeOfTheBoard(); ++i)
        {
            for (unsigned int j = 0; j < this->engine->sizeOfTheBoard(); ++j)
            {
                save->value += this->cells[index]->Text->Length > 0 ? this->cells[index]->Text : "0";

                // Save the cell's state
                if (!this->cells[index]->Enabled && this->cells[index]->ForeColor == defaultColor)
                {
                    save->state += "0";
                }
                else
                {
                    if (this->cells[index]->Enabled)
                    {
                        if (this->cells[index]->Text->Length == 0)
                        {
                            save->state += "1";
                        }
                        else
                        {
                            save->state += "2";
                        }
                    }
                    else
                    {
                        if (this->cells[index]->ForeColor == defaultColor)
                        {
                            save->state += "0";
                        }
                        else if (this->cells[index]->ForeColor == correctColor)
                        {
                            save->state += "3";
                        }
                        else if (this->cells[index]->ForeColor == hintColor)
                        {
                            save->state += "4";
                        }
                        else if (this->cells[index]->ForeColor == giveUpColor)
                        {
                            save->state += "5";
                        }
                        else if (this->cells[index]->ForeColor == solveColor)
                        {
                            save->state += "6";
                        }
                    }
                }

                ++index;
            }
        }

        // Serialize pencil marks as 81 space-separated integers
        for (unsigned int i = 0; i < this->numberOfCells; ++i)
        {
            if (i > 0) save->pencilMarks += " ";
            save->pencilMarks += this->pencilMarks[i].ToString();
        }

        FileStream^ fileStream = nullptr;

        try
        {
            fileStream = File::Create(this->saveGameDialog->FileName);
            BinaryFormatter^ formatter = gcnew BinaryFormatter();
            formatter->Serialize(fileStream, save);
        }
        catch (...)
        {
            this->showNotification(Strings::Get(StringId::NotifyFileSaveError, this->currentLanguage));
        }
        finally
        {
            if (fileStream != nullptr)
            {
                fileStream->Close();
            }
        }
    }

    private: void openGameDialog_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e)
    {
        SavedGame^ save = nullptr;
        FileStream^ fileStream = nullptr;

        try
        {
            // Read save object from the file
            fileStream = File::OpenRead(this->openGameDialog->FileName);
            BinaryFormatter^ formatter = gcnew BinaryFormatter();
            save = (SavedGame^)formatter->Deserialize(fileStream);

            // Only block size 3 is currently supported
            if (save->sizeFactor != 3)
            {
                throw "Invalid sizeFactor value " + save->sizeFactor.ToString();
            }

            // Check if the velues and states strings' lengths are of right length
            if (save->value->Length != this->numberOfCells)
            {
                throw "Invalid number of cell values " + save->value->Length.ToString();
            }
            else if (save->state->Length != save->value->Length)
            {
                throw "Invalid number of cell states " + save->value->Length.ToString();
            }

            // Reset the board
            this->clearBoard(false);
            this->engine->clear();
            this->disableHint();
            this->currentDifficulty = save->difficulty;
            this->difficultyComboBox->SelectedIndex = save->difficulty;
            this->numberOfFilledCells = 0;
            this->numberOfHints = save->numberOfHints;
            this->numberOfFixes = save->numberOfFixes;
            this->hasGivenUp = save->hasGivenUp;
            this->hasUsedFix = save->hasUsedFix;
            this->gameMode = static_cast<GameMode>(save->gameMode);
            this->restartButton->Enabled = this->gameMode == GameMode::Game;
            this->setGameControls(
                this->gameMode == GameMode::Game && !save->gameFinished,
                this->gameMode == GameMode::Game && !save->gameFinished,
                this->gameMode == GameMode::Game && !save->gameFinished,
                this->gameMode == GameMode::Solver && !save->gameFinished);
            this->updateClipboardControls();

            // Fill each cell
            unsigned int index = 0;
            unsigned int numberOfEnabledCells = 0;
            for (unsigned int i = 0; i < this->boardSize; ++i)
            {
                for (unsigned int j = 0; j < this->boardSize; ++j)
                {
                    System::String^ value = save->value[index].ToString();
                    System::String^ state = save->state[index].ToString();

                    // Check if the values are valid
                    if (value != "1" && value != "2" && value != "3" &&
                        value != "4" && value != "5" && value != "6" &&
                        value != "7" && value != "8" && value != "9" &&
                        value != "0")
                    {
                        throw "Invalid cell value " + value;
                    }

                    // Check if the state properties are valid
                    if (state != "0" && state != "1" && state != "2" &&
                        state != "3" && state != "4" && state != "5" &&
                        state != "6")
                    {
                        throw "Invalid cell state " + state;
                    }

                    // Check if cell value does not conflict with cell state
                    if (value->Equals("0") != state->Equals("1"))
                    {
                        throw "Invalid cell value and cell state pair";
                    }

                    // Fill the engine based on game mode
                    if (this->gameMode == GameMode::Game)
                    {
                        // If the cell was filled by the engine (immutable clue)
                        if (state->Equals("0"))
                        {
                            this->engine->setFilled(i, j, true);
                            this->engine->setCellValue(i, j, value[0] - '0');
                        }
                        else
                        {
                            // It was hidden by the engine
                            this->engine->setFilled(i, j, false);
                        }
                    }
                    else if (this->gameMode == GameMode::Solver)
                    {
                        if (state->Equals("0") || state->Equals("6"))
                        {
                            this->engine->setFilled(i, j, true);
                            this->engine->setCellValue(i, j, value[0] - '0');
                        }
                        else if (state->Equals("1") || state->Equals("2"))
                        {
                            this->engine->setFilled(i, j, false);
                        }
                        else
                        {
                            throw "Invalid cell state value " + state + " for game mode " + save->gameMode.ToString();
                        }
                    }
                    else
                    {
                        throw "Invalid gameMode value " + save->gameMode.ToString();
                    }

                    // If the cell is not empty
                    if (!state->Equals("1"))
                    {
                        ++(this->numberOfFilledCells);
                    }

                    // Fill the cell with its value
                    this->cells[index]->Text = value->Equals("0") ? "" : value;

                    // Check if the cell is enabled
                    if (state->Equals("1") || state->Equals("2"))
                    {
                        this->cells[index]->Enabled = true;
                        ++numberOfEnabledCells;
                    }
                    else
                    {
                        this->cells[index]->Enabled = false;
                    }

                    // Change cell color if needed
                    if (this->gameMode == GameMode::Game)
                    {
                        if (state->Equals("3"))
                        {
                            this->cells[index]->ForeColor = correctColor;
                        }
                        else if (state->Equals("4"))
                        {
                            this->cells[index]->ForeColor = hintColor;
                        }
                        else if (state->Equals("5"))
                        {
                            this->cells[index]->ForeColor = giveUpColor;
                        }
                        else if (state->Equals("6"))
                        {
                            throw "Invalid state " + state + " in game mode " + save->gameMode.ToString();
                        }
                    }
                    else if (this->gameMode == GameMode::Solver)
                    {
                        if (state->Equals("6"))
                        {
                            this->cells[index]->ForeColor = solveColor;
                        }
                        else if (
                            state->Equals("3") ||
                            state->Equals("4") ||
                            state->Equals("5"))
                        {
                            throw "Invalid state " + state + " in game mode " + save->gameMode.ToString();
                        }
                    }

                    ++index;
                }
            }

            // Restore pencil marks if present (new saves only)
            this->undoStack->Clear();
            this->undoToolStripMenuItem->Enabled = false;
            this->undoButton->Enabled = false;
            this->setPencilMode(false);
            if (save->pencilMarks != nullptr && save->pencilMarks->Length > 0)
            {
                array<System::String^>^ parts = save->pencilMarks->Split(' ');
                for (unsigned int i = 0; i < this->numberOfCells && i < (unsigned int)parts->Length; ++i)
                {
                    int mark = 0;
                    if (int::TryParse(parts[i], mark))
                        this->pencilMarks[i] = mark;
                }
                // Repaint all cells to show loaded marks
                for each (Button ^ cell in this->cells)
                {
                    cell->Invalidate();
                }
            }

            // The engine needs to solve the puzzle for 2 reasons:
            // 1) It needs the solution to validate hints/check progress later (game mode)
            // 2) It allows detection of corrupted saves
            if (this->gameMode == GameMode::Game || (this->gameMode == GameMode::Solver && engine->numberOfFilledCells() > 0))
            {
                this->engine->trySolve();
                if (engine->currentState() != SudokuGameEngine::SudokuEngineState::FilledValid)
                {
                    throw "Invalid cell values";
                }
            }
            else
            {
                // Solver mode with an empty board: resolve BeingEdited state without solving
                this->engine->updateState();
            }
        }
        catch (...)
        {
            this->showNotification(Strings::Get(StringId::NotifyFileLoadError, this->currentLanguage));
        }
        finally
        {
            if (fileStream != nullptr)
            {
                fileStream->Close();
            }
        }
    }
    };
}
