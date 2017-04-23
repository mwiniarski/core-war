#ifndef RAM_H_
#define RAM_H_

#include <string>

#include "Instruction.h"

class Ram
{
public:
    Ram(int size);
    
    void setInstruction(int address, Instruction i);
    Instruction getInstruction(int address);
private:
    const int MEMORY_SIZE;
    Instruction *memory;
    void throwRamError(std::string msg);
};

#endif // RAM_H_
