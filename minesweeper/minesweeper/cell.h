#pragma once
#include <iostream>

ref class cell : System::Windows::Forms::Button
{
private:
	bool^ flag;

	bool^ mine;

	bool^ isHide;

	uint16_t^ countMineAround;
public:
	cell();
	cell(bool mine);
	~cell();

	void hide();
	
	void setMine(bool mine);

	void setFlag(bool mine);

	void setCountMineAround(uint16_t countMineAround);

	bool getFlag();

	bool getMine();

	uint16_t getCountMineAround();
};

