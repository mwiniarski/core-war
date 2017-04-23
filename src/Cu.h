#ifndef CU_H_
#define CU_H_

#include <string>
#include "Ram.h"

class Cu
{
public:
    Cu(std::unique_ptr<Ram> ram_);

private:
    std::unique_ptr<Ram> ram;
    void throwCuError(std::string msg);
};

#endif // CU_H_
