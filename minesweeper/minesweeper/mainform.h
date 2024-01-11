#pragma once
#include <windows.h> 

namespace minesweeper {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ mainform
	/// </summary>
	public ref class mainform : public System::Windows::Forms::Form
	{
	public:

		mainform(void)
		{
			InitializeComponent();
		}



	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~mainform()
		{
			if (components)
			{
				delete components;
			}
		}
	private: int seconds = 0;
	public: int getseconds() { return seconds; }
	public: void setseconds(int sec) { seconds = sec; }
	public: System::Windows::Forms::Timer^ getTimer() { return timer1; }
	public: System::Windows::Forms::Label^ getLabel() { return Time; }
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Label^ Time;
	private: System::ComponentModel::IContainer^ components;
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
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
			this->Time->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(204)));
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