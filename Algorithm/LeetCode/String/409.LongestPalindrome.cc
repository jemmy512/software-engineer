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
#include <string>
#include <algorithm>
#include <unordered_map>

using std::string;
using std::unordered_map;

class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> hashMap;
        std::for_each(s.begin(), s.end(), [&hashMap](const auto& ch) {
            hashMap[ch] +=1;
        });

        bool hasSingle = false;
        int cnt = 0;
        for (const auto& [ch, count] : hashMap) {
            if (count % 2 == 0) {
                cnt += count;
            } else {
                cnt += count-1;
                hasSingle = true;
            }
        }

        return hasSingle ? cnt + 1 : cnt;
    }
};