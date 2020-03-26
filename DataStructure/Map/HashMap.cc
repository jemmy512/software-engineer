/* Author: Jemmy
 * Date: 2020-03-22 */

#include <iostream>
#include <vector>
#include <utility>
#include <optional>

template<typename KeyT, typename ValT, typename HashT = std::hash<KeyT>>
class HashMap {
public:
    using key_type = KeyT;
    using mapped_type = ValT;
    using value_type = std::pair<const key_type, mapped_type>;
    using size_type = size_t;
    using hash_type = HashT;
    using element_type = std::shared_ptr<value_type>;

public:
    HashMap() {
        mContainer = new element_type[mCapacity];
    }

    ~HashMap() {
        delete [] mContainer;
    }

    bool empty() { return mSize == 0; }
    size_type size() { return mSize; }
    size_type capacity() { return mCapacity; }

    using optional_type = std::optional<std::reference_wrapper<mapped_type>>;
    optional_type find (const key_type& key) const {
        auto idx = index(key);
        auto result = mContainer[idx];

        return result ? optional_type(std::ref(result->second)) : std::nullopt;
    }

    mapped_type& operator[](const key_type& key) {
        auto idx = index(key);
        if (!mContainer[idx] && insertAt(idx, key) && loadFactor() >= mLoadFactor) {
            expand();
            idx = index(key);   // mCapacity changed
        }

        return mContainer[idx]->second;
    }

    void insert(const key_type& key, const mapped_type& val) {
        operator[](key) = val;
    }

private:
    size_type index(const key_type& key) const {
        auto idx = mHasher(key) % mCapacity;
        auto count = 1;
        while (mContainer[idx] != nullptr && mContainer[idx]->first != key) {
            idx = (idx + count++) % mCapacity;
        }

        return idx;
    }

    double loadFactor() const {
        return static_cast<double>(mSize / mCapacity);
    }

    bool insertAt(size_t idx, const key_type& key) {
        ++mSize;

        mContainer[idx] = std::make_shared<value_type>(std::make_pair(key, mapped_type()));

        return true;
    }

    void expand() {
        auto preCapacity = mCapacity;
        mCapacity *= 2;
        element_type* tmp = new element_type[mCapacity];

        for (auto idx = 0; idx < preCapacity; ++idx) {
            if (auto val = mContainer[idx]) {
                tmp[index(val->first)] = val;
            }
        }

        delete [] mContainer;

        mContainer = tmp;
    }

private:
    size_t mSize = 0;
    size_t mCapacity = 4;
    double mLoadFactor = 0.75;
    const hash_type mHasher = hash_type();
    element_type *mContainer;
};

template<typename KeyT, typename ValT>
void TestHashMap(HashMap<KeyT, ValT>& map, const KeyT& key, const ValT& val) {
    map.insert(key, val);

    std::cout << "Size: " << map.size() << "  Capacity: " << map.capacity() <<
    " Key: " << key << "  val: " << map[key] << std::endl << std::endl;
}

int main() {
    HashMap<int, int> map;

    TestHashMap(map, 1, 1);
    TestHashMap(map, 2, 2);
    TestHashMap(map, 3, 3);
    TestHashMap(map, 4, 4);
    TestHashMap(map, 5, 5);
    TestHashMap(map, 6, 6);
    TestHashMap(map, 7, 7);
    TestHashMap(map, 8, 8);
    TestHashMap(map, 9, 9);
    TestHashMap(map, 10, 10);

    if (auto opt = map.find(4)) {
        std::cout << "find key = 4, valu = " << *opt << std::endl;
    }

    if (auto opt = map.find(20)) {
    } else {
        std::cout << "Oops, not find key = 20" << std::endl;
    }

    return 0;
}