#pragma once

typedef enum { easy, medium, hard } Gamemode;

class gamemode
{
private:

	int fieldHeight;

	int fieldWidth;

	int countOfBombs;

public:

	gamemode() {}
	gamemode(int fieldHeight, int fieldWidth, int countOfBombs) {
		setAllField(fieldHeight, fieldWidth, countOfBombs);
	}

	gamemode(Gamemode mode) {
		setGamemode(mode);
	}

	int getFieldHeight() { return fieldHeight; }
	int getFieldWidth() { return fieldWidth; }
	int getCountOfBombs() { return countOfBombs; }

	void setGamemode(Gamemode mode) {
		switch (mode)
		{
		case Gamemode::easy:
			fieldHeight = 9;
			fieldWidth = 9;
			countOfBombs = 10;
			break;
		case Gamemode::medium:
			fieldHeight = 16;
			fieldWidth = 16;
			countOfBombs = 40;
			break;
		case Gamemode::hard:
			fieldHeight = 16;
			fieldWidth = 30;
			countOfBombs = 99;
		}
	}

	void setAllField(int fieldHeight, int fieldWidth, int countOfBombs) {
		this->fieldHeight = fieldHeight;
		this->fieldWidth = fieldWidth;
		this->countOfBombs = countOfBombs;
	}

	bool operator==(gamemode x) {
		if (this->fieldHeight == x.fieldHeight && this->fieldWidth == x.fieldWidth && this->countOfBombs == x.countOfBombs)
			return true;
		return false;
	}
};

