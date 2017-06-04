#include "../Ram.h"

#include <sstream>

#include <boost/test/unit_test.hpp>

    //BOOST_CHECK_THROW(functon(), std::runtime_error);
BOOST_AUTO_TEST_SUITE(RamTests)

BOOST_AUTO_TEST_CASE(ram_init_test)
{
    Ram r(8);
    BOOST_CHECK_EQUAL(r.getInstruction(0).getOp(), Instruction::Op::DAT);
}

BOOST_AUTO_TEST_CASE(ram_set_instruction_get_instruction_over_size)
{
    Ram r(4);
    r.setInstruction(1, Instruction(Instruction::Op::MOV, {1}, {2}));
    BOOST_CHECK_EQUAL(r.getInstruction(5).getOp(), Instruction::Op::MOV);
}

BOOST_AUTO_TEST_CASE(ram_increment)
{
    Ram r(4);
    int addr = 1;
    Instruction a = r.getInstruction(addr);
    a.setA(a.getA().addr + 1);
    r.setInstruction(addr, a);
    BOOST_CHECK_EQUAL(r.getInstruction(addr).getA().addr, 1);
}

BOOST_AUTO_TEST_SUITE_END()
