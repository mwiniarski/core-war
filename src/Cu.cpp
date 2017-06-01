#include "Cu.h"

#include <stdexcept>
#include <fstream>
#include <memory>

Cu::Cu(std::unique_ptr<Ram> ram_)
    :ram(std::move(ram_)))
{}

void Cu:loadFile(str::string &filename)
{
    std::ifstream file(file1);
    parser = make_unique<Parser>(file);


}

void Cu::throwCuError(std::string msg){
    throw std::runtime_error("Cu error: " + msg);
}
