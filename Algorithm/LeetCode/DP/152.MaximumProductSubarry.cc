/* Medium
Given an integer array nums, find the contiguous subarray within an array
(containing at least one number) which has the largest product.

Example 1:
Input: [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.

Example 2:
Input: [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray. */

// The idea is similar with "Find the subarray wich has the largest sum"
// (See: http://en.wikipedia.org/wiki/Maximum_subarray_problem)
//
// The only thing to note here is, maximum product can also be obtained by minimum (negative) product
// ending with the previous element multiplied by this element. For example, in array {12, 2, -3, -5, -6, -2},
// when we are at element -2, the maximum product is multiplication of, minimum product ending with -6 and -2.

/* Relatives:
* 121. Best Time to Buy and Sell Stock
* 152. Maximum Product Subarry
* 437. Path Sum III
* 560. Sub array Sum Equals K */

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int len = nums.size();
        int maxPro = nums[0];
        int minPro = nums[0];
        int maxRet = nums[0];
        for (int i = 1; i < len; ++i) {
            if (nums[i] < 0)
                swap(maxPro, minPro);
            maxPro = max(nums[i], maxPro *= nums[i]);
            minPro = min(nums[i], minPro *= nums[i]);
            maxRet = max(maxRet, maxPro);
        }

        return maxRet;
    }
};
