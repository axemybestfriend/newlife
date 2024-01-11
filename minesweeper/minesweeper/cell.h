#pragma once
#include <iostream>
#include "resources.h"

ref class cell : System::Windows::Forms::Button
{
private:
	static uint16_t CellSize = 50;

	bool^ flag;

	bool^ mine;


public:
	bool^ isHide;
	uint16_t^ countMineAround;
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

