#include "../Fifo.h"

#include <sstream>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(FifoTests)

BOOST_AUTO_TEST_CASE(fifo_init)
{
    Fifo f(5);
    BOOST_CHECK_EQUAL(f.getNext(), 5);
}

BOOST_AUTO_TEST_CASE(fifo_few_addresses)
{
    Fifo f(5);
    f.add(3);
    BOOST_CHECK_EQUAL(f.getNext(), 5);
    BOOST_CHECK_EQUAL(f.getNext(), 3);
}

BOOST_AUTO_TEST_CASE(fifo_remove)
{
    Fifo f(1);
    f.add(2);
    f.getNext();
    f.remove();
    BOOST_CHECK_EQUAL(f.getNext(), 2);
    BOOST_CHECK_EQUAL(f.getNext(), 2);
}

BOOST_AUTO_TEST_CASE(fifo_remove_last)
{
    Fifo f(1);
    f.remove();
    BOOST_CHECK_EQUAL(f.getNext(), -1);
}

BOOST_AUTO_TEST_CASE(fifo_set)
{
    Fifo f(1);
    f.set(2);
    BOOST_CHECK_EQUAL(f.getNext(), 2);
}

BOOST_AUTO_TEST_SUITE_END()
