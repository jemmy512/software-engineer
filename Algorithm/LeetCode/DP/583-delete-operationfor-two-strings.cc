/* Medium
Given two strings word1 and word2,
return the minimum number of steps required to make word1 and word2 the same.

In one step, you can delete exactly one character in either string.

Example 1:
Input: word1 = "sea", word2 = "eat"
Output: 2
Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".

Example 2:
Input: word1 = "leetcode", word2 = "etco"
Output: 4

Constraints:
1 <= word1.length, word2.length <= 500
word1 and word2 consist of only lowercase English letters.

Relatives:
072. Edit Distance
161. One Edit Distance
392. Is Subsequence
583. Delete Operation for Two Strings
712. Minimum ASCII Delete Sum for Two Strings
792. Number of Matching Subsequences
1035. Uncrossed Lines

    ""  a   c   b   b   d
""  0   1   2   3   4   5
a   1   0   1   2   3   4
a   2   1   2   3   4   5
b   3   2   3   2   3   4
c   4   3   2   3   4   5
d   5   4   3   4   5   4
*/

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int minDistance(string src, string dst) {
        vector dp(src.size()+1, vector(dst.size()+1, 0));

        for (int i = 0; i <= src.size(); ++i) {
            for (int j = 0; j <= dst.size(); ++j) {
                if (i == 0 || j == 0) {
                    dp[i][j] = i + j;
                } else {
                    if (src[i-1] == dst[j-1]) {
                        dp[i][j] = dp[i-1][j-1];
                    } else {
                        dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1]);
                    }
                }
            }
        }

        return dp[src.size()][dst.size()];
    }
};