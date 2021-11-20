/* Easy
You are playing the following Nim Game with your friend:

Initially, there is a heap of stones on the table.
You and your friend will alternate taking turns, and you go first.
On each turn, the person whose turn it is will remove 1 to 3 stones from the heap.
The one who removes the last stone is the winner.
Given n, the number of stones in the heap, return true if you can win the game assuming
both you and your friend play optimally, otherwise return false.

Example 1:
Input: n = 4
Output: false
Explanation: These are the possible outcomes:
1. You remove 1 stone. Your friend removes 3 stones, including the last stone. Your friend wins.
2. You remove 2 stones. Your friend removes 2 stones, including the last stone. Your friend wins.
3. You remove 3 stones. Your friend removes the last stone. Your friend wins.
In all outcomes, your friend wins.

Example 2:
Input: n = 1
Output: true

Example 3:
Input: n = 2
Output: true

Constraints:
1 <= n <= 2^31 - 1

Mine turn      | Your turn
1 ~ 3          | 4
5 ~ 7          | 8
9 ~ 11         | 12
13 ~ 15        | 16 */

#include <vector>

using namespace std;

class Solution {
public:
    bool canWinNim(int n) {
        return n % 4 != 0;
    }
};

// DP
class Solution {
public:
    bool canWinNim(int n) {
        vector dp(4, false);
        dp[1] = dp[2] = dp[3] = true;

        for (auto i = 4; i <= n; ++i) {
            const auto canWin = dp[1] == false || dp[2] == false || dp[3] == false;
            dp[1] = dp[2];
            dp[2] = dp[3];
            dp[3] = canWin;
        }

        return dp[3];
    }
};