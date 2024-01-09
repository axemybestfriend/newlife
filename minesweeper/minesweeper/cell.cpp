#include "cell.h"


cell::cell() : System::Windows::Forms::Button()
{
    flag = gcnew bool;
    *flag = false;
    mine = gcnew bool;
    *mine = false;
    isHide = gcnew bool;
    *isHide = true;
    countMineAround = gcnew uint16_t;
    *countMineAround = 0;
    this->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
    this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
    this->Size = System::Drawing::Size(CellSize, CellSize);
    this->BackgroundImage = System::Drawing::Image::FromFile(cellImagePath);
}

cell::cell(bool mine)
{
    cell();
    *(this->mine) = mine;
}

cell::~cell()
{
    delete flag, mine, isHide, countMineAround;
}

void cell::hide()
{
    throw gcnew System::NotImplementedException();
}

void cell::setMine(bool mine) {
    *(this->mine) = mine;
}

void cell::setFlag(bool flag)
{
    *(this->flag) = flag;
    if (flag == true) this->BackgroundImage = System::Drawing::Image::FromFile(flagImagePath);
    else this->BackgroundImage = System::Drawing::Image::FromFile(cellImagePath);
}

void cell::setCountMineAround(uint16_t countMineAround)
{
    *(this->countMineAround) = countMineAround;
}

void cell::setCellSize(uint16_t x)
{
    cell::CellSize = x;
}

uint16_t cell::getCellSize()
{
    return cell::CellSize;
}

bool cell::getFlag() {
    return *flag;
}

bool cell::getMine() {
    return *mine;
}

uint16_t cell::getCountMineAround() {
    return *countMineAround;
}

