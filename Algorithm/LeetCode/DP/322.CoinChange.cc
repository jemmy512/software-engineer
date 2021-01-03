/* Medium
You are given coins of different denominations and a total amount of money amount.
Write a function to compute the fewest number of coins that you need to make up that amount.
If that amount of money cannot be made up by any combination of the coins, return -1.

You may assume that you have an infinite number of each kind of coin.

Example 1:
Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1

Example 2:
Input: coins = [2], amount = 3
Output: -1

Example 3:
Input: coins = [1], amount = 0
Output: 0

Example 4:
Input: coins = [1], amount = 1
Output: 1

Example 5:
Input: coins = [1], amount = 2
Output: 2

Constraints:
1 <= coins.length <= 12
1 <= coins[i] <= 2^31 - 1
0 <= amount <= 10^4

Relatives:
322. Coin Chagne
518. Coin Change 2
983. Minimum Cost For Tickets */

#include <vector>

using namespace std;

/* DP: bottom - up
 * Time complexity: O(SN), coins.size() * amount
 * Space complexity: O(amount) */
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount+1, amount+1);
        dp[0] = 0;

        for (int curAmount = 1; curAmount <= amount; ++curAmount) {
            for (int i = 0; i < coins.size(); ++i) {
                if (coins[i] <= curAmount) {
                    dp[curAmount] = min(dp[curAmount], dp[curAmount-coins[i]] + 1);
                }
            }
        }

        return dp[amount] > amount ? -1 : dp[amount];
    }
};

/* DP: top - down
 * Time complexity: O(SN), coins.size() * amount
 * Space complexity: O(amount) */
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount < 1)
            return 0;

        vector<int> count(amount+1, 0);
        return change(coins, amount, count);
    }

private:
    int change(vector<int>& coins, int remain, vector<int>& count) {
        if (remain < 0)
            return -1;
        if (remain == 0)
            return 0;
        if (count[remain] != 0) // use previously calculated result
            return count[remain];

        int min = INT_MAX;
        for (auto const& coin : coins) {
            int res = change(coins, remain - coin, count);
            if (res >= 0 && res < min)
                min = 1 + res;
        }
        count[remain] = min == INT_MAX ? -1 : min;

        return count[remain];
    }
};