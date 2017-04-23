#include "Fifo.h"

#include <stdexcept>

Fifo::Fifo()
{}

void Fifo::throwFifoError(std::string msg){
    throw std::runtime_error("Fifo error: " + msg);
}
