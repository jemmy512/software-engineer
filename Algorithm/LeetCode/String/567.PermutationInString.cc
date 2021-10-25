/* Medium
Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
In other words, return true if one of s1's permutations is the substring of s2.

Example 1:
Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").

Example 2:
Input: s1 = "ab", s2 = "eidboaoo"
Output: false

Constraints:
1 <= s1.length, s2.length <= 104
s1 and s2 consist of lowercase English letters. */

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool checkInclusion(string tar, string src) {
        unordered_map<char, int> dict, window;
        int beg = 0;
        int end = 0;
        int winSize = 0;

        for (const auto chr : tar) {
            ++dict[chr];
        }

        while (end < src.size()) {
            auto chr = src[end];
            ++end;
            if (dict.count(chr)) {
                ++window[chr];
                if (window[chr] == dict[chr]) {
                    ++winSize;
                }
            }

            while (end - beg >= tar.size()) {
                if (winSize == dict.size()) {
                    return true;
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

        return false;
    }
};