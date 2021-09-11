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

/* Binary search by a substring length
A naive solution would be to check all possible string length one by one starting from N - 1:
if there is a duplicate substring of length N - 1, then of length N - 2, etc.
Note that if there is a duplicate substring of length k,
that means that there is a duplicate substring of length k - 1.
Hence one could use a binary search by string length here,
and have the first problem solved in O(logN) time. */

#include <string>
#include <functional>
#include <unordered_set>
#include <string_view>

using namespace std;

/* Time complexity : O(NlogN) in the average case and O(N^2) in the worst case.
    One needs O((N−L)L) for one duplicate check, and one does up to O(logN) checks.
    Together that results in O(∑(N−L)L), i.e. in O(NlogN) in the average case
    and in O(N^2) in the worst case of L close to N/2.
    Space complexity : O(N^2) to keep the _HashSet. */
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
            const auto hashCode = _Hasher(string_view(&str[beg], len));
            if (_HashSet.find(hashCode) != _HashSet.end()) {
                ret = true;
                break;
            } else {
                _HashSet.emplace(std::move(hashCode));
            }
        }

        return ret;
    }

private:
    std::hash<string_view> _Hasher{};
    unordered_set<std::size_t> _HashSet;
};