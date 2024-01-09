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
			ArrCell[i][j]->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &field::cell_MouseDown);
		}
	}
    return ArrCell;
}

System::Void field::cell_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	cell^ c = dynamic_cast<cell^>(sender);
	if (e->Button == System::Windows::Forms::MouseButtons::Left) {

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