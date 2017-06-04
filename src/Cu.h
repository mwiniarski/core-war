#ifndef CU_H_
#define CU_H_

#include "Parser.h"
#include "Ram.h"
#include "Alu.h"
#include "Fifo.h"
#include <string>
#include <stdexcept>
#include <fstream>
#include <random>
#include <memory>


class Cu
{
public:
    Cu(std::shared_ptr<Ram> ram_);

    void run();
    void loadFile(std::string fileName, bool isFirst);

    std::shared_ptr<Ram> ram;

private:
    std::pair<int, int> processSpl(int address);
    int process(Instruction::Op op, int address);
    void throwCuError(std::string msg);

    std::unique_ptr<Fifo> fifo[2];
    std::unique_ptr<Alu> alu;
};

#endif // CU_H_
