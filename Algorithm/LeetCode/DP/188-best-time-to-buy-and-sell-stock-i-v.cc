/* Hard
You are given an integer array prices where prices[i] is the price of a given stock on the ith day.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

Notice that you may not engage in multiple transactions simultaneously
(i.e., you must sell the stock before you buy again).

Example 1:
Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.

Example 2:
Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4.
Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.

Constraints:
0 <= k <= 109
0 <= prices.length <= 1000
0 <= prices[i] <= 1000

Relatives:
121. Best Time to Buy and Sell Stock
122. Best Time to Buy and Sell Stock II
123. Best Time to Buy and Sell Stock III
188. Best Time to Buy and Sell Stock IV
309. Best Time to Buy and Sell Stock with Cooldown
714. Best Time to Buy and Sell Stock with Transaction Fee */

#include <climits>
#include <vector>

using namespace std;

/* https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/discuss/108870/Most-consistent-ways-of-dealing-with-the-series-of-stock-problems

 * T[i][k][0], denotes the maximum profit
    at the end of the i-th day with at most k transactions and with 0 stock in our hand AFTER taking the action
 * T[i][k][1], denotes the maximum profit
    at the end of the i-th day with at most k transactions and with 1 stock in our hand AFTER taking the action
 * Base cases:
    T[-1][k][0] = 0, T[-1][k][1] = -Infinity
    T[i][0][0] = 0, T[i][0][1] = -Infinity

 * Recurrence relations:
    T[i][k][0] = max(T[i-1][k][0], T[i-1][k][1] + prices[i])
    T[i][k][1] = max(T[i-1][k][1], T[i-1][k-1][0] - prices[i])

    For T[i][k][0] in the recurrence relations, the actions taken on the i-th day can only be rest and sell,
    since we have 0 stock in our hand at the end of the day.

    For T[i][k][1] in the recurrence relations, the actions taken on the i-th day can only be rest and buy,
    since we have 1 stock in our hand at the end of the day. */

/* unified solution */
class Solution {
public:
    int maxProfit(int N, vector<int>& prices) {
        if (prices.empty())
            return 0;

        // optimization
        if (N > prices.size() / 2) {
            // It menas N is infinite
            return maxProfit(prices);
        }

        vector<vector<vector<int>>> dp(prices.size(), vector(N + 1, vector(2, 0)));

        for (auto i = 0; i < prices.size(); ++i) {
            for (auto k = 1; k <= N; ++k) {
                if (i == 0) {
                    dp[i][k][0] = 0;
                    dp[i][k][1] = -prices[i];
                } else {
                    dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i]);
                    dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i]);
                }
            }
        }

        return dp[prices.size()-1][N][0];
    }

private:
    int maxProfit(vector<int>& prices) {
        const auto size = prices.size();

        vector<vector<int>> dp(size, vector(2, 0));

        for (auto i = 0; i < size; ++i) {
            if (i == 0) {
                dp[i][0] = 0;
                dp[i][1] = -prices[i];
            } else {
                dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
                dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]);
            }
        }

        return dp[size-1][0];
    }
};

/* Time Complexity: O(nk) if 2k <= n, O(n) if 2k > n
 * Space Complexity: O(k) */
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if (prices.size() < 2 || k < 1)
            return 0;

        vector<pair<int, int>> costProfits(k, {INT_MAX, 0});

        /* For each price, we can investment k times */
        for (int day = 0; day < prices.size(); ++day) {
            for (int i = 0; i < k && i <= day; ++i) {
                auto& [cost, profit] = costProfits[i];
                cost = (i == 0) ? min(cost, prices[day]) : min(cost, prices[day] - costProfits[i-1].second);
                profit = max(profit, prices[day] - cost);
            }
        }

        return costProfits.back().second;
    }
};

/* 3       2       6       5       0        3
[3, 0]  [2, 0]  [2, 4]  [2, 4]  [0,  4]  [0,  4]
[3, 0]  [2, 0]  [2, 4]  [1, 4]  [-4, 4]  [-4, 7]
[3, 0]  [2, 0]  [2, 4]  [1, 4]  [-4, 4]  [-4, 7]
[3, 0]  [2, 0]  [2, 4]  [1, 4]  [-4, 4]  [-4, 7] */