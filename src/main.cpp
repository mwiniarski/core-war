#include <iostream>
#include <memory>

#include "Cu.h"
#include "Ram.h"
#include "Instruction.h"

int main()
{

    Cu c(std::make_unique<Ram>(10));
    return 0;
}
