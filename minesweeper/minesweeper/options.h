#pragma once

#include "game.h"

namespace minesweeper {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// ������ ��� options
	/// </summary>
	public ref class options : public System::Windows::Forms::Form
	{
	public:
		options(void)
		{
			InitializeComponent();
			TextBoxHeight->Text = Convert::ToString(game::getField()->gety());
			TextBoxWidth->Text = Convert::ToString(game::getField()->getx());
			TextBoxCountOfmines->Text = Convert::ToString(game::getField()->getcountofBomb());

		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~options()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ ok;
	private: System::Windows::Forms::Button^ cancel;
	private: System::Windows::Forms::Panel^ panel1;

	public: System::Windows::Forms::RadioButton^ special;
	public: System::Windows::Forms::RadioButton^ hard;
	public: System::Windows::Forms::RadioButton^ medium;
	public: System::Windows::Forms::RadioButton^ easy;

	public: System::Windows::Forms::MaskedTextBox^ TextBoxHeight;
	public: System::Windows::Forms::MaskedTextBox^ TextBoxCountOfmines;
	public: System::Windows::Forms::MaskedTextBox^ TextBoxWidth;

	private: System::Windows::Forms::Panel^ panelOfSpecialmode;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label3;




	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->ok = (gcnew System::Windows::Forms::Button());
			this->cancel = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panelOfSpecialmode = (gcnew System::Windows::Forms::Panel());
			this->TextBoxCountOfmines = (gcnew System::Windows::Forms::MaskedTextBox());
			this->TextBoxWidth = (gcnew System::Windows::Forms::MaskedTextBox());
			this->TextBoxHeight = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->special = (gcnew System::Windows::Forms::RadioButton());
			this->hard = (gcnew System::Windows::Forms::RadioButton());
			this->medium = (gcnew System::Windows::Forms::RadioButton());
			this->easy = (gcnew System::Windows::Forms::RadioButton());
			this->panel1->SuspendLayout();
			this->panelOfSpecialmode->SuspendLayout();
			this->SuspendLayout();
			// 
			// ok
			// 
			this->ok->Location = System::Drawing::Point(55, 181);
			this->ok->Name = L"ok";
			this->ok->Size = System::Drawing::Size(98, 49);
			this->ok->TabIndex = 0;
			this->ok->Text = L"��";
			this->ok->UseVisualStyleBackColor = true;
			this->ok->Click += gcnew System::EventHandler(this, &options::ok_Click);
			// 
			// cancel
			// 
			this->cancel->Location = System::Drawing::Point(212, 181);
			this->cancel->Name = L"cancel";
			this->cancel->Size = System::Drawing::Size(98, 49);
			this->cancel->TabIndex = 1;
			this->cancel->Text = L"������";
			this->cancel->UseVisualStyleBackColor = true;
			this->cancel->Click += gcnew System::EventHandler(this, &options::cancel_Click);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->panelOfSpecialmode);
			this->panel1->Controls->Add(this->special);
			this->panel1->Controls->Add(this->hard);
			this->panel1->Controls->Add(this->medium);
			this->panel1->Controls->Add(this->easy);
			this->panel1->Location = System::Drawing::Point(12, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(352, 163);
			this->panel1->TabIndex = 2;
			// 
			// panelOfSpecialmode
			// 
			this->panelOfSpecialmode->Controls->Add(this->TextBoxCountOfmines);
			this->panelOfSpecialmode->Controls->Add(this->TextBoxWidth);
			this->panelOfSpecialmode->Controls->Add(this->TextBoxHeight);
			this->panelOfSpecialmode->Controls->Add(this->label3);
			this->panelOfSpecialmode->Controls->Add(this->label2);
			this->panelOfSpecialmode->Controls->Add(this->label1);
			this->panelOfSpecialmode->Enabled = false;
			this->panelOfSpecialmode->Location = System::Drawing::Point(182, 40);
			this->panelOfSpecialmode->Name = L"panelOfSpecialmode";
			this->panelOfSpecialmode->Size = System::Drawing::Size(167, 120);
			this->panelOfSpecialmode->TabIndex = 4;
			// 
			// TextBoxCountOfmines
			// 
			this->TextBoxCountOfmines->Location = System::Drawing::Point(125, 80);
			this->TextBoxCountOfmines->Mask = L"000";
			this->TextBoxCountOfmines->Name = L"TextBoxCountOfmines";
			this->TextBoxCountOfmines->PromptChar = ' ';
			this->TextBoxCountOfmines->Size = System::Drawing::Size(30, 20);
			this->TextBoxCountOfmines->TabIndex = 10;
			this->TextBoxCountOfmines->Leave += gcnew System::EventHandler(this, &options::TextBox_Leave);
			// 
			// TextBoxWidth
			// 
			this->TextBoxWidth->Location = System::Drawing::Point(125, 50);
			this->TextBoxWidth->Mask = L"00";
			this->TextBoxWidth->Name = L"TextBoxWidth";
			this->TextBoxWidth->PromptChar = ' ';
			this->TextBoxWidth->Size = System::Drawing::Size(30, 20);
			this->TextBoxWidth->TabIndex = 9;
			this->TextBoxWidth->Leave += gcnew System::EventHandler(this, &options::TextBox_Leave);
			// 
			// TextBoxHeight
			// 
			this->TextBoxHeight->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->TextBoxHeight->Location = System::Drawing::Point(125, 20);
			this->TextBoxHeight->Mask = L"00";
			this->TextBoxHeight->Name = L"TextBoxHeight";
			this->TextBoxHeight->PromptChar = ' ';
			this->TextBoxHeight->Size = System::Drawing::Size(30, 20);
			this->TextBoxHeight->TabIndex = 8;
			this->TextBoxHeight->Leave += gcnew System::EventHandler(this, &options::TextBox_Leave);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(30, 85);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(62, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"����� ���";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(30, 23);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(75, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"������ (4-24)";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(30, 54);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(76, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"������ (4-30)";
			// 
			// special
			// 
			this->special->AutoSize = true;
			this->special->Location = System::Drawing::Point(213, 17);
			this->special->Name = L"special";
			this->special->Size = System::Drawing::Size(65, 17);
			this->special->TabIndex = 3;
			this->special->Text = L"������";
			this->special->UseVisualStyleBackColor = true;
			this->special->CheckedChanged += gcnew System::EventHandler(this, &options::special_CheckedChanged);
			// 
			// hard
			// 
			this->hard->AutoSize = true;
			this->hard->Location = System::Drawing::Point(43, 106);
			this->hard->Name = L"hard";
			this->hard->Size = System::Drawing::Size(119, 43);
			this->hard->TabIndex = 2;
			this->hard->Text = L"������������\r\n99 ��� \r\n���� 16 x 30 �����";
			this->hard->UseVisualStyleBackColor = true;
			// 
			// medium
			// 
			this->medium->AutoSize = true;
			this->medium->Location = System::Drawing::Point(43, 57);
			this->medium->Name = L"medium";
			this->medium->Size = System::Drawing::Size(119, 43);
			this->medium->TabIndex = 1;
			this->medium->Text = L"��������\r\n40 ��� \r\n���� 16 x 16 �����";
			this->medium->UseVisualStyleBackColor = true;
			// 
			// easy
			// 
			this->easy->AutoSize = true;
			this->easy->Checked = true;
			this->easy->Location = System::Drawing::Point(43, 8);
			this->easy->Name = L"easy";
			this->easy->Size = System::Drawing::Size(107, 43);
			this->easy->TabIndex = 0;
			this->easy->TabStop = true;
			this->easy->Text = L"�������\r\n10 ��� \r\n���� 9 x 9 �����\r\n";
			this->easy->UseVisualStyleBackColor = true;
			// 
			// options
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(376, 242);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->cancel);
			this->Controls->Add(this->ok);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"options";
			this->Text = L"options";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panelOfSpecialmode->ResumeLayout(false);
			this->panelOfSpecialmode->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void special_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (this->special->Checked == true)this->panelOfSpecialmode->Enabled = true;
	else this->panelOfSpecialmode->Enabled = false;
}
private: System::Void TextBox_Leave(System::Object^ sender, System::EventArgs^ e) {
	MaskedTextBox^ textBox = safe_cast<MaskedTextBox^>(sender);
	if (TextBoxHeight->Name == textBox->Name) {
		if (textBox->Text->Trim() == String::Empty) textBox->Text = "4";
		else if (Convert::ToInt16(textBox->Text) < 4) textBox->Text = "4";
		else if (Convert::ToInt16(textBox->Text) > 24) textBox->Text = "24";
	}
	if (TextBoxWidth->Name == textBox->Name) {
		if (textBox->Text->Trim() == String::Empty) textBox->Text = "4";
		else if (Convert::ToInt16(textBox->Text) < 4) textBox->Text = "4";
		else if (Convert::ToInt16(textBox->Text) > 30) textBox->Text = "30";
	}
	if (TextBoxCountOfmines->Text->Trim() == String::Empty) TextBoxCountOfmines->Text = "1";
	if (Convert::ToInt16(TextBoxCountOfmines->Text) > Convert::ToInt16(TextBoxHeight->Text) * Convert::ToInt16(TextBoxWidth->Text) - 10) TextBoxCountOfmines->Text = Convert::ToString(Convert::ToInt16(TextBoxHeight->Text) * Convert::ToInt16(TextBoxWidth->Text) - 10);
}
private: System::Void ok_Click(System::Object^ sender, System::EventArgs^ e) {
	this->DialogResult = System::Windows::Forms::DialogResult::OK;
	this->Close();
}
private: System::Void cancel_Click(System::Object^ sender, System::EventArgs^ e) {
	this->Close();
}
};
}
