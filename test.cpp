// clang-format off
#include <iostream>
#include "hash.hpp"

#define BOOST_TEST_MODULE hash
#include <boost/test/included/unit_test.hpp>
// clang-format on

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR 0.75

BOOST_AUTO_TEST_CASE(test_resize1) {
    int i, threshold(INITIAL_CAPACITY * LOAD_FACTOR);
    HashTable<int, char> ht;

    for (i = 0; i < threshold; i++) {
        ht.put(i, i);
    }
    for (i = 0; i < threshold; i++) {
        BOOST_TEST(ht.get(i) == i);
    }
    BOOST_TEST(ht.size() == threshold);
}

BOOST_AUTO_TEST_CASE(test_resize2) {
    int i, threshold(INITIAL_CAPACITY * LOAD_FACTOR), offset(42);
    HashTable<int, char> ht;

    for (i = 0; i < threshold; i++) {
        ht.put(i + offset, i);
    }
    for (i = 0; i < threshold; i++) {
        BOOST_TEST(ht.get(i + offset) == i);
    }
    BOOST_TEST(ht.size() == threshold);
}

BOOST_AUTO_TEST_CASE(test_resize3) {
    int i, threshold(INITIAL_CAPACITY * LOAD_FACTOR * 2 * 2 * 2);
    HashTable<int, char> ht;

    for (i = 0; i < threshold; i++) {
        ht.put(i, i);
    }
    for (i = 0; i < threshold; i++) {
        BOOST_TEST(ht.get(i) == i);
    }
    BOOST_TEST(ht.size() == threshold);
}
