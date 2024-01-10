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
    this->BackgroundImage = resources::closedCell();
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
    if (*(this->isHide) == true) {
        srand(time(NULL));
        *countMineAround = rand() % 9;
        *(this->isHide) = false;
        this->Enabled = false;
        if (*mine == true)
            this->BackgroundImage = resources::redBomb();
        else 
        {
            switch (*countMineAround) {
            case 0:
                this->BackgroundImage = resources::emptyCell();
                break;
            case 1:
                this->BackgroundImage = resources::one();
                break;
            case 2:
                this->BackgroundImage = resources::two();
                break;
            case 3:
                this->BackgroundImage = resources::three();
                break;
            case 4:
                this->BackgroundImage = resources::four();
                break;
            case 5:
                this->BackgroundImage = resources::five();
                break;
            case 6:
                this->BackgroundImage = resources::six();
                break;
            case 7:
                this->BackgroundImage = resources::seven();
                break;
            case 8:
                this->BackgroundImage = resources::eight();
                break;
            }
        }
    }
}

void cell::setMine(bool mine) {
    *(this->mine) = mine;
}

void cell::setFlag(bool flag)
{
    *(this->flag) = flag;
    if (flag == true) this->BackgroundImage = resources::cellWithFlag();
    else this->BackgroundImage = resources::closedCell();
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

