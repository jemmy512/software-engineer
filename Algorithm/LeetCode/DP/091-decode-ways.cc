/* Medium
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given a non-empty string containing only digits, determine the total number of ways to decode it.

The answer is guaranteed to fit in a 32-bit integer.

Example 1:
Input: s = "12"
Output: 2
Explanation: It could be decoded as "AB" (1 2) or "L" (12).

Example 2:
Input: s = "226"
Output: 3
Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).

Example 3:
Input: s = "0"
Output: 0
Explanation: There is no character that is mapped to a number starting with '0'.
We cannot ignore a zero when we face it while decoding.
So, each '0' should be part of "10" --> 'J' or "20" --> 'T'.

Example 4:
Input: s = "1"
Output: 1

Constraints:
1 <= s.length <= 100
s contains only digits and may contain leading zero(s). */

#include <string>

using namespace std;

/* dp[i] = 0;
 * dp[i] += dp[i-1] // if (isDigit(s[i]))
 * dp[i] += dp[i-2] // if (isDigit(s[i-1], s[i]) */
class Solution {
public:
    int numDecodings(string s) {
        if (s.empty())
            return 0;
        if (s.size() == 1) {
            return isDigit(s[0]) ? 1 : 0;
        }

        int prevTwoSteps = isDigit(s[0]) ? 1 : 0;
        int prevOneStep = (isDigit(s[1]) ? prevTwoSteps : 0) + (isDigit(s[0], s[1]) ? 1 : 0);

        for (int i = 2; i < s.size(); ++i) {
            int path = 0;
            if (isDigit(s[i])) {
                path += prevOneStep;
            }
            if (isDigit(s[i-1], s[i])) {
                path += prevTwoSteps;
            }

            prevTwoSteps = prevOneStep;
            prevOneStep = path;
        }

        return prevOneStep;
    }

private:
    bool isDigit(char ones) {
        return ones >= '1' && ones <= '9';
    }

    bool isDigit(char tens, char ones) {
        return tens == '1' || (tens == '2' && ones <= '6');
    }
};