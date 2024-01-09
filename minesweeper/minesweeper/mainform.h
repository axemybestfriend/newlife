#pragma once
#include "cell.h"
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
			//
			//TODO: добавьте код конструктора
			//
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
	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// mainform
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(500, 500);
			this->Name = L"mainform";
			this->Text = L"mainform";
			this->ResumeLayout(false);
			array<array<cell^>^>^ arr = gcnew array<array<cell^>^>(10);
			for (int i = 0; i < 10; i++) {
				arr[i] = gcnew array<cell^>(10);
				for (int j = 0; j < 10; j++) {
					arr[i][j] = gcnew cell();
					arr[i][j]->Location = System::Drawing::Point(i*40, j*40);
					this->Controls->Add(arr[i][j]);
					arr[i][j]->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &mainform::cell_MouseDown);

				}
			}
		}
#pragma endregion
	private: System::Void cell_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		cell^ c = dynamic_cast<cell^>(sender);
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {

		}
		else if (e->Button == System::Windows::Forms::MouseButtons::Right) {
			if (c->getFlag() == false)
			{



			}
			else
			{


			}
		}
	}
	};
}