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
309. Best Time to Buy and Sell Stock with Cooldown [TODO] */

#include <climits>
#include <vector>

using namespace std;

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