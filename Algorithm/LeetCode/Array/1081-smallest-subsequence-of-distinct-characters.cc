/* Medium
Given a string s, return the lexicographically smallest subsequence of s
that contains all the distinct characters of s exactly once.

Example 1:
Input: s = "bcabc"
Output: "abc"

Example 2:
Input: s = "cbacdcbc"
Output: "acdb"

Constraints:
1 <= s.length <= 1000
s consists of lowercase English letters.

Relatives:
316. Remove Duplicate Letters
496. Next Greater Element I
503. Next Greater Element II
556. Next Greater Element III
739. Daily Temperatures
1081. Smallest Subsequence of Distinct Characters */

#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <string>

#include <string>

using namespace std;

class Solution {
public:
    string smallestSubsequence(string s) {
        deque<char> dq;
        unordered_set<char> hashSet;
        unordered_map<char, int> lastPos;

        for (auto i = 0; i < s.size(); ++i) {
            lastPos[s[i]] = i;
        }

        for (auto i = 0; i < s.size(); ++i) {
            if (!hashSet.count(s[i])) {
                while (!dq.empty() && dq.back() > s[i] && lastPos[dq.back()] > i) {
                    hashSet.erase(dq.back());
                    dq.pop_back();
                }

                dq.push_back(s[i]);
                hashSet.emplace(s[i]);
            }
        }

        return string(dq.begin(), dq.end());
    }
};