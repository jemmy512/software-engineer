/* Hard
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note: You may not engage in multiple transactions at the same time (i.e., you must sell the stock before you buy again).

Example 1:
Input: prices = [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.

Example 2:
Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging
    multiple transactions at the same time. You must sell before buying again.

Example 3:
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
Example 4:

Input: prices = [1]
Output: 0

Constraints:
1 <= prices.length <= 105
0 <= prices[i] <= 105 */

#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2)
            return 0;

        int N = 2; // can buy at most two times
        vector<pair<int, int>> costProfits(N, {INT_MAX, 0});

        /* For each price, we can investment N times */
        for (const auto& price : prices) {
            for (int i = 0; i < N; ++i) {
                auto& [cost, profit] = costProfits[i];
                cost = (i == 0) ? min(cost, price) : min(cost, price - costProfits[i-1].second);
                profit = max(profit, price - cost);
            }
        }

        return costProfits.back().second;
    }
};

/* Bidiration Dynamic Programming
 * Since we can buy at most twice, we can buy first time at the left of prices[i]
 * and second time at right of prices[i] */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = len;
        if (len < 2)
            return 0;

        int leftMin = prices[0];
        int rightMax = prices[len-1];
        vector<int> leftProfits(len, 0);
        vector<int> rightProfits(len+1, 0);

        for (int left = 1; left < len; ++left) {
            leftMin = min(leftMin, prices[left]);
            leftProfits[left] = max(leftProfits[left-1], prices[left] - leftMin);

            int right = len - left - 1;
            rightMax = max(rightMax, prices[right]);
            rightProfits[right] = max(rightProfits[right+1], rightMax - prices[right]);
        }

        int maxProfit = 0;
        for (int i = 0; i < len; ++i) {
            maxProfit = max(maxProfit, leftProfits[i] + rightProfits[i+1]);
        }

        return maxProfit;
    }
};