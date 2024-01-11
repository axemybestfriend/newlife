#pragma once
#include "mainform.h"

ref class game
{
private:
	game() {}

	static minesweeper::mainform^ form = nullptr;

public:

	static void setForm(minesweeper::mainform^ form);

	static bool firstClick = true;

	static void outputField();

	static void startTimer();
};