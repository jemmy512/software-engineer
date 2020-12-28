#include <unordered_map>
#include <iostream>
#include <list>

template<typename Key, typename Value>
struct CacheEntry {
    Key _Key;
    Value _Value;
    CacheEntry* _Prev = nullptr;
    CacheEntry* _Next = nullptr;

    CacheEntry(Key k, Value v) : _Key(k), _Value(v) {}

    const CacheEntry* next() const {
        return _Next;
    }
};

template<typename Key, typename Value>
struct Cache {
    using CacheEntry = CacheEntry<Key, Value>;

    CacheEntry* _Head = nullptr;
    CacheEntry* _Tail = nullptr;
    int _Size {0};

    Cache() : _Head(new CacheEntry(0, 0)), _Tail(new CacheEntry(0, 0)) {
        _Head->_Next = _Tail;
        _Tail->_Prev = _Head;
    }

    ~Cache() {
        delete _Head;
        delete _Tail;
    }

    CacheEntry* front() const {
        return _Head->_Next;
    }

    CacheEntry* back() const {
        return _Tail->_Prev;
    }

    int size() const {
        return _Size;
    }

    void move_front(CacheEntry* entry) {
        entry->_Prev->_Next = entry->_Next;
        entry->_Next->_Prev = entry->_Prev;

        entry->_Next = _Head->_Next;
        _Head->_Next->_Prev = entry;
        _Head->_Next = entry;
        entry->_Prev = _Head;
    }

    void pop_back() {
        --_Size;
        auto* back = _Tail->_Prev;
        back->_Prev->_Next = _Tail;
        _Tail->_Prev = back->_Prev;
        delete back;
    }

    void empalce_back(int key, int value) {
        ++_Size;
        auto* entry = new CacheEntry(key, value);
        entry->_Next = _Tail;
        entry->_Prev = _Tail->_Prev;
        _Tail->_Prev->_Next = entry;
        _Tail->_Prev = entry;
    }

    void empalce_front(int key, int value) {
        ++_Size;
        auto* entry = new CacheEntry(key, value);
        entry->_Next = _Head->_Next;
        entry->_Prev = _Head;
        _Head->_Next->_Prev = entry;
        _Head->_Next = entry;
    }
};

template<typename Key, typename Val>
class LRUCache {
public:
    using key_type = Key;
    using value_type = Val;
    using const_reference = const value_type&;

    friend std::ostream& operator<< (std::ostream& os, const LRUCache& cache) {
        const auto* head = cache._Cache.front();
        while (head && head != cache._Cache._Tail) {
            os << "[" << head->_Key << " : " << head->_Value << "]" << " ";
            head = head->next();
        }
        os << std::endl;
        return os;
    }

public:
    LRUCache(int size) : _Size(size) {}

    const_reference get(const key_type& key) {
        auto iter = _Index.find(key);
        if (iter == _Index.end()) {
            return _End;
        }

        _Cache.move_front(iter->second);
        return iter->second->_Value;
    }

    void put(const key_type& key, const value_type& value) {
        auto iter = _Index.find(key);
        if (iter == _Index.end()) {
            if (_Cache.size() >= _Size) {
                _Index.erase(_Cache.back()->_Key);
                _Cache.pop_back();
            }

            _Cache.empalce_front(key, std::move(value));
            _Index.emplace(key, _Cache.front());
        } else {
            iter->second->_Value = std::move(value);
            _Cache.move_front(iter->second);
        }
    }

    const_reference end() const {
        return _End;
    }

private:
    /* const or reference members case synthesized copy-assignment operator, move members are deleted */
    const int _Size;
    value_type _End;
    Cache<key_type, value_type> _Cache;
    std::unordered_map<key_type, CacheEntry<key_type, value_type>*> _Index;
};

#define P(x) std::cout << x << std::endl;

int main() {
    LRUCache<int, int> cache(2);

    auto& get1 = cache.get(1);
    P(get1);
    std::cout << "---" << cache << std::endl;

    cache.put(2, 2);
    auto& get2 = cache.get(2);
    P(get2);
    std::cout << "---" << cache << std::endl;

    cache.put(3, 3);
    auto& get3 = cache.get(3);
    P(get3);
    std::cout << "---" << cache << std::endl;

    cache.put(4, 4);
    auto& get4 = cache.get(4);
    P(get4);
    std::cout << "---" << cache << std::endl;

    cache.put(5, 5);
    auto& get5 = cache.get(5);
    P(get5);
    std::cout << "---" << cache << std::endl;

    auto& get6 = cache.get(6);
    P(get6);
    std::cout << "---" << cache << std::endl;


    auto& get41 = cache.get(4);
    P(get41);
    std::cout << "---" << cache << std::endl;

    auto& get31 = cache.get(3);
    P(get31);
    std::cout << "---" << cache << std::endl;
}