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
    std::istringstream in("MOV @1, <-5 \nADD 1, #177 \n");
    Parser p(in);
    p.getInstruction();
    p.getInstruction();
    return 0;
}
