#include "Alu.h"

#include <stdexcept>

Alu::Alu()
{}

void Alu::throwAluError(std::string msg){
    throw std::runtime_error("Alu error: " + msg);
}
