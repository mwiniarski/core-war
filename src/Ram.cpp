#include "Ram.h"

#include <stdexcept>

Ram::Ram(int size)
    :MEMORY_SIZE(size)
{
    memory = std::make_unique<Instruction[]>(MEMORY_SIZE);
}

void Ram::setInstruction(int address, Instruction i) {
    memory[address % MEMORY_SIZE] = i;
}
Instruction Ram::getInstruction(int address) {
    return memory[address % MEMORY_SIZE];
}

void Ram::throwRamError(std::string msg){
    throw std::runtime_error("Ram error: " + msg);
}
