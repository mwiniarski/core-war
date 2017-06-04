#include "Alu.h"

#include <stdexcept>

Alu::Alu(std::shared_ptr<Ram> ram_)
    :ram(std::move(ram_))
{}

void Alu::setB(Instruction &i, int b)
{
    i.setB(b % ram->getMemorySize());
}

void Alu::setA(Instruction &i, int a)
{
    i.setA(a % ram->getMemorySize());
}

int Alu::countAddress(Instruction::Arg arg)
{
    int ret = address + arg.addr;
    if(arg.sign == 0)
        return ret;

    if(arg.sign == '@')
        return ret + ram->getInstruction(ret).getB().addr;

    // so it must be '<'
    Instruction i = ram->getInstruction(ret);
    int newAddr = i.getB().addr - 1;
    setB(i, newAddr);
    ram->setInstruction(ret, i);
    return ret + newAddr;
}

/*
    MOV  A  B  :  If  the   A  operand  is
    immediate it  is placed in the B-field
    of the  memory  location  specified by
    the B  operand, otherwise the contents
    of   the    entire   memory   location
    specified by the A operand is moved to
    the memory location specified by the B
    operand.
*/
void Alu::mov()
{
    int b = countAddress(inst.getB());

    if(inst.getA().sign == '#')
    {
        Instruction i = ram->getInstruction(b);
        setB(i, inst.getB().addr);
        ram->setInstruction(b, i);
    } else
    {
        int a = countAddress(inst.getA());
        ram->setInstruction(b, ram->getInstruction(a));
    }

    address++;
}

/*
    ADD  A   B  :  If  the  A  operand  is
    immediate it  is added  to the B-field
    of the B operand.  If the A operand is
    not immediate both the  A-field and B-
    field  of  the  A  operand  are  added
    respectively  to  the  A-field  and B-
    field of the B operand.
*/
void Alu::add()
{
    int b = countAddress(inst.getB());
    Instruction i = ram->getInstruction(b);

    if(inst.getA().sign == '#')
    {
        setB(i, i.getB().addr + inst.getA().addr);
        ram->setInstruction(b, i);
    } else
    {
        Instruction i1 = ram->getInstruction(countAddress(inst.getA()));
        setA(i, i.getA().addr + i1.getA().addr);
        setB(i, i.getB().addr + i1.getB().addr);
        ram->setInstruction(b, i);
    }

    address++;
}

/*
    SUB  A   B  :  If  the  A  operand  is
    immediate it is subtracted from the B-
    field  of  the  B  operand.  If  the A
    operand is  not immediate  both the A-
    field and B-field of the A operand are
    subtracted  respectively  from  the A-
    field and B-field of the B operand.
*/
void Alu::sub()
{
    int b = countAddress(inst.getB());
    Instruction i = ram->getInstruction(b);

    if(inst.getA().sign == '#')
    {
        setB(i, i.getB().addr - inst.getA().addr);
        ram->setInstruction(b, i);
    } else
    {
        Instruction i1 = ram->getInstruction(countAddress(inst.getA()));
        setA(i, i.getA().addr - i1.getA().addr);
        setB(i, i.getB().addr - i1.getB().addr);
        ram->setInstruction(b, i);
    }

    address++;
}

/*
    JMP A  B :  The address  of the memory
    location specified by the A operand is
    placed  at  the  back  of  the process
    queue  associated  with  the executing
    program.   The   B  operand  does  not
    necessarily    participate    in   the
    execution of the instruction.
*/
void Alu::jmp()
{
    address = countAddress(inst.getA());
}

/*
    JMN A B :  If  the  B-field  of  the B
    operand is  not zero  then the address
    of the  memory  location  specifiec by
    the A operand is placed at the back of
    the process queue associated  with the
    executing program.`
*/
void Alu::jmn()
{
    int num;
    if(inst.getB().sign == '#')
    {
        num = inst.getB().addr;
    }
    else
    {
        int b = countAddress(inst.getB());
        num = ram->getInstruction(b).getB().addr;
    }

    if(num != 0)
    {
        address = countAddress(inst.getA());
    }
    else
    {
        address++;
    }
}

/*
    JMZ  A  B  :  If  the B-field of the B
    operand is zero  then  the  address of
    the memory location specified by the A
    operand is placed at  the back  of the
    process  queue   associated  with  the
    executing program.
*/
void Alu::jmz()
{
    int num;
    if(inst.getB().sign == '#')
    {
        num = inst.getB().addr;
    }
    else
    {
        int b = countAddress(inst.getB());
        num = ram->getInstruction(b).getB().addr;
    }

    if(num == 0)
    {
        address = countAddress(inst.getA());
    }
    else
    {
        address++;
    }
}

/*
    CMP  A   B  :  If  the  A  operand  is
    immediate it  is  compared  to  the B-
    field of the memory location specified
    by  the  B   operand,   otherwise  the
    contents of the entire memory location
    specified by the A operand is compared
    to the contents of the memory location
    specified by  the  B  operand.  If the
    compared  values  are  equal, the next
    instruction  is  skipped  (the program
    counter is incremented).
    */
void Alu::cmp()
{
    int b = countAddress(inst.getB());
    int a1, a2 = ram->getInstruction(b).getB().addr;

    if(inst.getA().sign == '#')
    {
        a1 = inst.getA().addr;
    }
    else
    {
        b = countAddress(inst.getA());
        a1 = ram->getInstruction(b).getB().addr;
    }

    if(a1 == a2)
    {
        address++;
    }

    address++;
}

/*
    SLT  A  B  :  If  the A operand is not
    immediate, the B-field  ot  the memory
    location specified by the A operand is
    compared  to  the  B-field  of  the  B
    operand,   otherwise   the  A  operand
    itself is  used in  the comparison. If
    the A  value is less than the B value,
    the next instruction  is  skipped (the
    program counter is incremented).
*/
void Alu::slt()
{
    int b = countAddress(inst.getB());
    int a1, a2 = ram->getInstruction(b).getB().addr;

    if(inst.getA().sign == '#')
    {
        a1 = inst.getA().addr;
    }
    else
    {
        b = countAddress(inst.getA());
        a1 = ram->getInstruction(b).getB().addr;
    }

    if(a1 < a2)
    {
        address++;
    }

    address++;
}

/*
    DJN  A  B  :  If  the B operand is not
    immediate, the B-field  of  the memory
    location specified by the B operand is
    fetched,    decremented,    and   then
    restored, otherwise the B-field of the
    current instruction  is  used.  If the
    value is  not zero, the address of the
    memory
    location specified by the  A operand is
    placed at the back of the process queue
    associated with the executing program.
*/
void Alu::djn()
{
    int num;
    if(inst.getB().sign == '#')
    {
        num = inst.getB().addr - 1;
        setB(inst, num);
        ram->setInstruction(address, inst);
    }
    else
    {
        int b = countAddress(inst.getB());
        Instruction i = ram->getInstruction(b);
        num = i.getB().addr - 1;
        setB(i, num);
        ram->setInstruction(b, i);
    }

    if(num != 0)
    {
        address = countAddress(inst.getA());
    }
    else
    {
        address++;
    }
}

/*
    SPL A B : After a process has caused an
    SPL  instruction  to  be  fetched,  the
    program  counter   is  incremented  and
    placed  at  the  back  of  its  process
    queue.  The  address  ot   the  spawned
    process is then placed  at the  back of
    the same queue, providing  the queue is
    not  full.  The  B   operand  does  not
    necessarily    participate    in    the
    execution of this instruction. 
*/
int Alu::spl()
{
    address++;
    return countAddress(inst.getA());;
}

void Alu::set(int addr_)
{
    inst = ram->getInstruction(addr_);
    address = addr_;
}

int Alu::getAddress()
{
    return address % ram->getMemorySize();
}

void Alu::throwAluError(std::string msg){
    throw std::runtime_error("Alu error: " + msg);
}
