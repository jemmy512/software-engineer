/* Hard
Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:
'.' Matches any single character.​​​​
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

Example 1:
Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:
Input: s = "aa", p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".

Example 3:
Input: s = "ab", p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".

Example 4:
Input: s = "aab", p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore, it matches "aab".
Example 5:

Input: s = "mississippi", p = "mis*is*p*."
Output: false

Constraints:
1 <= s.length <= 20
1 <= p.length <= 30
s contains only lowercase English letters.
p contains only lowercase English letters, '.', and '*'.
It is guaranteed for each appearance of the character '*', there will be a previous valid character to match.

Relatives:
010. Regular Expression Matching
044. Wildcard Matching */

#include <vector>
#include <string>

using namespace std;

namespace topdown {
    class Solution {
    public:
        bool isMatch(string s, string p) {
            Memo.resize(s.size()+1, vector(p.size()+1, -1));

            return dp(s, 0, p, 0);
        }

    private:
        // src[i...] matches pat[j...]
        bool dp(const string& src, int i, const string& pat, int j) {
            { // boundary check can be optimized
                if (j == pat.size())
                    return i == src.size();

                // s = "a", p = "ab*c*"
                if (i == src.size()) {
                    if ((pat.size() - j) % 2 != 0)
                        return false;

                    // the remaining must be pairs of characters and *, e.g., b*c*d*
                    for (; j + 1 < pat.size(); j += 2) {
                        if (pat[j+1] != '*')
                            return false;
                    }
                    return true;
                }
            }

            if (Memo[i][j] != -1) {
                return Memo[i][j];
            }

            auto ret = false;

            if (src[i] == pat[j] || pat[j] == '.') {
                if (j + 1 < pat.size() && pat[j+1] == '*') {
                    // '*' matches 0 and more times
                    ret = dp(src, i, pat, j + 2) || dp(src, i + 1, pat, j);
                } else {
                    ret = dp(src, i + 1, pat, j + 1);
                }
            } else {
                if (j + 1 < pat.size() && pat[j+1] == '*') {
                    // '*' matches 0 time
                    ret = dp(src, i, pat, j + 2);
                } else {
                    ret = false;
                }
            }

            Memo[i][j] = ret ? 1 : 0;

            return ret;
        }

    private:
        vector<vector<int>> Memo;
    };

    class Solution {
    public:
        bool isMatch(string s, string p) {
            Memo.resize(s.size()+1, vector(p.size()+1, -1));
            Memo[s.size()][p.size()] = true;

            return dp(s, 0, p, 0);
        }

    private:
        // src[i...] matches pat[j...]
        bool dp(const string& src, int i, const string& pat, int j) {
            if (Memo[i][j] != -1) {
                return Memo[i][j];
            }

            auto ret = false;

            if (i < src.size() && (src[i] == pat[j] || pat[j] == '.')) {
                if (j + 1 < pat.size() && pat[j+1] == '*') {
                    ret = dp(src, i, pat, j + 2) || dp(src, i + 1, pat, j);
                } else {
                    ret = dp(src, i + 1, pat, j + 1);
                }
            } else {
                if (j + 1 < pat.size() && pat[j+1] == '*') {
                    ret = dp(src, i, pat, j + 2);
                } else {
                    ret = false;
                }
            }

            Memo[i][j] = ret ? 1 : 0;

            return ret;
        }

    private:
        vector<vector<int>> Memo;
    };
}

namespace bottomup {
    class Solution {
    public:
        bool isMatch(string s, string p) {
            vector<vector<bool>> dp(s.size()+1, vector(p.size()+1, false));
            dp[s.size()][p.size()] = true;

            for (int i = s.size(); i >= 0; --i) {
                for (int j = p.size()-1; j >= 0; --j) {
                    if (i < s.size() && (s[i] == p[j] || p[j] == '.')) {
                        if (j + 1 < p.size() && p[j+1] == '*') {
                            dp[i][j] = dp[i+1][j] || dp[i][j+2];
                        } else {
                            dp[i][j] = dp[i+1][j+1];
                        }
                    } else {
                        if (j + 1 < p.size() && p[j+1] == '*') {
                            dp[i][j] = dp[i][j+2];
                        } else {
                            dp[i][j] = false;
                        }
                    }
                }
            }

            return dp[0][0];
        }
    };

    // bottom up
    class Solution {
    public:
        bool isMatch(string s, string p) {
            vector<vector<bool>> dp(s.size()+1, vector(p.size()+1, false));
            dp[s.size()][p.size()] = true;

            for (int i = s.size(); i >= 0; --i) {
                for (int j = p.size()-1; j >= 0; --j) {
                    const auto isMatch = i < s.size() && (s[i] == p[j] || p[j] == '.');

                    if (j + 1 < p.size() && p[j+1] == '*') {
                        dp[i][j] = (isMatch && dp[i+1][j]) || dp[i][j+2];
                    } else {
                        dp[i][j] = isMatch && dp[i+1][j+1];
                    }
                }
            }

            return dp[0][0];
        }
    };
}
