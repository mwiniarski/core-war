#ifndef PARSER_H_
#define PARSER_H_

#include <string>

class Parser
{
public:
    Parser();

private:
    void throwParserError(std::string msg);
};

#endif // PARSER_H_
