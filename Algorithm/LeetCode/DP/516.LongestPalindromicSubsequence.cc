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

/* supposed s = "abbcba"

   we can have a matrix,
   - dp[start, end] is the longest from s[start] to s[end]
   - if (start == end) dp[statr, end] = 1, it means every char can be palindromic

       a b b c b a
    a  1 0 0 0 0 0
    b  0 1 0 0 0 0
    b  0 0 1 0 0 0
    c  0 0 0 1 0 0
    b  0 0 0 0 1 0
    a  0 0 0 0 0 1

  calculating from the bottom to up. (Note: only care about the top-right trangle)

       a  b  b  c  b  a
    a  1  1  2  2  3 [5]  <--  a == a, so "abbcba" comes from "bbcb" + 2
    b  0  1 [2] 2  3  3   <--  b == b, so "bb" comes from "" + 2
    b  0  0  1  1 [3] 3   <--  b == b, so "bcb" comes from "c" + 2
    c  0  0  0  1  1 [1]  <--  c != a, so "cba" comes from max("cb", "a")
    b  0  0  0  0  1 [1]  <--  b != a, so "ba" comes from max ("b", "a")
    a  0  0  0  0  0  1

  So, we can have the following formular:
    s[start] != s[end]  ==> dp[start, end] = max (dp[start+1, end], dp[start, end-1]);
    s[start] == s[end]  ==> dp[start, end] = dp[start+1, end-1] + 2; */

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

// top down
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        if (s.empty()) {
            return 0;
        }

        vector dp(s.size(), vector(s.size(), 0));

        /* the deduced type of `auto i` is unsigned long [0 to 4,294,967,295], when i is 0, --i will rewind */
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

// bottom up
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        if (s.empty()) {
            return 0;
        }

        vector dp(s.size(), vector(s.size(), 0));

        for (int i = 0; i < s.size(); ++i) {
            dp[i][i] = 1;
            for (int j = i-1; j >= 0;--j) {
                dp[i][j] = s[i] == s[j]
                    ? dp[i-1][j+1] + 2
                    : max(dp[i-1][j], dp[i][j+1]);
            }
        }

        return dp[s.size()-1][0];
    }
};