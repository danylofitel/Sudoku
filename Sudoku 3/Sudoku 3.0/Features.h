#pragma once

namespace Sudoku_3_0
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Features : public System::Windows::Forms::Form
	{
	public:
		Features(void)
		{
			InitializeComponent();
		}

	protected:
		~Features()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  buttonOk;
	private: System::Windows::Forms::Label^  labelNewGame;
	private: System::Windows::Forms::Label^  labelRestart;
	private: System::Windows::Forms::Label^  labelHint;
	private: System::Windows::Forms::Label^  labelFix;
	private: System::Windows::Forms::Label^  labelGiveUp;
	private: System::Windows::Forms::Label^  labelNewCombo;
	private: System::Windows::Forms::Label^  labelCustomPuzzle;
	private: System::Windows::Forms::Label^  labelSolve;
	protected:

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->buttonOk = (gcnew System::Windows::Forms::Button());
			this->labelNewGame = (gcnew System::Windows::Forms::Label());
			this->labelRestart = (gcnew System::Windows::Forms::Label());
			this->labelHint = (gcnew System::Windows::Forms::Label());
			this->labelFix = (gcnew System::Windows::Forms::Label());
			this->labelGiveUp = (gcnew System::Windows::Forms::Label());
			this->labelNewCombo = (gcnew System::Windows::Forms::Label());
			this->labelCustomPuzzle = (gcnew System::Windows::Forms::Label());
			this->labelSolve = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// buttonOk
			// 
			this->buttonOk->FlatAppearance->BorderSize = 0;
			this->buttonOk->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonOk->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 27.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonOk->Location = System::Drawing::Point(225, 348);
			this->buttonOk->Name = L"buttonOk";
			this->buttonOk->Size = System::Drawing::Size(150, 50);
			this->buttonOk->TabIndex = 0;
			this->buttonOk->Text = L"OK";
			this->buttonOk->UseVisualStyleBackColor = true;
			this->buttonOk->Click += gcnew System::EventHandler(this, &Features::buttonOk_Click);
			// 
			// labelNewGame
			// 
			this->labelNewGame->AutoSize = true;
			this->labelNewGame->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelNewGame->Location = System::Drawing::Point(15, 15);
			this->labelNewGame->Name = L"labelNewGame";
			this->labelNewGame->Size = System::Drawing::Size(442, 29);
			this->labelNewGame->TabIndex = 1;
			this->labelNewGame->Text = L"New Game - create a new sudoku game";
			// 
			// labelRestart
			// 
			this->labelRestart->AutoSize = true;
			this->labelRestart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelRestart->Location = System::Drawing::Point(15, 55);
			this->labelRestart->Name = L"labelRestart";
			this->labelRestart->Size = System::Drawing::Size(331, 29);
			this->labelRestart->TabIndex = 2;
			this->labelRestart->Text = L"Restart - restart current puzzle";
			// 
			// labelHint
			// 
			this->labelHint->AutoSize = true;
			this->labelHint->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelHint->Location = System::Drawing::Point(15, 95);
			this->labelHint->Name = L"labelHint";
			this->labelHint->Size = System::Drawing::Size(509, 29);
			this->labelHint->TabIndex = 3;
			this->labelHint->Text = L"Hint - activate hint mode to open selected cells";
			// 
			// labelFix
			// 
			this->labelFix->AutoSize = true;
			this->labelFix->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelFix->Location = System::Drawing::Point(15, 135);
			this->labelFix->Name = L"labelFix";
			this->labelFix->Size = System::Drawing::Size(350, 29);
			this->labelFix->TabIndex = 4;
			this->labelFix->Text = L"Fix - remove all wrong numbers";
			// 
			// labelGiveUp
			// 
			this->labelGiveUp->AutoSize = true;
			this->labelGiveUp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelGiveUp->Location = System::Drawing::Point(15, 175);
			this->labelGiveUp->Name = L"labelGiveUp";
			this->labelGiveUp->Size = System::Drawing::Size(447, 29);
			this->labelGiveUp->TabIndex = 5;
			this->labelGiveUp->Text = L"Give Up - show solution of current puzzle";
			// 
			// labelNewCombo
			// 
			this->labelNewCombo->AutoSize = true;
			this->labelNewCombo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelNewCombo->Location = System::Drawing::Point(15, 215);
			this->labelNewCombo->Name = L"labelNewCombo";
			this->labelNewCombo->Size = System::Drawing::Size(541, 29);
			this->labelNewCombo->TabIndex = 6;
			this->labelNewCombo->Text = L"New Combo - create a new valid 9x9 combination";
			// 
			// labelCustomPuzzle
			// 
			this->labelCustomPuzzle->AutoSize = true;
			this->labelCustomPuzzle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelCustomPuzzle->Location = System::Drawing::Point(15, 255);
			this->labelCustomPuzzle->Name = L"labelCustomPuzzle";
			this->labelCustomPuzzle->Size = System::Drawing::Size(508, 29);
			this->labelCustomPuzzle->TabIndex = 7;
			this->labelCustomPuzzle->Text = L"Custom Puzzle - enter a custom sudoku puzzle";
			// 
			// labelSolve
			// 
			this->labelSolve->AutoSize = true;
			this->labelSolve->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelSolve->Location = System::Drawing::Point(15, 295);
			this->labelSolve->Name = L"labelSolve";
			this->labelSolve->Size = System::Drawing::Size(393, 29);
			this->labelSolve->TabIndex = 8;
			this->labelSolve->Text = L"Solve - solve custom sudoku puzzle";
			// 
			// Features
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(600, 410);
			this->Controls->Add(this->labelSolve);
			this->Controls->Add(this->labelCustomPuzzle);
			this->Controls->Add(this->labelNewCombo);
			this->Controls->Add(this->labelGiveUp);
			this->Controls->Add(this->labelFix);
			this->Controls->Add(this->labelHint);
			this->Controls->Add(this->labelRestart);
			this->Controls->Add(this->labelNewGame);
			this->Controls->Add(this->buttonOk);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Features";
			this->ShowInTaskbar = false;
			this->Text = L"Features";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: System::Void buttonOk_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->Visible = false;
		}
	};
}
