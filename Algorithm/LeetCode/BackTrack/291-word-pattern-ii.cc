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
        return isMatch(pattern, 0, s, 0);
    }

private:
    bool isMatch(const string& pat, int patI, const string& str, int strI) {
        if (strI == str.size() && patI == pat.size())
            return true;
        if (strI >= str.size() || patI >= pat.size())
            return false;

        const auto chr = pat[patI];

        if (Map.count(chr)) {
            auto word = Map[chr];

            if (strI + word.size() <= str.size() && string_view{&str[strI], word.size()} != word) {
                return false;
            }

            return isMatch(pat, patI + 1, str, strI + word.size());
        }

        for (auto i = strI + 1; i <= str.size(); ++i) {
            auto word = string_view(&str[strI], i - strI);

            if (Set.count(word))
                continue;

            Map.emplace(chr, word);
            Set.emplace(word);

            if (isMatch(pat, patI + 1, str, i))
                return true;

            Map.erase(chr);
            Set.erase(word);
        }

        return false;
    }

private:
    set<string_view> Set;
    map<char, string_view> Map;
};