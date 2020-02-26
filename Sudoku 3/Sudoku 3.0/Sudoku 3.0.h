#pragma once

#include "About.h"
#include "Features.h"
#include "HintsAndTips.h"
#include "Keyboard.h"
#include "Notification.h"
#include "Numbers.h"
#include "Rules.h"
#include "SavedGame.h"
#include "SudokuEngine.h"

namespace Sudoku_3_0
{
	using namespace System;
	using namespace System::IO;
	using namespace System::Drawing;
	using namespace System::Runtime::Serialization::Formatters::Binary;
	using namespace System::Windows::Forms;

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
		/// <summary>
		/// Clean up any resources being used
		/// </summary>
		~SudokuForm()
		{
			delete engine;
			delete cells;

			if (components)
			{
				delete components;
			}
		}

	// Set of standard colors
	private: static const System::Drawing::Color defaultColor = Color::Black;
	private: static const System::Drawing::Color correctColor = Color::SpringGreen;
	private: static const System::Drawing::Color hintColor = Color::Yellow;
	private: static const System::Drawing::Color hintButtonColor = Color::Orange;
	private: static const System::Drawing::Color giveUpColor = Color::Red;
	private: static const System::Drawing::Color solveColor = Color::BlueViolet;
	private: static const System::Drawing::Color defaultBackColor = SystemColors::Menu;
	private: static const System::Drawing::Color conflictBackColor = Color::Red;

	// Size of the board
	private: const unsigned int sizeFactor;
	private: const unsigned int boardSize;
	private: const unsigned int numberOfCells;

	// Sudoku engine
	private: SudokuGameEngine::SudokuEngine<>* engine;

	// Access to buttons by their numbers
	private: array<System::Windows::Forms::Button^>^ cells;

	// Cell buttons
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::Button^  button12;
	private: System::Windows::Forms::Button^  button13;
	private: System::Windows::Forms::Button^  button14;
	private: System::Windows::Forms::Button^  button15;
	private: System::Windows::Forms::Button^  button16;
	private: System::Windows::Forms::Button^  button17;
	private: System::Windows::Forms::Button^  button18;
	private: System::Windows::Forms::Button^  button19;
	private: System::Windows::Forms::Button^  button20;
	private: System::Windows::Forms::Button^  button21;
	private: System::Windows::Forms::Button^  button22;
	private: System::Windows::Forms::Button^  button23;
	private: System::Windows::Forms::Button^  button24;
	private: System::Windows::Forms::Button^  button25;
	private: System::Windows::Forms::Button^  button26;
	private: System::Windows::Forms::Button^  button27;
	private: System::Windows::Forms::Button^  button28;
	private: System::Windows::Forms::Button^  button29;
	private: System::Windows::Forms::Button^  button30;
	private: System::Windows::Forms::Button^  button31;
	private: System::Windows::Forms::Button^  button32;
	private: System::Windows::Forms::Button^  button33;
	private: System::Windows::Forms::Button^  button34;
	private: System::Windows::Forms::Button^  button35;
	private: System::Windows::Forms::Button^  button36;
	private: System::Windows::Forms::Button^  button37;
	private: System::Windows::Forms::Button^  button38;
	private: System::Windows::Forms::Button^  button39;
	private: System::Windows::Forms::Button^  button40;
	private: System::Windows::Forms::Button^  button41;
	private: System::Windows::Forms::Button^  button42;
	private: System::Windows::Forms::Button^  button43;
	private: System::Windows::Forms::Button^  button44;
	private: System::Windows::Forms::Button^  button45;
	private: System::Windows::Forms::Button^  button46;
	private: System::Windows::Forms::Button^  button47;
	private: System::Windows::Forms::Button^  button48;
	private: System::Windows::Forms::Button^  button49;
	private: System::Windows::Forms::Button^  button50;
	private: System::Windows::Forms::Button^  button51;
	private: System::Windows::Forms::Button^  button52;
	private: System::Windows::Forms::Button^  button53;
	private: System::Windows::Forms::Button^  button54;
	private: System::Windows::Forms::Button^  button55;
	private: System::Windows::Forms::Button^  button56;
	private: System::Windows::Forms::Button^  button57;
	private: System::Windows::Forms::Button^  button58;
	private: System::Windows::Forms::Button^  button59;
	private: System::Windows::Forms::Button^  button60;
	private: System::Windows::Forms::Button^  button61;
	private: System::Windows::Forms::Button^  button62;
	private: System::Windows::Forms::Button^  button63;
	private: System::Windows::Forms::Button^  button64;
	private: System::Windows::Forms::Button^  button65;
	private: System::Windows::Forms::Button^  button66;
	private: System::Windows::Forms::Button^  button67;
	private: System::Windows::Forms::Button^  button68;
	private: System::Windows::Forms::Button^  button69;
	private: System::Windows::Forms::Button^  button70;
	private: System::Windows::Forms::Button^  button71;
	private: System::Windows::Forms::Button^  button72;
	private: System::Windows::Forms::Button^  button73;
	private: System::Windows::Forms::Button^  button74;
	private: System::Windows::Forms::Button^  button75;
	private: System::Windows::Forms::Button^  button76;
	private: System::Windows::Forms::Button^  button77;
	private: System::Windows::Forms::Button^  button78;
	private: System::Windows::Forms::Button^  button79;
	private: System::Windows::Forms::Button^  button80;
	private: System::Windows::Forms::Button^  button81;

	// Control elements
	private: System::Windows::Forms::Label^  difficultyLabel;
	private: System::Windows::Forms::ComboBox^  difficultyComboBox;
	private: System::Windows::Forms::Button^  newGameButton;
	private: System::Windows::Forms::Button^  RestartButton;
	private: System::Windows::Forms::Button^  hintButton;
	private: System::Windows::Forms::Button^  fixButton;
	private: System::Windows::Forms::Button^  giveUpButton;
	private: System::Windows::Forms::Button^  customPuzzleButton;
	private: System::Windows::Forms::Button^  solveButton;
	private: System::Windows::Forms::Button^  buttonMinimize;
	private: System::Windows::Forms::Button^  buttonClose;
	private: System::Windows::Forms::Button^  newCombinationButton;

	// Menu elements
	private: System::Windows::Forms::MenuStrip^  menuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  minimizeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  gameToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  newCombinationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  newGameToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  RestartToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  hintToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  fixToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  giveUpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  customPuzzleToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  solveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  optionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  difficultyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  veryEasyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  easyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  mediumToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  hardToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  veryHardToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  rulesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  featuresToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  hintsAndTipsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  keyboardToolStripMenuItem;

	// Dialogs
	private: System::Windows::Forms::SaveFileDialog^  saveGameDialog;
	private: System::Windows::Forms::OpenFileDialog^  openGameDialog;

	// Numbers form
	private: Sudoku_3_0::Numbers^ numbersForm;

	// Notifications form
	private: Sudoku_3_0::Notification^ notificationForm;

	// About form
	private: Sudoku_3_0::About^ aboutForm;

	// Rules form
	private: Sudoku_3_0::Rules^ rulesForm;

	// Features form
	private: Sudoku_3_0::Features^ featuresForm;

	// HintsAndTips form
	private: Sudoku_3_0::HintsAndTips^ hintsAndTipsForm;

	// Keyboard form
	private: Sudoku_3_0::Keyboard^ keyboardForm;

	// Numbers form active
	private: bool numbersFormActive;

	// Number of filled cells
	private: unsigned int numberOfFilledCells;

	// State of the hint
	private: bool isHint;

	// Number of hints used so far
	private: unsigned int numberOfHints;

	// Game mode: 0 - combination, 1 - game, 2 - solver, 3 - other
	private: unsigned int gameMode;

	// Difficulty level of current puzzle
	private: unsigned int currentDifficulty;

	// Dragging state
	private: bool dragging;
	private: Point offset;


	// Components
	private: System::ComponentModel::Container ^components;

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
			this->newCombinationButton = (gcnew System::Windows::Forms::Button());
			this->newGameButton = (gcnew System::Windows::Forms::Button());
			this->RestartButton = (gcnew System::Windows::Forms::Button());
			this->hintButton = (gcnew System::Windows::Forms::Button());
			this->fixButton = (gcnew System::Windows::Forms::Button());
			this->giveUpButton = (gcnew System::Windows::Forms::Button());
			this->customPuzzleButton = (gcnew System::Windows::Forms::Button());
			this->solveButton = (gcnew System::Windows::Forms::Button());
			this->saveGameDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->openGameDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->minimizeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gameToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newGameToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->RestartToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->hintToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fixToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->giveUpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newCombinationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->customPuzzleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->solveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->difficultyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->veryEasyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->easyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->mediumToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->hardToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->veryHardToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rulesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->featuresToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->hintsAndTipsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->keyboardToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::Menu;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(35, 35);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(40, 40);
			this->button1->TabIndex = 3;
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &SudokuForm::button1_Click);
			this->button1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::SystemColors::Menu;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(78, 35);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(40, 40);
			this->button2->TabIndex = 4;
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &SudokuForm::button2_Click);
			this->button2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::SystemColors::Menu;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button3->Location = System::Drawing::Point(121, 35);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(40, 40);
			this->button3->TabIndex = 5;
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &SudokuForm::button3_Click);
			this->button3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::SystemColors::Menu;
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button4->Location = System::Drawing::Point(170, 35);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(40, 40);
			this->button4->TabIndex = 6;
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &SudokuForm::button4_Click);
			this->button4->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::SystemColors::Menu;
			this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button5->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button5->Location = System::Drawing::Point(213, 35);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(40, 40);
			this->button5->TabIndex = 7;
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &SudokuForm::button5_Click);
			this->button5->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button6
			// 
			this->button6->BackColor = System::Drawing::SystemColors::Menu;
			this->button6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button6->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button6->Location = System::Drawing::Point(256, 35);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(40, 40);
			this->button6->TabIndex = 8;
			this->button6->UseVisualStyleBackColor = false;
			this->button6->Click += gcnew System::EventHandler(this, &SudokuForm::button6_Click);
			this->button6->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button7
			// 
			this->button7->BackColor = System::Drawing::SystemColors::Menu;
			this->button7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button7->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button7->Location = System::Drawing::Point(305, 35);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(40, 40);
			this->button7->TabIndex = 9;
			this->button7->UseVisualStyleBackColor = false;
			this->button7->Click += gcnew System::EventHandler(this, &SudokuForm::button7_Click);
			this->button7->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button8
			// 
			this->button8->BackColor = System::Drawing::SystemColors::Menu;
			this->button8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button8->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button8->Location = System::Drawing::Point(348, 35);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(40, 40);
			this->button8->TabIndex = 10;
			this->button8->UseVisualStyleBackColor = false;
			this->button8->Click += gcnew System::EventHandler(this, &SudokuForm::button8_Click);
			this->button8->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button9
			// 
			this->button9->BackColor = System::Drawing::SystemColors::Menu;
			this->button9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button9->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button9->Location = System::Drawing::Point(391, 35);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(40, 40);
			this->button9->TabIndex = 11;
			this->button9->UseVisualStyleBackColor = false;
			this->button9->Click += gcnew System::EventHandler(this, &SudokuForm::button9_Click);
			this->button9->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button10
			// 
			this->button10->BackColor = System::Drawing::SystemColors::Menu;
			this->button10->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button10->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button10->Location = System::Drawing::Point(35, 78);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(40, 40);
			this->button10->TabIndex = 12;
			this->button10->UseVisualStyleBackColor = false;
			this->button10->Click += gcnew System::EventHandler(this, &SudokuForm::button10_Click);
			this->button10->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button11
			// 
			this->button11->BackColor = System::Drawing::SystemColors::Menu;
			this->button11->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button11->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button11->Location = System::Drawing::Point(78, 78);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(40, 40);
			this->button11->TabIndex = 13;
			this->button11->UseVisualStyleBackColor = false;
			this->button11->Click += gcnew System::EventHandler(this, &SudokuForm::button11_Click);
			this->button11->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button12
			// 
			this->button12->BackColor = System::Drawing::SystemColors::Menu;
			this->button12->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button12->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button12->Location = System::Drawing::Point(121, 78);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(40, 40);
			this->button12->TabIndex = 14;
			this->button12->UseVisualStyleBackColor = false;
			this->button12->Click += gcnew System::EventHandler(this, &SudokuForm::button12_Click);
			this->button12->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button13
			// 
			this->button13->BackColor = System::Drawing::SystemColors::Menu;
			this->button13->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button13->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button13->Location = System::Drawing::Point(170, 78);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(40, 40);
			this->button13->TabIndex = 15;
			this->button13->UseVisualStyleBackColor = false;
			this->button13->Click += gcnew System::EventHandler(this, &SudokuForm::button13_Click);
			this->button13->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button14
			// 
			this->button14->BackColor = System::Drawing::SystemColors::Menu;
			this->button14->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button14->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button14->Location = System::Drawing::Point(213, 78);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(40, 40);
			this->button14->TabIndex = 16;
			this->button14->UseVisualStyleBackColor = false;
			this->button14->Click += gcnew System::EventHandler(this, &SudokuForm::button14_Click);
			this->button14->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button15
			// 
			this->button15->BackColor = System::Drawing::SystemColors::Menu;
			this->button15->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button15->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button15->Location = System::Drawing::Point(256, 78);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(40, 40);
			this->button15->TabIndex = 17;
			this->button15->UseVisualStyleBackColor = false;
			this->button15->Click += gcnew System::EventHandler(this, &SudokuForm::button15_Click);
			this->button15->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button16
			// 
			this->button16->BackColor = System::Drawing::SystemColors::Menu;
			this->button16->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button16->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button16->Location = System::Drawing::Point(305, 78);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(40, 40);
			this->button16->TabIndex = 18;
			this->button16->UseVisualStyleBackColor = false;
			this->button16->Click += gcnew System::EventHandler(this, &SudokuForm::button16_Click);
			this->button16->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button17
			// 
			this->button17->BackColor = System::Drawing::SystemColors::Menu;
			this->button17->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button17->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button17->Location = System::Drawing::Point(348, 78);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(40, 40);
			this->button17->TabIndex = 19;
			this->button17->UseVisualStyleBackColor = false;
			this->button17->Click += gcnew System::EventHandler(this, &SudokuForm::button17_Click);
			this->button17->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button18
			// 
			this->button18->BackColor = System::Drawing::SystemColors::Menu;
			this->button18->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button18->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button18->Location = System::Drawing::Point(391, 78);
			this->button18->Name = L"button18";
			this->button18->Size = System::Drawing::Size(40, 40);
			this->button18->TabIndex = 20;
			this->button18->UseVisualStyleBackColor = false;
			this->button18->Click += gcnew System::EventHandler(this, &SudokuForm::button18_Click);
			this->button18->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button19
			// 
			this->button19->BackColor = System::Drawing::SystemColors::Menu;
			this->button19->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button19->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button19->Location = System::Drawing::Point(35, 121);
			this->button19->Name = L"button19";
			this->button19->Size = System::Drawing::Size(40, 40);
			this->button19->TabIndex = 21;
			this->button19->UseVisualStyleBackColor = false;
			this->button19->Click += gcnew System::EventHandler(this, &SudokuForm::button19_Click);
			this->button19->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button20
			// 
			this->button20->BackColor = System::Drawing::SystemColors::Menu;
			this->button20->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button20->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button20->Location = System::Drawing::Point(78, 121);
			this->button20->Name = L"button20";
			this->button20->Size = System::Drawing::Size(40, 40);
			this->button20->TabIndex = 22;
			this->button20->UseVisualStyleBackColor = false;
			this->button20->Click += gcnew System::EventHandler(this, &SudokuForm::button20_Click);
			this->button20->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button21
			// 
			this->button21->BackColor = System::Drawing::SystemColors::Menu;
			this->button21->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button21->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button21->Location = System::Drawing::Point(121, 121);
			this->button21->Name = L"button21";
			this->button21->Size = System::Drawing::Size(40, 40);
			this->button21->TabIndex = 23;
			this->button21->UseVisualStyleBackColor = false;
			this->button21->Click += gcnew System::EventHandler(this, &SudokuForm::button21_Click);
			this->button21->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button22
			// 
			this->button22->BackColor = System::Drawing::SystemColors::Menu;
			this->button22->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button22->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button22->Location = System::Drawing::Point(170, 121);
			this->button22->Name = L"button22";
			this->button22->Size = System::Drawing::Size(40, 40);
			this->button22->TabIndex = 24;
			this->button22->UseVisualStyleBackColor = false;
			this->button22->Click += gcnew System::EventHandler(this, &SudokuForm::button22_Click);
			this->button22->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button23
			// 
			this->button23->BackColor = System::Drawing::SystemColors::Menu;
			this->button23->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button23->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button23->Location = System::Drawing::Point(213, 121);
			this->button23->Name = L"button23";
			this->button23->Size = System::Drawing::Size(40, 40);
			this->button23->TabIndex = 25;
			this->button23->UseVisualStyleBackColor = false;
			this->button23->Click += gcnew System::EventHandler(this, &SudokuForm::button23_Click);
			this->button23->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button24
			// 
			this->button24->BackColor = System::Drawing::SystemColors::Menu;
			this->button24->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button24->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button24->Location = System::Drawing::Point(256, 121);
			this->button24->Name = L"button24";
			this->button24->Size = System::Drawing::Size(40, 40);
			this->button24->TabIndex = 26;
			this->button24->UseVisualStyleBackColor = false;
			this->button24->Click += gcnew System::EventHandler(this, &SudokuForm::button24_Click);
			this->button24->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button25
			// 
			this->button25->BackColor = System::Drawing::SystemColors::Menu;
			this->button25->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button25->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button25->Location = System::Drawing::Point(305, 121);
			this->button25->Name = L"button25";
			this->button25->Size = System::Drawing::Size(40, 40);
			this->button25->TabIndex = 27;
			this->button25->UseVisualStyleBackColor = false;
			this->button25->Click += gcnew System::EventHandler(this, &SudokuForm::button25_Click);
			this->button25->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button26
			// 
			this->button26->BackColor = System::Drawing::SystemColors::Menu;
			this->button26->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button26->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button26->Location = System::Drawing::Point(348, 121);
			this->button26->Name = L"button26";
			this->button26->Size = System::Drawing::Size(40, 40);
			this->button26->TabIndex = 28;
			this->button26->UseVisualStyleBackColor = false;
			this->button26->Click += gcnew System::EventHandler(this, &SudokuForm::button26_Click);
			this->button26->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button27
			// 
			this->button27->BackColor = System::Drawing::SystemColors::Menu;
			this->button27->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button27->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button27->Location = System::Drawing::Point(391, 121);
			this->button27->Name = L"button27";
			this->button27->Size = System::Drawing::Size(40, 40);
			this->button27->TabIndex = 29;
			this->button27->UseVisualStyleBackColor = false;
			this->button27->Click += gcnew System::EventHandler(this, &SudokuForm::button27_Click);
			this->button27->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button28
			// 
			this->button28->BackColor = System::Drawing::SystemColors::Menu;
			this->button28->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button28->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button28->Location = System::Drawing::Point(35, 170);
			this->button28->Name = L"button28";
			this->button28->Size = System::Drawing::Size(40, 40);
			this->button28->TabIndex = 30;
			this->button28->UseVisualStyleBackColor = false;
			this->button28->Click += gcnew System::EventHandler(this, &SudokuForm::button28_Click);
			this->button28->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button29
			// 
			this->button29->BackColor = System::Drawing::SystemColors::Menu;
			this->button29->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button29->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button29->Location = System::Drawing::Point(78, 170);
			this->button29->Name = L"button29";
			this->button29->Size = System::Drawing::Size(40, 40);
			this->button29->TabIndex = 31;
			this->button29->UseVisualStyleBackColor = false;
			this->button29->Click += gcnew System::EventHandler(this, &SudokuForm::button29_Click);
			this->button29->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button30
			// 
			this->button30->BackColor = System::Drawing::SystemColors::Menu;
			this->button30->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button30->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button30->Location = System::Drawing::Point(121, 170);
			this->button30->Name = L"button30";
			this->button30->Size = System::Drawing::Size(40, 40);
			this->button30->TabIndex = 32;
			this->button30->UseVisualStyleBackColor = false;
			this->button30->Click += gcnew System::EventHandler(this, &SudokuForm::button30_Click);
			this->button30->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button31
			// 
			this->button31->BackColor = System::Drawing::SystemColors::Menu;
			this->button31->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button31->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button31->Location = System::Drawing::Point(170, 170);
			this->button31->Name = L"button31";
			this->button31->Size = System::Drawing::Size(40, 40);
			this->button31->TabIndex = 33;
			this->button31->UseVisualStyleBackColor = false;
			this->button31->Click += gcnew System::EventHandler(this, &SudokuForm::button31_Click);
			this->button31->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button32
			// 
			this->button32->BackColor = System::Drawing::SystemColors::Menu;
			this->button32->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button32->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button32->Location = System::Drawing::Point(213, 170);
			this->button32->Name = L"button32";
			this->button32->Size = System::Drawing::Size(40, 40);
			this->button32->TabIndex = 34;
			this->button32->UseVisualStyleBackColor = false;
			this->button32->Click += gcnew System::EventHandler(this, &SudokuForm::button32_Click);
			this->button32->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button33
			// 
			this->button33->BackColor = System::Drawing::SystemColors::Menu;
			this->button33->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button33->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button33->Location = System::Drawing::Point(256, 170);
			this->button33->Name = L"button33";
			this->button33->Size = System::Drawing::Size(40, 40);
			this->button33->TabIndex = 35;
			this->button33->UseVisualStyleBackColor = false;
			this->button33->Click += gcnew System::EventHandler(this, &SudokuForm::button33_Click);
			this->button33->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button34
			// 
			this->button34->BackColor = System::Drawing::SystemColors::Menu;
			this->button34->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button34->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button34->Location = System::Drawing::Point(305, 170);
			this->button34->Name = L"button34";
			this->button34->Size = System::Drawing::Size(40, 40);
			this->button34->TabIndex = 36;
			this->button34->UseVisualStyleBackColor = false;
			this->button34->Click += gcnew System::EventHandler(this, &SudokuForm::button34_Click);
			this->button34->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button35
			// 
			this->button35->BackColor = System::Drawing::SystemColors::Menu;
			this->button35->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button35->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button35->Location = System::Drawing::Point(348, 170);
			this->button35->Name = L"button35";
			this->button35->Size = System::Drawing::Size(40, 40);
			this->button35->TabIndex = 37;
			this->button35->UseVisualStyleBackColor = false;
			this->button35->Click += gcnew System::EventHandler(this, &SudokuForm::button35_Click);
			this->button35->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button36
			// 
			this->button36->BackColor = System::Drawing::SystemColors::Menu;
			this->button36->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button36->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button36->Location = System::Drawing::Point(391, 170);
			this->button36->Name = L"button36";
			this->button36->Size = System::Drawing::Size(40, 40);
			this->button36->TabIndex = 38;
			this->button36->UseVisualStyleBackColor = false;
			this->button36->Click += gcnew System::EventHandler(this, &SudokuForm::button36_Click);
			this->button36->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button37
			// 
			this->button37->BackColor = System::Drawing::SystemColors::Menu;
			this->button37->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button37->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button37->Location = System::Drawing::Point(35, 213);
			this->button37->Name = L"button37";
			this->button37->Size = System::Drawing::Size(40, 40);
			this->button37->TabIndex = 39;
			this->button37->UseVisualStyleBackColor = false;
			this->button37->Click += gcnew System::EventHandler(this, &SudokuForm::button37_Click);
			this->button37->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button38
			// 
			this->button38->BackColor = System::Drawing::SystemColors::Menu;
			this->button38->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button38->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button38->Location = System::Drawing::Point(78, 213);
			this->button38->Name = L"button38";
			this->button38->Size = System::Drawing::Size(40, 40);
			this->button38->TabIndex = 40;
			this->button38->UseVisualStyleBackColor = false;
			this->button38->Click += gcnew System::EventHandler(this, &SudokuForm::button38_Click);
			this->button38->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button39
			// 
			this->button39->BackColor = System::Drawing::SystemColors::Menu;
			this->button39->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button39->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button39->Location = System::Drawing::Point(121, 213);
			this->button39->Name = L"button39";
			this->button39->Size = System::Drawing::Size(40, 40);
			this->button39->TabIndex = 41;
			this->button39->UseVisualStyleBackColor = false;
			this->button39->Click += gcnew System::EventHandler(this, &SudokuForm::button39_Click);
			this->button39->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button40
			// 
			this->button40->BackColor = System::Drawing::SystemColors::Menu;
			this->button40->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button40->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button40->Location = System::Drawing::Point(170, 213);
			this->button40->Name = L"button40";
			this->button40->Size = System::Drawing::Size(40, 40);
			this->button40->TabIndex = 42;
			this->button40->UseVisualStyleBackColor = false;
			this->button40->Click += gcnew System::EventHandler(this, &SudokuForm::button40_Click);
			this->button40->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button41
			// 
			this->button41->BackColor = System::Drawing::SystemColors::Menu;
			this->button41->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button41->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button41->Location = System::Drawing::Point(213, 213);
			this->button41->Name = L"button41";
			this->button41->Size = System::Drawing::Size(40, 40);
			this->button41->TabIndex = 43;
			this->button41->UseVisualStyleBackColor = false;
			this->button41->Click += gcnew System::EventHandler(this, &SudokuForm::button41_Click);
			this->button41->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button42
			// 
			this->button42->BackColor = System::Drawing::SystemColors::Menu;
			this->button42->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button42->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button42->Location = System::Drawing::Point(256, 213);
			this->button42->Name = L"button42";
			this->button42->Size = System::Drawing::Size(40, 40);
			this->button42->TabIndex = 44;
			this->button42->UseVisualStyleBackColor = false;
			this->button42->Click += gcnew System::EventHandler(this, &SudokuForm::button42_Click);
			this->button42->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button43
			// 
			this->button43->BackColor = System::Drawing::SystemColors::Menu;
			this->button43->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button43->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button43->Location = System::Drawing::Point(305, 213);
			this->button43->Name = L"button43";
			this->button43->Size = System::Drawing::Size(40, 40);
			this->button43->TabIndex = 45;
			this->button43->UseVisualStyleBackColor = false;
			this->button43->Click += gcnew System::EventHandler(this, &SudokuForm::button43_Click);
			this->button43->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button44
			// 
			this->button44->BackColor = System::Drawing::SystemColors::Menu;
			this->button44->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button44->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button44->Location = System::Drawing::Point(348, 213);
			this->button44->Name = L"button44";
			this->button44->Size = System::Drawing::Size(40, 40);
			this->button44->TabIndex = 46;
			this->button44->UseVisualStyleBackColor = false;
			this->button44->Click += gcnew System::EventHandler(this, &SudokuForm::button44_Click);
			this->button44->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button45
			// 
			this->button45->BackColor = System::Drawing::SystemColors::Menu;
			this->button45->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button45->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button45->Location = System::Drawing::Point(391, 213);
			this->button45->Name = L"button45";
			this->button45->Size = System::Drawing::Size(40, 40);
			this->button45->TabIndex = 47;
			this->button45->UseVisualStyleBackColor = false;
			this->button45->Click += gcnew System::EventHandler(this, &SudokuForm::button45_Click);
			this->button45->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button46
			// 
			this->button46->BackColor = System::Drawing::SystemColors::Menu;
			this->button46->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button46->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button46->Location = System::Drawing::Point(35, 256);
			this->button46->Name = L"button46";
			this->button46->Size = System::Drawing::Size(40, 40);
			this->button46->TabIndex = 48;
			this->button46->UseVisualStyleBackColor = false;
			this->button46->Click += gcnew System::EventHandler(this, &SudokuForm::button46_Click);
			this->button46->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button47
			// 
			this->button47->BackColor = System::Drawing::SystemColors::Menu;
			this->button47->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button47->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button47->Location = System::Drawing::Point(78, 256);
			this->button47->Name = L"button47";
			this->button47->Size = System::Drawing::Size(40, 40);
			this->button47->TabIndex = 49;
			this->button47->UseVisualStyleBackColor = false;
			this->button47->Click += gcnew System::EventHandler(this, &SudokuForm::button47_Click);
			this->button47->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button48
			// 
			this->button48->BackColor = System::Drawing::SystemColors::Menu;
			this->button48->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button48->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button48->Location = System::Drawing::Point(121, 256);
			this->button48->Name = L"button48";
			this->button48->Size = System::Drawing::Size(40, 40);
			this->button48->TabIndex = 50;
			this->button48->UseVisualStyleBackColor = false;
			this->button48->Click += gcnew System::EventHandler(this, &SudokuForm::button48_Click);
			this->button48->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button49
			// 
			this->button49->BackColor = System::Drawing::SystemColors::Menu;
			this->button49->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button49->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button49->Location = System::Drawing::Point(170, 256);
			this->button49->Name = L"button49";
			this->button49->Size = System::Drawing::Size(40, 40);
			this->button49->TabIndex = 51;
			this->button49->UseVisualStyleBackColor = false;
			this->button49->Click += gcnew System::EventHandler(this, &SudokuForm::button49_Click);
			this->button49->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button50
			// 
			this->button50->BackColor = System::Drawing::SystemColors::Menu;
			this->button50->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button50->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button50->Location = System::Drawing::Point(213, 256);
			this->button50->Name = L"button50";
			this->button50->Size = System::Drawing::Size(40, 40);
			this->button50->TabIndex = 52;
			this->button50->UseVisualStyleBackColor = false;
			this->button50->Click += gcnew System::EventHandler(this, &SudokuForm::button50_Click);
			this->button50->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button51
			// 
			this->button51->BackColor = System::Drawing::SystemColors::Menu;
			this->button51->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button51->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button51->Location = System::Drawing::Point(256, 256);
			this->button51->Name = L"button51";
			this->button51->Size = System::Drawing::Size(40, 40);
			this->button51->TabIndex = 53;
			this->button51->UseVisualStyleBackColor = false;
			this->button51->Click += gcnew System::EventHandler(this, &SudokuForm::button51_Click);
			this->button51->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button52
			// 
			this->button52->BackColor = System::Drawing::SystemColors::Menu;
			this->button52->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button52->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button52->Location = System::Drawing::Point(305, 256);
			this->button52->Name = L"button52";
			this->button52->Size = System::Drawing::Size(40, 40);
			this->button52->TabIndex = 54;
			this->button52->UseVisualStyleBackColor = false;
			this->button52->Click += gcnew System::EventHandler(this, &SudokuForm::button52_Click);
			this->button52->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button53
			// 
			this->button53->BackColor = System::Drawing::SystemColors::Menu;
			this->button53->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button53->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button53->Location = System::Drawing::Point(348, 256);
			this->button53->Name = L"button53";
			this->button53->Size = System::Drawing::Size(40, 40);
			this->button53->TabIndex = 55;
			this->button53->UseVisualStyleBackColor = false;
			this->button53->Click += gcnew System::EventHandler(this, &SudokuForm::button53_Click);
			this->button53->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button54
			// 
			this->button54->BackColor = System::Drawing::SystemColors::Menu;
			this->button54->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button54->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button54->Location = System::Drawing::Point(391, 256);
			this->button54->Name = L"button54";
			this->button54->Size = System::Drawing::Size(40, 40);
			this->button54->TabIndex = 56;
			this->button54->UseVisualStyleBackColor = false;
			this->button54->Click += gcnew System::EventHandler(this, &SudokuForm::button54_Click);
			this->button54->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button55
			// 
			this->button55->BackColor = System::Drawing::SystemColors::Menu;
			this->button55->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button55->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button55->Location = System::Drawing::Point(35, 305);
			this->button55->Name = L"button55";
			this->button55->Size = System::Drawing::Size(40, 40);
			this->button55->TabIndex = 57;
			this->button55->UseVisualStyleBackColor = false;
			this->button55->Click += gcnew System::EventHandler(this, &SudokuForm::button55_Click);
			this->button55->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button56
			// 
			this->button56->BackColor = System::Drawing::SystemColors::Menu;
			this->button56->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button56->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button56->Location = System::Drawing::Point(78, 305);
			this->button56->Name = L"button56";
			this->button56->Size = System::Drawing::Size(40, 40);
			this->button56->TabIndex = 58;
			this->button56->UseVisualStyleBackColor = false;
			this->button56->Click += gcnew System::EventHandler(this, &SudokuForm::button56_Click);
			this->button56->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button57
			// 
			this->button57->BackColor = System::Drawing::SystemColors::Menu;
			this->button57->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button57->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button57->Location = System::Drawing::Point(121, 305);
			this->button57->Name = L"button57";
			this->button57->Size = System::Drawing::Size(40, 40);
			this->button57->TabIndex = 59;
			this->button57->UseVisualStyleBackColor = false;
			this->button57->Click += gcnew System::EventHandler(this, &SudokuForm::button57_Click);
			this->button57->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button58
			// 
			this->button58->BackColor = System::Drawing::SystemColors::Menu;
			this->button58->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button58->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button58->Location = System::Drawing::Point(170, 305);
			this->button58->Name = L"button58";
			this->button58->Size = System::Drawing::Size(40, 40);
			this->button58->TabIndex = 60;
			this->button58->UseVisualStyleBackColor = false;
			this->button58->Click += gcnew System::EventHandler(this, &SudokuForm::button58_Click);
			this->button58->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button59
			// 
			this->button59->BackColor = System::Drawing::SystemColors::Menu;
			this->button59->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button59->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button59->Location = System::Drawing::Point(213, 305);
			this->button59->Name = L"button59";
			this->button59->Size = System::Drawing::Size(40, 40);
			this->button59->TabIndex = 61;
			this->button59->UseVisualStyleBackColor = false;
			this->button59->Click += gcnew System::EventHandler(this, &SudokuForm::button59_Click);
			this->button59->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button60
			// 
			this->button60->BackColor = System::Drawing::SystemColors::Menu;
			this->button60->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button60->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button60->Location = System::Drawing::Point(256, 305);
			this->button60->Name = L"button60";
			this->button60->Size = System::Drawing::Size(40, 40);
			this->button60->TabIndex = 62;
			this->button60->UseVisualStyleBackColor = false;
			this->button60->Click += gcnew System::EventHandler(this, &SudokuForm::button60_Click);
			this->button60->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button61
			// 
			this->button61->BackColor = System::Drawing::SystemColors::Menu;
			this->button61->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button61->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button61->Location = System::Drawing::Point(305, 305);
			this->button61->Name = L"button61";
			this->button61->Size = System::Drawing::Size(40, 40);
			this->button61->TabIndex = 63;
			this->button61->UseVisualStyleBackColor = false;
			this->button61->Click += gcnew System::EventHandler(this, &SudokuForm::button61_Click);
			this->button61->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button62
			// 
			this->button62->BackColor = System::Drawing::SystemColors::Menu;
			this->button62->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button62->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button62->Location = System::Drawing::Point(348, 305);
			this->button62->Name = L"button62";
			this->button62->Size = System::Drawing::Size(40, 40);
			this->button62->TabIndex = 64;
			this->button62->UseVisualStyleBackColor = false;
			this->button62->Click += gcnew System::EventHandler(this, &SudokuForm::button62_Click);
			this->button62->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button63
			// 
			this->button63->BackColor = System::Drawing::SystemColors::Menu;
			this->button63->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button63->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button63->Location = System::Drawing::Point(391, 305);
			this->button63->Name = L"button63";
			this->button63->Size = System::Drawing::Size(40, 40);
			this->button63->TabIndex = 65;
			this->button63->UseVisualStyleBackColor = false;
			this->button63->Click += gcnew System::EventHandler(this, &SudokuForm::button63_Click);
			this->button63->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button64
			// 
			this->button64->BackColor = System::Drawing::SystemColors::Menu;
			this->button64->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button64->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button64->Location = System::Drawing::Point(35, 348);
			this->button64->Name = L"button64";
			this->button64->Size = System::Drawing::Size(40, 40);
			this->button64->TabIndex = 66;
			this->button64->UseVisualStyleBackColor = false;
			this->button64->Click += gcnew System::EventHandler(this, &SudokuForm::button64_Click);
			this->button64->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button65
			// 
			this->button65->BackColor = System::Drawing::SystemColors::Menu;
			this->button65->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button65->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button65->Location = System::Drawing::Point(78, 348);
			this->button65->Name = L"button65";
			this->button65->Size = System::Drawing::Size(40, 40);
			this->button65->TabIndex = 67;
			this->button65->UseVisualStyleBackColor = false;
			this->button65->Click += gcnew System::EventHandler(this, &SudokuForm::button65_Click);
			this->button65->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button66
			// 
			this->button66->BackColor = System::Drawing::SystemColors::Menu;
			this->button66->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button66->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button66->Location = System::Drawing::Point(121, 348);
			this->button66->Name = L"button66";
			this->button66->Size = System::Drawing::Size(40, 40);
			this->button66->TabIndex = 68;
			this->button66->UseVisualStyleBackColor = false;
			this->button66->Click += gcnew System::EventHandler(this, &SudokuForm::button66_Click);
			this->button66->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button67
			// 
			this->button67->BackColor = System::Drawing::SystemColors::Menu;
			this->button67->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button67->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button67->Location = System::Drawing::Point(170, 348);
			this->button67->Name = L"button67";
			this->button67->Size = System::Drawing::Size(40, 40);
			this->button67->TabIndex = 69;
			this->button67->UseVisualStyleBackColor = false;
			this->button67->Click += gcnew System::EventHandler(this, &SudokuForm::button67_Click);
			this->button67->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button68
			// 
			this->button68->BackColor = System::Drawing::SystemColors::Menu;
			this->button68->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button68->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button68->Location = System::Drawing::Point(213, 348);
			this->button68->Name = L"button68";
			this->button68->Size = System::Drawing::Size(40, 40);
			this->button68->TabIndex = 70;
			this->button68->UseVisualStyleBackColor = false;
			this->button68->Click += gcnew System::EventHandler(this, &SudokuForm::button68_Click);
			this->button68->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button69
			// 
			this->button69->BackColor = System::Drawing::SystemColors::Menu;
			this->button69->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button69->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button69->Location = System::Drawing::Point(256, 348);
			this->button69->Name = L"button69";
			this->button69->Size = System::Drawing::Size(40, 40);
			this->button69->TabIndex = 71;
			this->button69->UseVisualStyleBackColor = false;
			this->button69->Click += gcnew System::EventHandler(this, &SudokuForm::button69_Click);
			this->button69->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button70
			// 
			this->button70->BackColor = System::Drawing::SystemColors::Menu;
			this->button70->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button70->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button70->Location = System::Drawing::Point(305, 348);
			this->button70->Name = L"button70";
			this->button70->Size = System::Drawing::Size(40, 40);
			this->button70->TabIndex = 72;
			this->button70->UseVisualStyleBackColor = false;
			this->button70->Click += gcnew System::EventHandler(this, &SudokuForm::button70_Click);
			this->button70->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button71
			// 
			this->button71->BackColor = System::Drawing::SystemColors::Menu;
			this->button71->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button71->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button71->Location = System::Drawing::Point(348, 348);
			this->button71->Name = L"button71";
			this->button71->Size = System::Drawing::Size(40, 40);
			this->button71->TabIndex = 73;
			this->button71->UseVisualStyleBackColor = false;
			this->button71->Click += gcnew System::EventHandler(this, &SudokuForm::button71_Click);
			this->button71->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button72
			// 
			this->button72->BackColor = System::Drawing::SystemColors::Menu;
			this->button72->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button72->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button72->Location = System::Drawing::Point(391, 348);
			this->button72->Name = L"button72";
			this->button72->Size = System::Drawing::Size(40, 40);
			this->button72->TabIndex = 74;
			this->button72->UseVisualStyleBackColor = false;
			this->button72->Click += gcnew System::EventHandler(this, &SudokuForm::button72_Click);
			this->button72->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button73
			// 
			this->button73->BackColor = System::Drawing::SystemColors::Menu;
			this->button73->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button73->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button73->Location = System::Drawing::Point(35, 391);
			this->button73->Name = L"button73";
			this->button73->Size = System::Drawing::Size(40, 40);
			this->button73->TabIndex = 75;
			this->button73->UseVisualStyleBackColor = false;
			this->button73->Click += gcnew System::EventHandler(this, &SudokuForm::button73_Click);
			this->button73->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button74
			// 
			this->button74->BackColor = System::Drawing::SystemColors::Menu;
			this->button74->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button74->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button74->Location = System::Drawing::Point(78, 391);
			this->button74->Name = L"button74";
			this->button74->Size = System::Drawing::Size(40, 40);
			this->button74->TabIndex = 76;
			this->button74->UseVisualStyleBackColor = false;
			this->button74->Click += gcnew System::EventHandler(this, &SudokuForm::button74_Click);
			this->button74->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button75
			// 
			this->button75->BackColor = System::Drawing::SystemColors::Menu;
			this->button75->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button75->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button75->Location = System::Drawing::Point(121, 391);
			this->button75->Name = L"button75";
			this->button75->Size = System::Drawing::Size(40, 40);
			this->button75->TabIndex = 77;
			this->button75->UseVisualStyleBackColor = false;
			this->button75->Click += gcnew System::EventHandler(this, &SudokuForm::button75_Click);
			this->button75->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button76
			// 
			this->button76->BackColor = System::Drawing::SystemColors::Menu;
			this->button76->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button76->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button76->Location = System::Drawing::Point(170, 391);
			this->button76->Name = L"button76";
			this->button76->Size = System::Drawing::Size(40, 40);
			this->button76->TabIndex = 78;
			this->button76->UseVisualStyleBackColor = false;
			this->button76->Click += gcnew System::EventHandler(this, &SudokuForm::button76_Click);
			this->button76->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button77
			// 
			this->button77->BackColor = System::Drawing::SystemColors::Menu;
			this->button77->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button77->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button77->Location = System::Drawing::Point(213, 391);
			this->button77->Name = L"button77";
			this->button77->Size = System::Drawing::Size(40, 40);
			this->button77->TabIndex = 79;
			this->button77->UseVisualStyleBackColor = false;
			this->button77->Click += gcnew System::EventHandler(this, &SudokuForm::button77_Click);
			this->button77->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button78
			// 
			this->button78->BackColor = System::Drawing::SystemColors::Menu;
			this->button78->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button78->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button78->Location = System::Drawing::Point(256, 391);
			this->button78->Name = L"button78";
			this->button78->Size = System::Drawing::Size(40, 40);
			this->button78->TabIndex = 80;
			this->button78->UseVisualStyleBackColor = false;
			this->button78->Click += gcnew System::EventHandler(this, &SudokuForm::button78_Click);
			this->button78->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button79
			// 
			this->button79->BackColor = System::Drawing::SystemColors::Menu;
			this->button79->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button79->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button79->Location = System::Drawing::Point(305, 391);
			this->button79->Name = L"button79";
			this->button79->Size = System::Drawing::Size(40, 40);
			this->button79->TabIndex = 81;
			this->button79->UseVisualStyleBackColor = false;
			this->button79->Click += gcnew System::EventHandler(this, &SudokuForm::button79_Click);
			this->button79->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button80
			// 
			this->button80->BackColor = System::Drawing::SystemColors::Menu;
			this->button80->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button80->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button80->Location = System::Drawing::Point(348, 391);
			this->button80->Name = L"button80";
			this->button80->Size = System::Drawing::Size(40, 40);
			this->button80->TabIndex = 82;
			this->button80->UseVisualStyleBackColor = false;
			this->button80->Click += gcnew System::EventHandler(this, &SudokuForm::button80_Click);
			this->button80->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// button81
			// 
			this->button81->BackColor = System::Drawing::SystemColors::Menu;
			this->button81->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button81->Font = (gcnew System::Drawing::Font(L"Cambria", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button81->Location = System::Drawing::Point(391, 391);
			this->button81->Name = L"button81";
			this->button81->Size = System::Drawing::Size(40, 40);
			this->button81->TabIndex = 83;
			this->button81->UseVisualStyleBackColor = false;
			this->button81->Click += gcnew System::EventHandler(this, &SudokuForm::button81_Click);
			this->button81->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SudokuForm::buttonKeyPress);
			// 
			// buttonMinimize
			// 
			this->buttonMinimize->FlatAppearance->BorderSize = 0;
			this->buttonMinimize->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonMinimize->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonMinimize->Location = System::Drawing::Point(560, 0);
			this->buttonMinimize->Name = L"buttonMinimize";
			this->buttonMinimize->Size = System::Drawing::Size(50, 50);
			this->buttonMinimize->TabIndex = 84;
			this->buttonMinimize->TabStop = false;
			this->buttonMinimize->Text = L"_";
			this->buttonMinimize->UseVisualStyleBackColor = true;
			this->buttonMinimize->Click += gcnew System::EventHandler(this, &SudokuForm::buttonMinimize_Click);
			// 
			// buttonClose
			// 
			this->buttonClose->FlatAppearance->BorderSize = 0;
			this->buttonClose->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonClose->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonClose->Location = System::Drawing::Point(610, 0);
			this->buttonClose->Name = L"buttonClose";
			this->buttonClose->Size = System::Drawing::Size(50, 50);
			this->buttonClose->TabIndex = 85;
			this->buttonClose->TabStop = false;
			this->buttonClose->Text = L"X";
			this->buttonClose->UseVisualStyleBackColor = true;
			this->buttonClose->Click += gcnew System::EventHandler(this, &SudokuForm::buttonClose_Click);
			// 
			// difficultyLabel
			// 
			this->difficultyLabel->AutoSize = true;
			this->difficultyLabel->BackColor = System::Drawing::SystemColors::Menu;
			this->difficultyLabel->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->difficultyLabel->Location = System::Drawing::Point(505, 76);
			this->difficultyLabel->Name = L"difficultyLabel";
			this->difficultyLabel->Size = System::Drawing::Size(78, 23);
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
			this->difficultyComboBox->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->difficultyComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"Very Easy", L"Easy", L"Medium", L"Hard",
					L"Very Hard"
			});
			this->difficultyComboBox->Location = System::Drawing::Point(466, 117);
			this->difficultyComboBox->Name = L"difficultyComboBox";
			this->difficultyComboBox->Size = System::Drawing::Size(160, 31);
			this->difficultyComboBox->TabIndex = 86;
			this->difficultyComboBox->TabStop = false;
			this->difficultyComboBox->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SudokuForm::difficultyComboBox_MouseDown);
			// 
			// newCombinationButton
			// 
			this->newCombinationButton->BackColor = System::Drawing::SystemColors::Menu;
			this->newCombinationButton->FlatAppearance->BorderSize = 0;
			this->newCombinationButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->newCombinationButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->newCombinationButton->Location = System::Drawing::Point(466, 335);
			this->newCombinationButton->Name = L"newCombinationButton";
			this->newCombinationButton->Size = System::Drawing::Size(160, 28);
			this->newCombinationButton->TabIndex = 92;
			this->newCombinationButton->TabStop = false;
			this->newCombinationButton->Text = L"New Combo";
			this->newCombinationButton->UseVisualStyleBackColor = false;
			this->newCombinationButton->Click += gcnew System::EventHandler(this, &SudokuForm::newCombinationButton_Click);
			// 
			// newGameButton
			// 
			this->newGameButton->BackColor = System::Drawing::SystemColors::Menu;
			this->newGameButton->FlatAppearance->BorderSize = 0;
			this->newGameButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->newGameButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->newGameButton->Location = System::Drawing::Point(466, 165);
			this->newGameButton->Name = L"newGameButton";
			this->newGameButton->Size = System::Drawing::Size(160, 28);
			this->newGameButton->TabIndex = 87;
			this->newGameButton->TabStop = false;
			this->newGameButton->Text = L"New Game";
			this->newGameButton->UseVisualStyleBackColor = false;
			this->newGameButton->Click += gcnew System::EventHandler(this, &SudokuForm::newGameButton_Click);
			// 
			// RestartButton
			// 
			this->RestartButton->BackColor = System::Drawing::SystemColors::Menu;
			this->RestartButton->FlatAppearance->BorderSize = 0;
			this->RestartButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->RestartButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RestartButton->Location = System::Drawing::Point(466, 199);
			this->RestartButton->Name = L"RestartButton";
			this->RestartButton->Size = System::Drawing::Size(160, 28);
			this->RestartButton->TabIndex = 88;
			this->RestartButton->TabStop = false;
			this->RestartButton->Text = L"Restart";
			this->RestartButton->UseVisualStyleBackColor = false;
			this->RestartButton->Click += gcnew System::EventHandler(this, &SudokuForm::RestartButton_Click);
			// 
			// hintButton
			// 
			this->hintButton->BackColor = System::Drawing::SystemColors::Menu;
			this->hintButton->FlatAppearance->BorderSize = 0;
			this->hintButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->hintButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->hintButton->Location = System::Drawing::Point(466, 233);
			this->hintButton->Name = L"hintButton";
			this->hintButton->Size = System::Drawing::Size(160, 28);
			this->hintButton->TabIndex = 89;
			this->hintButton->TabStop = false;
			this->hintButton->Text = L"Hint";
			this->hintButton->UseVisualStyleBackColor = false;
			this->hintButton->Click += gcnew System::EventHandler(this, &SudokuForm::hintButton_Click);
			// 
			// fixButton
			// 
			this->fixButton->BackColor = System::Drawing::SystemColors::Menu;
			this->fixButton->FlatAppearance->BorderSize = 0;
			this->fixButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->fixButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->fixButton->Location = System::Drawing::Point(466, 267);
			this->fixButton->Name = L"fixButton";
			this->fixButton->Size = System::Drawing::Size(160, 28);
			this->fixButton->TabIndex = 90;
			this->fixButton->TabStop = false;
			this->fixButton->Text = L"Fix";
			this->fixButton->UseVisualStyleBackColor = false;
			this->fixButton->Click += gcnew System::EventHandler(this, &SudokuForm::fixButton_Click);
			// 
			// giveUpButton
			// 
			this->giveUpButton->BackColor = System::Drawing::SystemColors::Menu;
			this->giveUpButton->FlatAppearance->BorderSize = 0;
			this->giveUpButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->giveUpButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->giveUpButton->Location = System::Drawing::Point(466, 301);
			this->giveUpButton->Name = L"giveUpButton";
			this->giveUpButton->Size = System::Drawing::Size(160, 28);
			this->giveUpButton->TabIndex = 91;
			this->giveUpButton->TabStop = false;
			this->giveUpButton->Text = L"Give Up";
			this->giveUpButton->UseVisualStyleBackColor = false;
			this->giveUpButton->Click += gcnew System::EventHandler(this, &SudokuForm::giveUpButton_Click);
			// 
			// customPuzzleButton
			// 
			this->customPuzzleButton->BackColor = System::Drawing::SystemColors::Menu;
			this->customPuzzleButton->FlatAppearance->BorderSize = 0;
			this->customPuzzleButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->customPuzzleButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->customPuzzleButton->Location = System::Drawing::Point(466, 369);
			this->customPuzzleButton->Name = L"customPuzzleButton";
			this->customPuzzleButton->Size = System::Drawing::Size(160, 28);
			this->customPuzzleButton->TabIndex = 93;
			this->customPuzzleButton->TabStop = false;
			this->customPuzzleButton->Text = L"Custom Puzzle";
			this->customPuzzleButton->UseVisualStyleBackColor = false;
			this->customPuzzleButton->Click += gcnew System::EventHandler(this, &SudokuForm::customPuzzleButton_Click);
			// 
			// solveButton
			// 
			this->solveButton->BackColor = System::Drawing::SystemColors::Menu;
			this->solveButton->FlatAppearance->BorderSize = 0;
			this->solveButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->solveButton->Font = (gcnew System::Drawing::Font(L"Calibri", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->solveButton->Location = System::Drawing::Point(466, 403);
			this->solveButton->Name = L"solveButton";
			this->solveButton->Size = System::Drawing::Size(160, 28);
			this->solveButton->TabIndex = 94;
			this->solveButton->TabStop = false;
			this->solveButton->Text = L"Solve";
			this->solveButton->UseVisualStyleBackColor = false;
			this->solveButton->Click += gcnew System::EventHandler(this, &SudokuForm::solveButton_Click);
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
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->fileToolStripMenuItem,
					this->gameToolStripMenuItem, this->optionsToolStripMenuItem, this->helpToolStripMenuItem
			});
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(660, 24);
			this->menuStrip->TabIndex = 0;
			this->menuStrip->Text = L"menuStrip";
			this->menuStrip->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &SudokuForm::menuStrip_ItemClicked);
			this->menuStrip->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SudokuForm::menuStrip_MouseDown);
			this->menuStrip->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &SudokuForm::menuStrip_MouseMove);
			this->menuStrip->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &SudokuForm::menuStrip_MouseUp);
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->saveToolStripMenuItem,
					this->openToolStripMenuItem, this->minimizeToolStripMenuItem, this->exitToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
			this->saveToolStripMenuItem->Size = System::Drawing::Size(200, 22);
			this->saveToolStripMenuItem->Text = L"Save";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::saveToolStripMenuItem_Click);
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
			this->openToolStripMenuItem->Size = System::Drawing::Size(200, 22);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::openToolStripMenuItem_Click);
			// 
			// minimizeToolStripMenuItem
			// 
			this->minimizeToolStripMenuItem->Name = L"minimizeToolStripMenuItem";
			this->minimizeToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift)
				| System::Windows::Forms::Keys::M));
			this->minimizeToolStripMenuItem->Size = System::Drawing::Size(200, 22);
			this->minimizeToolStripMenuItem->Text = L"Minimize";
			this->minimizeToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::minimizeToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift)
				| System::Windows::Forms::Keys::E));
			this->exitToolStripMenuItem->Size = System::Drawing::Size(200, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::exitToolStripMenuItem_Click);
			// 
			// gameToolStripMenuItem
			// 
			this->gameToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {
				this->newGameToolStripMenuItem,
					this->RestartToolStripMenuItem, this->hintToolStripMenuItem, this->fixToolStripMenuItem, this->giveUpToolStripMenuItem, this->newCombinationToolStripMenuItem,
					this->customPuzzleToolStripMenuItem, this->solveToolStripMenuItem
			});
			this->gameToolStripMenuItem->Name = L"gameToolStripMenuItem";
			this->gameToolStripMenuItem->Size = System::Drawing::Size(50, 20);
			this->gameToolStripMenuItem->Text = L"Game";
			// 
			// newGameToolStripMenuItem
			// 
			this->newGameToolStripMenuItem->Name = L"newGameToolStripMenuItem";
			this->newGameToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
			this->newGameToolStripMenuItem->Size = System::Drawing::Size(193, 22);
			this->newGameToolStripMenuItem->Text = L"New Game";
			this->newGameToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::newGameToolStripMenuItem_Click);
			// 
			// RestartToolStripMenuItem
			// 
			this->RestartToolStripMenuItem->Name = L"RestartToolStripMenuItem";
			this->RestartToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::R));
			this->RestartToolStripMenuItem->Size = System::Drawing::Size(193, 22);
			this->RestartToolStripMenuItem->Text = L"Restart";
			this->RestartToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::RestartToolStripMenuItem_Click);
			// 
			// hintToolStripMenuItem
			// 
			this->hintToolStripMenuItem->Name = L"hintToolStripMenuItem";
			this->hintToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::H));
			this->hintToolStripMenuItem->Size = System::Drawing::Size(193, 22);
			this->hintToolStripMenuItem->Text = L"Hint";
			this->hintToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::hintToolStripMenuItem_Click);
			// 
			// fixToolStripMenuItem
			// 
			this->fixToolStripMenuItem->Name = L"fixToolStripMenuItem";
			this->fixToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::F));
			this->fixToolStripMenuItem->Size = System::Drawing::Size(193, 22);
			this->fixToolStripMenuItem->Text = L"Fix";
			this->fixToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::fixToolStripMenuItem_Click);
			// 
			// giveUpToolStripMenuItem
			// 
			this->giveUpToolStripMenuItem->Name = L"giveUpToolStripMenuItem";
			this->giveUpToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::G));
			this->giveUpToolStripMenuItem->Size = System::Drawing::Size(193, 22);
			this->giveUpToolStripMenuItem->Text = L"Give Up";
			this->giveUpToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::giveUpToolStripMenuItem_Click);
			// 
			// newCombinationToolStripMenuItem
			// 
			this->newCombinationToolStripMenuItem->Name = L"newCombinationToolStripMenuItem";
			this->newCombinationToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::M));
			this->newCombinationToolStripMenuItem->Size = System::Drawing::Size(193, 22);
			this->newCombinationToolStripMenuItem->Text = L"New Combo";
			this->newCombinationToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::newCombinationToolStripMenuItem_Click);
			// 
			// customPuzzleToolStripMenuItem
			// 
			this->customPuzzleToolStripMenuItem->Name = L"customPuzzleToolStripMenuItem";
			this->customPuzzleToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::P));
			this->customPuzzleToolStripMenuItem->Size = System::Drawing::Size(193, 22);
			this->customPuzzleToolStripMenuItem->Text = L"Custom Puzzle";
			this->customPuzzleToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::customPuzzleToolStripMenuItem_Click);
			// 
			// solveToolStripMenuItem
			// 
			this->solveToolStripMenuItem->Name = L"solveToolStripMenuItem";
			this->solveToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::L));
			this->solveToolStripMenuItem->Size = System::Drawing::Size(193, 22);
			this->solveToolStripMenuItem->Text = L"Solve";
			this->solveToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::solveToolStripMenuItem_Click);
			// 
			// optionsToolStripMenuItem
			// 
			this->optionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->difficultyToolStripMenuItem });
			this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(61, 20);
			this->optionsToolStripMenuItem->Text = L"Options";
			// 
			// difficultyToolStripMenuItem
			// 
			this->difficultyToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->veryEasyToolStripMenuItem,
					this->easyToolStripMenuItem, this->mediumToolStripMenuItem, this->hardToolStripMenuItem, this->veryHardToolStripMenuItem
			});
			this->difficultyToolStripMenuItem->Name = L"difficultyToolStripMenuItem";
			this->difficultyToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->difficultyToolStripMenuItem->Text = L"Difficulty";
			// 
			// veryEasyToolStripMenuItem
			// 
			this->veryEasyToolStripMenuItem->Name = L"veryEasyToolStripMenuItem";
			this->veryEasyToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D1));
			this->veryEasyToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->veryEasyToolStripMenuItem->Text = L"Very Easy";
			this->veryEasyToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::veryEasyToolStripMenuItem_Click);
			// 
			// easyToolStripMenuItem
			// 
			this->easyToolStripMenuItem->Name = L"easyToolStripMenuItem";
			this->easyToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D2));
			this->easyToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->easyToolStripMenuItem->Text = L"Easy";
			this->easyToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::easyToolStripMenuItem_Click);
			// 
			// mediumToolStripMenuItem
			// 
			this->mediumToolStripMenuItem->Name = L"mediumToolStripMenuItem";
			this->mediumToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D3));
			this->mediumToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->mediumToolStripMenuItem->Text = L"Medium";
			this->mediumToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::mediumToolStripMenuItem_Click);
			// 
			// hardToolStripMenuItem
			// 
			this->hardToolStripMenuItem->Name = L"hardToolStripMenuItem";
			this->hardToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D4));
			this->hardToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->hardToolStripMenuItem->Text = L"Hard";
			this->hardToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::hardToolStripMenuItem_Click);
			// 
			// veryHardToolStripMenuItem
			// 
			this->veryHardToolStripMenuItem->Name = L"veryHardToolStripMenuItem";
			this->veryHardToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D5));
			this->veryHardToolStripMenuItem->Size = System::Drawing::Size(166, 22);
			this->veryHardToolStripMenuItem->Text = L"Very Hard";
			this->veryHardToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::veryHardToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->aboutToolStripMenuItem,
					this->rulesToolStripMenuItem, this->featuresToolStripMenuItem, this->hintsAndTipsToolStripMenuItem, this->keyboardToolStripMenuItem
			});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::A));
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(194, 22);
			this->aboutToolStripMenuItem->Text = L"About";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::aboutToolStripMenuItem_Click);
			// 
			// rulesToolStripMenuItem
			// 
			this->rulesToolStripMenuItem->Name = L"rulesToolStripMenuItem";
			this->rulesToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::B));
			this->rulesToolStripMenuItem->Size = System::Drawing::Size(194, 22);
			this->rulesToolStripMenuItem->Text = L"Rules";
			this->rulesToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::rulesToolStripMenuItem_Click);
			// 
			// featuresToolStripMenuItem
			// 
			this->featuresToolStripMenuItem->Name = L"featuresToolStripMenuItem";
			this->featuresToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::C));
			this->featuresToolStripMenuItem->Size = System::Drawing::Size(194, 22);
			this->featuresToolStripMenuItem->Text = L"Features";
			this->featuresToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::featuresToolStripMenuItem_Click);
			// 
			// hintsAndTipsToolStripMenuItem
			// 
			this->hintsAndTipsToolStripMenuItem->Name = L"hintsAndTipsToolStripMenuItem";
			this->hintsAndTipsToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D));
			this->hintsAndTipsToolStripMenuItem->Size = System::Drawing::Size(194, 22);
			this->hintsAndTipsToolStripMenuItem->Text = L"Hints And Tips";
			this->hintsAndTipsToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::hintsAndTipsToolStripMenuItem_Click);
			// 
			// keyboardToolStripMenuItem
			// 
			this->keyboardToolStripMenuItem->Name = L"keyboardToolStripMenuItem";
			this->keyboardToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::E));
			this->keyboardToolStripMenuItem->Size = System::Drawing::Size(194, 22);
			this->keyboardToolStripMenuItem->Text = L"Keyboard";
			this->keyboardToolStripMenuItem->Click += gcnew System::EventHandler(this, &SudokuForm::keyboardToolStripMenuItem_Click);
			// 
			// SudokuForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnablePreventFocusChange;
			this->BackColor = System::Drawing::SystemColors::Menu;
			this->ClientSize = System::Drawing::Size(660, 460);
			this->Controls->Add(this->solveButton);
			this->Controls->Add(this->customPuzzleButton);
			this->Controls->Add(this->giveUpButton);
			this->Controls->Add(this->fixButton);
			this->Controls->Add(this->hintButton);
			this->Controls->Add(this->RestartButton);
			this->Controls->Add(this->newGameButton);
			this->Controls->Add(this->newCombinationButton);
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
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(660, 460);
			this->MinimumSize = System::Drawing::Size(660, 460);
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
			// Location of the form
			int left = this->Left + (this->Width - this->notificationForm->Width) / 2;
			int top = this->Top + (this->Height - this->notificationForm->Height) / 2;

			this->notificationForm->Left = left;
			this->notificationForm->Top = top;
			this->notificationForm->setMessage(message);
			this->notificationForm->Visible = true;
			this->notificationForm->Activate();
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

			// Create notifications form
			this->notificationForm = gcnew Sudoku_3_0::Notification();
			this->notificationForm->Visible = true;
			this->notificationForm->Visible = false;

			// About and Rules forms will be created on demand
			this->aboutForm = nullptr;
			this->rulesForm = nullptr;

			// Initialize dragging state
			this->dragging = false;
			this->offset = this->Location;

			// Initialize cells
			this->cells = gcnew array<System::Windows::Forms::Button^>(this->boardSize * this->boardSize);
			this->initializeCells();

			// Initialize the form
			this->numbersFormActive = false;
			this->numberOfFilledCells = 0;
			this->isHint = false;
			this->numberOfHints = 0;
			this->gameMode = 3;
			this->currentDifficulty = 2;
			this->difficultyComboBox->SelectedIndex = currentDifficulty;
			this->difficultyComboBox->Select();
			this->newGameButton->Select();

			// Start a new game
			this->newGame(SudokuGameEngine::DifficultyLevel::Medium);
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
					cell->Enabled = enableCells;
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
						cell->Text = ((int) engine->getCellValue(i, j)).ToString();
					}
					else
					{
						if (engine->getFilled(i, j))
						{
							cell->Text = ((int) engine->operator()(i, j)).ToString();
						}
						else
						{
							cell->Text = String::Empty;
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
			this->gameMode = 1;
			this->numberOfHints = 0;
			this->RestartButton->Enabled = true;
			this->hintButton->Enabled = true;
			this->fixButton->Enabled = true;
			this->giveUpButton->Enabled = true;
			this->solveButton->Enabled = false;
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
			if (this->numberOfFilledCells == this->boardSize * this->boardSize)
			{
				if (this->checkSolution())
				{
					for (unsigned int i = 0; i < this->boardSize * this->boardSize; ++i)
					{
						if (this->cells[i]->Enabled)
						{
							this->cells[i]->Enabled = false;
							this->cells[i]->ForeColor = correctColor;
						}
					}

					this->disableHint();
					this->difficultyComboBox->SelectedIndex = this->currentDifficulty;
					this->hintButton->Enabled = false;
					this->fixButton->Enabled = false;
					this->giveUpButton->Enabled = false;

					if (this->numberOfHints == 0)
					{
						this->showNotification("Congratulations! You won without hints!");
					}
					else if (this->numberOfHints == 1)
					{
						this->showNotification("Congratulations! You only used one hint!");
					}
					else
					{
						this->showNotification("You completed the game using " + this->numberOfHints + " hints!");
					}
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
				if (currentButton->Text->Length == 0)
				{
					++(this->numberOfFilledCells);
				}

				currentButton->Text =
					((int) this->engine->getCellValue(
					((number - 1) / this->boardSize),
					((number - 1) % this->boardSize))).ToString();
				currentButton->Enabled = false;
				currentButton->ForeColor = hintColor;
				++(this->numberOfHints);

				this->checkGameState();
			}
			// Else show the numbers form
			else
			{
				// Location of the numbers window
				int left(this->Left), top(this->Top);

				left += currentButton->Left;

				if (number <= this->boardSize*this->boardSize / 3)
				{
					top += currentButton->Top;
				}
				else if (number <= this->boardSize*this->boardSize * 2 / 3)
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
			if (changed)
			{
				if (cell->Text->Length == 0)
				{
					if (choice != 0)
					{
						cell->Text = choice.ToString();
						++(this->numberOfFilledCells);
						this->highlightCellConflict(cellNumber - 1);
					}
				}
				else
				{
					if (choice == 0)
					{
						cell->Text = String::Empty;
						--(this->numberOfFilledCells);
					}
					else
					{
						cell->Text = choice.ToString();
						this->highlightCellConflict(cellNumber - 1);
					}
				}

				this->checkGameState();
			}
			else
			{
				this->highlightCellConflict(cellNumber - 1);
			}
		}

		private: void highlightCellConflict(const unsigned int cellNumber)
		{
			if (this->cells[cellNumber]->Text->Length > 0)
			{
				// Coordinates of the cell
				const unsigned int rowIndex = cellNumber / this->boardSize;
				const unsigned int columnIndex = cellNumber % this->boardSize;;

				// First cells in the cell's row and column respectively
				unsigned int row = rowIndex * this->boardSize;
				unsigned int column = columnIndex;

				// No conflicts have been found yet
				bool conflict = false;

				// Check row and column
				while (row < this->numberOfCells && column < this->numberOfCells)
				{
					if (row != cellNumber)
					{
						if (this->cells[row]->Text->Equals(this->cells[cellNumber]->Text))
						{
							conflict = true;
							break;
						}
					}

					if (column != cellNumber)
					{
						if (this->cells[column]->Text->Equals(this->cells[cellNumber]->Text))
						{
							conflict = true;
							break;
						}
					}

					row += 1;
					column += this->boardSize;
				}

				// Check block if no conflicts have been found in row and column
				if (!conflict)
				{
					// Row number of the first cell in the block
					const unsigned int rBegin((rowIndex / this->sizeFactor) * this->sizeFactor);

					// Column number of the first cell in the block
					const unsigned int cBegin((columnIndex / this->sizeFactor) * this->sizeFactor);

					// Row number after the last cell in the block
					const unsigned int rEnd(rBegin + this->sizeFactor);

					// Column number after the last cell in the block
					const unsigned int cEnd(cBegin + this->sizeFactor);

					// Iterate through each cell in the block
					for (unsigned int i = rBegin; i < rEnd; ++i)
					{
						for (unsigned int j = cBegin; j < cEnd && !conflict; ++j)
						{
							if (i * this->boardSize + j != cellNumber)
							{
								// Check if it contains the value
								if (this->cells[i * this->boardSize + j]->Text->Equals(this->cells[cellNumber]->Text))
								{
									conflict = true;
									break;
								}
							}
						}
					}
				}

				if (conflict)
				{
					this->cells[cellNumber]->BackColor = conflictBackColor;
					this->Refresh();
					System::Threading::Thread::Sleep(100);
					this->cells[cellNumber]->BackColor = defaultBackColor;
				}
			}
		}

		// Close the numbers form if it is open
		private: void closeHelperForms()
		{
			// Close numbers form
			this->numbersForm->Visible = false;
			this->numbersFormActive = false;

			// Close notifications form
			this->notificationForm->Visible = false;

			// Close about form
			if (this->aboutForm != nullptr)
			{
				this->aboutForm->Visible = false;
			}

			// Close rules form
			if (this->rulesForm != nullptr)
			{
				this->rulesForm->Visible = false;
			}

			// Close features form
			if (this->featuresForm != nullptr)
			{
				this->featuresForm->Visible = false;
			}

			// Close hints and tips form
			if (this->hintsAndTipsForm != nullptr)
			{
				this->hintsAndTipsForm->Visible = false;
			}

			// Close keyboard form
			if (this->keyboardForm != nullptr)
			{
				this->keyboardForm->Visible = false;
			}
		}

		// Enable hint mode
		private: void enableHint()
		{
			this->isHint = true;
			this->hintButton->ForeColor = hintButtonColor;
		}

		// Enable hint mode
		private: void disableHint()
		{
			this->isHint = false;
			this->hintButton->ForeColor = defaultColor;
		}

		private: void newGameButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
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

		private: void RestartButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->closeHelperForms();
			this->disableHint();

			this->numberOfFilledCells = 0;
			this->numberOfHints = 0;

			// Fill the board
			for (unsigned int index = 0; index < this->boardSize * this->boardSize; ++index)
			{
				Button^ cell = this->cells[index];
				if (!cell->Enabled && cell->ForeColor == defaultColor)
				{
					++this->numberOfFilledCells;
				}
				else
				{
					cell->Text = System::String::Empty;
					cell->ForeColor = defaultColor;
					cell->Enabled = true;
				}
			}

			this->difficultyComboBox->SelectedIndex = this->currentDifficulty;
			this->hintButton->Enabled = true;
			this->fixButton->Enabled = true;
			this->giveUpButton->Enabled = true;
		}

		private: void hintButton_Click(System::Object^  sender, System::EventArgs^  e)
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

		private: void fixButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->closeHelperForms();

			++this->numberOfHints;

			unsigned int index = 0;
			for (unsigned int i = 0; i < this->boardSize; ++i)
				for (unsigned int j = 0; j < this->boardSize; ++j)
				{
					if (this->cells[index]->Enabled && 
						!this->cells[index]->Text->Equals(String::Empty) &&
						!this->cells[index]->Text->Equals(((int) this->engine->getCellValue(i, j)).ToString()))
					{
						this->cells[index]->Text = "";
						--(this->numberOfFilledCells);
					}

					++index;
				}
		}

		private: void giveUpButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->closeHelperForms();
			this->disableHint();

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

						cell->Text = ((int) engine->getCellValue(i, j)).ToString();
						cell->ForeColor = giveUpColor;
						cell->Enabled = false;
					}

					++index;
				}
			}

			this->difficultyComboBox->SelectedIndex = this->currentDifficulty;
			this->hintButton->Enabled = false;
			this->fixButton->Enabled = false;
			this->giveUpButton->Enabled = false;
		}

		private: void newCombinationButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->closeHelperForms();
			this->disableHint();

			this->engine->newCombination();
			this->fillBoardFromEngine(false);

			this->gameMode = 0;
			this->RestartButton->Enabled = false;
			this->hintButton->Enabled = false;
			this->fixButton->Enabled = false;
			this->giveUpButton->Enabled = false;
			this->solveButton->Enabled = false;
		}

		private: void customPuzzleButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->closeHelperForms();
			this->disableHint();

			this->engine->clear();
			this->clearBoard(true);

			this->gameMode = 2;
			this->RestartButton->Enabled = false;
			this->hintButton->Enabled = false;
			this->fixButton->Enabled = false;
			this->giveUpButton->Enabled = false;
			this->solveButton->Enabled = true;
		}

		private: void solveButton_Click(System::Object^  sender, System::EventArgs^  e)
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
							cell->Text = ((int) engine->getCellValue(i, j)).ToString();
							cell->ForeColor = solveColor;
						}

						cell->Enabled = false;
						++index;
					}
				}

				this->solveButton->Enabled = false;
			}
			else if (engine->currentState() == SudokuGameEngine::SudokuEngineState::HasMultipleSolutions)
			{
				this->showNotification("The puzzle has multiple solutions!");
			}
			else if (
				engine->currentState() == SudokuGameEngine::SudokuEngineState::HasNoSolution ||
				engine->currentState() == SudokuGameEngine::SudokuEngineState::FilledInvalid)
			{
				this->showNotification("The puzzle has no solution!");
			}
			else if (engine->currentState() == SudokuGameEngine::SudokuEngineState::Empty)
			{
				this->showNotification("The board is empty!");
			}
		}

		private: void menuStrip_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e)
		{
			this->closeHelperForms();
		}

		private: void saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->gameMode >= 0 && this->gameMode <= 2)
			{
				this->saveGameDialog->ShowDialog();
			}
		}

		private: void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->openGameDialog->ShowDialog();
		}

		private: void minimizeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->closeHelperForms();
			this->buttonMinimize_Click(sender, e);
		}

		private: void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->closeHelperForms();
			this->buttonClose_Click(sender, e);
		}

		private: void newGameToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->newGameButton->Enabled)
			{
				this->newGameButton_Click(sender, e);
			}
		}

		private: void RestartToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->RestartButton->Enabled)
			{
				this->RestartButton_Click(sender, e);
			}
		}

		private: void hintToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->hintButton->Enabled)
			{
				this->hintButton_Click(sender, e);
			}
		}

		private: void fixToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->fixButton->Enabled)
			{
				this->fixButton_Click(sender, e);
			}
		}

		private: void giveUpToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->giveUpButton->Enabled)
			{
				this->giveUpButton_Click(sender, e);
			}
		}

		private: void customPuzzleToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->customPuzzleButton->Enabled)
			{
				this->customPuzzleButton_Click(sender, e);
			}
		}

		private: void solveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->solveButton->Enabled)
			{
				this->solveButton_Click(sender, e);
			}
		}

		private: void newCombinationToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->newCombinationButton->Enabled)
			{
				this->newCombinationButton_Click(sender, e);
			}
		}

		private: void veryEasyToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->difficultyComboBox->SelectedIndex = 0;
			this->difficultyComboBox->Select();
		}

		private: void easyToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->difficultyComboBox->SelectedIndex = 1;
			this->difficultyComboBox->Select();
		}

		private: void mediumToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->difficultyComboBox->SelectedIndex = 2;
			this->difficultyComboBox->Select();
		}

		private: void hardToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->difficultyComboBox->SelectedIndex = 3;
			this->difficultyComboBox->Select();
		}

		private: void veryHardToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->difficultyComboBox->SelectedIndex = 4;
			this->difficultyComboBox->Select();
		}

		private: void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->aboutForm == nullptr)
			{
				this->aboutForm = gcnew Sudoku_3_0::About();
				this->aboutForm->Visible = true;
				this->aboutForm->Visible = false;
			}

			this->initializeForm(this->aboutForm);
		}

		private: void rulesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->rulesForm == nullptr)
			{
				this->rulesForm = gcnew Sudoku_3_0::Rules();
				this->rulesForm->Visible = true;
				this->rulesForm->Visible = false;
			}

			this->initializeForm(this->rulesForm);
		}

		private: void featuresToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->featuresForm == nullptr)
			{
				this->featuresForm = gcnew Sudoku_3_0::Features();
				this->featuresForm->Visible = true;
				this->featuresForm->Visible = false;
			}

			this->initializeForm(this->featuresForm);
		}

		private: void hintsAndTipsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->hintsAndTipsForm == nullptr)
			{
				this->hintsAndTipsForm = gcnew Sudoku_3_0::HintsAndTips();
				this->hintsAndTipsForm->Visible = true;
				this->hintsAndTipsForm->Visible = false;
			}

			this->initializeForm(this->hintsAndTipsForm);
		}

		private: void keyboardToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (this->keyboardForm == nullptr)
			{
				this->keyboardForm = gcnew Sudoku_3_0::Keyboard();
				this->keyboardForm->Visible = true;
				this->keyboardForm->Visible = false;
			}

			this->initializeForm(this->keyboardForm);
		}

		private: void initializeForm(Form^ form)
		{
			form->Left = this->Left + (this->Width - form->Width) / 2;
			form->Top = this->Top + (this->Height - form->Height) / 2;
			form->Visible = true;
			form->Activate();
		}

		private: void button1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(1, sender, e);
		}

		private: void button2_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(2, sender, e);
		}

		private: void button3_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(3, sender, e);
		}

		private: void button4_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(4, sender, e);
		}

		private: void button5_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(5, sender, e);
		}

		private: void button6_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(6, sender, e);
		}

		private: void button7_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(7, sender, e);
		}

		private: void button8_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(8, sender, e);
		}

		private: void button9_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(9, sender, e);
		}

		private: void button10_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(10, sender, e);
		}

		private: void button11_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(11, sender, e);
		}

		private: void button12_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(12, sender, e);
		}

		private: void button13_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(13, sender, e);
		}

		private: void button14_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(14, sender, e);
		}

		private: void button15_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(15, sender, e);
		}

		private: void button16_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(16, sender, e);
		}

		private: void button17_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(17, sender, e);
		}

		private: void button18_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(18, sender, e);
		}

		private: void button19_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(19, sender, e);
		}

		private: void button20_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(20, sender, e);
		}

		private: void button21_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(21, sender, e);
		}

		private: void button22_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(22, sender, e);
		}

		private: void button23_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(23, sender, e);
		}

		private: void button24_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(24, sender, e);
		}

		private: void button25_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(25, sender, e);
		}

		private: void button26_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(26, sender, e);
		}

		private: void button27_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(27, sender, e);
		}

		private: void button28_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(28, sender, e);
		}

		private: void button29_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(29, sender, e);
		}

		private: void button30_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(30, sender, e);
		}

		private: void button31_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(31, sender, e);
		}

		private: void button32_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(32, sender, e);
		}

		private: void button33_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(33, sender, e);
		}

		private: void button34_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(34, sender, e);
		}

		private: void button35_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(35, sender, e);
		}

		private: void button36_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(36, sender, e);
		}

		private: void button37_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(37, sender, e);
		}

		private: void button38_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(38, sender, e);
		}

		private: void button39_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(39, sender, e);
		}

		private: void button40_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(40, sender, e);
		}

		private: void button41_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(41, sender, e);
		}

		private: void button42_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(42, sender, e);
		}

		private: void button43_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(43, sender, e);
		}

		private: void button44_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(44, sender, e);
		}

		private: void button45_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(45, sender, e);
		}

		private: void button46_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(46, sender, e);
		}

		private: void button47_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(47, sender, e);
		}

		private: void button48_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(48, sender, e);
		}

		private: void button49_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(49, sender, e);
		}

		private: void button50_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(50, sender, e);
		}

		private: void button51_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(51, sender, e);
		}

		private: void button52_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(52, sender, e);
		}

		private: void button53_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(53, sender, e);
		}

		private: void button54_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(54, sender, e);
		}

		private: void button55_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(55, sender, e);
		}

		private: void button56_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(56, sender, e);
		}

		private: void button57_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(57, sender, e);
		}

		private: void button58_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(58, sender, e);
		}

		private: void button59_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(59, sender, e);
		}

		private: void button60_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(60, sender, e);
		}

		private: void button61_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(61, sender, e);
		}

		private: void button62_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(62, sender, e);
		}

		private: void button63_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(63, sender, e);
		}

		private: void button64_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(64, sender, e);
		}

		private: void button65_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(65, sender, e);
		}

		private: void button66_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(66, sender, e);
		}

		private: void button67_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(67, sender, e);
		}

		private: void button68_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(68, sender, e);
		}

		private: void button69_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(69, sender, e);
		}

		private: void button70_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(70, sender, e);
		}

		private: void button71_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(71, sender, e);
		}

		private: void button72_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(72, sender, e);
		}

		private: void button73_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(73, sender, e);
		}

		private: void button74_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(74, sender, e);
		}

		private: void button75_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(75, sender, e);
		}

		private: void button76_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(76, sender, e);
		}

		private: void button77_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(77, sender, e);
		}

		private: void button78_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(78, sender, e);
		}

		private: void button79_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(79, sender, e);
		}

		private: void button80_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(80, sender, e);
		}

		private: void button81_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->cellButtonClicked(81, sender, e);
		}

		private: void difficultyComboBox_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		{
			this->closeHelperForms();
		}

		private: void buttonMinimize_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->closeHelperForms();

			this->WindowState = FormWindowState::Minimized;
		}

		private: void buttonClose_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->closeHelperForms();

			this->Close();
		}

		private: void SudokuForm_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		{
			this->closeHelperForms();

			this->dragging = true;
			this->offset = Point(e->X, e->Y);
		}

		private: void SudokuForm_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		{
			if (this->dragging)
			{
				Point currentScreenPos = PointToScreen(e->Location);
				Location = Point(currentScreenPos.X - this->offset.X, currentScreenPos.Y - this->offset.Y);
			}
		}

		private: void SudokuForm_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		{
			this->closeHelperForms();
			this->dragging = false;
		}

		private: void menuStrip_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		{
			this->SudokuForm_MouseDown(sender, e);
		}

		private: void menuStrip_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		{
			this->SudokuForm_MouseMove(sender, e);
		}

		private: void menuStrip_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		{
			this->SudokuForm_MouseUp(sender, e);
		}

		private: void difficultyLabel_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		{
			this->SudokuForm_MouseDown(sender, e);
		}

		private: void difficultyLabel_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		{
			this->SudokuForm_MouseMove(sender, e);
		}

		private: void difficultyLabel_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
		{
			this->SudokuForm_MouseUp(sender, e);
		}

		private: void buttonKeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
		{
			if (!this->isHint)
			{
				int buttonIndex = array<Button^>::IndexOf(this->cells, ((Button^) sender)) + 1;

				unsigned int choice = 0;
				if (e->KeyChar >= '0' && e->KeyChar <= '9')
				{
					choice = e->KeyChar - '0';
				}
				else if (e->KeyChar == 'c')
				{
					choice = 0;
				}

				bool changed = false;
				if (((Button^) sender)->Text->Length == 0 && choice != 0 ||
					((Button^) sender)->Text->Length != 0 && choice == 0 ||
					!((Button^) sender)->Text->Equals(choice.ToString()))
				{
					changed = true;
				}

				this->choiceMade(buttonIndex, changed, choice);
			}
		}

		private: void saveGameDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
		{
			SavedGame^ save = gcnew SavedGame();
			save->sizeFactor = this->engine->sizeOfTheBlock();
			save->difficulty = this->currentDifficulty;
			save->numberOfHints = this->numberOfHints;
			save->gameMode = this->gameMode;
			if (this->gameMode == 0)
			{
				save->gameFinished = true;
			}
			else if (this->gameMode == 1)
			{
				save->gameFinished = !this->giveUpButton->Enabled;
			}
			else
			{
				save->gameFinished = !this->solveButton->Enabled;
			}
			save->value = gcnew String("");
			save->state = gcnew String("");

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

			FileStream^ fileStream = nullptr;

			try
			{
				fileStream = File::Create(this->saveGameDialog->FileName);
				BinaryFormatter^ formatter = gcnew BinaryFormatter();
				formatter->Serialize(fileStream, save);
			}
			catch (...)
			{
				this->showNotification("Could not write the file!");
			}
			finally
			{
				if (fileStream != nullptr)
				{
					fileStream->Close();
				}
			}
		}

		private: void openGameDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
		{
			SavedGame^ save = nullptr;
			FileStream^ fileStream = nullptr;

			try
			{
				// Read save object from the file
				fileStream = File::OpenRead(this->openGameDialog->FileName);
				BinaryFormatter^ formatter = gcnew BinaryFormatter();
				save = (SavedGame^) formatter->Deserialize(fileStream);

				// Only block size 3 is currently supported
				if (save->sizeFactor != 3)
				{
					throw "Invalid sizeFactor value " + save->sizeFactor.ToString();
				}

				// Check if the velues and states strings' lengths are of right length
				if (save->value->Length != this->boardSize * this->boardSize)
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
				this->gameMode = save->gameMode;
				this->RestartButton->Enabled = save->gameMode == 1;
				this->hintButton->Enabled = save->gameMode == 1 && !save->gameFinished;
				this->fixButton->Enabled = save->gameMode == 1 && !save->gameFinished;
				this->giveUpButton->Enabled = save->gameMode == 1 && !save->gameFinished;
				this->solveButton->Enabled = save->gameMode == 2 && !save->gameFinished;

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

						// Check if cell value dows not conflict with cell state
						if (value->Equals("0") != state->Equals("1"))
						{
							throw "Invalid cell value and cell state pair";
						}

						// Fill the engine
						if (save->gameMode == 0)
						{
							if (state->Equals("0"))
							{
								this->engine->setFilled(i, j, true);
								this->engine->setCellValue(i, j, value[0] - '0');
							}
							else
							{
								throw "Invalid cell state value " + state + " for game mode " + save->gameMode.ToString();
							}
						}
						else if (save->gameMode == 1)
						{
							// If the cell was filled by the engine
							if (state->Equals("0"))
							{
								// Fill the engine with it
								this->engine->setFilled(i, j, true);
								this->engine->setCellValue(i, j, value[0] - '0');
							}
							else
							{
								// It was hidden by the engine
								this->engine->setFilled(i, j, false);
							}
						}
						else if (save->gameMode == 2)
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
						if (save->gameMode == 0)
						{
							if (!state->Equals("0"))
							{
								throw "Invalid state " + state + " in game mode " + save->gameMode.ToString();
							}
						}
						else if (save->gameMode == 1)
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
						else if (save->gameMode == 2)
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

				// The engine needs to solve the puzzle for 2 reasons
				// 1) It needs them to check the solution later in case of game mode
				// 2) It allows to check if the game save has not been corrupted
				if (save->gameMode == 0 || save->gameMode == 1 || (save->gameMode == 2 && engine->numberOfFilledCells() > 0))
				{
					this->engine->trySolve();
					if (engine->currentState() != SudokuGameEngine::SudokuEngineState::FilledValid)
					{
						throw "Invalid cell values";
					}
				}
			}
			catch (...)
			{
				// If an error occured, clear the board
				this->clearBoard(false);
				this->RestartButton->Enabled = false;
				this->hintButton->Enabled = false;
				this->fixButton->Enabled = false;
				this->giveUpButton->Enabled = false;
				this->solveButton->Enabled = false;
				this->gameMode = 3;
				this->cells[1]->Text = "B";
				this->cells[4]->Text = "A";
				this->cells[7]->Text = "D";
				this->cells[10]->Text = "F";
				this->cells[12]->Text = "I";
				this->cells[14]->Text = "L";
				this->cells[16]->Text = "E";
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