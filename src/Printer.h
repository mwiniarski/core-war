#ifndef PRINTER_H_
#define PRINTER_H_

#include <string>
#include <memory>
#include <iostream>

#include <ncurses.h>
#include <unistd.h>
using namespace std;

#include "Ram.h"
#include "Instruction.h"

class Printer
{
public:
    Printer(std::shared_ptr<Ram> ram_);
    ~Printer();

    Printer(const Printer&) = delete;
    const Ram& operator=(const Printer&) = delete;

    void winner(int winner);
    void print(int address = 0);
private:
    std::shared_ptr<Ram> ram;
};

#endif // RAM_H_
