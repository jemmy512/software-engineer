/* Medium
You are given an array prices where prices[i] is the price of a given stock on the ith day,
and an integer fee representing a transaction fee.

Find the maximum profit you can achieve. You may complete as many transactions as you like,
but you need to pay the transaction fee for each transaction.

Note: You may not engage in multiple transactions simultaneously
(i.e., you must sell the stock before you buy again).

Example 1:
Input: prices = [1,3,2,8,4,9], fee = 2
Output: 8
Explanation: The maximum profit can be achieved by:
- Buying at prices[0] = 1
- Selling at prices[3] = 8
- Buying at prices[4] = 4
- Selling at prices[5] = 9
The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.

Example 2:
Input: prices = [1,3,7,5,10,3], fee = 3
Output: 6

Constraints:
1 <= prices.length <= 5 * 10^4
1 <= prices[i] < 5 * 10^4
0 <= fee < 5 * 10^4

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
    int maxProfit(vector<int>& prices, int fee) {
        vector<vector<int>> dp(prices.size(), vector(2, 0));

        for (auto i = 0; i < prices.size(); ++i) {
            if (i == 0) {
                dp[i][0] = 0;
                dp[i][1] = -prices[i];
            } else {
                dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i] - fee);
                dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]);
            }
        }

        return dp[prices.size()-1][0];
    }

    int maxProfit(vector<int>& prices, int fee) {
        int dp_i_0 = 0;
        int dp_i_1 = INT_MIN;

        for (const auto price : prices) {
            auto temp = dp_i_0;
            dp_i_0 = max(dp_i_0, dp_i_1 + price);
            dp_i_1 = max(dp_i_1, temp - price - fee);
        }

        return dp_i_0;
    }
};