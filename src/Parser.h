#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <iostream>
#include "Instruction.h"

class Parser
{
public:
    Parser(std::istream& in_, int memorySize);

    Instruction getInstruction();
private:
    char signA, signB;
    int argA, argB;
    Instruction::Op opCode;

    void parseLine();
    char getChar();
    void whitespace();
    void endLine();
    int getNumber();

    std::istream &in;
    int memorySize;
    void throwParserError(std::string msg);
};

#endif // PARSER_H_
