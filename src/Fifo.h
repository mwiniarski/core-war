#ifndef FIFO_H_
#define FIFO_H_

#include <string>

class Fifo
{
public:
    Fifo();

private:
    void throwFifoError(std::string msg);
};

#endif // FIFO_H_
