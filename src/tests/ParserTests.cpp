#include "../Parser.h"

#include <sstream>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(InstructionTests)

BOOST_AUTO_TEST_CASE(parser_simple)
{
    std::istringstream in("MOV @1 <-5 \nADD 1 #178 \n");
    auto p = std::make_unique<Parser>(in, 500);
    BOOST_CHECK_EQUAL(p->getInstruction().to_string(), "MOV@1<-5");
    BOOST_CHECK_EQUAL(p->getInstruction().to_string(), "ADD1#178");
}

BOOST_AUTO_TEST_SUITE_END()
