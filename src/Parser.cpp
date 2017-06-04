#include "Parser.h"

#include <stdexcept>

Parser::Parser(std::istream& in_, int mem_)
:in(in_), memorySize(mem_)
{
}

int Parser::getNumber()
{
    std::string ret;
    int sign = 1;
    if(in.peek() == '-'){
        sign = -1;
        getChar();
    }

    if(!isdigit(in.peek()))
        throwParserError("argument not a number");

    ret += getChar();

    while(isdigit(in.peek()))
        ret += getChar();

    return (stoi(ret) % memorySize) * sign;
}

char Parser::getChar() {
    if (in)
        return static_cast<char>(in.get());
    else
        return -1;
}

void Parser::whitespace(){
    while(in.peek() == ' ' || in.peek() == '\n')
        getChar();
}

void Parser::parseLine()
{
    std::string opName;

    for(int i=0; i<3 ; i++)
        opName += getChar();

    whitespace();

    opCode = Instruction::findOp(opName);

    if(opCode == Instruction::Op::ERROR)
        throwParserError("no such instruction");

    signA = 0; signB = 0;

    if(Instruction::isAllowed(in.peek()))
        signA = getChar();

    argA = getNumber();
    whitespace();

    if(Instruction::isAllowed(in.peek()))
        signB = getChar();

    argB = getNumber();
    whitespace();
}

Instruction Parser::getInstruction()
{
    if(!in.eof()){
        parseLine();
        return Instruction(opCode, {argA, signA}, {argB, signB});
    }
    return Instruction();
}


void Parser::throwParserError(std::string msg){
    throw std::runtime_error("Parser error: " + msg);
}
