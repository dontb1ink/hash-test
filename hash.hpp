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

        Element() : next{} {};
        void set(const K& key, const V& val) {
            this->key = key;
            this->val = val;
        }
    };
    static constexpr std::hash<K> hash{};
    std::size_t m_bucket_count;
    std::size_t m_size;
    std::size_t m_capacity;
    Element** m_table;

    void ht_resize() {
        std::size_t old_capacity{m_capacity};
        Element** old_table{m_table};

        m_bucket_count = 0;
        m_size = 0;
        m_capacity = old_capacity * 2;
        m_table = new Element* [m_capacity] {};
        for (std::size_t index{0}; index < old_capacity; index++) {
            for (Element *e{old_table[index]}, *tmp{}; e; tmp = e, put(e->key, e->val), e = e->next, delete tmp)
                ;
        }
        delete[] old_table;
    }

    void ht_put(const K& key, const V& val) {
        std::size_t index{hash(key) % m_capacity};
        Element* e{m_table[index]};

        if (e) {
            for (; e->key != key; e = e->next) {
                if (!e->next) {
                    e->next = new Element();
                    e = e->next;
                    break;
                }
            }
        } else if (m_bucket_count + 1 >= LOAD_FACTOR * m_capacity) {
            ht_resize();
            return put(key, val);
        } else {
            e = new Element();
            m_table[index] = e;
            m_bucket_count++;
        }
        e->set(key, val);
        m_size++;
    }

    const V& ht_get(const K& key) {
        std::size_t index{hash(key) % m_capacity};
        Element* e{m_table[index]};

        for (; e && e->key != key; e = e->next)
            ;
        if (!e) throw key;
        return e->val;
    }

    void ht_remove(const K& key) {
        std::size_t index{hash(key) % m_capacity};
        Element *e{m_table[index]}, *tmp{};

        if (!e) return;
        if (e->key == key) {
            tmp = e;
            m_table[index] = e->next;
            if (!e->next) m_bucket_count--;
        } else {
            for (; e->next; e = e->next) {
                if (e->next->key == key) {
                    tmp = e->next;
                    e->next = e->next->next;
                    break;
                }
            }
        }
        if (tmp) {
            delete tmp;
            m_size--;
        }
    }

    void ht_free() {
        for (std::size_t index{0}; index < m_capacity; index++) {
            for (Element *e{m_table[index]}, *tmp{}; e; tmp = e, e = e->next, delete tmp)
                ;
        }
        delete[] m_table;
    }

public:
    static constexpr float LOAD_FACTOR = 0.75;
    static constexpr std::size_t INITIAL_CAPACITY = 16;
    HashTable() : m_bucket_count{0}, m_size{0}, m_capacity{INITIAL_CAPACITY}, m_table{new Element* [m_capacity] {}} {};
    ~HashTable() { ht_free(); }
    void put(const K& key, const V& val) { return ht_put(key, val); }
    const V& get(const K& key) { return ht_get(key); }
    void remove(const K& key) { return ht_remove(key); }
    std::size_t size() { return m_size; }
};

#endif
