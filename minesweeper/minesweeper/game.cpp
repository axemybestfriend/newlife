#include "game.h"
#include "field.h"

static struct {
	int fieldHeight = 15;
	int fieldWidth = 8;
	int countOfBombs = 110;
} gamemodeNormal;

void game::outputField()
{
	game::generatedField = gcnew field();
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
	game::firstClick = true;
	form->setseconds(0);
	form->getLabel()->Text = "000";
	field^ tmpField = game::generatedField;
	game::outputField();
	for (int i = 0; i < gamemodeNormal.fieldHeight; i++) {
		for (int j = 0; j < gamemodeNormal.fieldWidth; j++) {
			form->Controls->Remove(tmpField->getArrCell()[i][j]);
		}
	}
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
