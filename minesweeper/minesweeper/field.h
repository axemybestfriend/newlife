#pragma once

#include "cell.h"

ref class field
{
private:
	array<array<cell^>^>^ ArrCell;
	
	uint16_t^ x;

	uint16_t^ y;

	uint16_t^ countofBomb;

public:
	field();
	array<array<cell^>^>^ generatefield(uint16_t x, uint16_t y, uint16_t countofBomb);

};

