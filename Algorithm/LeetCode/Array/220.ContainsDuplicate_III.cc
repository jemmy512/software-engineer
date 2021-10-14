/* Middle
Given an array of integers, find out whether there are two distinct indices i
and j in the array such that the absolute difference between nums[i] and nums[j]
is at most t and the absolute difference between i and j is at most k.

Constraints:
0 <= nums.length <= 2 * 10^4
-2^31 <= nums[i] <= 2^31 - 1
0 <= k <= 10^4
0 <= t <= 2^31 - 1 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <map>

using namespace std;

// bucket sort
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if (nums.empty())
            return false;

        // 2^31 + 1 overflow
        const long bucketSize = (long)t + 1;

        map<long, long> bucket;

        for (auto i = 0; i < nums.size(); ++i) {
            auto index = getIndex(nums[i], bucketSize);

            if (bucket.find(index) != bucket.end())
                return true;
            if (bucket.find(index+1) != bucket.end() && abs(nums[i] - bucket[index+1]) < bucketSize)
                return true;
            if (bucket.find(index-1) != bucket.end() && abs(nums[i] - bucket[index-1]) < bucketSize)
                return true;

            bucket.emplace(index, nums[i]);

            if (i >= k)
                bucket.erase(getIndex(nums[i-k], bucketSize));
        }

        return false;
    }

private:
    long getIndex(long num, long size) {
        // -3 / 5 = 0, we want -3 / 5 = -1
        return num < 0 ? (num + 1) / size - 1 : (num / size);
    }
};


class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        int len = nums.size();
        set<long long> window;
        int low = 0;
        for (int i = 0; i < len; ++i) {
            if (i - low > k) {
                window.erase(nums[low++]);
            }
            set<long long>::iterator ite = window.lower_bound((long long)nums[i] - (long long)t);
            if (ite != window.end() && abs((long long)nums[i] - *ite) <= (long long)t)
                return true;
            window.insert(nums[i]);
        }
        // Time Limit Exceeded
        // unordered_map<int, int> umap;
        // pair<int, int> a;
        // function<bool(pair<long long, long long>)> pred = [&a, &t, &k](pair<long long, long long> b) {
        //     if (abs(a.first - b.first) <= t && abs(a.second - b.second) <= k)
        //         return true;
        //     return false;
        // };
        // for (int i = 0; i < len; ++i) {
        //     a = make_pair(nums[i], i);
        //     if (find_if(umap.begin(), umap.end(), pred) != umap.end())
        //         return true;
        //     umap[nums[i]] = i;
        // }
        return false;
    }
};