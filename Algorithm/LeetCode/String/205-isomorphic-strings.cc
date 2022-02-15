/* Easy
Given two strings s and t, determine if they are isomorphic.
Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving 
the order of characters. No two characters may map to the same character but a character may map to itself.

For example,
Given "egg", "add", return true.
Given "foo", "bar", return false.
Given "paper", "title", return true.

Note:
You may assume both s and t have the same length.

Constraints:
1 <= s.length <= 5 * 10^4
t.length == s.length
s and t consist of any valid ascii character. */

#include <iostream>
#include <string>

using std::string;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.size() != t.size()) 
            return false;

        char maps[256] = { 0 };
        char mapt[256] = { 0 };

        for (auto i = 0; i < s.size(); ++i) {
            if (maps[s[i]] == 0 && mapt[t[i]] == 0) {
                maps[s[i]] = t[i];
                mapt[t[i]] = s[i];
            } else if (maps[s[i]] != t[i]) {
                return false;
            }
        }
        
        return true;
    }
};

// 30 test cases, 16ms, beat 27.23%
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s == "" && t == "")
            return true;
        
        int len = s.size();
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j <= i; ++j) {
                if (s[i] == s[j] && t[i] == t[j]) {
                    break;
                } else  if (s[i] != s[j] && t[i] != t[j]) {
                    continue;
                } else {
                    return false;
                }
            }
        }
        
        return true;
    }
};