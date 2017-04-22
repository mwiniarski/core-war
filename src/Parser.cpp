#include "Parser.h"

#include <stdexcept>

Parser::Parser()
{}

void Parser::throwParserError(std::string msg){
    throw std::runtime_error("Parser error: " + msg);
}
