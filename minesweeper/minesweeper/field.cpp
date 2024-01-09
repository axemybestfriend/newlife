#include "field.h"


field::field()
{

}

array<array<cell^>^>^ field::generatefield(uint16_t x, uint16_t y, uint16_t countofBomb)
{
	array<array<cell^>^>^ ArrCell = gcnew array<array<cell^>^>(10);
	for (int i = 0; i < x; i++) {
		ArrCell[i] = gcnew array<cell^>(10);
		for (int j = 0; j < y; j++) {
			ArrCell[i][j] = gcnew cell();
			ArrCell[i][j]->Location = System::Drawing::Point(i * cell::getCellSize(), j * cell::getCellSize());
		}
	}
    return ArrCell;
}