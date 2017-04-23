#include "../Cu.h"

#include <sstream>

#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(CuTests)

BOOST_AUTO_TEST_CASE(Cu_init_test)
{
    Cu c(std::make_unique<Ram>(10));
}

BOOST_AUTO_TEST_SUITE_END()
