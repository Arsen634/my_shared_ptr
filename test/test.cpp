﻿#include <iostream>
#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include "shaed_ptr.h"

BOOST_AUTO_TEST_CASE(test_unique_and_use_count)
{
    shared_ptr<int> p1(new int(9));
    BOOST_CHECK(p1.unique() == true);
    BOOST_CHECK(p1.use_count() == 1);
    BOOST_CHECK(p1.existsPtr() == true);
    BOOST_CHECK(p1.existsCount() == true);
    shared_ptr<int> p2(new int(10));
    BOOST_CHECK(p2.unique() == true);
    BOOST_CHECK(p2.use_count() == 1);
    BOOST_CHECK(p2.existsPtr() == true);
    BOOST_CHECK(p2.existsCount() == true);

    shared_ptr<int> p3(p1);
    BOOST_CHECK(p3.existsPtr() == true);
    BOOST_CHECK(p3.existsCount() == true);
    BOOST_CHECK(p1.use_count() == 2);
    BOOST_CHECK(p2.use_count() == 1);
    BOOST_CHECK(p3.use_count() == 2);
    BOOST_CHECK(p1.unique() == false);
    BOOST_CHECK(p2.unique() == true);
    BOOST_CHECK(p3.unique() == false);
    p3 = p2;
    BOOST_CHECK(p1.use_count() == 1);
    BOOST_CHECK(p2.use_count() == 2);
    BOOST_CHECK(p3.use_count() == 2);
    BOOST_CHECK(p1.unique() == true);
    BOOST_CHECK(p2.unique() == false);
    BOOST_CHECK(p3.unique() == false);

}

BOOST_AUTO_TEST_CASE(test_swap)
{
    shared_ptr<int> p1(new int(1));
    shared_ptr<int> p2(new int(2));
    BOOST_CHECK(p2.unique() == true);
    BOOST_CHECK(p2.use_count() == 1);
    shared_ptr<int> p3(p2);
    BOOST_CHECK(p2.unique() == false);
    BOOST_CHECK(p2.use_count() == 2);
    BOOST_CHECK(p1.unique() == true);
    BOOST_CHECK(p1.use_count() == 1);
    BOOST_CHECK(*p1 == 1);
    BOOST_CHECK(*p2 == 2);
    swap(p1, p2);
    BOOST_CHECK(*p1 == 2);
    BOOST_CHECK(*p2 == 1);
    BOOST_CHECK(p2.unique() == true);
    BOOST_CHECK(p2.use_count() == 1);
    BOOST_CHECK(p1.unique() == false);
    BOOST_CHECK(p1.use_count() == 2);
    shared_ptr<int> p4(p3);
    BOOST_CHECK(p1.unique() == false);
    BOOST_CHECK(p1.use_count() == 3);
    BOOST_CHECK(p2.unique() == true);
    BOOST_CHECK(p2.use_count() == 1);
    swap(p1, p2);
    BOOST_CHECK(p2.unique() == false);
    BOOST_CHECK(p3.unique() == false);
    BOOST_CHECK(p2.use_count() == 3);
    BOOST_CHECK(p3.use_count() == 3);
    BOOST_CHECK(p1.unique() == true);
    BOOST_CHECK(p1.use_count() == 1);

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

