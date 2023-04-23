#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include "shared_ptr.h"
BOOST_AUTO_TEST_CASE(subtractTest)
{
    shared_ptr<int> p1(new int(9));
    BOOST_CHECK(p1.unique() == true);

    shared_ptr<int> p2(new int(10));
    BOOST_CHECK(p2.unique() == true);

    shared_ptr<int> p3(p1);
    BOOST_CHECK(p1.unique() == false);
    BOOST_CHECK(p2.unique() == true);
    BOOST_CHECK(p3.unique() == false);
    p3 = p2;
    BOOST_CHECK(p1.unique() == true);
    BOOST_CHECK(p2.unique() == false);
    BOOST_CHECK(p3.unique() == false);
    //fgjopwrgjopwrgjopwrgjop
}