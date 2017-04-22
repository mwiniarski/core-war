#include "Ram.h"

#include <stdexcept>

Ram::Ram()
{}

void Ram::throwRamError(std::string msg){
    throw std::runtime_error("Ram error: " + msg);
}
