/* Medium
Given two strings s and t, return true if they are both one edit distance apart, otherwise return false.

A string s is said to be one distance apart from a string t if you can:
1. Insert exactly one character into s to get t.
2. Delete exactly one character from s to get t.
3. Replace exactly one character of s with a different character to get t.


Example 1:
Input: s = "ab", t = "acb"
Output: true
Explanation: We can insert 'c' into s to get t.

Example 2:
Input: s = "", t = ""
Output: false
Explanation: We cannot get t from s by only one step.

Example 3:
Input: s = "a", t = ""
Output: true

Example 4:
Input: s = "", t = "A"
Output: true

Constraints:
0 <= s.length <= 10^4
0 <= t.length <= 10^4
s and t consist of lower-case letters, upper-case letters and/or digits.

Relatives:
161. One Edit Distance
583. Delete Operation for Two Strings
712. Minimum ASCII Delete Sum for Two Strings
1035. Uncrossed Lines */

#include <string>
#include <vector>
#include <string_view>

using namespace std;

class Solution {
public:
    bool isOneEditDistance(string src, string dst) {
        if (src.size() > dst.size())
            swap(src, dst);

        if (dst.size() - src.size() > 1)
            return false;

        for (int i = 0; i < src.size(); ++i) {
            if (src[i] != dst[i]) {
                if (src.size() == dst.size())
                    return string_view(&src[i+1]) == string_view(&dst[i+1]);
                else
                    return string_view(&src[i]) == string_view(&dst[i+1]);
            }
        }

        return src.size() + 1 == dst.size();
    }
};

// Time Limit Exceeded
class Solution {
public:
    bool isOneEditDistance(string src, string dst) {
        int lenSrc = src.length();
        int lenDst = dst.length();
        if (!lenSrc || !lenDst)
            return lenSrc + lenDst;

        vector dp(lenSrc+1, vector(lenDst+1, 0));

        for (int i = 0; i <= lenSrc; ++i) {
            for (int j = 0; j <= lenDst; ++j) {
                if (i == 0)
                    dp[i][j] = j;
                else if (j == 0)
                    dp[i][j] = i;
                else
                    dp[i][j] = min(dp[i-1][j-1] + (src[i-1] == dst[j-1] ? 0 : 1), min(dp[i][j-1], dp[i-1][j]) + 1);
            }
        }

        return dp[lenSrc][lenDst] == 1;
    }
};
