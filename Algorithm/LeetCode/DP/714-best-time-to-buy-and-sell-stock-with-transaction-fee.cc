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

class Solution {
public:
    int maxProfit(vector<int>& prices, int maxK, int fee, int cooldown) {
        const auto size = prices.size();

        if (size <= 0) {
            return 0;
        }
        if (maxK > size / 2) {
            return maxProfit(prices, cooldown, fee);
        }

        vector<vector<vector<int>>> dp(size, vector(maxK + 1, vector(2, 0)));

        for (int i = 0; i < size; i++) {
            dp[i][0][0] = 0;
            dp[i][0][1] = INT_MIN;
        }

        for (int i = 0; i < size; ++i) {
            for (int k = maxK; k >= 1; --k) {
                if (i == 0) {
                    dp[i][k][0] = 0;
                    dp[i][k][1] = -prices[i] - fee;
                } else if (i - cooldown < 1) {
                    dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i]);
                    dp[i][k][1] = max(dp[i-1][k][1], -prices[i] - fee);
                } else {
                    dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i]);
                    dp[i][k][1] = max(dp[i-1][k][1], dp[i-cooldown-1][k-1][0] - prices[i] - fee);
                }
            }
        }

        return dp[size - 1][maxK][0];
    }

private:
    int maxProfit(vector<int>& prices, int cooldown, int fee) {
        const auto  size = prices.size();
        vector<vector<int>> dp(size, vector(2, 0));

        for (int i = 0; i < size; i++) {
            if (i == 0) {
                dp[i][0] = 0;
                dp[i][1] = -prices[i] - fee;
            }else if (i - cooldown < 1) {
                dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
                dp[i][1] = max(dp[i-1][1], -prices[i] - fee);
            } else {
                dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
                dp[i][1] = max(dp[i - 1][1], dp[i - cooldown - 1][0] - prices[i] - fee);
            }
        }

        return dp[size - 1][0];
    }
};