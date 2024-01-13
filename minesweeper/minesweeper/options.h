#pragma once

namespace minesweeper {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для options
	/// </summary>
	public ref class options : public System::Windows::Forms::Form
	{
	public:
		options(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~options()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ ok;
	protected:
	private: System::Windows::Forms::Button^ cancel;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::RadioButton^ special;

	private: System::Windows::Forms::RadioButton^ hard;

	private: System::Windows::Forms::RadioButton^ medium;

	private: System::Windows::Forms::RadioButton^ easy;
	private: System::Windows::Forms::Panel^ panelOfSpecialmode;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;



	private: System::Windows::Forms::Label^ label3;


	private: System::Windows::Forms::MaskedTextBox^ TextBoxHeight;
	private: System::Windows::Forms::MaskedTextBox^ TextBoxCountOfmines;
	private: System::Windows::Forms::MaskedTextBox^ TextBoxWidth;


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->ok = (gcnew System::Windows::Forms::Button());
			this->cancel = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panelOfSpecialmode = (gcnew System::Windows::Forms::Panel());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->special = (gcnew System::Windows::Forms::RadioButton());
			this->hard = (gcnew System::Windows::Forms::RadioButton());
			this->medium = (gcnew System::Windows::Forms::RadioButton());
			this->easy = (gcnew System::Windows::Forms::RadioButton());
			this->TextBoxHeight = (gcnew System::Windows::Forms::MaskedTextBox());
			this->TextBoxWidth = (gcnew System::Windows::Forms::MaskedTextBox());
			this->TextBoxCountOfmines = (gcnew System::Windows::Forms::MaskedTextBox());
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
			this->ok->Text = L"Ок";
			this->ok->UseVisualStyleBackColor = true;
			// 
			// cancel
			// 
			this->cancel->Location = System::Drawing::Point(212, 181);
			this->cancel->Name = L"cancel";
			this->cancel->Size = System::Drawing::Size(98, 49);
			this->cancel->TabIndex = 1;
			this->cancel->Text = L"Отмена";
			this->cancel->UseVisualStyleBackColor = true;
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
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(30, 85);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(62, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Число мин";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(30, 23);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(75, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Высота (4-24)";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(30, 54);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(76, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Ширина (4-30)";
			// 
			// special
			// 
			this->special->AutoSize = true;
			this->special->Location = System::Drawing::Point(213, 17);
			this->special->Name = L"special";
			this->special->Size = System::Drawing::Size(65, 17);
			this->special->TabIndex = 3;
			this->special->Text = L"Особый";
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
			this->hard->Text = L"Профессионал\r\n99 мин \r\nполе 16 x 30 ячеек";
			this->hard->UseVisualStyleBackColor = true;
			// 
			// medium
			// 
			this->medium->AutoSize = true;
			this->medium->Location = System::Drawing::Point(43, 57);
			this->medium->Name = L"medium";
			this->medium->Size = System::Drawing::Size(119, 43);
			this->medium->TabIndex = 1;
			this->medium->Text = L"Любитель\r\n40 мин \r\nполе 16 x 16 ячеек";
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
			this->easy->Text = L"Новичок\r\n10 мин \r\nполе 9 x 9 ячеек\r\n";
			this->easy->UseVisualStyleBackColor = true;
			// 
			// TextBoxHeight
			// 
			this->TextBoxHeight->Location = System::Drawing::Point(125, 20);
			this->TextBoxHeight->Name = L"TextBoxHeight";
			this->TextBoxHeight->Size = System::Drawing::Size(30, 20);
			this->TextBoxHeight->TabIndex = 8;
			// 
			// TextBoxWidth
			// 
			this->TextBoxWidth->Location = System::Drawing::Point(125, 50);
			this->TextBoxWidth->Name = L"TextBoxWidth";
			this->TextBoxWidth->Size = System::Drawing::Size(30, 20);
			this->TextBoxWidth->TabIndex = 9;
			// 
			// TextBoxCountOfmines
			// 
			this->TextBoxCountOfmines->Location = System::Drawing::Point(125, 80);
			this->TextBoxCountOfmines->Name = L"TextBoxCountOfmines";
			this->TextBoxCountOfmines->Size = System::Drawing::Size(30, 20);
			this->TextBoxCountOfmines->TabIndex = 10;
			// 
			// options
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(376, 242);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->cancel);
			this->Controls->Add(this->ok);
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
};
}
