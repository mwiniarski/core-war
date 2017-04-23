#include "Cu.h"

#include <stdexcept>
#include <memory>

Cu::Cu(std::unique_ptr<Ram> ram_)
    :ram(std::move(ram_))
{

}

void Cu::throwCuError(std::string msg){
    throw std::runtime_error("Cu error: " + msg);
}
