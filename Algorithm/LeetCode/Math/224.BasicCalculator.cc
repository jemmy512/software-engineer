/* Hard
Given a string s representing a valid expression, implement a basic calculator to evaluate it,
and return the result of the evaluation.

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

Example 1:
Input: s = "1 + 1"
Output: 2

Example 2:
Input: s = " 2-1 + 2 "
Output: 3

Example 3:
Input: s = "(1+(4+5+2)-3)+(6+8)"
Output: 23

Constraints:
1 <= s.length <= 3 * 105
s consists of digits, '+', '-', '(', ')', and ' '.
s represents a valid expression.
'+' is not used as a unary operation (i.e., "+1" and "+(2 + 3)" is invalid).
'-' could be used as a unary operation (i.e., "-1" and "-(2 + 3)" is valid).
There will be no two consecutive operators in the input.
Every number and running calculation will fit in a signed 32-bit integer.

Relatives:
224. Basic Calculator
227. Basic Calculator II
772. Basic Calculator II */

#include <stack>
#include <string>

using namespace std;

class Solution {
public:
    int calculate(string s) {
        stack<int> stk;
        int operand = 0;
        int result = 0; // For the on-going result
        int sign = 1;  // 1 means positive, -1 means negative

        for (auto i = 0; i < s.size(); i++) {
            const char chr = s[i];

            if (isdigit(chr)) {
                // Forming operand, since it could be more than one digit
                operand = 10 * operand + (int) (chr - '0');
            } else if (chr == '+') {
                // Evaluate the expression to the left,
                // with result, sign, operand
                result += sign * operand;

                // Save the recently encountered '+' sign
                sign = 1;

                // Reset operand
                operand = 0;

            } else if (chr == '-') {
                result += sign * operand;
                sign = -1;
                operand = 0;

            } else if (chr == '(') {
                // Push the result and sign on to the stk, for later
                // We push the result first, then sign
                stk.push(result);
                stk.push(sign);

                // Reset operand and result, as if new evaluation begins for the new sub-expression
                sign = 1;
                result = 0;
            } else if (chr == ')') {
                // Evaluate the expression to the left
                // with result, sign and operand
                result += sign * operand;

                // ')' marks end of expression within a set of parenthesis
                // Its result is multiplied with sign on top of stk
                // as stk.pop() is the sign before the parenthesis
                result *= stk.top();
                stk.pop();

                // Then add to the next operand on the top.
                // as stk.pop() is the result calculated before this parenthesis
                // (operand on stk) + (sign on stk * (result from parenthesis))
                result += stk.top();
                stk.pop();

                // Reset the operand
                operand = 0;
            }
        }

        return result + (sign * operand);
    }
};