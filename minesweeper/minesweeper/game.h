#pragma once
#include "mainform.h"
#include "field.h"
#include "gamemode.h"



ref class game
{
private:

	static field^ generatedField = gcnew field();

	game() {}

	static minesweeper::mainform^ form = nullptr;

	static gamemode* mode = nullptr;

public:

	static int16_t^ countofflaggedbomb;

	static void setcountofflaggedbomb(int number);

	static bool firstClick = true;
	
	static void setForm(minesweeper::mainform^ form);

	static field^ getField();
	
	static void victory();

	static void lose();

	static void updateField();

	static void newOutputField();

	static void startTimer();
	
	static void setup();

	static void setGamemode(gamemode* mode);

	static void OnClick_RestartButton(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
};