#ifndef HASH_HPP
#define HASH_HPP

template <class T>
class HashTable {
private:
    struct Element {
        bool isOpen;
        T val;
        Element* next;
        Element() : isOpen(true), next(nullptr){};
        Element(T val) : isOpen(false), val(val), next(nullptr){};
    };
    int size;
    Element* table;
    unsigned long hash(const T* val) { return reinterpret_cast<unsigned long>(val); }

public:
    HashTable() : size(16), table(new Element[size]){};
    void put(const T& val) {
        int index(hash(&val) % size);
        Element* i(&table[index]);

        if (i->isOpen) {
            i->val = val;
            i->isOpen = false;
        } else {
            while (i->next) i = i->next;
            i->next = new Element(val);
        }
    }
    int get() { return 2; }
};

#endif