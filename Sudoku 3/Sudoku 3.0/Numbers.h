#pragma once

namespace Sudoku_3_0 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public delegate void choiceAction(
		const unsigned int cellNumber,
		const bool changed,
		const unsigned int choice);

	/// <summary>
	/// Number choice form
	/// </summary>
	public ref class Numbers : public System::Windows::Forms::Form
	{
	public:
		Numbers(void) : currentCellNumber(0), choiceMade(false), choice(0)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used
		/// </summary>
		~Numbers()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Button^  button8;
	private: System::Windows::Forms::Button^  button9;
	private: System::Windows::Forms::Button^  buttonClear;
	private: System::Windows::Forms::Button^  buttonCancel;

	// Number of current cell
	private: unsigned int currentCellNumber;

	// True of the choice has been made and false if the action was canceled
	private: bool choiceMade;

	// The number that was chosen
	private: unsigned int choice;

	// Action delegate from the father form
	private: choiceAction^ choiceDelegate;

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->buttonClear = (gcnew System::Windows::Forms::Button());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::Menu;
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(0, 0);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(50, 50);
			this->button1->TabIndex = 0;
			this->button1->Text = L"1";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Numbers::button1_Click);
			this->button1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Numbers::button1_KeyPress);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::SystemColors::Menu;
			this->button2->FlatAppearance->BorderSize = 0;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(50, 0);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(50, 50);
			this->button2->TabIndex = 1;
			this->button2->Text = L"2";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Numbers::button2_Click);
			this->button2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Numbers::button2_KeyPress);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::SystemColors::Menu;
			this->button3->FlatAppearance->BorderSize = 0;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button3->Location = System::Drawing::Point(100, 0);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(50, 50);
			this->button3->TabIndex = 2;
			this->button3->Text = L"3";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &Numbers::button3_Click);
			this->button3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Numbers::button3_KeyPress);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::SystemColors::Menu;
			this->button4->FlatAppearance->BorderSize = 0;
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button4->Location = System::Drawing::Point(0, 50);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(50, 50);
			this->button4->TabIndex = 3;
			this->button4->Text = L"4";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &Numbers::button4_Click);
			this->button4->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Numbers::button4_KeyPress);
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::SystemColors::Menu;
			this->button5->FlatAppearance->BorderSize = 0;
			this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button5->Location = System::Drawing::Point(50, 50);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(50, 50);
			this->button5->TabIndex = 4;
			this->button5->Text = L"5";
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &Numbers::button5_Click);
			this->button5->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Numbers::button5_KeyPress);
			// 
			// button6
			// 
			this->button6->BackColor = System::Drawing::SystemColors::Menu;
			this->button6->FlatAppearance->BorderSize = 0;
			this->button6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button6->Location = System::Drawing::Point(100, 50);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(50, 50);
			this->button6->TabIndex = 5;
			this->button6->Text = L"6";
			this->button6->UseVisualStyleBackColor = false;
			this->button6->Click += gcnew System::EventHandler(this, &Numbers::button6_Click);
			this->button6->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Numbers::button6_KeyPress);
			// 
			// button7
			// 
			this->button7->BackColor = System::Drawing::SystemColors::Menu;
			this->button7->FlatAppearance->BorderSize = 0;
			this->button7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button7->Location = System::Drawing::Point(0, 100);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(50, 50);
			this->button7->TabIndex = 6;
			this->button7->Text = L"7";
			this->button7->UseVisualStyleBackColor = false;
			this->button7->Click += gcnew System::EventHandler(this, &Numbers::button7_Click);
			this->button7->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Numbers::button7_KeyPress);
			// 
			// button8
			// 
			this->button8->BackColor = System::Drawing::SystemColors::Menu;
			this->button8->FlatAppearance->BorderSize = 0;
			this->button8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button8->Location = System::Drawing::Point(50, 100);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(50, 50);
			this->button8->TabIndex = 7;
			this->button8->Text = L"8";
			this->button8->UseVisualStyleBackColor = false;
			this->button8->Click += gcnew System::EventHandler(this, &Numbers::button8_Click);
			this->button8->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Numbers::button8_KeyPress);
			// 
			// button9
			// 
			this->button9->BackColor = System::Drawing::SystemColors::Menu;
			this->button9->FlatAppearance->BorderSize = 0;
			this->button9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button9->Location = System::Drawing::Point(100, 100);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(50, 50);
			this->button9->TabIndex = 8;
			this->button9->Text = L"9";
			this->button9->UseVisualStyleBackColor = false;
			this->button9->Click += gcnew System::EventHandler(this, &Numbers::button9_Click);
			this->button9->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Numbers::button9_KeyPress);
			// 
			// buttonClear
			// 
			this->buttonClear->BackColor = System::Drawing::SystemColors::Menu;
			this->buttonClear->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->buttonClear->FlatAppearance->BorderSize = 0;
			this->buttonClear->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonClear->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonClear->Location = System::Drawing::Point(0, 150);
			this->buttonClear->Name = L"buttonClear";
			this->buttonClear->Size = System::Drawing::Size(67, 50);
			this->buttonClear->TabIndex = 9;
			this->buttonClear->Text = L"Clear";
			this->buttonClear->UseVisualStyleBackColor = false;
			this->buttonClear->Click += gcnew System::EventHandler(this, &Numbers::buttonClear_Click);
			this->buttonClear->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Numbers::buttonClear_KeyPress);
			// 
			// buttonCancel
			// 
			this->buttonCancel->BackColor = System::Drawing::SystemColors::Menu;
			this->buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->buttonCancel->FlatAppearance->BorderSize = 0;
			this->buttonCancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonCancel->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->buttonCancel->Location = System::Drawing::Point(67, 150);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(83, 50);
			this->buttonCancel->TabIndex = 10;
			this->buttonCancel->Text = L"Cancel";
			this->buttonCancel->UseVisualStyleBackColor = false;
			this->buttonCancel->Click += gcnew System::EventHandler(this, &Numbers::buttonCancel_Click);
			this->buttonCancel->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Numbers::buttonCancel_KeyPress);
			// 
			// Numbers
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->buttonClear;
			this->ClientSize = System::Drawing::Size(150, 200);
			this->Controls->Add(this->buttonCancel);
			this->Controls->Add(this->buttonClear);
			this->Controls->Add(this->button9);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(150, 200);
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(150, 200);
			this->Name = L"Numbers";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->TransparencyKey = System::Drawing::Color::White;
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Numbers::Numbers_KeyPress);
			this->ResumeLayout(false);

		}
#pragma endregion

		// Set the delegate from the main form to atc when the choice has been made
		public: void setChoiceDelegate(choiceAction^ choiceActionDelegate)
		{
			this->choiceDelegate = choiceActionDelegate;
		}

		// Set the number of current cell
		public: void setCellNumber(const unsigned int cellNumber)
		{
			this->Activate();
			this->currentCellNumber = cellNumber;
			this->choiceMade = false;
		}

		// Perform action when a choice has been made
		private: void buttonClicked(
			const unsigned int number,
			System::Object^  sender,
			System::EventArgs^  e)
		{
			this->choiceMade = true;
			this->choice = number;
			this->Visible = false;
			this->choiceDelegate(this->currentCellNumber, this->choiceMade, this->choice);
		}

		private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->buttonClicked(1, sender, e);
		}

		private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->buttonClicked(2, sender, e);
		}

		private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->buttonClicked(3, sender, e);
		}

		private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->buttonClicked(4, sender, e);
		}

		private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->buttonClicked(5, sender, e);
		}

		private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->buttonClicked(6, sender, e);
		}
		private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->buttonClicked(7, sender, e);
		}

		private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->buttonClicked(8, sender, e);
		}

		private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->buttonClicked(9, sender, e);
		}

		private: System::Void buttonClear_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->buttonClicked(0, sender, e);
		}

		private: System::Void buttonCancel_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->choiceMade = false;
			this->Visible = false;
			this->choiceDelegate(this->currentCellNumber, this->choiceMade, this->choice);
		}

		private: System::Void Numbers_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
		{
			switch (e->KeyChar)
			{
			case '0': case 'c':
				this->buttonClear_Click(sender, e);
				break;
			case '1':
				this->button1_Click(sender, e);
				break;
			case '2':
				this->button2_Click(sender, e);
				break;
			case '3':
				this->button3_Click(sender, e);
				break;
			case '4':
				this->button4_Click(sender, e);
				break;
			case '5':
				this->button5_Click(sender, e);
				break;
			case '6':
				this->button6_Click(sender, e);
				break;
			case '7':
				this->button7_Click(sender, e);
				break;
			case '8':
				this->button8_Click(sender, e);
				break;
			case '9':
				this->button9_Click(sender, e);
				break;
			default:
				this->buttonCancel_Click(sender, e);
				break;
			}
		}

		private: System::Void button1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
		{
			this->Numbers_KeyPress(sender, e);
		}

		private: System::Void button2_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
		{
			this->Numbers_KeyPress(sender, e);
		}

		private: System::Void button3_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
		{
			this->Numbers_KeyPress(sender, e);
		}

		private: System::Void button4_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
		{
			this->Numbers_KeyPress(sender, e);
		}

		private: System::Void button5_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
		{
			this->Numbers_KeyPress(sender, e);
		}

		private: System::Void button6_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
		{
			this->Numbers_KeyPress(sender, e);
		}

		private: System::Void button7_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
		{
			this->Numbers_KeyPress(sender, e);
		}

		private: System::Void button8_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
		{
			this->Numbers_KeyPress(sender, e);
		}

		private: System::Void button9_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
		{
			this->Numbers_KeyPress(sender, e);
		}

		private: System::Void buttonClear_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
		{
			this->Numbers_KeyPress(sender, e);
		}

		private: System::Void buttonCancel_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
		{
			this->Numbers_KeyPress(sender, e);
		}
};
}
