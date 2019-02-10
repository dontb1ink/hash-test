// clang-format off
#include <iostream>
#include "hash.hpp"

#define BOOST_TEST_MODULE hash
#include <boost/test/included/unit_test.hpp>
// clang-format on

BOOST_AUTO_TEST_CASE(test_put_get) {
    HashTable<int, char> ht;
    int key(42);
    char val('v');

    ht.put(key, val);
    BOOST_TEST(ht.size() == 1);
    BOOST_TEST(ht.get(key) == val);
}

BOOST_AUTO_TEST_CASE(test_size) {
    HashTable<int, char> ht;

    BOOST_TEST(ht.size() == 0);
    ht.put(42, 'v');
    BOOST_TEST(ht.size() == 1);
}

BOOST_AUTO_TEST_CASE(test_remove_empty) {
    HashTable<int, char> ht;

    ht.remove(42);
    BOOST_TEST(ht.size() == 0);
}

BOOST_AUTO_TEST_CASE(test_remove_single) {
    HashTable<int, int> ht;
    int key(42);

    ht.put(key, key);
    ht.remove(key);
    BOOST_CHECK_THROW(ht.get(key), int);
    BOOST_TEST(ht.size() == 0);
}

BOOST_AUTO_TEST_CASE(test_remove_front) {
    HashTable<int, int> ht;
    int key1(0), key2(ht.INITIAL_CAPACITY), key3(ht.INITIAL_CAPACITY * 2);

    ht.put(key1, key1);
    ht.put(key2, key2);
    ht.put(key3, key3);
    ht.remove(key1);
    BOOST_TEST(ht.size() == 2);
    BOOST_CHECK_THROW(ht.get(key1), int);
    BOOST_TEST(ht.get(key2) == key2);
    BOOST_TEST(ht.get(key3) == key3);
}

BOOST_AUTO_TEST_CASE(test_remove_back) {
    HashTable<int, int> ht;
    int key1(0), key2(ht.INITIAL_CAPACITY), key3(ht.INITIAL_CAPACITY * 2);

    ht.put(key1, key1);
    ht.put(key2, key2);
    ht.put(key3, key3);
    ht.remove(key3);
    BOOST_TEST(ht.size() == 2);
    BOOST_CHECK_THROW(ht.get(key3), int);
    BOOST_TEST(ht.get(key1) == key1);
    BOOST_TEST(ht.get(key2) == key2);
}

BOOST_AUTO_TEST_CASE(test_remove_middle) {
    HashTable<int, int> ht;
    int key1(0), key2(ht.INITIAL_CAPACITY), key3(ht.INITIAL_CAPACITY * 2);

    ht.put(key1, key1);
    ht.put(key2, key2);
    ht.put(key3, key3);
    ht.remove(key2);
    BOOST_TEST(ht.size() == 2);
    BOOST_CHECK_THROW(ht.get(key2), int);
    BOOST_TEST(ht.get(key1) == key1);
    BOOST_TEST(ht.get(key3) == key3);
}


BOOST_AUTO_TEST_CASE(test_collision_single) {
    HashTable<int, char> ht;
    int key1(0), key2(ht.INITIAL_CAPACITY);
    int val1('x'), val2('y');

    ht.put(key1, val1);
    BOOST_TEST(ht.size() == 1);
    BOOST_TEST(ht.get(key1) == val1);
    ht.put(key2, val2);
    BOOST_TEST(ht.size() == 2);
    BOOST_TEST(ht.get(key1) == val1);
    BOOST_TEST(ht.get(key2) == val2);
}

BOOST_AUTO_TEST_CASE(test_collision_multiple) {
    HashTable<int, char> ht;
    int key1(0), key2(ht.INITIAL_CAPACITY), key3(ht.INITIAL_CAPACITY * 2);

    ht.put(key1, key1);
    ht.put(key2, key2);
    ht.put(key3, key3);
    BOOST_TEST(ht.size() == 3);
    BOOST_TEST(ht.get(key1) == key1);
    BOOST_TEST(ht.get(key2) == key2);
    BOOST_TEST(ht.get(key3) == key3);
}

BOOST_AUTO_TEST_CASE(test_resize1) {
    int i;
    HashTable<int, int> ht;
    int threshold(ht.INITIAL_CAPACITY * ht.LOAD_FACTOR);

    for (i = 0; i < threshold; i++) {
        ht.put(i, i);
    }
    for (i = 0; i < threshold; i++) {
        BOOST_TEST(ht.get(i) == i);
    }
    BOOST_TEST(ht.size() == threshold);
}

BOOST_AUTO_TEST_CASE(test_resize2) {
    int i, offset(42);
    HashTable<int, int> ht;
    int threshold(ht.INITIAL_CAPACITY * ht.LOAD_FACTOR);

    for (i = 0; i < threshold; i++) {
        ht.put(i + offset, i);
    }
    for (i = 0; i < threshold; i++) {
        BOOST_TEST(ht.get(i + offset) == i);
    }
    BOOST_TEST(ht.size() == threshold);
}

BOOST_AUTO_TEST_CASE(test_resize3) {
    int i;
    HashTable<int, int> ht;
    int threshold(ht.INITIAL_CAPACITY * ht.LOAD_FACTOR * 2 * 2 * 2);

    for (i = 0; i < threshold; i++) {
        ht.put(i, i);
    }
    for (i = 0; i < threshold; i++) {
        BOOST_TEST(ht.get(i) == i);
    }
    BOOST_TEST(ht.size() == threshold);
}
