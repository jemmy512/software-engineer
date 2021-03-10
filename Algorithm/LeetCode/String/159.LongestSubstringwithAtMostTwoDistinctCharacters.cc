/* Medium
Given a string s , find the length of the longest substring t that contains at most 2 distinct characters.

Example 1:
Input: "eceba"
Output: 3
Explanation: t is "ece" which its length is 3.

Example 2:
Input: "ccaabbb"
Output: 5
Explanation: t is "aabbb" which its length is 5.

Relatives:
003. Longest Substring Without Repeating Characters
159. Longest Substring with At Most Two Distinct Characters
340. Longest Substring with At Most K Distinct Characters
239. Sliding Window Maximum
992. Subarrays with K Different Integers */

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        unordered_map<char, int> hashMap; // <char, lastPos>
        hashMap.reserve(s.size());
        int maxLen = 0;

        for (int beg = 0, end = 0; end < s.size(); ++end) {
            hashMap[s[end]] = end;
            if (hashMap.size() > 2) {
                const auto& [key, pos] = *min_element(hashMap.begin(), hashMap.end(), [](const auto& lhs, const auto& rhs) {
                    return lhs.second < rhs.second;
                });
                beg = pos + 1;
                hashMap.erase(key);
            }
            maxLen = max(maxLen, end - beg + 1);
        }

        return maxLen;
    }
};

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        unordered_map<char, int> hashMap;
        int maxLen = 0;

        for (int beg = 0, end = 0; end < s.size(); ++end) {
            ++hashMap[s[end]];
            if (hashMap.size() > 2) {
                while (hashMap.size() > 2 && beg < end) {
                    if (--hashMap[s[beg]] == 0)
                        hashMap.erase(s[beg]);
                    ++beg;
                }
            }
            maxLen = max(maxLen, end - beg + 1);
        }

        return maxLen;
    }
};