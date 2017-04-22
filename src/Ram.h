#ifndef RAM_H_
#define RAM_H_

#include <string>

class Ram
{
public:
    Ram();

private:
    void throwRamError(std::string msg);
};

#endif // RAM_H_
