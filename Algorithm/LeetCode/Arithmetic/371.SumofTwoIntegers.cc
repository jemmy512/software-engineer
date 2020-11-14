/*Medium

Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example:
Given a = 1 and b = 2, return 3. */


/* 1. Sum of Two Positive Integers:
 * XOR is a sum of two integers in the binary form without taking carry into account.
 * Carry is logical AND of two input numbers, shifted one bit to the left: carry=(x&y)<<1.
 *
 * x = 15               1   1   1   1
 * y = 2                0   0   1   0
 * x&y                  0   0   1   0
 * x^y without carry    1   1   0   1
 * carry = (x&y) << 1   0   1   0   0
 *
 * 2. Difference of Two Positive Integers:
 * As for addition, XOR is a difference of two integers without taking borrow into account.
 * The borrow contains common set bits of x and unset bits of x: borrow=((∼x)&y)<<1. */

class Solution {
public:
    int getSum(int a, int b) {
        long mask = 0xFFFFFFFF;

        while (b != 0) {
            int answer = (a ^ b) & mask;
            int carry = ((a & b) & mask) << 1;
            a = answer;
            b = carry;
        }

        return a < INT_MAX ? a : ~(a ^ mask);
    }
};

/* Simplify problem down to two cases: sum or subtraction of two positive integers: x±y, where x>y.
 * Save down the sign of the result.
 *
 * If one has to compute the sum:
 *  While carry is nonzero: y != 0:
 *      Current answer without carry is XOR of x and y: answer = x^y.
 *      Current carry is left-shifted AND of x and y: carry = (x & y) << 1.
 *      Job is done, prepare the next loop: x = answer, y = carry.
 *  Return x * sign.
 *
 * If one has to compute the difference:
 *  While borrow is nonzero: y != 0:
 *      Current answer without borrow is XOR of x and y: answer = x^y.
 *      Current borrow is left-shifted AND of NOT x and y: borrow = ((~x) & y) << 1.
 *      Job is done, prepare the next loop: x = answer, y = borrow.
 *  Return x * sign. */

/* This solution is easy to attack during the follow-up:
 *  Different languages represent negative numbers differently.
 *
 * Once you start to manage negative numbers using bit manipulation, your solution becomes language-specific.*/
class Solution {
public :
    int getSum(int a, int b) {
        int x = std::abs(a), y = std::abs(b);
        // ensure that abs(a) >= abs(b)
        if (x < y) return getSum(b, a);

        // abs(a) >= abs(b) -->
        // a determines the sign
        int sign = a > 0 ? 1 : -1;

        if (a * b >= 0) {
            // sum of two positive integers x + y
            // where x > y
            while (y != 0) {
                int answer = x ^ y;
                int carry = (x & y) << 1;
                x = answer;
                y = carry;
            }
        } else {
            // difference of two positive integers x - y
            // where x > y
            while (y != 0) {
                int answer = x ^ y;
                int borrow = ((~x) & y) << 1;
                x = answer;
                y = borrow;
            }
        }
        return x * sign;
    }
};