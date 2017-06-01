#ifndef CU_H_
#define CU_H_

#include "Parser.h"
#include "Ram.h"
#include <string>
#include <stdexcept>
#include <fstream>
#include <random>
#include <memory>


class Cu
{
public:
    Cu(std::unique_ptr<Ram> ram_);

private:
    void loadFile(std::string &fileName, bool isFirst);

    std::unique_ptr<Ram> ram;
    std::unique_ptr<Parser> parser;
    void throwCuError(std::string msg);
};

#endif // CU_H_
