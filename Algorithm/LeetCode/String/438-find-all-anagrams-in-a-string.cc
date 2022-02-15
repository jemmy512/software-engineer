/* Medium
Given two strings s and p, return an array of all the start indices of p's anagrams in s.
You may return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
typically using all the original letters exactly once.

Example 1:
Input: s = "cbaebabacd", p = "abc"
Output: [0,6]
Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".

Example 2:
Input: s = "abab", p = "ab"
Output: [0,1,2]
Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

Constraints:
1 <= s.length, p.length <= 3 * 10^4
s and p consist of lowercase English letters.

Relativeness:
049. Group Anagrams
242. Valid Anagram
438. Find All Anagrams in a String
760. Find Anagram Mappings
1347. Minimum Number of Steps to Make Two Strings Anagram */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string src, string tar) {
        int beg = 0, end = 0;
        int winSize = 0;
        vector<int> result;
        unordered_map<char, int> dict, window;

        for (const auto chr : tar) {
            ++dict[chr];
        }

        while (end < src.size()) {
            auto chr = src[end++];
            if (dict.count(chr)) {
                if (++window[chr] == dict[chr]) {
                    ++winSize;
                }
            }

            while (end - beg >= tar.size()) {
                if (winSize == dict.size()) {
                    result.emplace_back(beg);
                }

                chr = src[beg++];
                if (dict.count(chr)) {
                    if (window[chr]-- == dict[chr]) {
                        --winSize;
                    }
                }
            }
        }

        return result;
    }
};