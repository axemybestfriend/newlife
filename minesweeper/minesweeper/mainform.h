#pragma once

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
		mainform(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
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


			field^ a = gcnew field();
			array<array<cell^>^>^ arr = a->generatefield(10, 10, 10);

			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					this->Controls->Add(arr[i][j]);
				}
			}
		}
#pragma endregion
	};
}