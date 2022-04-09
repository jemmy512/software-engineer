/* Easy
Given an array of integers and an integer k, find out whether there are
two distinct indices i and j in the array such that nums[i] = nums[j] and the
absolute difference between i and j is at most k.

Constraints:
1 <= nums.length <= 10^5
-109 <= nums[i] <= 10^9
0 <= k <= 10^5 */

#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> hashSet;

        for (auto i = 0; i < nums.size(); ++i) {
            if (hashSet.count(nums[i]))
                return true;

            hashSet.emplace(nums[i]);

            if (hashSet.size() > k) {
                hashSet.erase(nums[i-k]);
            }
        }

        return false;
    }
};

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> hashMap;

        for (int i = 0; i < nums.size(); ++i) {
            if (hashMap.find(nums[i]) != hashMap.end() && i - hashMap[nums[i]] <= k)
                return true;
            hashMap[nums[i]] = i;
        }

        return false;
    }
};