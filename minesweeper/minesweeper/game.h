#pragma once
#include "mainform.h"
#include "field.h"


ref class game
{
private:

	static field^ generatedField;

	game() {}

	static minesweeper::mainform^ form = nullptr;

public:
	static void victory();

	static void setForm(minesweeper::mainform^ form);

	static bool firstClick = true;

	static void outputField();

	static void startTimer();
	
	static void setup();
};