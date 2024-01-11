#pragma once
#include <iostream>
#include "resources.h"

ref class cell : System::Windows::Forms::Button
{
private:
	static uint16_t CellSize = 50;

	bool^ flag;

	bool^ mine;

	bool^ isHide;

public:
	uint16_t^ countMineAround;
	cell();
	cell(bool mine);
	~cell();

	bool getIsHide();

	void setIsHide(bool hide);

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

