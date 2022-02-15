/* Easy
You are a professional robber planning to rob houses along a street. Each house
has a certain amount of money stashed, the only constraint stopping you from robbing
each of them is that adjacent houses have security system connected and it will automatically
contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house,
determine the maximum amount of money you can rob tonight without alerting the police.

Constraints:
1 <= nums.length <= 100
0 <= nums[i] <= 400

Dynamic Programming
We can easy find the recurive fomulary:

    dp[n] = max(
        dp[n-1],            // the previous house has been robbed.
        dp[n-2] + money[n]  // the previous house has NOT been robbed.
    )

The initalization is obvious:
    dp[1] = money[1]
    dp[2] = max(money[1], money[2])

Relatives:
053. Maximum Subarray
121. Best Time to Buy and Sell Stock
152. Maximum Product Subarry
198. House Robber
213. House Robber II
337. House Robber III
238. Product of Array Except Self
256. Paint House
276. Paint Fence
437. Path Sum III
560. Sub array Sum Equals K
600. Non-negative Integers without Consecutive Ones
628. Maximum Product of Three Numbers
656. Coin Path
713. Subarray Product Less Than K
740. Delete and Earn */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int rob(vector<int>& money) {
        int dp_i_1 = 0;
        int dp_i_2 = 0;

        for (const auto mon : money) {
            auto curMax = std::max(dp_i_1, mon + dp_i_2);
            dp_i_2 = dp_i_1;
            dp_i_1 = curMax;
        }

        return dp_i_1;
    }
};

/* dont need to handle special case: i == 1, i == 2
 * rob money in order of i-1, i-2, i-3 ... 0 */
class Solution {
public:
    int rob(vector<int>& money) {
        const auto size = money.size();
        vector dp(size+2, 0);

        for (int i = size - 1; i >= 0; --i) {
            dp[i] = max(dp[i+1], money[i] + dp[i+2]);
        }

        return dp[0];
    }
};

// need to handle special cases: i == 1, i == 2
class Solution {
public:
    int rob(vector<int>& money) {
        const auto size = money.size();

        vector<int> dp(size, 0);
        if (size >= 1) dp[0] = money[0];
        if (size >= 2) dp[1] = max(money[0], money[1]);

        for (int i = 2; i < size; ++i){
            dp[i] = max(dp[i-1], dp[i-2] + money[i]);
        }

        return dp[size-1];
    }
};