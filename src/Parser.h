#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <iostream>

class Parser
{
public:
    Parser();

private:
    //std::istream in;
    void throwParserError(std::string msg);
};

#endif // PARSER_H_
