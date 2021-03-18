/* Medium
Given a non-empty array of integers, return the k most frequent elements.

Example 1:
Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2:
Input: nums = [1], k = 1
Output: [1]

Note:
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
It's guaranteed that the answer is unique, in other words the set of the top k frequent elements is unique.
You can return the answer in any order. */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> hashMap;
        for (const auto& n : nums) {
            ++hashMap[n];
        }

    }

private:
    template<typename Iter,
        typename T = std::iterator_traits<Iter>::value_type,
        typename Compare = std::less<T>>
    void heapifyDown(Iter beg, Iter cur, Iter end, Compare comp) {
        auto parent = cur;
        auto child = cur;

        for (std::advance(child, std::distance(beg, child)+1);
            child < end;
            std::advance(child, std::distance(beg, child) + 1))
        {
            if (child + 1 < end && comp(*(child+1), *child))
                child += 1;
        }
    }
};