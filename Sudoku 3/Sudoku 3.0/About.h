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
	/// Summary for About
	/// </summary>
	public ref class About : public System::Windows::Forms::Form
	{
	public:
		About(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~About()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  buttonOk;
	private: System::Windows::Forms::Label^  labelSudoku;
	protected:

	private: System::Windows::Forms::Label^  labelCopyright;

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
			this->labelSudoku = (gcnew System::Windows::Forms::Label());
			this->labelCopyright = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// buttonOk
			// 
			this->buttonOk->FlatAppearance->BorderSize = 0;
			this->buttonOk->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonOk->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonOk->Location = System::Drawing::Point(100, 140);
			this->buttonOk->Name = L"buttonOk";
			this->buttonOk->Size = System::Drawing::Size(140, 60);
			this->buttonOk->TabIndex = 0;
			this->buttonOk->Text = L"OK";
			this->buttonOk->UseVisualStyleBackColor = true;
			this->buttonOk->Click += gcnew System::EventHandler(this, &About::buttonOk_Click);
			// 
			// labelSudoku
			// 
			this->labelSudoku->AutoSize = true;
			this->labelSudoku->Font = (gcnew System::Drawing::Font(L"Calibri", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelSudoku->Location = System::Drawing::Point(35, 21);
			this->labelSudoku->Name = L"labelSudoku";
			this->labelSudoku->Size = System::Drawing::Size(269, 59);
			this->labelSudoku->TabIndex = 1;
			this->labelSudoku->Text = L"SUDOKU 3.0";
			// 
			// labelCopyright
			// 
			this->labelCopyright->AutoSize = true;
			this->labelCopyright->Font = (gcnew System::Drawing::Font(L"Calibri", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelCopyright->Location = System::Drawing::Point(44, 87);
			this->labelCopyright->Name = L"labelCopyright";
			this->labelCopyright->Size = System::Drawing::Size(252, 39);
			this->labelCopyright->TabIndex = 2;
			this->labelCopyright->Text = L"All rights reserved";
			// 
			// About
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(340, 220);
			this->ControlBox = false;
			this->Controls->Add(this->labelCopyright);
			this->Controls->Add(this->labelSudoku);
			this->Controls->Add(this->buttonOk);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"About";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->Text = L"About";
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
