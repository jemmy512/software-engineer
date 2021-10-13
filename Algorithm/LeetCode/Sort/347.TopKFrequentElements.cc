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
You can return the answer in any order.

Constraints:
1 <= nums.length <= 10^5
k is in the range [1, the number of unique elements in the array].
It is guaranteed that the answer is unique.

Relatives:
215. Kth Largest Element in an Array
324. Wiggle Sort II
347. Top K Frequent Elements
414. Third Maximum Number
703. Kth Largest Element in a Stream
973. K Closest Points to Origin
1985. Find the Kth Largest Integer in the Array */

#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> hashMap;
        for (const auto& n : nums) {
            ++hashMap[n];
        }

        auto comp = [&hashMap](const auto& lhs, const auto& rhs) {
            return hashMap[lhs] > hashMap[rhs];
        };

        priority_queue<int, vector<int>, decltype(comp)> heap(comp);

        for (const auto& [num, cnt] : hashMap) {
            heap.push(num);
            if (heap.size() > k)
                heap.pop();
        }

        vector<int> top;
        top.reserve(k);

        while (!heap.empty()) {
            top.emplace_back(heap.top());
            heap.pop();
        }

        return top;
    }
};

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> top;
        top.reserve(k);

        _HashMap.clear();
        for (const auto& n : nums) {
            ++_HashMap[n];
        }

        for (const auto& [num, cnt] : _HashMap) {
            if (top.size() < k) {
                top.emplace_back(num);
                heapifyDown(top, top.size()/2-1, top.size());
            } else {
                if (cnt > _HashMap[top[0]]) {
                    top[0] = num;
                    heapifyDown(top, 0, top.size());
                }
            }
        }

        return top;
    }

private:
    void heapifyDown(vector<int>& nums, int beg, int end) {
        for (auto parent = beg, child = 2 * parent + 1; child >= 0 && child < end; child = 2 * child + 1) {
            if (child + 1 < end && _HashMap[nums[child+1]] < _HashMap[nums[child]])
                ++child;

            if (_HashMap[nums[parent]] <= _HashMap[nums[child]])
                break;

            swap(nums[parent], nums[child]);
            parent = child;
        }
    }

private:
    unordered_map<int, int> _HashMap;
};