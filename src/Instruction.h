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

    Instruction(Op op_, Arg a_, Arg b_);
    Instruction(Op op_, Arg a_, int b_);
    Instruction(Op op_, int a_, Arg b_);
    Instruction(Op op_, int a_, int b_);

    Arg getA(){return argA; }
    Arg getB(){return argB; }
    Op getOp(){ return opcode; }

    static Op findOp(std::string op);
    static std::string toString(Op op){ return OpNames[(int)op]; }
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
