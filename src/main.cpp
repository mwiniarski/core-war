#include <iostream>
#include <memory>
#include <sstream>
#include "Cu.h"
#include "Ram.h"
#include "Instruction.h"
#include "Parser.h"
using namespace std;

int main(int argc, char** argv)
{

    if(argc != 4)
    {
        cout << "wrong arguments count!" << endl;
        return 0;
    }

    int memSize = atoi(argv[1]);
    if(memSize % 100 != 0) {
        cout << "Memory size should be devidable by 80!"<< endl;
        return 0;
    }

    std::string arg1(argv[2]);
    std::string arg2(argv[3]);

    Cu cu(std::make_unique<Ram>(memSize));

    cu.loadFile(arg1, true);
    cu.loadFile(arg2, false);

    cu.run();

    return 1;
}
