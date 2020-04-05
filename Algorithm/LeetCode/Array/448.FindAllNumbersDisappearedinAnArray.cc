/*
Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.

Find all the elements of [1, n] inclusive that do not appear in this array.

Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.

Example:

Input:
    [4,3,2,7,8,2,3,1]

Output:
    [5,6]

*/

// 34 test case, 129ms, beat 88.27%
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int len = nums.size();
        vector<int> vec;
        
//         int indx;
//         for (int i = 0; i < len; ++i) {
//             indx = (nums[i] > 0 ? nums[i] : -nums[i]) - 1;
//             if (nums[indx] > 0)
//                 nums[indx] = -nums[indx];
//         }
        
//         for (int i = 0; i < len; ++i) {
//             if (nums[i] > 0)
//                 vec.push_back(i+1);
//         }
        for (int i = 0; i < len; ++i) nums[(nums[i] - 1) % len] += len;
        for (int i = 0; i < len; ++i) {
            if (nums[i] <= len)
                vec.push_back(i + 1);
        }
        
        return vec;
    }
};