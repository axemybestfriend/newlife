#pragma once
#include "mainform.h"
#include "field.h"


ref class game
{
private:

	static field^ generatedField = gcnew field();

	game() {}

	static minesweeper::mainform^ form = nullptr;

public:
	static bool firstClick = true;
	
	static void setForm(minesweeper::mainform^ form);
	
	static void victory();

	static void lose();



	static void updateField();

	static void newOutputField();

	static void startTimer();
	
	static void setup();
};