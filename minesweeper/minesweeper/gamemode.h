#pragma once
//#include <iostream>
#include "game.h"

typedef enum { easy, medium, hard } Gamemode;

class gamemode
{
private:

	uint16_t fieldHeight;

	uint16_t fieldWidth;

	uint16_t countOfBombs;
public:
	gamemode(uint16_t fieldHeight, uint16_t fieldWidth, uint16_t countOfBombs) {
		this->fieldHeight = fieldHeight;
		this->fieldWidth = fieldWidth;
		this->countOfBombs = countOfBombs;
	}

	gamemode(Gamemode mode) {
		switch (mode)
		{
		case Gamemode::easy:
			fieldHeight = 9;
			fieldWidth = 9;
			countOfBombs = 10;
			break;
		case Gamemode::medium:
			fieldHeight = 16;
			fieldWidth = 16;
			countOfBombs = 40;
			break;
		case Gamemode::hard:
			fieldHeight = 16;
			fieldWidth = 30;
			countOfBombs = 99;
		}
	}

	uint16_t getFieldHeight() { return fieldHeight; }
	uint16_t getFieldWidth() { return fieldWidth; }
	uint16_t getCountOfBombs() { return countOfBombs; }
};

