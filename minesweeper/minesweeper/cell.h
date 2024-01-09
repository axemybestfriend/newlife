#pragma once
#include <iostream>
#include "resources.h"

ref class cell : System::Windows::Forms::Button
{
private:
	static uint16_t CellSize = 40;

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

	void setFlag(bool flag);

	void setCountMineAround(uint16_t countMineAround);

	static void setCellSize(uint16_t);

	static uint16_t getCellSize();

	bool getFlag();

	bool getMine();

	uint16_t getCountMineAround();
};

