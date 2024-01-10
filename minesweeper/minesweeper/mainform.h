#pragma once

#include "game.h"
#include "cell.h"
#include "field.h"
#include <windows.h> 

namespace minesweeper {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// ������ ��� mainform
	/// </summary>
	public ref class mainform : public System::Windows::Forms::Form
	{
	public:
		int seconds = 0;
		mainform(void)
		{
			InitializeComponent();
			timer1->Start();
			game::form = this;
			game::outputField();
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~mainform()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Label^ Time;
	private: 

	private: System::ComponentModel::IContainer^ components;
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->Time = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &mainform::timer_Tick);
			// 
			// Time
			// 
			this->Time->AutoSize = true;
			this->Time->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Time->ForeColor = System::Drawing::Color::Red;
			this->Time->Location = System::Drawing::Point(445, 9);
			this->Time->Name = L"Time";
			this->Time->Size = System::Drawing::Size(43, 24);
			this->Time->TabIndex = 0;
			this->Time->Text = L"000";
			// 
			// mainform
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(500, 500);
			this->Controls->Add(this->Time);
			this->Name = L"mainform";
			this->Text = L"mainform";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void timer_Tick(System::Object^ sender, System::EventArgs^ e) {
		seconds++;
		if (seconds < 10)Time->Text = "00" + Convert::ToString(seconds);
		else if (seconds < 100)Time->Text = "0" + Convert::ToString(seconds);
		else if (seconds < 1000)Time->Text = Convert::ToString(seconds);
		else Text = "999";
	}
	};
}