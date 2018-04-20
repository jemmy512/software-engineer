/*
Given an array of integers, every element appears twice except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

Tips:
    The same numbers XOR together will be 0
*/
#include<iostream>
#include<vector>
#include<numeric>    // accumulate
#include<functional> // bit_xor
using namespace std;

// 14ms, beat 85.23%
int singleNumber(vector<int>& nums) {
    return accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
}

// 15ms, 66.37%
int singleNumber_1(vector<int>& nums) {
    int len = nums.size();
    int ret = 0;
    for (int i = 0; i < len; ++i)
        ret = ret ^ nums[i];
    
    return ret;
}

int main() {
    vector<int> vec = {1, 2, 6, 2, 1};
    cout << singleNumber(vec) << endl;
}