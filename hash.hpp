#ifndef HASH_HPP
#define HASH_HPP

template <class K, class V>
class HashTable {
private:
    struct Element {
        bool open;
        K key;
        V val;
        Element* next;

        Element() : open(true), next(nullptr){};
        void set(const K& key, const V& val) {
            this->key = key;
            this->val = val;
            open = false;
        }
    };
    int size;
    Element* table;
    unsigned long hash(const K* key) { return reinterpret_cast<unsigned long>(key); }

public:
    HashTable() : size(16), table(new Element[size]){};
    void put(const K& key, const V& val) {
        int index(hash(&key) % size);
        Element* i(&table[index]);

        if (!i->open) {
            // Implement find element with key or new element at end
        }
        i->set(key, val);
    }
    const V& get(const K& key) {
        int index(hash(&key) % size);
        Element* i(&table[index]);

        while (i->key != key && i->next) i = i->next;
        return i->val;
    }
};

#endif