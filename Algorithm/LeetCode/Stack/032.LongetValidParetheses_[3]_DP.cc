/*
Difficulty: Hard

Given a string containing just the characters '(' and ')', find the length of the longest 
    valid (well-formed) parentheses substring.

Example 1:

Input: "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()"
Example 2:

Input: ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()"

*/

class Solution {
public:
    int longestValidParentheses(string s) {
        int len = s.size();
        stack<int> stk;
        int lenCur = 0, lenMax = 0;
        int lastError = -1;
        
        for (int i = 0; i < len; ++i) {
            if (s[i] == '(') {
                stk.push(i);
            } else if (s[i] == ')') {
                if (stk.empty()) {
                    lastError = i;
                } else {
                    stk.pop();
                    if (stk.empty()) {
                        lenCur = i - lastError;
                    } else {
                        lenCur = i - stk.top();
                    }
                    lenMax = lenCur > lenMax ? lenCur : lenMax;
                }
            }
        }
        
        return lenMax;
    }
};