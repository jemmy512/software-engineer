/* Easy
Given a string containing just the characters '(', ')', '{', '}', '[' and ']',
determine if the input string is valid.
The brackets must close in the correct order, "()" and "()[]{}" are all valid
but "(]" and "([)]" are not

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

#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> stk;

        for (const auto& chr : s) {
            if (chr == '(' || chr == '{' || chr == '[') {
                stk.emplace(chr);
            } else if (!stk.empty() && openPartOf(chr) == stk.top()) {
                stk.pop();
            } else {
                return false;
            }
        }

        return stk.empty();
    }

private:
    char openPartOf(char chr) {
        switch (chr) {
            case '}': return '{';
            case ')': return '(';
            default:  return '[';
        }
    }
};