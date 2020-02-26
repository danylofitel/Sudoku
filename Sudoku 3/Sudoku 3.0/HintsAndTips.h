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
	/// Summary for HintsAndTips
	/// </summary>
	public ref class HintsAndTips : public System::Windows::Forms::Form
	{
	public:
		HintsAndTips(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~HintsAndTips()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  buttonOk;
	private: System::Windows::Forms::Label^  labelSave;
	private: System::Windows::Forms::Label^  labelClick;
	private: System::Windows::Forms::Label^  labelDrag;
	private: System::Windows::Forms::Label^  labelHintOn;
	private: System::Windows::Forms::Label^  labelHintOff;
	private: System::Windows::Forms::Label^  labelBlink;
	private: System::Windows::Forms::Label^  labelBlink2;
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
			this->labelSave = (gcnew System::Windows::Forms::Label());
			this->labelClick = (gcnew System::Windows::Forms::Label());
			this->labelDrag = (gcnew System::Windows::Forms::Label());
			this->labelHintOn = (gcnew System::Windows::Forms::Label());
			this->labelHintOff = (gcnew System::Windows::Forms::Label());
			this->labelBlink = (gcnew System::Windows::Forms::Label());
			this->labelBlink2 = (gcnew System::Windows::Forms::Label());
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
			this->buttonOk->Click += gcnew System::EventHandler(this, &HintsAndTips::buttonOk_Click);
			// 
			// labelSave
			// 
			this->labelSave->AutoSize = true;
			this->labelSave->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelSave->Location = System::Drawing::Point(15, 15);
			this->labelSave->Name = L"labelSave";
			this->labelSave->Size = System::Drawing::Size(529, 29);
			this->labelSave->TabIndex = 1;
			this->labelSave->Text = L"You can save the game anytime and open it later";
			// 
			// labelClick
			// 
			this->labelClick->AutoSize = true;
			this->labelClick->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelClick->Location = System::Drawing::Point(15, 60);
			this->labelClick->Name = L"labelClick";
			this->labelClick->Size = System::Drawing::Size(576, 29);
			this->labelClick->TabIndex = 3;
			this->labelClick->Text = L"Click on any cell you want to fill to see a choice menu";
			// 
			// labelDrag
			// 
			this->labelDrag->AutoSize = true;
			this->labelDrag->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelDrag->Location = System::Drawing::Point(15, 285);
			this->labelDrag->Name = L"labelDrag";
			this->labelDrag->Size = System::Drawing::Size(493, 29);
			this->labelDrag->TabIndex = 4;
			this->labelDrag->Text = L"Press and hold anywhere to drag the window";
			// 
			// labelHintOn
			// 
			this->labelHintOn->AutoSize = true;
			this->labelHintOn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelHintOn->Location = System::Drawing::Point(15, 195);
			this->labelHintOn->Name = L"labelHintOn";
			this->labelHintOn->Size = System::Drawing::Size(443, 29);
			this->labelHintOn->TabIndex = 5;
			this->labelHintOn->Text = L"Click the Hint button to enable hint mode";
			// 
			// labelHintOff
			// 
			this->labelHintOff->AutoSize = true;
			this->labelHintOff->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelHintOff->Location = System::Drawing::Point(15, 240);
			this->labelHintOff->Name = L"labelHintOff";
			this->labelHintOff->Size = System::Drawing::Size(427, 29);
			this->labelHintOff->TabIndex = 6;
			this->labelHintOff->Text = L"Click it again to go back to game mode";
			// 
			// labelBlink
			// 
			this->labelBlink->AutoSize = true;
			this->labelBlink->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelBlink->Location = System::Drawing::Point(15, 105);
			this->labelBlink->Name = L"labelBlink";
			this->labelBlink->Size = System::Drawing::Size(484, 29);
			this->labelBlink->TabIndex = 7;
			this->labelBlink->Text = L"If the number you have entered blinks in red,";
			// 
			// labelBlink2
			// 
			this->labelBlink2->AutoSize = true;
			this->labelBlink2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelBlink2->Location = System::Drawing::Point(55, 150);
			this->labelBlink2->Name = L"labelBlink2";
			this->labelBlink2->Size = System::Drawing::Size(355, 29);
			this->labelBlink2->TabIndex = 8;
			this->labelBlink2->Text = L"it conflicts with existing numbers";
			// 
			// HintsAndTips
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(600, 410);
			this->Controls->Add(this->labelBlink2);
			this->Controls->Add(this->labelBlink);
			this->Controls->Add(this->labelHintOff);
			this->Controls->Add(this->labelHintOn);
			this->Controls->Add(this->labelDrag);
			this->Controls->Add(this->labelClick);
			this->Controls->Add(this->labelSave);
			this->Controls->Add(this->buttonOk);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"HintsAndTips";
			this->ShowInTaskbar = false;
			this->Text = L"HintsAndTips";
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
