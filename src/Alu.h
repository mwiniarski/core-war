#ifndef ALU_H_
#define ALU_H_

#include <string>
#include <iostream>
#include "Ram.h"

class Alu
{
public:
    Alu(std::shared_ptr<Ram> ram_);

    void mov();
    void add();
    void sub();
    void jmp();
    void jmn();
    void jmz();
    void cmp();
    void slt();
    void djn();
    int spl();

    void set(int address);
    int getAddress();
    void setB(Instruction &i, int b);
    void setA(Instruction &i, int b);

    std::shared_ptr<Ram> ram;
private:
    Instruction inst;
    int address;

    int countAddress(Instruction::Arg arg);
    void throwAluError(std::string msg);
};

#endif // ALU_H_
