/* Medium
Given two strings strA and strB, return the size of their longest common subsequence.
If there is no common subsequence, return 0.

A subsequence of a string is a new string generated from the original string
with some characters (can be none) deleted without changing the relative order of the remaining characters.

For example, "ace" is a subsequence of "abcde".
A common subsequence of two strings is a subsequence that is common to both strings.

Example 1:
Input: strA = "abcde", strB = "ace"
Output: 3
Explanation: The longest common subsequence is "ace" and its size is 3.

Example 2:
Input: strA = "abc", strB = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its size is 3.

Example 3:
Input: strA = "abc", strB = "def"
Output: 0
Explanation: There is no such common subsequence, so the result is 0.

Constraints:
1 <= strA.size, strB.size <= 1000
strA and strB consist of only lowercase English characters.

Relatives:
0516. Longest Palindromic Subsequence
1682. Longest Palindromic Subsequence II
1062. Longest Repeating Substring
1092. Shortest Common Supersequence
1143. Longest Common Subsequence

072. Edit Distance
161. One Edit Distance
392. Is Subsequence
583. Delete Operation for Two Strings
712. Minimum ASCII Delete Sum for Two Strings
792. Number of Matching Subsequences
1035. Uncrossed Lines */

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// bottom -> up
class Solution {
public:
    int longestCommonSubsequence(string strShort, string strLong) {
        if (strLong.size() < strShort.size()) {
            std::swap(strShort, strLong);
        }

        vector prev(strShort.size()+1, 0);
        vector cur(strShort.size()+1, 0);

        for (int col = 1; col <= strLong.size(); ++col) {
            for (int row = 1; row <= strShort.size(); ++row) {
                cur[row] = (strShort[row-1] == strLong[col-1])
                    ? (1+prev[row-1])
                    : std::max(prev[row], cur[row-1]);
            }
            std::swap(cur, prev);
        }

        return prev[strShort.size()];
    }
};

// top -> down
class Solution {
public:
    int longestCommonSubsequence(string strShort, string strLong) {
        if (strLong.size() < strShort.size()) {
            std::swap(strShort, strLong);
        }

        vector prev(strShort.size()+1, 0);
        vector cur(strShort.size()+1, 0);

        for (int col = strLong.size()-1; col >= 0; --col) {
            for (int row = strShort.size()-1; row >= 0; --row) {
                cur[row] = (strShort[row] == strLong[col])
                    ? (1+prev[row+1])
                    : std::max(prev[row], cur[row+1]);
            }
            std::swap(cur, prev);
        }

        return prev[0];
    }
};

class Solution {
public:
    int longestCommonSubsequence(string strA, string strB) {
        int lenA = strA.length();
        int lenB = strB.length();
        vector<vector<int>> dp(lenA+1, vector(lenB+1, 0));

        for (int i = 1; i <= lenA; i++) {
            for (int j = 1; j <= lenB; j++) {
                if (strA[i-1] == strB[j-1]) {
                    dp[i][j] = 1 + dp[i-1][j-1];
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        return dp[lenA][lenB];
    }
};