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
	/// Summary for Notification
	/// </summary>
	public ref class Notification : public System::Windows::Forms::Form
	{
	public:
		Notification(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Notification()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  labelText;

	private: System::Windows::Forms::Button^  buttonOk;

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
			this->labelText = (gcnew System::Windows::Forms::Label());
			this->buttonOk = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// labelText
			// 
			this->labelText->AutoSize = true;
			this->labelText->Font = (gcnew System::Drawing::Font(L"Calibri", 20.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelText->Location = System::Drawing::Point(275, 50);
			this->labelText->Name = L"labelText";
			this->labelText->Size = System::Drawing::Size(0, 33);
			this->labelText->TabIndex = 0;
			// 
			// buttonOk
			// 
			this->buttonOk->FlatAppearance->BorderSize = 0;
			this->buttonOk->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonOk->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonOk->Location = System::Drawing::Point(210, 120);
			this->buttonOk->Name = L"buttonOk";
			this->buttonOk->Size = System::Drawing::Size(140, 60);
			this->buttonOk->TabIndex = 1;
			this->buttonOk->Text = L"OK";
			this->buttonOk->UseVisualStyleBackColor = true;
			this->buttonOk->Click += gcnew System::EventHandler(this, &Notification::buttonOk_Click);
			// 
			// Notification
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(550, 200);
			this->ControlBox = false;
			this->Controls->Add(this->buttonOk);
			this->Controls->Add(this->labelText);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Notification";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		public: void setMessage(System::String^ message)
		{
			this->labelText->Text = message;
			this->labelText->Left = (this->Width - this->labelText->Width) / 2;
			this->labelText->Update();
		}

		private: System::Void buttonOk_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->Visible = false;
		}
	};
}