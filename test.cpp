// clang-format off
#include <iostream>
#include <string>
#include "hash.hpp"

#define BOOST_TEST_MODULE hash
#include <boost/test/included/unit_test.hpp>
// clang-format on

using namespace std;

BOOST_AUTO_TEST_CASE(test1) {
    HashTable<char, char> ht;
    ht.put('a', 'a');
    ht.put('b', 'b');
    ht.put('d', 'u');
}

/* BOOST_AUTO_TEST_CASE(test1) {

    RBTree<int> rbt;
    rbt.insert(1);
    rbt.insert(1);
    rbt.insert(1);
    rbt.insert(1);
    rbt.insert(1);
    rbt.insert(1);
    rbt.insert(1);
    rbt.insert(1);
    rbt.insert(2);
    BOOST_TEST(rbt.find(6) == false);
} */
