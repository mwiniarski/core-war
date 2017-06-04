#ifndef FIFO_H_
#define FIFO_H_

#include <string>
#include <list>

class Fifo
{
public:
    Fifo(int addr_);

    int getNext();
    void add(int addr_);
    void remove();
    void set(int addr_);
    
private:
    std::list<int> address;
    std::list<int>::iterator iter;
    void throwFifoError(std::string msg);
};

#endif // FIFO_H_
