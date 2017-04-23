#include "../Instruction.h"

#include <sstream>

#include <boost/test/unit_test.hpp>
typedef Instruction::Op Iop;
typedef Instruction::Arg Iarg;

BOOST_AUTO_TEST_SUITE(InstructionTests)

BOOST_AUTO_TEST_CASE(instruction_get_opcode_and_optypes_works)
{
    Instruction i;
    BOOST_CHECK_EQUAL(i.getOp(), Iop::DAT);
}

BOOST_AUTO_TEST_CASE(instruction_findop_returns_good_op)
{
    BOOST_CHECK_EQUAL(Instruction::findOp("DAT"), Iop::DAT);
    BOOST_CHECK_EQUAL(Instruction::findOp("JMN"), Iop::JMN);
    BOOST_CHECK_EQUAL(Instruction::findOp("SPL"), Iop::SPL);
    BOOST_CHECK_EQUAL(Instruction::findOp("asd"), Iop::ERROR);
}

BOOST_AUTO_TEST_CASE(instruction_struct_assigning)
{
    Iarg a{123};
    Iarg b{124, '@'};
    Instruction i(Iop::MOV, a, b);
    BOOST_CHECK_EQUAL(i.getA().addr, 123);
    BOOST_CHECK_EQUAL(i.getB().sign, '@');
    BOOST_CHECK_EQUAL(i.getA().sign, 0);
}

BOOST_AUTO_TEST_SUITE_END()
