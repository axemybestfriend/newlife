#pragma once

#include "cell.h"

ref class field
{
private:
	array<array<cell^>^>^ ArrCell;
	
	uint16_t^ x;

	uint16_t^ y;

	uint16_t^ countofBomb;

	System::Void cell_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

public:
	field();

	~field();

	array<array<cell^>^>^ generatefield(uint16_t x, uint16_t y, uint16_t countofBomb);

};

