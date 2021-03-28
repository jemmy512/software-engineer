/* Medium
Given a string s, find the longest palindromic subsequence's length in s.
You may assume that the maximum length of s is 1000.

Example 1:
Input: "bbbab"
Output: 4
One possible longest palindromic subsequence is "bbbb".

Example 2:
Input: "cbbd"
Output: 2
One possible longest palindromic subsequence is "bb".

Constraints:
1 <= s.length <= 1000
s consists only of lowercase English letters.

Relatives:
5. Longest Palindromic Substring
266. Palindrome Permutation
267. Palindrome Permutation II
516. Longest Palindromic Subsequence
647. Palindromic Substrings


214. Shortest Palindrome
336. Palindrome Pairs */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        if (s.empty()) {
            return 0;
        }

        vector dp(s.size(), 0);

        for (int i = s.size()-1; i >= 0; --i) {
            int j_1 = dp[i];
            dp[i] = 1;
            for (int j = i+1; j < s.size(); ++j) {
                if (s[i] == s[j]) {
                    int tmp = (j_1 + 2);
                    j_1 = dp[j];
                    dp[j] = tmp;
                } else {
                    j_1 = dp[j];
                    dp[j] = max(dp[j-1], dp[j]);
                }
            }
        }

        return dp[s.size()-1];
    }
};

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        if (s.empty()) {
            return 0;
        }

        vector dp(s.size(), vector(s.size(), 0));

        for (int i = s.size()-1; i >= 0; --i) {
            dp[i][i] = 1;
            for (int j = i+1; j < s.size(); ++j) {
                dp[i][j] = (s[i] == s[j])
                    ? (dp[i+1][j-1] + 2)
                    : max(dp[i+1][j], dp[i][j-1]);
            }
        }

        return dp[0][s.size()-1];
    }
};