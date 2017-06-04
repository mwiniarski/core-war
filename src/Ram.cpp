#include "Ram.h"

#include <stdexcept>

Ram::Ram(int size)
    :MEMORY_SIZE(size)
{
    memory = std::make_unique<Instruction[]>(MEMORY_SIZE);
}

void Ram::setInstruction(int address, Instruction i) {
    address = address % MEMORY_SIZE;
    if(address < 0)
        address += MEMORY_SIZE;
    memory[address % MEMORY_SIZE] = i;
}
Instruction Ram::getInstruction(int address) {
    address = address % MEMORY_SIZE;
    if(address < 0)
        address += MEMORY_SIZE;
    return memory[address];
}

void Ram::throwRamError(std::string msg){
    throw std::runtime_error("Ram error: " + msg);
}
