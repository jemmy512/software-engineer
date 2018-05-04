/*
Given a non-empty array of integers, return the third maximum number in this array.
 If it does not exist, return the maximum number. The time complexity must be in O(n).

Example 1:
Input: [3, 2, 1]

Output: 1

Explanation: The third maximum is 1.
Example 2:
Input: [1, 2]

Output: 2

Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
Example 3:
Input: [2, 2, 3, 1]

Output: 1

Explanation: Note that the third maximum here means the third maximum distinct number.
Both numbers with value 2 are both considered as second maximum.
*/

class Solution {
public:
    int thirdMax(vector<int>& nums) {
        int len = nums.size();
        long max[3] = {LONG_MIN, LONG_MIN, LONG_MIN};
        
        for (int i = 0; i < len; ++i) {
            if (nums[i] == max[0] || nums[i] == max[1] || nums[i] == max[2])
                continue;
            if (nums[i] > max[0]) {
                max[2] = max[1];
                max[1] = max[0];
                max[0] = nums[i];
            } else if (nums[i] > max[1]) {
                max[2] = max[1];
                max[1] = nums[i];
            } else if (nums[i] > max[2]) {
                max[2] = nums[i];
            }
        }
        
        if (max[2] != LONG_MIN)
            return max[2];
        else 
            return max[0];
    }
};