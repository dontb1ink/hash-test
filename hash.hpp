#ifndef HASH_HPP
#define HASH_HPP

template <class T>
class HashTable {
private:
    struct Element {
        T val;
        Element* next;
        Element() : next(nullptr){};
        Element(T val) : val(val), next(nullptr){};
    };
    int size;
    Element *table;
    unsigned long hash(const T* val){
        return reinterpret_cast<unsigned long>(val);
    }

public:
    HashTable(): size(16), table(new Element[size]){};
    void put(const T& val){
        int index(hash(&val) % size);
        Element *i(&table[index]);
        for(;i->next;i=i->next);
        i->next = new Element(val);
    }
    int get(){
        return 2;
    }
};

#endif