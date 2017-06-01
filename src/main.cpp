#include <iostream>
#include <memory>
#include <sstream>

#include "Cu.h"
#include "Ram.h"
#include "Instruction.h"
#include "Parser.h"
using namespace std;

int main()
{
    Cu c(std::make_unique<Ram>(20));
    
    c.loadFile("src/tests/test_files/test1", true);
    return 0;
}
