#pragma once

#include "cell.h"

ref class field
{
private:
	array<array<cell^>^>^ ArrCell;

	uint16_t^ countOfClosedCells;

	uint16_t^ x;

	uint16_t^ y;

	uint16_t^ countofBomb;

	System::Void cell_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

public:
	field();

	~field();

	array<array<cell^>^>^ getArrCell();

	array<array<cell^>^>^ generatefield(uint16_t x, uint16_t y, uint16_t countofBomb);

	void generateBomb(cell^);

	void setx(uint16_t x);

	void sety(uint16_t y);

	void setcountofBomb(uint16_t countobBomb);

	uint16_t getx();

	uint16_t gety();

	uint16_t getcountofBomb();

	void openCells(cell^ pressedCell);

	void openBomb();
};