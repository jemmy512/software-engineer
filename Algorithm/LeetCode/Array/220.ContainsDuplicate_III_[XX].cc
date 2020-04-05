/*
Given an array of integers, find out whether there are two distinct indices i 
and j in the array such that the absolute difference between nums[i] and nums[j]
 is at most t and the absolute difference between i and j is at most k.
*/
#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<functional>
using namespace std;


// 40/40 cases, 17ms, beat 77.87%
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

int main() {
    vector<int> vec = {-1, 2147483647};
    cout << Solution::containsNearbyAlmostDuplicate(vec, 1, 2147483647) << endl;
}