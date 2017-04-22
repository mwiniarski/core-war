#ifndef ALU_H_
#define ALU_H_

#include <string>

class Alu
{
public:
    Alu();

private:
    void throwAluError(std::string msg);
};

#endif // ALU_H_
