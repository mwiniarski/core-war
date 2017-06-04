#include "../Alu.h"

#include <sstream>

#include <boost/test/unit_test.hpp>

typedef Instruction::Op IO;
BOOST_AUTO_TEST_SUITE(AluTests)

void printI(Instruction i) {
    std::cout << Instruction::toString(i.getOp()) << " ";
    std::cout << i.getA().sign << i.getA().addr << " ";
    std::cout << i.getB().sign << i.getB().addr << std::endl;
}

BOOST_AUTO_TEST_CASE(alu_init_test)
{
    Alu a(std::make_unique<Ram>(3));
    Instruction i1(IO::MOV, {1, 0}, {2, 0});
    a.ram->setInstruction(0, i1);
    a.ram->setInstruction(1, i1);
    a.set(0);
    a.mov();
    BOOST_CHECK(a.ram->getInstruction(2) == i1);
}

BOOST_AUTO_TEST_CASE(alu_mov_alpha)
{
    Alu a(std::make_unique<Ram>(5));
    Instruction i1(IO::ADD, {0, 0}, {4, 0});
    Instruction i2(IO::MOV, {-2, 0}, {-2, '@'});
    a.ram->setInstruction(0, i1);
    a.ram->setInstruction(2, i2);
    a.set(2);
    a.mov();
    BOOST_CHECK(a.ram->getInstruction(4) == i1);
}

BOOST_AUTO_TEST_CASE(alu_decrement)
{
    Alu a(std::make_unique<Ram>(5));
    Instruction i1(IO::ADD, {0, 0}, {4, 0});
    Instruction res(IO::ADD, {0, 0}, {3, 0});
    Instruction i2(IO::MOV, {-2, 0}, {-2, '<'});
    a.ram->setInstruction(0, i1);
    a.ram->setInstruction(2, i2);
    a.set(2);
    a.mov();
    BOOST_CHECK(a.ram->getInstruction(3) == res);
    BOOST_CHECK(a.ram->getInstruction(0) == res);
}

BOOST_AUTO_TEST_CASE(alu_add_immidiate)
{
    Alu a(std::make_unique<Ram>(10));
    Instruction i1(IO::ADD, {5, '#'}, {0, 0});
    Instruction res(IO::ADD, {5, '#'}, {5, 0});
    a.ram->setInstruction(0, i1);
    a.set(0);
    a.add();
    BOOST_CHECK(a.ram->getInstruction(0) == res);
}

BOOST_AUTO_TEST_CASE(alu_add)
{
    Alu a(std::make_unique<Ram>(3));
    Instruction i1(IO::ADD, {1, 0}, {2, 0});
    Instruction i2(IO::MOV, {1, '<'}, {2, 0});
    Instruction res(IO::DAT, {1, 0}, {2, 0});
    a.ram->setInstruction(2, i1);
    a.ram->setInstruction(0, i2);
    a.set(2);
    a.add();
    BOOST_CHECK(a.ram->getInstruction(1) == res);
}

BOOST_AUTO_TEST_CASE(alu_sub)
{
    Alu a(std::make_unique<Ram>(3));
    Instruction i1(IO::SUB, {1, 0}, {2, 0});
    Instruction i2(IO::MOV, {1, '<'}, {2, 0});
    Instruction res(IO::DAT, {-1, 0}, {-2, 0});
    a.ram->setInstruction(2, i1);
    a.ram->setInstruction(0, i2);
    a.set(2);
    a.sub();
    BOOST_CHECK(a.ram->getInstruction(1) == res);
}

BOOST_AUTO_TEST_CASE(alu_jmp)
{
    Alu a(std::make_unique<Ram>(3));
    Instruction i1(IO::JMP, {2, 0}, {2, 0});
    Instruction i2(IO::MOV, {1, '<'}, {1, 0});
    a.ram->setInstruction(0, i1);
    a.ram->setInstruction(2, i2);
    a.set(0);
    a.jmp();
    BOOST_CHECK(a.ram->getInstruction(a.getAddress()) == i2);
}


BOOST_AUTO_TEST_SUITE_END()
