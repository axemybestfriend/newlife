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
	private: System::Windows::Forms::Label^ labelcountofbomb;
	private: System::Windows::Forms::PictureBox^ fotomenu;
	private: System::Windows::Forms::Button^ restartButton;
	protected:

	protected:

	protected:





	private: int seconds = 0;
	public: int getseconds() { return seconds; }
	public: void setseconds(int sec) { seconds = sec; }
	public: System::Windows::Forms::Timer^ getTimer() { return timer1; }
	public: System::Windows::Forms::Label^ getLabel() { return Time; }
	public: System::Windows::Forms::Label^ getLabelcountofbomb() { return labelcountofbomb; }
	public: System::Windows::Forms::PictureBox^ getFotoMenu() { return fotomenu; }
	public: System::Windows::Forms::Button^ getRestartButton() { return restartButton; }
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(mainform::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->Time = (gcnew System::Windows::Forms::Label());
			this->labelcountofbomb = (gcnew System::Windows::Forms::Label());
			this->fotomenu = (gcnew System::Windows::Forms::PictureBox());
			this->restartButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fotomenu))->BeginInit();
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
			this->Time->BackColor = System::Drawing::Color::Black;
			this->Time->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Time->ForeColor = System::Drawing::Color::Red;
			this->Time->Location = System::Drawing::Point(445, 40);
			this->Time->Name = L"Time";
			this->Time->Size = System::Drawing::Size(43, 24);
			this->Time->TabIndex = 0;
			this->Time->Text = L"000";
			// 
			// labelcountofbomb
			// 
			this->labelcountofbomb->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->labelcountofbomb->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelcountofbomb->ForeColor = System::Drawing::Color::Red;
			this->labelcountofbomb->Location = System::Drawing::Point(12, 40);
			this->labelcountofbomb->Name = L"labelcountofbomb";
			this->labelcountofbomb->Size = System::Drawing::Size(43, 24);
			this->labelcountofbomb->TabIndex = 1;
			this->labelcountofbomb->Text = L"000";
			this->labelcountofbomb->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// fotomenu
			// 
			this->fotomenu->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(195)), static_cast<System::Int32>(static_cast<System::Byte>(195)),
				static_cast<System::Int32>(static_cast<System::Byte>(195)));
			this->fotomenu->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->fotomenu->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->fotomenu->Location = System::Drawing::Point(0, 0);
			this->fotomenu->Name = L"fotomenu";
			this->fotomenu->Padding = System::Windows::Forms::Padding(50);
			this->fotomenu->Size = System::Drawing::Size(495, 69);
			this->fotomenu->TabIndex = 2;
			this->fotomenu->TabStop = false;
			// 
			// restartButton
			// 
			this->restartButton->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"restartButton.BackgroundImage")));
			this->restartButton->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->restartButton->Location = System::Drawing::Point(214, 12);
			this->restartButton->Name = L"restartButton";
			this->restartButton->Size = System::Drawing::Size(50, 50);
			this->restartButton->TabIndex = 3;
			this->restartButton->UseVisualStyleBackColor = false;
			// 
			// mainform
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(500, 500);
			this->Controls->Add(this->restartButton);
			this->Controls->Add(this->Time);
			this->Controls->Add(this->labelcountofbomb);
			this->Controls->Add(this->fotomenu);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"mainform";
			this->Text = L"mainform";
			this->TopMost = true;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fotomenu))->EndInit();
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