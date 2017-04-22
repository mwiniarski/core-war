#include "Instruction.h"

Instruction::Instruction(Op op_, Arg a_, Arg b_)
    :opcode(op_), argA(a_), argB(b_)
{
    char allowedSigns[4] = {'<', '@', '#', 0};

    int t = 0;
    for(int i=0; i < 4; i++){
        if(a_.sign == allowedSigns[i])
            t++;
        if(b_.sign == allowedSigns[i])
            t++;
    }

    if(t != 2)
        throwInstructionError("sign not allowed");
}

Instruction::Instruction(Op op_, Arg a_, int b_)
    :Instruction(op_, a_, Arg{b_})
{}

Instruction::Instruction(Op op_, int a_, Arg b_)
    :Instruction(op_, Arg{a_}, b_)
{}

Instruction::Instruction(Op op_, int a_, int b_)
    :Instruction(op_, Arg{a_}, Arg{b_})
{}

const std::string Instruction::OpNames[(int)Op::COUNT] = {
    "DAT", "MOV", "ADD", "SUB", "JPM", "JMZ",
    "JMN", "CMP", "SLT", "DJN", "SPL"
};

// check if given string is a known atom
Instruction::Op Instruction::findOp(std::string op) {
    for(int i=0; i < (int)Op::COUNT; i++){
        if(op == OpNames[i])
            return static_cast<Op>(i);
    }
    return Op::ERROR;
}

void Instruction::throwInstructionError(std::string msg)
{
    throw std::runtime_error("Instruction error: " + msg);
}
