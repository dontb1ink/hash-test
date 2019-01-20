#ifndef HASH_HPP
#define HASH_HPP

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
    int size;
    Element** table;
    unsigned long hash(const K* key) { return reinterpret_cast<unsigned long>(key); }

public:
    HashTable() : size(16), table(new Element*[size]()){};
    void put(const K& key, const V& val) {
        int index(hash(&key) % size);
        Element* i(table[index]);

        if (!i) {
            i = new Element();
            table[index] = i;
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
        int index(hash(&key) % size);
        Element* i(table[index]);

        while (i && i->key != key) i = i->next;
        if (!i) throw key;
        return i->val;
    }

    void remove(const K& key) {
        int index(hash(&key) % size);
        Element* i(table[index]);
        Element* tmp;

        if (!i) {
            return;
        } else if (i->key == key) {
            table[index] = i->next;
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