/* Hard
Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers, '+', '-', '*', '/' operators,
and open '(' and closing parentheses ')'. The integer division should truncate toward zero.

You may assume that the given expression is always valid.
All intermediate results will be in the range of [-2^31, 2^31 - 1].

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions,
such as eval().

Example 1:
Input: s = "1+1"
Output: 2

Example 2:
Input: s = "6-4/2"
Output: 4

Example 3:
Input: s = "2*(5+5*2)/3+(6/2+8)"
Output: 21

Example 4:
Input: s = "(2+6*3+5-(3*14/7+2)*5)+3"
Output: -12

Example 5:
Input: s = "0"
Output: 0


Constraints:
1 <= s <= 10^4
s consists of digits, '+', '-', '*', '/', '(', and ')'.
s is a valid expression.

Relatives:
224. Basic Calculator
227. Basic Calculator II
772. Basic Calculator II
770. Basic Calculator IV */

#include <string>
#include <stack>
#include <cctype>
#include <deque>

using namespace std;

class Solution {
public:
    int calculate(string s) {
        auto data = deque(s.begin(), s.end());
        return recursion(data);
    }

private:
    int recursion(deque<char>& s) {
        stack<int> stk;
        char operater = '+';
        int operand = 0;
        int result = 0;

        while (!s.empty()) {
            const char chr = s.front();
            s.pop_front();

            if (isdigit(chr)) {
                operand = operand * 10 + (chr - '0');
            }

            if (chr == '(')
                operand = recursion(s);

            if (!isdigit(chr) && !isspace(chr) || s.empty()) {
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
                        const int top = stk.top();
                        stk.pop();
                        stk.push(top * operand);
                        break;
                    }
                    case '/': {
                        const int top = stk.top();
                        stk.pop();
                        stk.push(top / operand);
                        break;
                    }
                }

                operater = chr;
                operand = 0;
            }

            if (chr == ')')
                break;
        }

        while (!stk.empty()) {
            result += stk.top();
            stk.pop();
        }

        return result;
    }
};