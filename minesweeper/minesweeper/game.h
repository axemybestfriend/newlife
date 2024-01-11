#pragma once


ref class game
{
private:
	game() {}


public:
	static System::Windows::Forms::Form^ form = nullptr;

	static void setForm(System::Windows::Forms::Form^ form);

	static bool firstClick = true;

	static void outputField();

	static void startTimer();

	//static void setup();
};


