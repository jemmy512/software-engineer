/* Hard
Given a string s. In one step you can insert any character at any index of the string.

Return the minimum number of steps to make s palindrome.

A Palindrome String is one that reads the same backward as well as forward.

Example 1:
Input: s = "zzazz"
Output: 0
Explanation: The string "zzazz" is already palindrome we don't need any insertions.

Example 2:
Input: s = "mbadm"
Output: 2
Explanation: String can be "mbdadbm" or "mdbabdm".

Example 3:
Input: s = "leetcode"
Output: 5
Explanation: Inserting 5 characters the string becomes "leetcodocteel".

Example 4:
Input: s = "g"
Output: 0
Example 5:

Input: s = "no"
Output: 1

Constraints:
1 <= s.length <= 500
All characters of s are lower case English letters.

Relatives:
005. Longest Palindromic Substring
009. Palindrom Number
125. Valid Palindrome
680. Valid Palindrome II
409. Longest Palindrome
234. Palindrome Linked List
266. Palindrome Permutation
267. Palindrome Permutation II
516. Longest Palindromic Subsequence
647. Palindromic Substrings

214. Shortest Palindrome
336. Palindrome Pairs
1312. Minimum Insertion Steps to Make a String Palindrome */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int minInsertions(string s) {
        const auto size = s.size();
        vector<vector<int>> dp(size, vector(size, 0));

        for (int i = size - 2; i >= 0; --i) {
            for (int j = i + 1; j < size; ++j) {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i+1][j-1];
                } else {
                    dp[i][j] = min(dp[i+1][j], dp[i][j-1]) + 1;
                }
            }
        }

        return dp[0][size-1];
    }
};