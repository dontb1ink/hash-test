#ifndef HASH_HPP
#define HASH_HPP

#include <cstddef>
#include <functional>

template <class K, class V>
class HashTable {
private:
    struct Element {
        K key;
        V val;
        Element* next;

        Element() : next(nullptr){};
        void set(const K& key, const V& val) {
            this->key = key;
            this->val = val;
        }
    };
    static constexpr float loadFactor = 0.75;
    static constexpr std::hash<K> hash{};
    std::size_t bucket_count;
    std::size_t size;
    std::size_t capacity;
    Element** table;
    void resize(){

    }

public:
    HashTable() : bucket_count(0), size(0), capacity(16), table(new Element*[capacity]()){};
    void put(const K& key, const V& val) {
        std::size_t index(hash(key) % capacity);
        Element* i(table[index]);

        if (!i) {
            if (bucket_count + 1 >= loadFactor * capacity) {
                resize();
                return put(key, val);
            }
            i = new Element();
            table[index] = i;
            bucket_count++;
        } else {
            for (; i->key != key; i = i->next) {
                if (!i->next) {
                    i->next = new Element();
                    i = i->next;
                    break;
                }
            }
        }
        i->set(key, val);
    }

    const V& get(const K& key) {
        int index(hash(&key) % capacity);
        Element* i(table[index]);

        while (i && i->key != key) i = i->next;
        if (!i) throw key;
        return i->val;
    }

    void remove(const K& key) {
        int index(hash(&key) % capacity);
        Element* i(table[index]);
        Element* tmp;

        if (!i) {
            return;
        } else if (i->key == key) {
            table[index] = i->next;
            if(!table[index]) bucket_count--;
            tmp = i;
        } else {
            for (; i->next; i = i->next) {
                if (i->next->key == key) {
                    tmp = i->next;
                    i->next = i->next->next;
                    break;
                }
            }
        }
        delete tmp;
    }
};

#endif