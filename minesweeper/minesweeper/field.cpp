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

	game::setcountofflaggedbomb(countofBomb);

	*countOfClosedCells = x * y;

	ArrCell = gcnew array<array<cell^>^>(x);

	for (int i = 0; i < x; i++) {
		ArrCell[i] = gcnew array<cell^>(y);
		for (int j = 0; j < y; j++) {
			ArrCell[i][j] = gcnew cell();
			ArrCell[i][j]->Location = System::Drawing::Point(i * cell::getCellSize(), (j + 1.5) * cell::getCellSize() );
			ArrCell[i][j]->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &field::cell_MouseUp);
		}
	}
    return ArrCell;
}




void field::generateBomb(cell^ btn) {

	int count = getcountofBomb();
	int banCellX = 0;
	int banCellY = 0;
	int f = 1;
	for (banCellX = 0; (banCellX < *x) && f; banCellX++) {
		for (banCellY = 0; (banCellY < *y) && f; banCellY++) {
			if (btn == ArrCell[banCellX][banCellY]) f = 0;
		}
	}
	banCellX--;
	banCellY--;


	srand(time(NULL));

	for (int k = 0; k < count; k++)
	{
		int randomI, randomJ;
		while (true)
		{
			bool flag = true;
			randomI = rand() % *x;
			randomJ = rand() % *y;
			if ((this->ArrCell[randomI][randomJ]->getMine() == true) || (randomI >= (banCellX - 1) && randomI <= (banCellX + 1) && randomJ >= (banCellY - 1) && randomJ <= (banCellY + 1))) { continue; }
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

void field::openCells(cell^ pressedCell)
{
	int cellX = 0;
	int cellY = 0;
	int f = 1;
	for (cellX = 0; (cellX < *x) && f; cellX++) {
		for (cellY = 0; (cellY < *y) && f; cellY++) {
			if (pressedCell == ArrCell[cellX][cellY]) f = 0;
		}
	}
	cellX--;
	cellY--;

	if (pressedCell->getFlag() == true) return;
	if (pressedCell->getMine() == false ) {
		*countOfClosedCells -= 1;
		pressedCell->hide();
	}
	if (pressedCell->getCountMineAround() == 0 && pressedCell->getMine() == false) {
		for (int i = cellX - 1; i <= cellX + 1; i++) {
			for (int j = cellY - 1; j <= cellY + 1; j++) {
				if (i < 0 || j < 0 || i >= *(this->x) || j >= *(this->y)) continue;
				if (ArrCell[i][j]->getIsHide() == false ) {
					continue;
				}
				openCells(ArrCell[i][j]);
			}
		}
	}
}

void field::openBomb()
{
	for (int i = 0; i < *x; i++) {
		for (int j = 0; j < *y; j++) {
			if (ArrCell[i][j]->getIsHide() == true && ArrCell[i][j]->getMine() == true) ArrCell[i][j]->hide();
		}
	}
}

void field::setcountofClosedCells(int x)
{
	*countOfClosedCells = x;
}

System::Void field::cell_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	cell^ c = dynamic_cast<cell^>(sender);
	System::Drawing::Point cursorPos = c->PointToClient(System::Windows::Forms::Control::MousePosition);
	if (c->ClientRectangle.Contains(cursorPos))
	{
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			if (game::firstClick == true) {
				this->generateBomb(c);
				game::firstClick = false;
				game::startTimer();
			}
			if (c->getFlag() == false) {
				if (c->getMine() == true) {
					c->BackgroundImage = resources::redBomb();
					c->setIsHide(false);
					game::lose();
				}
				else openCells(c);
			}
			if (*countOfClosedCells == *countofBomb) {
				game::victory();
			}
		}
		else if (e->Button == System::Windows::Forms::MouseButtons::Right) {
			if (c->getFlag() == false)
			{
				game::setcountofflaggedbomb(*game::countofflaggedbomb - 1);
				c->setFlag(true);
			}
			else
			{
				game::setcountofflaggedbomb(*game::countofflaggedbomb + 1);
				c->setFlag(false);
			}
		}
	}
}