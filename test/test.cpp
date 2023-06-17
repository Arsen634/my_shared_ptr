#include <iostream>
#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include "..shaed_ptr.h"

BOOST_AUTO_TEST_CASE(test_main_1)
{
    shared_ptr<int> p1(new int(9));
    BOOST_CHECK(*p1 == 9);
    BOOST_CHECK(p1.unique() == true);
    BOOST_CHECK(p1.use_count() == 1);
    BOOST_CHECK(p1.existsPtr() == true);
    BOOST_CHECK(p1.existsCount() == true);
    shared_ptr<int> p2(new int(10));
    BOOST_CHECK(*p2 == 10);
    BOOST_CHECK(p2.unique() == true);
    BOOST_CHECK(p2.use_count() == 1);
    BOOST_CHECK(p2.existsPtr() == true);
    BOOST_CHECK(p2.existsCount() == true);
}

BOOST_AUTO_TEST_CASE(test_main_2)
{

    shared_ptr<int> p1(new int(9));
    shared_ptr<int> p2(new int(10));
    BOOST_CHECK(p1.use_count() == 1);
    BOOST_CHECK(p2.use_count() == 1);
    p1 = p2;
    BOOST_CHECK(*p1 == 10);
    BOOST_CHECK(*p2 == 10);
    BOOST_CHECK(p2.unique() == false);
    BOOST_CHECK(p2.unique() == false);
    BOOST_CHECK(p1.use_count() == 2);
    BOOST_CHECK(p2.use_count() == 2);
}

BOOST_AUTO_TEST_CASE(test_main_3)
{

    shared_ptr<int> p1(new int(9));
    shared_ptr<int> p2(p1);
    BOOST_CHECK(*p1 == 9);
    BOOST_CHECK(*p2 == 9);
    BOOST_CHECK(p2.unique() == false);
    BOOST_CHECK(p2.unique() == false);
    BOOST_CHECK(p1.use_count() == 2);
    BOOST_CHECK(p2.use_count() == 2);
}

BOOST_AUTO_TEST_CASE(test_main_4)
{
    shared_ptr<int> p1(new int(9));
    {
        shared_ptr<int> p2(new int(10));
        p1 = p2;
        BOOST_CHECK(p2.unique() == false);
        BOOST_CHECK(p2.unique() == false);
        BOOST_CHECK(p1.use_count() == 2);
        BOOST_CHECK(p2.use_count() == 2);
    }
    BOOST_CHECK(p1.unique() == true);
    BOOST_CHECK(p1.use_count() == 1);
}

BOOST_AUTO_TEST_CASE(test_main_5)
{
    shared_ptr<int> p1(new int(8));
    {
        shared_ptr<int> p2(new int(9));
        {
            shared_ptr<int> p3(new int(10));
            p1 = p2;
            BOOST_CHECK(p2.unique() == false);
            BOOST_CHECK(p2.unique() == false);
            BOOST_CHECK(p1.use_count() == 2);
            BOOST_CHECK(p2.use_count() == 2);
            p3 = p2;
            BOOST_CHECK(p1.use_count() == 3);
            BOOST_CHECK(p2.use_count() == 3);
        }
        BOOST_CHECK(p1.unique() == false);
        BOOST_CHECK(p1.use_count() == 2);
        BOOST_CHECK(p2.unique() == false);
        BOOST_CHECK(p2.use_count() == 2);
    }
    BOOST_CHECK(p1.unique() == true);
    BOOST_CHECK(p1.use_count() == 1);
}

BOOST_AUTO_TEST_CASE(test_main_6)
{
    shared_ptr<int> p1(new int(9));
    {
        shared_ptr<int> p2(p1);

        BOOST_CHECK(p2.unique() == false);
        BOOST_CHECK(p2.unique() == false);
        BOOST_CHECK(p1.use_count() == 2);
        BOOST_CHECK(p2.use_count() == 2);
    }
    BOOST_CHECK(p1.unique() == true);
    BOOST_CHECK(p1.use_count() == 1);
}

BOOST_AUTO_TEST_CASE(test_swap_main_1)
{
    shared_ptr<int> p1(new int(1));
    shared_ptr<int> p2(new int(2));
    swap(p1, p2);
    BOOST_CHECK(*p1 == 2);
    BOOST_CHECK(*p2 == 1);
    // BOOST_CHECK();
}

BOOST_AUTO_TEST_CASE(test_swap_main_2)
{
    shared_ptr<int> p1(new int(1));
    shared_ptr<int> p2(new int(2));
    shared_ptr<int> p3(p2);
    BOOST_CHECK(*p1 == 1);
    BOOST_CHECK(*p2 == 2);
    BOOST_CHECK(*p3 == 2);
    BOOST_CHECK(p1.use_count() == 1);
    BOOST_CHECK(p2.use_count() == 2);
    BOOST_CHECK(p3.use_count() == 2);
    swap(p1, p3);
    BOOST_CHECK(*p1 == 2);
    BOOST_CHECK(*p2 == 2);
    BOOST_CHECK(*p3 == 1);
    // BOOST_CHECK();
}

BOOST_AUTO_TEST_CASE(test_nollptr)
{
    shared_ptr<int> p1(new int(9));
    shared_ptr<int> p2;
    BOOST_CHECK(p1.unique() == true);
    BOOST_CHECK(p1.use_count() == 1);
    BOOST_CHECK(p1.existsPtr() == true);
    BOOST_CHECK(p1.existsCount() == true);
    BOOST_CHECK(p2.unique() == false);
    BOOST_CHECK(p2.use_count() == 0);
    BOOST_CHECK(p2.existsPtr() == false);
    BOOST_CHECK(p2.existsCount() == false);
    p1 = p2;
    BOOST_CHECK(p1.unique() == false);
    BOOST_CHECK(p1.use_count() == 0);
    BOOST_CHECK(p1.existsPtr() == false);
    BOOST_CHECK(p1.existsCount() == false);

}