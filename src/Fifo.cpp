#include "Fifo.h"

#include <stdexcept>

Fifo::Fifo(int addr_)
{
    address.push_back(addr_);
    iter = address.end();
}
void Fifo::check()
{
    if(iter == address.end())
        iter = address.begin();
}

int Fifo::getNext()
{
    if(address.empty())
        return -1;

    iter++;
    check();

    return *iter;
}

void Fifo::remove()
{
    check();
    iter = address.erase(iter);
}

void Fifo::set(int addr_)
{
    check();
    *iter = addr_;
}

void Fifo::add(int addr_)
{
    address.insert(iter, addr_);
}

void Fifo::throwFifoError(std::string msg){
    throw std::runtime_error("Fifo error: " + msg);
}
