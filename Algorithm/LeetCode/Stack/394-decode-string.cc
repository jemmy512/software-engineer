/* Medium
Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square
brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white spaces,
square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any
digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].

Example 1:
Input: s = "3[a]2[bc]"
Output: "aaabcbc"

Example 2:
Input: s = "3[a2[c]]"
Output: "accaccacc"


Example 3:
Input: s = "2[abc]3[cd]ef"
Output: "abcabccdcdcdef"

Example 4:
Input: s = "abc3[cd]xyz"
Output: "abccdcdcdxyz"


Example 5:
"3[a2[c]]"

Constraints:
1 <= s.length <= 30
s consists of lowercase English letters, digits, and square brackets '[]'.
s is guaranteed to be a valid input.
All the integers in s are in the range [1, 300]. */

#include <cctype>
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    string decodeString(string s) {
        int index = 0;
        return decodeString(s, index);
    }

private:
    string decodeString(const string& s, int& i) {
        string result;
        while (i < s.size() && s[i] != ']') {
            if (isdigit(s[i])) {
                int cnt = 0;
                while (i < s.length() && isdigit(s[i])) {
                    cnt = cnt * 10 + s[i++] - '0';
                }

                ++i; // ignore the opening bracket '['
                string decodedString = decodeString(s, i);
                ++i; // ignore the closing bracket ']'

                while (cnt--) {
                    result += decodedString;
                }
            } else {
                result += s[i++];
            }
        }
        return result;
    }
};

class Solution {
public:
    string decodeString(string s) {
        stack<int> countStk;
        stack<string> strStk;
        string curStr;
        int cnt = 0;

        for (const auto& chr : s) {
            if (isdigit(chr)) {
                cnt = cnt * 10 + chr - '0';
            } else if (chr == '[') {
                countStk.push(cnt);
                cnt = 0;
                strStk.push(curStr);
                curStr.clear();
            } else if (chr == ']') {
                auto curCnt = countStk.top();
                countStk.pop();
                auto decodedStr = strStk.top();
                strStk.pop();
                while (curCnt--) {
                    decodedStr += curStr;
                }
                curStr = decodedStr;
            } else {
                curStr += chr;
            }
        }

        return curStr;
    }
};