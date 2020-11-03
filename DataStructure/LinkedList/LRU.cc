#include <unordered_map>
#include <iostream>
#include <list>

template<typename KeyT, typename ValT>
using faultFunction = std::function<ValT(const KeyT&)>;

template<typename KeyT, typename ValT>
class LRUCache {
public:
    using KeyValuePair = std::pair<KeyT, ValT>;

    friend std::ostream& operator<< (std::ostream& os, const LRUCache& cache) {
        for (const auto& [k, v] : cache.mCache) {
            os << v <<  " ";
        }
        return os;
    }

public:
    LRUCache(int size, faultFunction<KeyT, ValT> faultFn)
    : mSize(size), mFaultFunction(faultFn) {}

    ValT& get(const KeyT& key) {
        ValT val;
        auto iter = mIndex.find(key);
        if (iter == mIndex.end()) {
            if (mCache.size() == mSize && !mCache.empty()) {
                const auto& [key, val] = mCache.back();
                mIndex.erase(key);
                mCache.pop_back();
            }
            val = std::move(mFaultFunction(key));
        } else {
            val = std::move(iter->second->second);
            mCache.erase(iter->second);
        }

        mCache.push_front(std::make_pair(key, std::move(val)));
        mIndex[key] = mCache.begin();

        return mCache.front().second;
    }

private:
    /* const or reference members case synthesized copy-assignment operator, move members are deleted */
    const int mSize;
    std::list<KeyValuePair> mCache;
    faultFunction<KeyT, ValT> mFaultFunction;
    std::unordered_map<KeyT, typename std::list<KeyValuePair>::iterator> mIndex;
};

#define P(x) std::cout << x << std::endl;

int main() {
    auto faultFn = [](const int& key) -> int { return key; };
    LRUCache<int, int> cache(3, faultFn);

    auto& get1 = cache.get(1);
    P(get1);
    std::cout << "---" << cache << std::endl;

    auto& get2 = cache.get(2);
    P(get2);
    std::cout << "---" << cache << std::endl;

    auto& get3 = cache.get(3);
    P(get3);
    std::cout << "---" << cache << std::endl;

    auto& get4 = cache.get(4);
    P(get4);
    std::cout << "---" << cache << std::endl;

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