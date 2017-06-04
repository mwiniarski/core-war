#include "Cu.h"

Cu::Cu(std::shared_ptr<Ram> ram_)
    :ram(std::move(ram_))
{}

void Cu::loadFile(std::string fileName, bool isFirst)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::ifstream file(fileName);
    if(!file.is_open())
        throwCuError("CANT OPEN FILE");

    Parser parser(file, ram->getMemorySize());

    int start, stop;

    //first quarter
    if(isFirst) {
        start = 0;
        stop = ram->getMemorySize() / 4;

    //third quarter
    } else {
        start = ram->getMemorySize() / 2;
        stop = ram->getMemorySize() * 3 / 4;
    }

    std::uniform_int_distribution<> dis(start, stop);
    int address = dis(gen);

    fifo[isFirst ? 0 : 1] = std::make_unique<Fifo>(address);

    Instruction instruction = parser.getInstruction();
    while(instruction.getOp() != Instruction::Op::DAT){
        ram->setInstruction(address, instruction);
        address++;
        instruction = parser.getInstruction();
    }
}

int Cu::process(Instruction::Op op, int address)
{
    typedef Instruction::Op IO;

    alu->set(address);

    switch(op)
    {
        case IO::MOV: alu->mov(); break;
        case IO::ADD: alu->add(); break;
        case IO::SUB: alu->sub(); break;
        case IO::JMP: alu->jmp(); break;
        case IO::JMN: alu->jmn(); break;
        case IO::JMZ: alu->jmz(); break;
        case IO::CMP: alu->cmp(); break;
        case IO::SLT: alu->slt(); break;
        case IO::DJN: alu->djn(); break;
        case IO::SPL: alu->spl(); break;

        default: break;
    }

    return alu->getAddress();
}

std::pair<int, int> Cu::processSpl(int address)
{
    alu->set(address);
    int address1 = alu->spl();
    int address2 = alu->getAddress();
    return std::make_pair(address1, address2);
}

void Cu::run()
{
    int program = 1, address;

    while(true)
    {
        program = !program;
        //get instruction
        address = fifo[program]->getNext();

        if(address == -1)
            break;

        Instruction::Op op = ram->getInstruction(address).getOp();

        //dat instruction ends life of thread
        if(op == Instruction::Op::DAT) {
            fifo[program]->remove();
            continue;
        }

        //new 'thread'
        if(op == Instruction::Op::SPL) {
            auto pair = processSpl(address);
            fifo[program]->add(pair.first);
            address = pair.second;
        }
        else
        {
            //process instruction and update fifo
            address = process(op, address);
        }

        fifo[program]->set(address);
    }

    std::cout << "The winner is program " << !program << " !" << std::endl;
}

void Cu::throwCuError(std::string msg){
    throw std::runtime_error("Cu error: " + msg);
}
