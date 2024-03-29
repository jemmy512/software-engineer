/* Medium
There is only one character 'A' on the screen of a notepad. You can perform two operations on this notepad for each step:

Copy All: You can copy all the characters present on the screen (a partial copy is not allowed).
Paste: You can paste the characters which are copied last time.

Given an integer n, return the minimum number of operations to get the character 'A' exactly n times on the screen.

Example 1:
Input: n = 3
Output: 3
Explanation: Intitally, we have one character 'A'.
In step 1, we use Copy All operation.
In step 2, we use Paste operation to get 'AA'.
In step 3, we use Paste operation to get 'AAA'.

Example 2:
Input: n = 1
Output: 0

Constraints:
1 <= n <= 1000

Relatives:
650. 2 Keys Keyboard
651. 4 Keys Keyboard */

#include <vector>

using namespace std;

class Solution {
public:
    int minSteps(int N) {
        vector dp(N+1, 0);

        for (auto i = 2; i <= N; ++i) {
            dp[i] = i;
            for (int j = i - 1; j > 1; --j) {
                // if sequence of length 'j' can be pasted multiple times to get length 'i' sequence
                if (i % j == 0) {
                    // we just need to copy 1 time and paste (i / j - 1) times,
                    // hence additional (i / j) = (i / j - 1) + 1 times
                    dp[i] = dp[j] + (i / j);
                    // we don't need checking any smaller length sequences since j is the biggest divisor
                    break;
                }
            }
        }

        return dp[N];
    }
};