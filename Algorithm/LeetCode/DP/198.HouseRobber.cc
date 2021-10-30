/* Easy
You are a professional robber planning to rob houses along a street. Each house
has a certain amount of money stashed, the only constraint stopping you from robbing
each of them is that adjacent houses have security system connected and it will automatically
contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house,
determine the maximum amount of money you can rob tonight without alerting the police.

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

/* Acutally, we no need to allocate an additional array for DP.
 * we can only use several variables to record previous steps */
int rob2(vector<int> &money) {
    std::vector dp{0, 0};

    for (const auto& mon : money) {
        auto curMax = std::max(dp[1], dp[0] + mon);
        dp[0] = dp[1];
        dp[1] = curMax;
    }

    return dp[1];
}

// 69 test 2ms, beat 100%
int rob1(vector<int> &money) {

    int n = money.size();
    if (n ==0 ) return 0;

    vector<int> dp(n, 0);
    if (n >= 1) dp[0] = money[0];
    if (n >= 2) dp[1] = max(money[0], money[1]);

    for (int i = 2; i < n; ++i){
        dp[i] = max(dp[i-1], dp[i-2] + money[i]);
    }
    return dp[n-1];
}

/* Combination usage of rob1 and robs will beat 100%,
 * but single usage of rob1 or rob2 just beat 73.93% */
int rob(vector<int> &num) {
    if (rand()%2)
        return rob1(num);
    return rob2(num);
}

/******************************************************************************/
// 69 test cases, 3ms, beat 73.93%
int rob(vector<int>& num) {
    int n = num.size();
    int a = 0;
    int b = 0;

    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0)
            a = max(a + num[i], b);
        } else {
            b = max(a, b + num[i]);
        }
    }

    return max(a, b);
}
