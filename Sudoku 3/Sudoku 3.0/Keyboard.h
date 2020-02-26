#pragma once

namespace Sudoku_3_0
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Keyboard
	/// </summary>
	public ref class Keyboard : public System::Windows::Forms::Form
	{
	public:
		Keyboard(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Keyboard()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  buttonOk;
	private: System::Windows::Forms::Label^  labelKeyboardSupport;
	private: System::Windows::Forms::Label^  labelTab;
	private: System::Windows::Forms::Label^  labelNavigation;
	private: System::Windows::Forms::Label^  labelPress;
	private: System::Windows::Forms::Label^  labelEnterNumber;
	private: System::Windows::Forms::Label^  labelHotkeys;
	private: System::Windows::Forms::Label^  labelListOfHotkeys;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->buttonOk = (gcnew System::Windows::Forms::Button());
			this->labelKeyboardSupport = (gcnew System::Windows::Forms::Label());
			this->labelTab = (gcnew System::Windows::Forms::Label());
			this->labelNavigation = (gcnew System::Windows::Forms::Label());
			this->labelPress = (gcnew System::Windows::Forms::Label());
			this->labelEnterNumber = (gcnew System::Windows::Forms::Label());
			this->labelHotkeys = (gcnew System::Windows::Forms::Label());
			this->labelListOfHotkeys = (gcnew System::Windows::Forms::Label());
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
			this->buttonOk->Click += gcnew System::EventHandler(this, &Keyboard::buttonOk_Click);
			// 
			// labelKeyboardSupport
			// 
			this->labelKeyboardSupport->AutoSize = true;
			this->labelKeyboardSupport->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->labelKeyboardSupport->Location = System::Drawing::Point(15, 15);
			this->labelKeyboardSupport->Name = L"labelKeyboardSupport";
			this->labelKeyboardSupport->Size = System::Drawing::Size(397, 29);
			this->labelKeyboardSupport->TabIndex = 1;
			this->labelKeyboardSupport->Text = L"The game has full keyboard support";
			// 
			// labelTab
			// 
			this->labelTab->AutoSize = true;
			this->labelTab->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelTab->Location = System::Drawing::Point(15, 60);
			this->labelTab->Name = L"labelTab";
			this->labelTab->Size = System::Drawing::Size(276, 29);
			this->labelTab->TabIndex = 2;
			this->labelTab->Text = L"Press Tab to select cells";
			// 
			// labelNavigation
			// 
			this->labelNavigation->AutoSize = true;
			this->labelNavigation->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelNavigation->Location = System::Drawing::Point(15, 105);
			this->labelNavigation->Name = L"labelNavigation";
			this->labelNavigation->Size = System::Drawing::Size(532, 29);
			this->labelNavigation->TabIndex = 3;
			this->labelNavigation->Text = L"Use Tab or arrow keys to navigate between cells";
			// 
			// labelPress
			// 
			this->labelPress->AutoSize = true;
			this->labelPress->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelPress->Location = System::Drawing::Point(15, 150);
			this->labelPress->Name = L"labelPress";
			this->labelPress->Size = System::Drawing::Size(463, 29);
			this->labelPress->TabIndex = 4;
			this->labelPress->Text = L"Press Enter or Space to click celected cell";
			// 
			// labelEnterNumber
			// 
			this->labelEnterNumber->AutoSize = true;
			this->labelEnterNumber->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelEnterNumber->Location = System::Drawing::Point(15, 195);
			this->labelEnterNumber->Name = L"labelEnterNumber";
			this->labelEnterNumber->Size = System::Drawing::Size(464, 29);
			this->labelEnterNumber->TabIndex = 5;
			this->labelEnterNumber->Text = L"Press the number key to quickly fill the cell";
			// 
			// labelHotkeys
			// 
			this->labelHotkeys->AutoSize = true;
			this->labelHotkeys->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelHotkeys->Location = System::Drawing::Point(15, 240);
			this->labelHotkeys->Name = L"labelHotkeys";
			this->labelHotkeys->Size = System::Drawing::Size(269, 29);
			this->labelHotkeys->TabIndex = 6;
			this->labelHotkeys->Text = L"All buttons have hotkeys";
			// 
			// labelListOfHotkeys
			// 
			this->labelListOfHotkeys->AutoSize = true;
			this->labelListOfHotkeys->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelListOfHotkeys->Location = System::Drawing::Point(15, 285);
			this->labelListOfHotkeys->Name = L"labelListOfHotkeys";
			this->labelListOfHotkeys->Size = System::Drawing::Size(523, 29);
			this->labelListOfHotkeys->TabIndex = 7;
			this->labelListOfHotkeys->Text = L"You can see the list of hotkeys in the main menu";
			// 
			// Keyboard
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(600, 410);
			this->Controls->Add(this->labelListOfHotkeys);
			this->Controls->Add(this->labelHotkeys);
			this->Controls->Add(this->labelEnterNumber);
			this->Controls->Add(this->labelPress);
			this->Controls->Add(this->labelNavigation);
			this->Controls->Add(this->labelTab);
			this->Controls->Add(this->labelKeyboardSupport);
			this->Controls->Add(this->buttonOk);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Keyboard";
			this->ShowInTaskbar = false;
			this->Text = L"Keyboard";
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
