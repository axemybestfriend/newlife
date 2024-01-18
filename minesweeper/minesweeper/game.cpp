#include "game.h"
#include "options.h"
#include "field.h"

void game::updateField()
{
	array<array<cell^>^>^ arr = generatedField->getArrCell();
	for (int i = 0; i < generatedField->getx(); i++) {
		for (int j = 0; j < generatedField->gety(); j++) {
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
	static bool flag = false;
	game::countofflaggedbomb = gcnew int16_t;
	array<array<cell^>^>^ arr = generatedField->generatefield(mode->getFieldWidth(), mode->getFieldHeight(), mode->getCountOfBombs());
	form->ClientSize = System::Drawing::Size(arr[0][0]->getCellSize() * mode->getFieldWidth(), arr[0][0]->getCellSize() * mode->getFieldHeight() + arr[0][0]->getCellSize() * 1.5);
	form->getFotoMenu()->Size = System::Drawing::Size(form->ClientSize.Width, arr[0][0]->getCellSize() * 1.5);
	form->getLabel()->Location = System::Drawing::Point(form->ClientSize.Width - form->getLabel()->Size.Width - 15, (form->getFotoMenu()->Size.Height - form->getLabel()->Size.Height) / 2.);
	form->getLabelcountofbomb()->Location = System::Drawing::Point(15, (form->getFotoMenu()->Size.Height - form->getLabelcountofbomb()->Size.Height) / 2.);
	form->getRestartButton()->Location = System::Drawing::Point((form->getFotoMenu()->Size.Width - form->getRestartButton()->Size.Width) / 2., (form->getFotoMenu()->Size.Height - form->getRestartButton()->Size.Height) / 2.);
	if (flag == false) {
		form->getRestartButton()->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(&game::OnClick_RestartButton);
		flag = true;
	}
	
	for (int i = 0; i < mode->getFieldWidth(); i++) {
		for (int j = 0; j < mode->getFieldHeight(); j++) {
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

field^ game::getField()
{
	return game::generatedField;
}

void game::setup()
{
	form->getTimer()->Stop();
	game::setcountofflaggedbomb(game::generatedField->getcountofBomb());
	generatedField->setcountofClosedCells(generatedField->getx() * generatedField->gety());
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

void game::setGamemode(gamemode* mode)
{
	game::mode = mode;
}

void game::victory()
{
	generatedField->openBomb();
	form->getTimer()->Stop();
	System::Windows::Forms::MessageBox::Show("Победа за " + System::Convert::ToString(form->getseconds()) + " секунд", "Победа", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Information);
	setup();
}

void game::lose()
{
	generatedField->openBomb();
	form->getTimer()->Stop();
	form->getRestartButton()->BackgroundImage = resources::loseButton();
	System::Windows::Forms::MessageBox::Show("Вы прыгнули на бомбу за " + System::Convert::ToString(form->getseconds()) + " секунд, если ваши руки еще на месте можете сыграть снова", "Конец", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Information);
	form->getRestartButton()->BackgroundImage = resources::restertButton();
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

void game::OnClick_RestartButton(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	if ((e->Button == System::Windows::Forms::MouseButtons::Left))
	{
		if (firstClick == true) return;
		setup();
	}
	else if ((e->Button == System::Windows::Forms::MouseButtons::Right)) 
	{
		minesweeper::options^ formoptions = gcnew minesweeper::options;
		
		if (formoptions->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;
		
		gamemode* newMode = new gamemode;
		if (formoptions->easy->Checked == true) {
			newMode->setGamemode(Gamemode::easy);
		}
		else if (formoptions->medium->Checked == true) {
			newMode->setGamemode(Gamemode::medium);
		}
		else if (formoptions->hard->Checked == true) {
			newMode->setGamemode(Gamemode::hard);
		}
		else if (formoptions->special->Checked == true) {
			newMode->setAllField(System::Convert::ToInt32(formoptions->TextBoxHeight->Text), System::Convert::ToInt32(formoptions->TextBoxWidth->Text), System::Convert::ToInt32(formoptions->TextBoxCountOfmines->Text));
		}
		if (*game::mode == *newMode) { delete formoptions; return; }
		for (int i = 0; i < game::mode->getFieldWidth(); i++) {
			for (int j = 0; j < game::mode->getFieldHeight(); j++) {
				form->Controls->Remove(generatedField->getArrCell()[i][j]);
			}
		}
		game::mode = newMode;
		game::newOutputField();
		game::setup();
		delete formoptions;
	}
}
