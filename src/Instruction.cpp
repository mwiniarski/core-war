#include "Instruction.h"

Instruction::Instruction()
    :opcode(Op::DAT), argA({0}), argB({0})
{}

Instruction::Instruction(Op op_, Arg a_, Arg b_)
    :opcode(op_), argA(a_), argB(b_)
{}

const std::string Instruction::OpNames[(int)Op::COUNT] = {
    "DAT", "MOV", "ADD", "SUB", "JMP", "JMZ",
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

bool Instruction::isAllowed(char c) {
    const char allowedSigns[3] = {'<', '@', '#'};
    for(int i=0; i<3; i++){
        if(c == allowedSigns[i])
            return true;
    }
    return false;
}
void Instruction::throwInstructionError(std::string msg)
{
    throw std::runtime_error("Instruction error: " + msg);
}

bool Instruction::operator==(const Instruction& rhs)
{
    return opcode == rhs.opcode &&
           argA.sign == rhs.argA.sign &&
           argB.sign == rhs.argB.sign &&
           argB.addr == rhs.argB.addr &&
           argA.addr == rhs.argA.addr;
}
