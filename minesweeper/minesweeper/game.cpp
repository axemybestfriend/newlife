#include "game.h"
#include "field.h"

static struct {
	int fieldHeight = 10;
	int fieldWidth = 10;
	int countOfBombs = 10;
} gamemodeNormal;


void game::outputField()
{
	field^ generatedField = gcnew field();
	array<array<cell^>^>^ arr = generatedField->generatefield(gamemodeNormal.fieldHeight, gamemodeNormal.fieldWidth, gamemodeNormal.countOfBombs);

	generatedField->generateBomb();

	for (int i = 0; i < gamemodeNormal.fieldHeight; i++) {
		for (int j = 0; j < gamemodeNormal.fieldWidth; j++) {
			form->Controls->Add(arr[i][j]);
			arr[i][j]->hide();
		}
	}
}

void game::setForm(System::Windows::Forms::Form^ form)
{	
	game::form = form; 
}
