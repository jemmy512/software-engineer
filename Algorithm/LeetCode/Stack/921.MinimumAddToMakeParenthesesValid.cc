/* Medium
A parentheses string is valid if and only if:

It is the empty string,
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
You are given a parentheses string s. In one move, you can insert a parenthesis at any position of the string.

For example, if s = "()))", you can insert an opening parenthesis to be "(()))" or a closing parenthesis to be "())))".
Return the minimum number of moves required to make s valid.

Example 1:
Input: s = "())"
Output: 1

Example 2:
Input: s = "((("
Output: 3

Example 3:
Input: s = "()"
Output: 0

Example 4:
Input: s = "()))(("
Output: 4

Constraints:
1. <= s.length <= 1000
s[i] is either '(' or ')'.

Relatives:
0017. Letter Combination of a Phone Number
0020. Valid Parentheses
0022. Generate Parentheses
0032. Longest Valid Parentheses
0241. Different Ways to Add Parentheses
0301. Remove Invalid Parentheses
0856. Score of Parentheses
0921. Minimum Add to Make Parentheses Valid
1021. Remove Outermost Parentheses
1111. Maximum Nesting Depth of Two Valid Parentheses Strings
1190. Reverse Substrings Between Each Pair of Parentheses
1249. Minimum Remove to Make Valid Parentheses
1541. Minimum Insertions to Balance a Parentheses String
1614. Maximum Nesting Depth of the Parentheses */

#include <stack>
#include <string>

using namespace std;

class Solution {
public:
    int minAddToMakeValid(string s) {
        int insertCnt = 0;
        int needRight = 0;

        for (const auto& chr : s) {
            if (chr == '(') {
                ++needRight;
            }

            if (chr == ')') {
                --needRight;
                if (needRight == -1) {
                    ++insertCnt; // insert a (
                    needRight = 0;
                }
            }
        }

        return insertCnt + needRight;
    }
};

class Solution {
public:
    int minAddToMakeValid(string s) {
        stack<char> stk;

        for (const auto& chr : s) {
            if (!stk.empty() && leftOf(chr) == stk.top()) {
                stk.pop();
            } else {
                stk.emplace(chr);
            }
        }

        return stk.size();
    }

private:
    char leftOf(char chr) {
        switch (chr) {
            case ')': return '(';
            default:  return '[';
        }
    }
};