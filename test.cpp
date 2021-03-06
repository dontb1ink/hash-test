// clang-format off
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include "hash.hpp"

#define BOOST_TEST_MODULE hash
#include <boost/test/included/unit_test.hpp>
// clang-format on

BOOST_AUTO_TEST_CASE(test_put_get) {
    HashTable<int, char> ht;
    int key(-42);
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

// TODO: update single, fornt back

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
    int threshold(ht.INITIAL_CAPACITY * ht.MAX_LOAD_FACTOR);

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
    int threshold(ht.INITIAL_CAPACITY * ht.MAX_LOAD_FACTOR);

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
    int threshold(ht.INITIAL_CAPACITY * ht.MAX_LOAD_FACTOR * 2 * 2 * 2);

    for (i = 0; i < threshold; i++) {
        ht.put(i, i);
    }
    for (i = 0; i < threshold; i++) {
        BOOST_TEST(ht.get(i) == i);
    }
    BOOST_TEST(ht.size() == threshold);
}

BOOST_AUTO_TEST_CASE(test_unique_and_random_put) {
    const std::size_t size{100000};
    std::size_t i{};
    std::unordered_set<int> keys;
    std::unordered_set<int>::iterator it;
    HashTable<int, int> ht;

    for (; keys.size() != size; keys.insert(rand()))
        ;

    for (it = keys.begin(); it != keys.cend(); it++, i++) {
        ht.put(*it, *it);
        BOOST_TEST(ht.size() == i + 1);
        BOOST_TEST(ht.get(*it) == *it);
    }
    for (it = keys.begin(); it != keys.cend(); it++) {
        BOOST_TEST(ht.get(*it) == *it);
    }
}

BOOST_AUTO_TEST_CASE(test_chaos) {
    const std::size_t size{100000};
    std::size_t i{};
    int key;
    HashTable<int, int> ht;
    std::unordered_map<int, int> control;

    for (key = rand() % size; i < size; key = rand() % size, i++) {
        if (i % 2) {
            ht.put(key, key);
            control.insert({key, key});
        } else {
            ht.remove(key);
            control.erase(key);
        }
    }

    for (auto it = control.begin(); it != control.end(); it++) {
        BOOST_TEST(ht.get(it->first) == control.find(it->first)->second);
    }
}
