#include "Fifo.h"

#include <stdexcept>

Fifo::Fifo(int addr_)
{
    address.push_back(addr_);
    iter = address.begin();
}

int Fifo::getNext()
{
    if(address.empty())
        return -1;

    if(iter == address.end()) {
        iter = address.begin();
        return *iter;
    }

    return *iter++;
}

void Fifo::remove()
{
    iter = address.erase(iter);
}

void Fifo::set(int addr_)
{
    *iter = addr_;
}

void Fifo::add(int addr_)
{
    address.insert(iter, addr_);
}

void Fifo::throwFifoError(std::string msg){
    throw std::runtime_error("Fifo error: " + msg);
}
