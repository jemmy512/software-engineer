/*
Difficulty: Easy

Given a string which consists of lowercase or uppercase letters, find the length
 of the longest palindromes that can be built with those letters.

This is case sensitive, for example "Aa" is not considered a palindrome here.

Note:
Assume the length of given string will not exceed 1,010.

Example:

Input:
"abccccdd"

Output:
7

Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.
*/

// 95 tese cases, 7ms, beat 69.70%
class Solution {
public:
    int longestPalindrome(string s) {
        int cnt = 0;
        unordered_map<char, int> omap;
        int len = s.size();
        for (int i = 0; i < len; ++i) {
            omap[s[i]] += 1;
        }
        bool single = false;;
        for (pair<char, int> pa : omap) {
            if (pa.second % 2 == 0) {
                cnt += pa.second;
            } else {
                cnt += pa.second - 1;
                single = true;
            }
        }
        
        return single ? cnt + 1 : cnt;
    }
};