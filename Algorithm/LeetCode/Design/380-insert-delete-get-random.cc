/* Medium
Implement the RandomizedSet class:
bool insert(int val)
    Inserts an item val into the set if not present. Returns true if the item was not present, false otherwise.
bool remove(int val)
    Removes an item val from the set if present. Returns true if the item was present, false otherwise.
int getRandom()
    Returns a random element from the current set of elements
    (it's guaranteed that at least one element exists when this method is called).
    Each element must have the same probability of being returned.

Follow up: Could you implement the functions of the class with each function works in average O(1) time?

Example 1:
Input
["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
[[], [1], [2], [2], [], [1], [2], []]
Output
[null, true, false, true, 2, true, false, 2]

Explanation
RandomizedSet randomizedSet = new RandomizedSet();
randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomizedSet.remove(2); // Returns false as 2 does not exist in the set.
randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now contains [1,2].
randomizedSet.getRandom(); // getRandom() should return either 1 or 2 randomly.
randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now contains [2].
randomizedSet.insert(2); // 2 was already in the set, so return false.
randomizedSet.getRandom(); // Since 2 is the only number in the set, getRandom() will always return 2.


Constraints:
-2^31 <= val <= 2^31 - 1
At most 105 calls will be made to insert, remove, and getRandom.
There will be at least one element in the data structure when getRandom is called. */

#include <list>
#include <vector>
#include <chrono>
#include <random>
#include <unordered_map>

/* Vector supports random access to ith element, which can do O(1) getRandom
 * Hash Map supports O(1) access to specific key, which can do O(1) insert, remove */
class RandomizedSet {
public:
    using value_type = int;
    using size_type = typename std::vector<value_type>::size_type;

public:
    RandomizedSet() = default;

    bool insert(value_type val) {
        if (hashMap.find(val) != hashMap.end())
            return false;

        vec.emplace_back(val);
        hashMap.emplace(vec.back(), vec.size()-1);
        return true;
    }

    /* remove ith element from vec will cause all indcies in hashMap invalide
     * swap the ith elem and back elem of vec, then delete the back elem */
    bool remove(value_type val) {
        auto iter = hashMap.find(val);
        if (iter == hashMap.end())
            return false;

        vec[iter->second] = vec.back();
        hashMap[vec.back()] = iter->second;
        hashMap.erase(val);
        vec.pop_back();
        return true;
    }

    int getRandom() {
        return *(vec.begin() + getRandom<value_type>(0, vec.size()-1));
    }

private:
    std::vector<value_type> vec;
    std::unordered_map<value_type, size_type> hashMap;

    // hashMap default constructor is deleted since std::reference_wrapper is deleted default construct,
    // std::unordered_map<std::reference_wrapper<const value_type>, size_type> hashMap;

    template<typename Size = int>
    Size getRandom(Size min, Size max) {
        static std::random_device dev;
        static std::default_random_engine engine(dev());
        static std::uniform_int_distribution<Size> distribute(min, max);

        return distribute(engine);
    }
};

/* List Version */
class RandomizedSet {
public:
    RandomizedSet() = default;

    bool insert(int val) {
        if (hashMap.find(val) != hashMap.end())
            return false;

        list.emplace_back(val);
        hashMap.emplace(val, --list.end());
        return true;
    }

    bool remove(int val) {
        auto iter = hashMap.find(val);
        if (iter == hashMap.end())
            return false;

        list.erase(hashMap[val]);
        hashMap.erase(val);
        return true;
    }

    /* Time complexity: O(N) */
    int getRandom() {
        auto begin = list.begin();
        std::advance(begin, getRandom<size_t>(0, list.size()-1));
        return *begin;
    }

private:
    std::list<int> list;
    std::unordered_map<int, std::list<int>::iterator> hashMap;

    template<typename Size = int>
    Size getRandom(Size min, Size max) {
        std::random_device dev;
        std::default_random_engine engine(dev());
        std::uniform_int_distribution<Size> distribution(min, max);

        return distribution(engine);
    }
};

/* Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom(); */