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
* 053. Maximum Subarray
* 121. Best Time to Buy and Sell Stock
* 152. Maximum Product Subarry
* 198. House Robber
* 238. Product of Array Except Self
* 437. Path Sum III
* 560. Sub array Sum Equals K
* 628. Maximum Product of Three Numbers
* 713. Subarray Product Less Than K

Constraints:
1 <= nums.length <= 2 * 10^4
-10 <= nums[i] <= 10
The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer. */

class Solution {
public:
    int maxProduct(vector<int>& nums) {
       if (nums.empty())
            return 0;

        auto maxPro = nums[0];
        auto minPro = nums[0];
        auto result = nums[0];

        for (auto i = 1; i < nums.size(); ++i) {
            if (nums[i] < 0) {
                swap(maxPro, minPro);
            }
            maxPro = max(nums[i], maxPro *= nums[i]);
            minPro = min(nums[i], minPro *= nums[i]);
            result = max(result, maxPro);
        }

        return result;
    }
};
