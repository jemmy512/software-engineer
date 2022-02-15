/* Medium
Given a string s which represents an expression, evaluate this expression and return its value.

The integer division should truncate toward zero.

You may assume that the given expression is always valid.
All intermediate results will be in the range of [-231, 231 - 1].

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions,
such as eval().

Example 1:
Input: s = "3+2*2"
Output: 7

Example 2:
Input: s = " 3/2 "
Output: 1

Example 3:
Input: s = " 3+5 / 2 "
Output: 5

Constraints:
1 <= s.length <= 3 * 10^5
s consists of integers and operators ('+', '-', '*', '/') separated by some number of spaces.
s represents a valid expression.
All the integers in the expression are non-negative integers in the range [0, 231 - 1].
The answer is guaranteed to fit in a 32-bit integer.

Relatives:
224. Basic Calculator
227. Basic Calculator II
772. Basic Calculator II
770. Basic Calculator IV */

#include <stack>
#include <string>

using namespace std;

class Solution {
public:
    int calculate(string s) {
        stack<int> stk;
        int operand = 0;
        int result = 0;
        char operater = '+';

        for (auto i = 0; i < s.size(); ++i) {
            const char chr = s[i];

            if (isdigit(chr)) {
                operand = operand * 10 + (chr - '0');
            }

            const auto isOperator = !isdigit(chr) && !isspace(chr);
            const auto isLastChar = i == s.size() - 1;

            if (isOperator || isLastChar) {
                switch (operater) {
                    case '+': {
                        stk.push(operand);
                        break;
                    }
                    case '-': {
                        stk.push(-operand);
                        break;
                    }
                    case '*': {
                        int top = stk.top();
                        stk.pop();
                        stk.push(top * operand);
                        break;
                    }
                    case '/': {
                        int top = stk.top();
                        stk.pop();
                        stk.push(top / operand);
                        break;
                    }
                }

                operand = 0;
                operater = chr;
            }
        }

        while (!stk.empty()) {
            result += stk.top();
            stk.pop();
        }

        return result;
    }
};