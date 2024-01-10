#include "field.h"
#include "game.h"


field::field()
{
	x = gcnew uint16_t;
	y = gcnew uint16_t;
	countOfClosedCells = gcnew uint16_t;
	countofBomb = gcnew uint16_t;
}

field::~field()
{
	delete[] ArrCell;
	delete x, y, countofBomb, countOfClosedCells;
}

array<array<cell^>^>^ field::generatefield(uint16_t x, uint16_t y, uint16_t countofBomb)
{
	*countOfClosedCells = x * y;
	this->ArrCell = gcnew array<array<cell^>^>(x);
	for (int i = 0; i < x; i++) {
		ArrCell[i] = gcnew array<cell^>(y);
		for (int j = 0; j < y; j++) {
			ArrCell[i][j] = gcnew cell();
			ArrCell[i][j]->Location = System::Drawing::Point(i * cell::getCellSize(), j * cell::getCellSize());
			ArrCell[i][j]->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &field::cell_MouseDown);
		}
	}
    return ArrCell;
}


void field::setx(uint16_t x) 
{
	*(this->x) = x;
}

void field::sety(uint16_t y)
{
	*(this->y) = y;

}

void field::setcpuntofBonb(uint16_t countobBomb) 
{
	*(this->countofBomb) = countobBomb;
}

uint16_t field::getx()
{
	return *x;

}

uint16_t field::gety()
{
	return *y;
}

uint16_t field::getcountofBomb()
{
	return *countofBomb;
}


System::Void field::cell_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	cell^ c = dynamic_cast<cell^>(sender);
	if (e->Button == System::Windows::Forms::MouseButtons::Left) {
		if (c->getFlag() == false)
			c->hide();
	}
	else if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		if (game::firstClick == true) {
			//тут короче прикол который поле сгенерирует вызвать
			game::firstClick == false;
		}
		if (c->getFlag() == false)
		{
			c->setFlag(true);
		}
		else
		{
			c->setFlag(false);
		}
	}
}