/* Media
Given a pattern and a string s, return true if s matches the pattern.

A string s matches a pattern if there is some bijective mapping of single characters to strings
such that if each character in pattern is replaced by the string it maps to,
then the resulting string is s.
A bijective mapping means that no two characters map to the same string,
and no character maps to two different strings.

Example 1:
Input: pattern = "abab", s = "redblueredblue"
Output: true
Explanation: One possible mapping is as follows:
'a' -> "red"
'b' -> "blue"

Example 2:
Input: pattern = "aaaa", s = "asdasdasdasd"
Output: true
Explanation: One possible mapping is as follows:
'a' -> "asd"

Example 3:
Input: pattern = "aabb", s = "xyzabcxzyabc"
Output: false

Constraints:
1 <= pattern.length, s.length <= 20
pattern and s consist of only lowercase English letters.

Relativeness:
205. Isomorphic Strings

079. Word Search
212. Word Search II
290. Word Pattern
291. Word Pattern II */

#include <string>
#include <set>
#include <map>
#include <string_view>

using namespace std;

class Solution {
public:
    bool wordPatternMatch(string pattern, string s) {
        return backtrack(pattern, 0, s, 0);
    }

private:
    bool backtrack(const string& pat, int patI, const string& str, int strI) {
        if (patI == pat.size() && strI == str.size()) {
            return true;
        }

        if (patI >= pat.size() || strI >= str.size()) {
            return false;
        }

        const auto chr = pat[patI];

        if (patTokenMap.count(chr)) {
            const auto& token = patTokenMap[chr];
            if (strI + token.size() <= str.size() && string_view(&str[strI], token.size()) != token) {
                return false;
            }

            return backtrack(pat, patI + 1, str, strI + token.size());
        }

        for (auto b = strI, e = b + 1; e <= str.size(); ++e) {
            auto token = string_view(&str[b], e - b);

            if (tokenSet.count(token)) {
                continue;
            }

            tokenSet.emplace(token);
            patTokenMap.emplace(chr, token);

            if (backtrack(pat, patI + 1, str, e)) {
                return true;
            }

            tokenSet.erase(token);
            patTokenMap.erase(chr);
        }

        return false;
    }

private:
    set<string_view> tokenSet;
    unordered_map<char, string_view> patTokenMap;
};