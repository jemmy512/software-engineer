/* Easy
Given a signed 32-bit integer x, return x with its digits reversed.
If reversing x causes the value to go outside the signed 32-bit integer range [-2^32, 2^32 - 1], then return 0.

Assume the environment does not allow you to store 64-bit integers (signed or unsigned).

Example 1:
Input: x = 123
Output: 321

Example 2:
Input: x = -123
Output: -321

Example 3:
Input: x = 120
Output: 21

Example 4:
Input: x = 0
Output: 0

Constraints:
-2^32 <= x <= 2^32 - 1

Relatives:
007. Reverse Integer
008. String to Integer (atoi)
065. Valid Number

190. Reverse Bits */

#include <climits>

/* Time Complexity: O(log(x)). There are roughly log10(x) digits in x.
 * Space Complexity: O(1). */
int reverse(int x) {
    int ret = 0;

    while (x != 0) {
        int pop = x % 10;
        // 2147483647 -2147483648
        if ((ret > INT_MAX/10) || (ret == INT_MAX/10 && pop > 7)
            || (ret < INT_MIN/10) || (ret == INT_MIN/10 && pop < -8))
        {
            return 0;
        }

        x /= 10;
        ret = ret * 10 + pop;
    }

    return ret;
}

// beat 50.41 cpp submission
int reverse1(int x) {
    long long ret = 0;
    while (x) {
        ret = ret * 10 + x % 10;
        x /= 10;
        if (ret < INT_MIN || ret > INT_MAX)
            return 0;
    }

    return ret;
}

// only beat 2.65 cpp submission
int reverse2(int x) {
    int ret = 0;
    int newRet, tail;
    while (x) {
        tail = x % 10;
        newRet = ret * 10 + tail;
        if (newRet/ 10 != ret)
            return 0;
        ret = newRet;
        x /= 10;
    }
    return ret;
}