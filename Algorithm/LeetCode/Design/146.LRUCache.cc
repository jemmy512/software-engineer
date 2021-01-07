/* Medium
Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.

void put(int key, int value) Update the value of the key if the key exists.
Otherwise, add the key-value pair to the cache. If the number of keys exceeds
the capacity from this operation, evict the least recently used key.

Follow up:
Could you do get and put in O(1) time complexity?

Example 1:
Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4


Constraints:
1 <= capacity <= 3000
0 <= key <= 3000
0 <= value <= 104
At most 3 * 104 calls will be made to get and put. */

#include <list>
#include <cassert>
#include <unordered_map>

using namespace std;

class LRUCache {
private:
    template<typename Key, typename Value>
    struct CacheEntry {
        Key _Key;
        Value _Value;
        CacheEntry* _Prev = nullptr;
        CacheEntry* _Next = nullptr;

        CacheEntry(Key k, Value v) : _Key(k), _Value(v) {}
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

private:
    int _Capacity;
    Cache<int, int> _Cache;
    unordered_map<int, CacheEntry<int, int>*> _Index;

public:
    LRUCache(int capacity) {
        assert(capacity > 0);
        _Capacity = capacity;
        _Index.reserve(capacity);
    }

    int get(int key) {
        auto iter = _Index.find(key);
        if (iter == _Index.end()) {
            return -1;
        }

        _Cache.move_front(iter->second);
        return iter->second->_Value;
    }

    void put(int key, int value) {
        auto iter = _Index.find(key);
        if (iter != _Index.end()) {
            iter->second->_Value = value;
            _Cache.move_front(iter->second);
        } else {
            if (_Cache.size() >= _Capacity) {
                _Index.erase(_Cache.back()->_Key);
                _Cache.pop_back();
            }
            _Cache.empalce_front(key, value);
            _Index.emplace(key, _Cache.front());
        }
    }
};

/* STL List Version */
class LRUCache {
public:
    LRUCache(int capacity) {
        assert(capacity > 0);
        _Capacity = capacity;
        _Index.reserve(capacity);
    }

    int get(int key) {
        auto iter = _Index.find(key);
        if (iter == _Index.end()) {
            return -1;
        }

        _Cache.splice(_Cache.begin(), _Cache, iter->second);
        return iter->second->second;
    }

    void put(int key, int value) {
        auto iter = _Index.find(key);
        if (iter != _Index.end()) {
            iter->second->second = value;
            _Cache.splice(_Cache.begin(), _Cache, iter->second);
        } else {
            if (_Cache.size() >= _Capacity) {
                _Index.erase((--_Cache.end())->first);
                _Cache.erase(--_Cache.end());
            }
            _Cache.emplace_front(key, value);
            _Index.emplace(key, _Cache.begin());
        }
    }

private:
    int _Capacity;
    std::list<std::pair<int, int>> _Cache;
    unordered_map<int, std::list<std::pair<int, int>>::iterator> _Index;
};

/* Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value); */

int main() {
    LRUCache cache{2};
    cache.put(1, 1);
    cache.put(2, 2);
    cache.get(1);
    cache.put(3, 3);
    cache.get(2);
    cache.put(4, 4);
    cache.put(2, 3);
    cache.get(1);
    cache.get(3);
    cache.get(2);
    cache.get(4);
}