#include "Printer.h"

Printer::Printer(std::shared_ptr<Ram> ram_)
    :ram(ram_)
{
    initscr();
    print();
}

Printer::~Printer()
{
    getch();
    endwin();
}

void Printer::winner(int winner)
{
    move(ram->getMemorySize() / 80 + 1, 0);
    printw("The winner is: program  %d !\n", winner);
}

void Printer::print(int address)
{
    int mem = ram->getMemorySize();
    move(0,0);
    for (int i = 0; i < mem; i += 80)
    {
        for (int j = 0; j < 80; j++)
        {
            if(ram->getInstruction(i + j).getOp() == Instruction::Op::DAT)
                printw("#");
            else
                printw("_");
        }
        printw("\n");
    }

    if(address != 0)
    {
        move(address/80, address%80);
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_GREEN);
        attron(COLOR_PAIR(1));
        printw("_");
        attroff(COLOR_PAIR(1));
    }

    refresh();
    usleep(10000);
}
