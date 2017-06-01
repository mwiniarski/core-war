#include "Cu.h"

Cu::Cu(std::unique_ptr<Ram> ram_)
    :ram(std::move(ram_))
{}

void Cu::loadFile(std::string fileName, bool isFirst)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::ifstream file(fileName);
    if(!file.is_open())
        throwCuError("CANT OPEN FILE");

    parser = std::make_unique<Parser>(file);

    int start, stop;

    //first quarter
    if(isFirst) {
        start = 0;
        stop = ram->getMemorySize() / 4;

    //third quarter
    } else {
        start = ram->getMemorySize() / 2;
        stop = ram->getMemorySize() * 3 / 4;
    }

    std::uniform_int_distribution<> dis(start, stop);
    int address = dis(gen);

    Instruction instruction = parser->getInstruction();
    while(instruction.getOp() != Instruction::Op::DAT){
        ram->setInstruction(address, instruction);
        address++;
        instruction = parser->getInstruction();
    }
}

void Cu::throwCuError(std::string msg){
    throw std::runtime_error("Cu error: " + msg);
}
