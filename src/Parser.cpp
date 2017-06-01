#include "Parser.h"

#include <stdexcept>

Parser::Parser(std::istream& in1_)
:in(in_)
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

    return stoi(ret) * sign;
}

char Parser::getChar() {
    if (in)
        return static_cast<char>(in.get());
    else
        return -1;
}

void Parser::whitespace(){
    if(getChar() != ' ')
        throwParserError("required whitespece");
}

void Parser::endLine() {
    while(in.peek() == ' ')
        getChar();

    if(in.peek() != '\n')
        throwParserError("can't reach newline");

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
    endLine();
}

Instruction Parser::getInstruction(){
    parseLine();

    return Instruction(opCode, {argA, signA}, {argB, signB});
}


void Parser::throwParserError(std::string msg){
    throw std::runtime_error("Parser error: " + msg);
}
