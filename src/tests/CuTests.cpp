#include "../Cu.h"

#include <sstream>

#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(CuTests)

BOOST_AUTO_TEST_CASE(Cu_init_test)
{
    Cu c(std::make_unique<Ram>(20));
    c.loadFile("src/tests/test_files/test1", true);
    Instruction op;
    for(int i=0; i<10; i++) {
        op = c.ram->getInstruction(i);
        if(op.getOp() != Instruction::Op::DAT) {
            BOOST_CHECK_EQUAL(op.to_string(), "MOV@1#-4");
            op = c.ram->getInstruction(i+1);
            BOOST_CHECK_EQUAL(op.to_string(), "ADD12");
            break;
        }
    }
}

BOOST_AUTO_TEST_CASE(cu_test2)
{
    Cu c(std::make_unique<Ram>(20));
    c.loadFile("src/tests/test_files/test1", true);
    Instruction op;
    for(int i=10; i<20; i++) {
        op = c.ram->getInstruction(i);
        if(op.getOp() != Instruction::Op::DAT) {
            BOOST_CHECK_EQUAL(op.to_string(), "MOV@1#-4");
            op = c.ram->getInstruction(i+1);
            BOOST_CHECK_EQUAL(op.to_string(), "ADD12");
            break;
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()
