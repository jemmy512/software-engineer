/* Hard
Given two strings s and t of lengths m and n respectively,
return the minimum window substring of s such that
every character in t (including duplicates) is included in the window.
If there is no such substring, return the empty string "".

The testcases will be generated such that the answer is unique.
A substring is a contiguous sequence of characters within the string.

Example 1:
Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

Example 2:
Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.

Example 3:
Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.


Constraints:
m == s.length
n == t.length
1 <= m, n <= 10^5
s and t consist of uppercase and lowercase English letters.

Follow up: Could you find an algorithm that runs in O(m + n) time?

Rletiveness:
030. Substring with Concatenation of All Words
209. Minimum Size Subarray Sum
239. Sliding Window Maximum
567. Permutation in String
632. Smallest Range Covering Elements from K Lists
727. Minimum Window Subsequence */

#include <climits>
#include <string>
#include <string_view>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        int minLen = INT_MAX;
        string_view retView;
        int beg = 0, end = 0;
        int windowSize = 0;
        unordered_map<char, int> dict, window;

        for (auto chr : t) {
            ++dict[chr];
        }

        while (end < s.size()) {
            auto chr = s[end++];
            if (dict.count(chr)) {
                if (++window[chr] == dict[chr]) {
                    ++windowSize;
                }
            }

            while (windowSize == dict.size()) {
                if (end - beg < minLen) {
                    minLen = end - beg;
                    retView = string_view(&s[beg], end-beg);
                }

                auto chr = s[beg++];
                if (dict.count(chr)) {
                    if (window[chr]-- == dict[chr]) {
                        --windowSize;
                    }
                }
            }
        }

        return string(retView);
    }
};