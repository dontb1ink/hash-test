// clang-format off
#include <iostream>
#include <cstdlib>
#include <stack>
#include "hash.hpp"

#define BOOST_TEST_MODULE hash
#include <boost/test/included/unit_test.hpp>
// clang-format on

using namespace std;

BOOST_AUTO_TEST_CASE(test1) {
    srand(42);
    
    std::stack<int> stack;
    HashTable<int, int> ht;
    int adds(0), removes(0);
    for(int i=0; i<1000; i++){
        int random = rand();
        if(random % 9 == 0 && !stack.empty()){
            ht.remove(stack.top());
            stack.pop();
            removes++;
        } else {
            ht.put(random, 0);
            stack.push(random);
            adds++;
        }
    }
    BOOST_TEST(ht.get(stack.top()) == 0);
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
