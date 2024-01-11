#include "game.h"
#include "field.h"

static struct {
	int fieldHeight = 9;
	int fieldWidth = 9;
	int countOfBombs = 20;
} gamemodeNormal;

void game::outputField()
{
	game::generatedField = gcnew field();
	array<array<cell^>^>^ arr = generatedField->generatefield(gamemodeNormal.fieldHeight, gamemodeNormal.fieldWidth, gamemodeNormal.countOfBombs);

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
	for (int i = 0; i < gamemodeNormal.fieldHeight; i++) {
		for (int j = 0; j < gamemodeNormal.fieldWidth; j++) {
			form->Controls->Remove(game::generatedField->getArrCell()[i][j]);
		}
	}
	game::outputField();
}

void game::victory()
{
	form->getTimer()->Stop();
	System::Windows::Forms::MessageBox::Show(System::Convert::ToString(form->getseconds()), "Победа", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Information);
	setup();
}

void game::lose()
{
	form->getTimer()->Stop();
	System::Windows::Forms::MessageBox::Show("Вы прыгнули на бомбу за " + System::Convert::ToString(form->getseconds()) + " секунд, если ваши руки еще на месте можете сыграть снова", "Конец", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Information);
	setup();

}
