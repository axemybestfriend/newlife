#pragma once


ref class resources {
public:
	static System::Drawing::Image^ ClosedCell = nullptr;
	static System::Drawing::Image^ CellWithFlag = nullptr;
	static System::Drawing::Image^ EmptyCell = nullptr;
	static System::Drawing::Image^ One = nullptr;
	static System::Drawing::Image^ Two = nullptr;
	static System::Drawing::Image^ Three = nullptr;
	static System::Drawing::Image^ Four = nullptr;
	static System::Drawing::Image^ Five = nullptr;
	static System::Drawing::Image^ Six = nullptr;
	static System::Drawing::Image^ Seven = nullptr;
	static System::Drawing::Image^ Eight = nullptr;
	static System::Drawing::Image^ Bomb = nullptr;
	static System::Drawing::Image^ RedBomb = nullptr;
	static System::Drawing::Image^ RestertButton = nullptr;
	static System::Drawing::Image^ LoseButton = nullptr;
	//static System::Drawing::Image^ CellWithFlag = System::Drawing::Image::FromFile("image\\cellWithFlag.png");
	//static System::Drawing::Image^ EmptyCell = System::Drawing::Image::FromFile("image\\emptyCell.png");
	//static System::Drawing::Image^ One = System::Drawing::Image::FromFile("image\\one.png");
	//static System::Drawing::Image^ Two = System::Drawing::Image::FromFile("image\\two.png");
	//static System::Drawing::Image^ Three = System::Drawing::Image::FromFile("image\\three.png");
	//static System::Drawing::Image^ Four = System::Drawing::Image::FromFile("image\\four.png");
	//static System::Drawing::Image^ Five = System::Drawing::Image::FromFile("image\\five.png");
	//static System::Drawing::Image^ Six = System::Drawing::Image::FromFile("image\\six.png");
	//static System::Drawing::Image^ Seven = System::Drawing::Image::FromFile("image\\seven.png");
	//static System::Drawing::Image^ Eight = System::Drawing::Image::FromFile("image\\eight.png");
	//static System::Drawing::Image^ Bomb = System::Drawing::Image::FromFile("image\\bomb.png");
	//static System::Drawing::Image^ RedBomb = System::Drawing::Image::FromFile("image\\redBomb.png");
	//static System::Drawing::Image^ RestertButton = System::Drawing::Image::FromFile("image\\restart.png");


	resources() {}

public:
	static System::Drawing::Image^ closedCell() { return ClosedCell; }
	static System::Drawing::Image^ cellWithFlag() { return CellWithFlag; }
	static System::Drawing::Image^ emptyCell() { return EmptyCell; }
	static System::Drawing::Image^ one() { return One; }
	static System::Drawing::Image^ two() { return Two; }
	static System::Drawing::Image^ three() { return Three; }
	static System::Drawing::Image^ four() { return Four; }
	static System::Drawing::Image^ five() { return Five; }
	static System::Drawing::Image^ six() { return Six; }
	static System::Drawing::Image^ seven() { return Seven; }
	static System::Drawing::Image^ eight() { return Eight; }
	static System::Drawing::Image^ bomb() { return Bomb; }
	static System::Drawing::Image^ redBomb() { return RedBomb; }
	static System::Drawing::Image^ restertButton() { return RestertButton; }
	static System::Drawing::Image^ loseButton() { return LoseButton; }


};




