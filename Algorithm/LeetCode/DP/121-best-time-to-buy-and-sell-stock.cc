/* Easy
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (i.e., buy one and sell
 one share of the stock), design an algorithm to find the maximum profit.

Note that you cannot sell a stock before you buy one.

Example 1:
Input: [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
    Not 7-1 = 6, as selling price needs to be larger than buying price.

Example 2:
Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.

Solution:
Ref: https://en.wikipedia.org/wiki/Maximum_subarray_problem#Kadane's_algorithm

The logic to solve this problem is same as "max subarray problem" using Kadane's Algorithm.

All the straight forward solution should work, but if the interviewer twists the question
slightly by giving the difference array of prices, Ex: for {1, 7, 4, 11}, if he gives {0, 6, -3, 7},
you might end up being confused.

Here, the logic is to calculate the difference (maxCur += prices[i] - prices[i-1]) of the original
array, and find a contiguous subarray giving maximum profit. If the difference falls below 0, reset it to zero.

Relatives:
121. Best Time to Buy and Sell Stock
122. Best Time to Buy and Sell Stock II
123. Best Time to Buy and Sell Stock III
188. Best Time to Buy and Sell Stock IV
309. Best Time to Buy and Sell Stock with Cooldown
714. Best Time to Buy and Sell Stock with Transaction Fee */

#include <vector>

using namespace std;

/* unified solution */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector(2, 0));

        for (auto i = 0; i < prices.size(); ++i) {
            if (i == 0) {
                dp[i][0] = 0;
                dp[i][1] = -prices[i];
            } else {
                dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
                dp[i][1] = max(dp[i-1][1], -prices[i]);
            }
        }

        return dp[prices.size()-1][0];
    }

    int maxProfit(vector<int>& prices) {
        int dp_i_0 = 0;
        int dp_i_1 = INT_MIN;

        for (const auto price : prices) {
            dp_i_0 = max(dp_i_0, dp_i_1 + price);
            dp_i_1 = max(dp_i_1, -price);
        }

        return dp_i_0;
    }
};

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int result = 0, maxCur = 0;

        for (int i = 1; i < prices.size(); ++i) {
            maxCur = max(0, maxCur += prices[i] - prices[i-1]);
            result = max(result, maxCur);
        }

        return result;
    }
};