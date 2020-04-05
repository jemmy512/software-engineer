/*
Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.

Credits:
Special thanks to @ts for adding this problem and creating all test cases.
*/
#include<iostream>
#include<vector>
#include<map>
using namespace std;

// 44/44 test cases, 19ms, beat 97.24%
class Solution {
public:
    static int majorityElement(vector<int>& nums) {
        map<int, int> data;
        int len = nums.size();
        for (int i = 0; i < len; ++i) {
            if (++data[nums[i]] > len / 2)
                return nums[i];
        }
    }
    
// A Linear Time Majority Vote Algorithm  
// http://www.cs.utexas.edu/~moore/best-ideas/mjrty/index.html    
    static int majorityElement_(vector<int> &nums) {
        int majority;
        int cnt = 0;
        int len = nums.size();
        for (int i = 0; i < len; ++i) {
            if (cnt == 0) {
                majorit = nums[i];
                ++cnt;
            } else {
                majority = nums[i] == majority ? ++cnt : --cnt;
                // if (cnt > len / 2) return majority;
            }
        }
        
        return majority;
    }
};

int main() {
    vector<int> vec = {1,2,3,2,2,2,4,2,2,4};
    vector<int> ve = {1};
    cout << Solution::majorityElement(vec);
}