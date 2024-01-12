#include "game.h"
#include "field.h"

static struct {
	int fieldHeight = 15;
	int fieldWidth = 9;
	int countOfBombs = 10;
} gamemodeNormal;

void game::updateField()
{
	array<array<cell^>^>^ arr = generatedField->getArrCell();
	for (int i = 0; i < gamemodeNormal.fieldHeight; i++) {
		for (int j = 0; j < gamemodeNormal.fieldWidth; j++) {
			if (arr[i][j]->getMine() == true) arr[i][j]->setMine(false);
			arr[i][j]->setCountMineAround(0);
			arr[i][j]->setFlag(false);
			arr[i][j]->setIsHide(true);
			arr[i][j]->BackgroundImage = resources::closedCell();
			arr[i][j]->Enabled = true;
		}
	}
}

void game::newOutputField()
{
	game::countofflaggedbomb = gcnew int16_t;
	array<array<cell^>^>^ arr = generatedField->generatefield(gamemodeNormal.fieldHeight, gamemodeNormal.fieldWidth, gamemodeNormal.countOfBombs);
	form->ClientSize = System::Drawing::Size(arr[0][0]->getCellSize() * gamemodeNormal.fieldHeight, arr[0][0]->getCellSize() * gamemodeNormal.fieldWidth + arr[0][0]->getCellSize() * 1.5);
	form->getFotoMenu()->Size = System::Drawing::Size(form->ClientSize.Width, arr[0][0]->getCellSize() * 1.5);
	form->getLabel()->Location = System::Drawing::Point(form->ClientSize.Width - form->getLabel()->Size.Width - 15, (form->getFotoMenu()->Size.Height - form->getLabel()->Size.Height) / 2.);
	form->getLabelcountofbomb()->Location = System::Drawing::Point(15, (form->getFotoMenu()->Size.Height - form->getLabelcountofbomb()->Size.Height) / 2.);
	form->getRestartButton()->Location = System::Drawing::Point((form->getFotoMenu()->Size.Width - form->getRestartButton()->Size.Width) / 2., (form->getFotoMenu()->Size.Height - form->getRestartButton()->Size.Height) / 2.);


	
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
	game::setcountofflaggedbomb(game::generatedField->getcountofBomb());
	generatedField->setcountofClosedCells(gamemodeNormal.fieldHeight * gamemodeNormal.fieldWidth);
	game::firstClick = true;
	form->setseconds(0);
	form->getLabel()->Text = "000";
	//field^ tmpField = game::generatedField;
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
	System::Windows::Forms::MessageBox::Show(System::Convert::ToString(form->getseconds()), "������", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Information);
	setup();
}

void game::lose()
{
	generatedField->openBomb();
	form->getTimer()->Stop();
	System::Windows::Forms::MessageBox::Show("�� �������� �� ����� �� " + System::Convert::ToString(form->getseconds()) + " ������, ���� ���� ���� ��� �� ����� ������ ������� �����", "�����", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Information);
	setup();
}

void game::setcountofflaggedbomb(int number)
{
	*game::countofflaggedbomb = number;
	if (number < 0)form->getLabelcountofbomb()->Text = System::Convert::ToString(countofflaggedbomb);
	else if (number < 10)form->getLabelcountofbomb()->Text = "00" + System::Convert::ToString(countofflaggedbomb);
	else if (number < 100)form->getLabelcountofbomb()->Text = "0" + System::Convert::ToString(countofflaggedbomb);
	else if(number < 1000)form->getLabelcountofbomb()->Text = System::Convert::ToString(countofflaggedbomb);
}