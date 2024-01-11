#include "mainform.h"
#include "Windows.h"
#include "game.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    minesweeper::mainform home;
    game::setForm(%home);
    game::newOutputField();
    Application::Run(%home);
}