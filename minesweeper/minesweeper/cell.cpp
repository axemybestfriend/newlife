#include "cell.h"


cell::cell()
{
    flag = gcnew bool;
    mine = gcnew bool;
    *mine = false;
    isHide = gcnew bool;
    *isHide = true;
    countMineAround = gcnew uint16_t;
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
}

void cell::setCountMineAround(uint16_t countMineAround)
{
    *(this->countMineAround) = countMineAround;
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