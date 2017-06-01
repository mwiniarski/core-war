#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include <string>
#include <stdexcept>

class Instruction
{
public:
    enum class Op {
        //opcodes
        DAT=0, MOV, ADD, SUB, JPM, JMZ,
        JMN, CMP, SLT, DJN, SPL,

        //helpers
        COUNT, ERROR
    };

    struct Arg {
        int  addr;
        char sign = 0;
    };

    Instruction();
    Instruction(Op op_, Arg a_, Arg b_);

    Arg getA(){ return argA; }
    Arg getB(){ return argB; }
    void setA(Arg a) { argA = a; }
    void setB(Arg a) { argB = a; }

    Op getOp(){ return opcode; }

    static bool isAllowed(char c);
    static Op findOp(std::string op);
    static std::string toString(Op op){ return OpNames[(int)op]; }

    std::string to_string() {
        std::string ret = OpNames[(int)opcode];
        if(argA.sign != 0)
            ret += argA.sign;
        ret += std::to_string(argA.addr);
        if(argB.sign != 0)
            ret += argB.sign;
        return ret += std::to_string(argB.addr);
    }

private:
    Op opcode;
    Arg argA, argB;

    void throwInstructionError(std::string msg);
    static const std::string OpNames[(int)Op::COUNT];
};

inline std::ostream& operator<<(std::ostream& o, Instruction::Op op)
{
    return o << Instruction::toString(op);
}

#endif // INSTRUCTION_H_
