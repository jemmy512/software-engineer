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

Follow up: Could you find an algorithm that runs in O(m + n) time? */

#include <climits>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string minWindow(string src, string tar) {
        unordered_map<char, int> dict, window;
        dict.reserve(tar.size());
        window.reserve(tar.size());

        for (char chr : tar) {
            ++dict[chr];
        }

        int beg = 0, end = 0;
        int winSize = 0;
        int start = 0, len = INT_MAX;

        while (end < src.size()) {
            char chr = src[end];
            ++end;
            if (dict.count(chr)) {
                ++window[chr];
                if (window[chr] == dict[chr]) {
                    ++winSize;
                }
            }

            while (winSize == dict.size()) {
                if (end - beg < len) {
                    start = beg;
                    len = end - beg;
                }

                chr = src[beg];
                ++beg;
                if (dict.count(chr)) {
                    if (window[chr] == dict[chr]) {
                        --winSize;
                    }
                    --window[chr];
                }
            }
        }

        return len == INT_MAX ? "" : src.substr(start, len);
    }
};