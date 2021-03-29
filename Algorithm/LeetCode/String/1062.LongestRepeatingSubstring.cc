/* Medium
Given a string S, find out the length of the longest repeating substring(s).
Return 0 if no repeating substring exists.

Example 1:
Input: S = "abcd"
Output: 0
Explanation: There is no repeating substring.

Example 2:
Input: S = "abbaba"
Output: 2
Explanation: The longest repeating substrings are "ab" and "ba", each of which occurs twice.

Example 3:
Input: S = "aabcaabdaab"
Output: 3
Explanation: The longest repeating substring is "aab", which occurs 3 times.

Example 4:
Input: S = "aaaaa"
Output: 4
Explanation: The longest repeating substring is "aaaa", which occurs twice.

Constraints:
The string S consists of only lowercase English letters from 'a' - 'z'.
1 <= S.length <= 1500

Relatives:
0516. Longest Palindromic Subsequence
1682. Longest Palindromic Subsequence II
1062. Longest Repeating Substring
1092. Shortest Common Supersequence
1143. Longest Common Subsequence */

#include <string>
#include <functional>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int longestRepeatingSubstring(string str) {
        int beg = 1, end = str.size();

        while (beg <= end) {
            auto len = beg + (end - beg) / 2;
            if (search(str, len))
                beg = len + 1;
            else
                end = len - 1;
        }

        return beg - 1;
    }

private:
    bool search(const string& str, int len) {
        auto ret = false;

        for (int beg = 0; beg < str.size() - len + 1; ++beg) {
            auto subStr = str.substr(beg, len);
            auto hashCode = std::hash<string>{}(subStr);
            if (hashSet.find(hashCode) != hashSet.end()) {
                ret = true;
                break;
            } else {
                hashSet.emplace(std::move(hashCode));
            }
        }

        return ret;
    }

private:
    unordered_set<std::size_t> hashSet;
};