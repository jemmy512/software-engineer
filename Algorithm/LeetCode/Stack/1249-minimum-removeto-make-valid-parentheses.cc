/* Medium
Given a string s of '(' , ')' and lowercase English characters.

Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions )
so that the resulting parentheses string is valid and return any valid string.

Formally, a parentheses string is valid if and only if:
It is the empty string, contains only lowercase characters, or
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.


Example 1:
Input: s = "lee(t(c)o)de)"
Output: "lee(t(c)o)de"
Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.

Example 2:
Input: s = "a)b(c)d"
Output: "ab(c)d"

Example 3:
Input: s = "))(("
Output: ""
Explanation: An empty string is also valid.

Example 4:
Input: s = "(a(b(c)d)"
Output: "a(b(c)d)"


Constraints:
1 <= s.length <= 10^5
s[i] is one of  '(' , ')' and lowercase English letters. */

#include <vector>
#include <deque>
#include <stack>
#include <string>

using namespace std;

/* 1. Non-stack solution */
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int insert_loc = s.size();

        // remove all unneeded '('
        int right_par = 0;
        for (int i = (int)s.size() - 1; i >= 0; --i) {
            if (s[i] == '(') {
                if (right_par == 0) {
                    continue;
                } else {
                    right_par--;
                }
            } else if (s[i] == ')') {
                right_par++;
            }
            insert_loc--;
            s[insert_loc] = s[i];
        }

        // remove all unneeded '('
        int left_par = 0;
        int len = 0;
        for (int i = insert_loc; i < s.size(); ++i) {
            if (s[i] == ')') {
                if (left_par == 0) {
                    continue;
                } else {
                    left_par--;
                }

            } else if (s[i] == '(') {
                left_par++;
            }
            s[len] = s[i];
            len++;
        }
        s.erase(len);
        return s;
    }
};

/* 2. Stack solution */
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        stack<int> stk;
        vector<bool> validChar(s.size(), false);

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                stk.emplace(i);
            } else if (s[i] == ')') {
                if (stk.size() && s[stk.top()] == '(') {
                    validChar[stk.top()] = validChar[i] = true;
                    stk.pop();
                }
            } else {
                validChar[i] = true;
            }
        }

        string str;
        str.reserve(s.size());

        for (auto i = 0; i < s.size(); ++i) {
            if (validChar[i]) {
                str += s[i];
            }
        }

        return str;
    }
};