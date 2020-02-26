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
	/// Summary for Rules
	/// </summary>
	public ref class Rules : public System::Windows::Forms::Form
	{
	public:
		Rules(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Rules()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  buttonOk;
	private: System::Windows::Forms::Label^  labelRules;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Rules::typeid));
			this->buttonOk = (gcnew System::Windows::Forms::Button());
			this->labelRules = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// buttonOk
			// 
			this->buttonOk->FlatAppearance->BorderSize = 0;
			this->buttonOk->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonOk->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 27.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonOk->Location = System::Drawing::Point(200, 348);
			this->buttonOk->Name = L"buttonOk";
			this->buttonOk->Size = System::Drawing::Size(150, 50);
			this->buttonOk->TabIndex = 0;
			this->buttonOk->Text = L"OK";
			this->buttonOk->UseVisualStyleBackColor = true;
			this->buttonOk->Click += gcnew System::EventHandler(this, &Rules::button1_Click);
			// 
			// labelRules
			// 
			this->labelRules->AutoSize = true;
			this->labelRules->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelRules->Location = System::Drawing::Point(25, 15);
			this->labelRules->Name = L"labelRules";
			this->labelRules->Size = System::Drawing::Size(491, 312);
			this->labelRules->TabIndex = 1;
			this->labelRules->Text = resources->GetString(L"labelRules.Text");
			// 
			// Rules
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(550, 410);
			this->Controls->Add(this->labelRules);
			this->Controls->Add(this->buttonOk);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Rules";
			this->ShowInTaskbar = false;
			this->Text = L"Rules";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->Visible = false;
		}
	};
}
