/* Hard
Given a string, find the length of the longest substring T that contains at most k distinct characters.

Example 1:
Input: s = "eceba", k = 2
Output: 3
Explanation: T is "ece" which its length is 3.

Example 2:
Input: s = "aa", k = 1
Output: 2
Explanation: T is "aa" which its length is 2.

Relatives:
003. Longest Substring Without Repeating Characters
159. Longest Substring with At Most Two Distinct Characters
340. Longest Substring with At Most K Distinct Characters
239. Sliding Window Maximum
992. Subarrays with K Different Integers */

#include <string>
#include <unordered_map>

using namespace std;


/* Time complexity:
 *  * the best case is O(N) where the string contains at most k distinct characters
 *  * the worst case is O(NK) where the string contains more than k distinct characters
 * Space complexity: O(K) + 1 */
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        unordered_map<char, int> charIdx;
        charIdx.reserve(s.size());
        int maxLen = 0;

        for (int beg = 0, end = 0; end < s.size(); ++end) {
            charIdx[s[end]] = end;
            if (charIdx.size() > k) {
                const auto& [key, pos] = *min_element(charIdx.begin(), charIdx.end(), [](const auto& lhs, const auto& rhs) {
                    return lhs.second < rhs.second;
                });
                beg = pos + 1;
                charIdx.erase(key);
            }
            maxLen = max(maxLen, end - beg + 1);
        }

        return maxLen;
    }
};

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        unordered_map<char, int> charCnt;
        int b = 0, e = 0;
        int maxLen = 0;

        for (int b = 0, e = 0; e < s.size(); ++e) {
            ++charCnt[s[e++]];

            while (charCnt.size() > k) {
                if (--chrCnt[b] == 0) {
                    charCnt.erase(chrCnt[b]);
                }
                ++b;
            }

            maxLen = max(maxLen, e - b + 1);
        }

        return maxLen;
    }
};