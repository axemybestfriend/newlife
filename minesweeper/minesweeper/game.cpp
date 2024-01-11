#include "game.h"
#include "field.h"

static struct {
	int fieldHeight = 30;
	int fieldWidth = 16;
	int countOfBombs = 99;
} gamemodeNormal;

void game::updateField()
{
	array<array<cell^>^>^ arr = generatedField->getArrCell();
	for (int i = 0; i < gamemodeNormal.fieldHeight; i++) {
		for (int j = 0; j < gamemodeNormal.fieldWidth; j++) {
			if (arr[i][j]->getMine() == true) arr[i][j]->setMine(false);
			arr[i][j]->setCountMineAround(0);
			arr[i][j]->setIsHide(true);
			arr[i][j]->BackgroundImage = resources::closedCell();
			arr[i][j]->Enabled = true;
		}
	}
}

void game::newOutputField()
{
	array<array<cell^>^>^ arr = generatedField->generatefield(gamemodeNormal.fieldHeight, gamemodeNormal.fieldWidth, gamemodeNormal.countOfBombs);
	form->ClientSize = System::Drawing::Size(arr[0][0]->getCellSize() * gamemodeNormal.fieldHeight, arr[0][0]->getCellSize() * gamemodeNormal.fieldWidth);
	for (int i = 0; i < gamemodeNormal.fieldHeight; i++) {
		for (int j = 0; j < gamemodeNormal.fieldWidth; j++) {
			form->Controls->Add(arr[i][j]);
		}
	}
}

void game::startTimer()
{
	form->getTimer()->Start();
}

void game::setForm(minesweeper::mainform^ form)
{	
	game::form = form; 
}

void game::setup()
{
	generatedField->setcountofClosedCells(gamemodeNormal.fieldHeight * gamemodeNormal.fieldWidth);
	game::firstClick = true;
	form->setseconds(0);
	form->getLabel()->Text = "000";
	field^ tmpField = game::generatedField;
	game::updateField();
	//for (int i = 0; i < gamemodeNormal.fieldHeight; i++) {
	//	for (int j = 0; j < gamemodeNormal.fieldWidth; j++) {
	//		form->Controls->Remove(tmpField->getArrCell()[i][j]);
	//	}
	//}
}

void game::victory()
{
	generatedField->openBomb();
	form->getTimer()->Stop();
	System::Windows::Forms::MessageBox::Show(System::Convert::ToString(form->getseconds()), "Победа", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Information);
	setup();
}

void game::lose()
{
	generatedField->openBomb();
	form->getTimer()->Stop();
	System::Windows::Forms::MessageBox::Show("Вы прыгнули на бомбу за " + System::Convert::ToString(form->getseconds()) + " секунд, если ваши руки еще на месте можете сыграть снова", "Конец", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Information);
	setup();
}
