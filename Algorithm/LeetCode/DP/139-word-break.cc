/* Medium Given a non-empty string s and a dictionary wordDict containing a list of non-empty words,
determine if s can be segmented into a space-separated sequence of one or more dictionary words.

Note:
The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.

Example 1:
Input: s = "leetcode", wordDict = ["leet", "code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".

Example 2:
Input: s = "applepenapple", wordDict = ["apple", "pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
             Note that you are allowed to reuse a dictionary word.
Example 3:
Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
Output: false

Constraints:
1 <= s.length <= 300
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 20
s and wordDict[i] consist of only lowercase English letters.
All the strings of wordDict are unique. */

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

/* DP, bottom up
 * Time complexity: O(N^3). There are two nested loops, and substring computation at each iteration.
 *      Overall that results in O(N^3) time complexity.
 * Space complexity: O(n). The depth of recursion tree can go up to N */
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if (wordDict.empty())
            return false;

        _MaxLen = std::max_element(wordDict.cbegin(), wordDict.cend(), [](const auto& lhs, const auto& rhs) {
            return lhs.size() < rhs.size();
        })->size();

        _Dict.insert(wordDict.cbegin(), wordDict.cend());
        vector<bool> dp(s.size()+1, false);
        dp[0] = true;

        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (dp[j] && find(s, j, i)) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp.back();
    }

private:
    bool find(const string& s, int beg, int end) {
        return end - beg <= _MaxLen             // optimization, improve set find performance
            && _Dict.find(s.substr(beg, end-beg)) != _Dict.cend();
    }

private:
    size_t _MaxLen{0};
    unordered_set<string> _Dict;
};

/* backtrack, with memory optimization
 * Time complexity: o(N^3). Size of recursion tree can go up to N^2
 * Space complexity: O(n). The depth of recursion tree can go up to N */
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if (wordDict.empty())
            return false;

        const auto [minIte, maxIte] = minmax_element(wordDict.cbegin(), wordDict.cend(), [](const auto& lhs, const auto& rhs) {
            return lhs.size() < rhs.size();
        });
        MinDicLen = minIte->size();
        MaxDicLen = maxIte->size();

        Memo = vector<int>(s.size(), -1);
        Dict.insert(wordDict.cbegin(), wordDict.cend());

        return backtrack(s, 0);
    }

private:
    bool backtrack(const string& s, int beg) {
        if (beg == s.size())
            return true;

        if (Memo[beg] != -1)
            return Memo[beg] == 1;

        for (int end = beg + MinDicLen; end <= min(s.size(), beg + MaxDicLen); ++end) {
            if (find(s, beg, end) && backtrack(s, end)) {
                return Memo[beg] = 1;
            }
        }

        return Memo[beg] = 0;
    }

    bool find(const string& s, int beg, int end) {
        return isValidLen(beg, end) && Dict.find(s.substr(beg, end-beg)) != Dict.cend();
    }

    bool isValidLen(int beg, int end) {
        auto len = end - beg;
        return len >= MinDicLen && len <= MaxDicLen;
    }

private:
    vector<int> Memo;
    std::size_t MinDicLen{ 0 };
    std::size_t MaxDicLen{ 0 };
    unordered_set<string> Dict;
};

/* backtrack, burt force, timeout
 * Time complexity: O(2^N) Given an array of length n, there are n+1 ways to split it into two parts.
 * At each step, we have a choice: to split or not to split.
 * In the worse case, when all choices are to be checked, that results in O(2^N) */
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if (s.empty())
            return false;
        _Dict.insert(wordDict.cbegin(), wordDict.cend());

        return backtrack(s, 0);
    }

private:
    bool backtrack(const string& s, int beg) {
        if (beg == s.size())
            return true;

        for (int end = beg + 1; end <= s.size(); ++end) {
            if (find(s, beg, end) && backtrack(s, end)) {
                return true;
            }
        }

        return false;
    }

    bool find(const string& s, int beg, int end) {
        return _Dict.find(s.substr(beg, end-beg)) != _Dict.cend();
    }

private:
    unordered_set<string> _Dict;
};

/*
"aaaaaaa" // split to: <3, 3, 1>, <3, 4>, <4, 3>
["aaaa","aaa"]
*/