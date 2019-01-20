// clang-format off
#include "hash.hpp"

#define BOOST_TEST_MODULE hash
#include <boost/test/included/unit_test.hpp>
// clang-format on

using namespace std;

BOOST_AUTO_TEST_CASE(test1) {
    HashTable<char, char> ht;
    char x;

    x = 'a';
    ht.put(x,x);
    x = 'b';
    ht.put(x,x);
    x = 'b';
    ht.put(x,'u');
    BOOST_TEST(ht.get(x) == 'u');
    x = 'a';
    ht.remove(x);
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
