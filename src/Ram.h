#ifndef RAM_H_
#define RAM_H_

#include <string>
#include <memory>

#include "Instruction.h"

class Ram
{
public:
    Ram(int size);

    void setInstruction(int address, Instruction i);
    Instruction getInstruction(int address);

    int getMemorySize() {return MEMORY_SIZE;}
private:
    const int MEMORY_SIZE;
    std::unique_ptr<Instruction[]> memory;
    void throwRamError(std::string msg);
};

#endif // RAM_H_
