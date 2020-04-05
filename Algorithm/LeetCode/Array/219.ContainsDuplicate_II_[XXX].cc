/*
Given an array of integers and an integer k, find out whether there are 
two distinct indices i and j in the array such that nums[i] = nums[j] and the
 absolute difference between i and j is at most k.
*/

#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

// 23/23 test cases, 26ms, beat 92.72%
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        int len = nums.size();
        // Time Limit Exceeded
        // for (int i = 0; i < len; ++i) {
        //     for (int j = i + 1; j <= i + k && j < len; ++j) {
        //         if (nums[i] == nums[j] && abs(i - j) <= k)
        //             return true;
        //     }
        // }
        unordered_map<int, int> umap;
        for (int i = 0; i < len; ++i) {
            if (umap.find(nums[i]) != umap.end() && i - umap[nums[i]] <= k)
                return true;
            umap[nums[i]] = i;
        }
        
        return false;
    }
};

int main() {
    vector<int> vec = {}
}