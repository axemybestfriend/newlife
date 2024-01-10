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
	*(this->x) = x;
	*(this->y) = y;
	*(this->countofBomb) = countofBomb;

	*countOfClosedCells = x * y;

	ArrCell = gcnew array<array<cell^>^>(x);

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




void field::generateBomb(cell^ btn) {

	int count = getcountofBomb();
	int banCellX = btn->Location.X / btn->getCellSize();
	int banCellY = btn->Location.Y / btn->getCellSize();


	srand(time(NULL));

	for (int k = 0; k < count; k++)
	{
		int randomI, randomJ;
		while (true)
		{
			bool flag = true;
			randomI = rand() % *x;
			randomJ = rand() % *y;
			if ((this->ArrCell[randomI][randomJ]->getMine() == true) || (randomI == banCellX && randomJ == banCellY)) { continue; }
			break;
		}
		this->ArrCell[randomI][randomJ]->setMine(true);
		for (int i = randomI - 1; i <= randomI + 1; i++) {
			for (int j = randomJ - 1; j <= randomJ + 1; j++) {
				if (i < 0 || j < 0 || i >= *(this->x) || j >= *(this->y)) continue;
				else ArrCell[i][j]->setCountMineAround(ArrCell[i][j]->getCountMineAround() + 1);
			}
		}
	}
}



array<array<cell^>^>^ field::getArrCell() {
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

void field::setcountofBomb(uint16_t countobBomb) 
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
	//static int f = 1;
	cell^ c = dynamic_cast<cell^>(sender);
	if (e->Button == System::Windows::Forms::MouseButtons::Left) {
		if (game::firstClick == true) {
			this->generateBomb(c);
			game::firstClick = false;
		}
		if (c->getFlag() == false)
			c->hide();
	}
	else if (e->Button == System::Windows::Forms::MouseButtons::Right) {
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