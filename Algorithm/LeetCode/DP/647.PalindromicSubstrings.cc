/* Medium
Given a string, your task is to count how many palindromic substrings in this string.

The substrings with different start indexes or end indexes are counted as
different substrings even they consist of same characters.

Example 1:
Input: "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".

Example 2:
Input: "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".

Constraints:
1 <= s.length <= 1000
s consists of lowercase English letters.

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
    int countSubstrings(string s) {
        auto count = 0;
        const auto size = s.size();
        vector<vector<bool>> dp(size, vector(size, false));

        for (int i = size - 1; i >= 0; --i) {
            ++count;
            dp[i][i] = true;

            for (auto j = i + 1; j < size; ++j) {
               if (s[i] == s[j] && (dp[i+1][j-1] || j == i + 1)) {
                   ++count;
                   dp[i][j] = true;
               }
            }
        }

        return count;
    }
};