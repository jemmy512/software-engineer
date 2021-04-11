/* East
Given two strings s and t, check if s is a subsequence of t.

A subsequence of a string is a new string that is formed from the original string
by deleting some (can be none) of the characters without disturbing the relative
positions of the remaining characters.
(i.e., "ace" is a subsequence of "abcde" while "aec" is not).

Example 1:
Input: s = "abc", t = "ahbgdc"
Output: true

Example 2:
Input: s = "axc", t = "ahbgdc"
Output: false

Constraints:
0 <= s.length <= 100
0 <= t.length <= 10^4
s and t consist only of lowercase English letters.

Follow up: If there are lots of incoming s, say s1, s2, ..., sk where k >= 10^9,
and you want to check one by one to see if t has its subsequence.
In this scenario, how would you change your code?

Relatives:
392. Is Subsequence
792. Number of Matching Subsequences
1055. Shortest Way to Form String

072. Edit Distance */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t) {
        if (s.empty())
            return true;

        vector dp(s.size()+1, vector(t.size()+1, 0));

        for (int row = s.size()-1; row >= 0; --row) {
            for (int col = t.size()-1; col >= 0; --col) {
                if (s[row] == t[col]) {
                    dp[row][col] = dp[row+1][col+1] + 1;
                } else {
                    dp[row][col] = max(dp[row+1][col], dp[row][col+1]);
                }
            }
        }

        return dp[0][0] == s.size();
    }
};

class Solution {
public:
    bool isSubsequence(string s, string t) {
        if (s.empty())
            return true;

        vector dp(s.size()+1, vector(t.size()+1, 0));

        for (int row = 1; row <= s.size(); ++row) {
            for (int col = 1; col <= t.size(); ++col) {
                if (s[row-1] == t[col-1]) {
                    dp[row][col] = dp[row-1][col-1] + 1;
                } else {
                    dp[row][col] = max(dp[row-1][col], dp[row][col-1]);
                }
            }
        }

        return dp[s.size()][t.size()] == s.size();
    }
};

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int beg = 0;

        for (const auto& chr : s) {
            beg = t.find(chr, beg);
            if (beg == string::npos) {
                return false;
            }
            ++beg;
        }

        return true;
    }
};