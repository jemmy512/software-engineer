/* Easy

Given an integer, write a function to determine if it is a power of two.
An integer n is a power of two, if there exists an integer x such that n == 2^x.


Example 1:
Input: n = 1
Output: true
Explanation: 20 = 1

Example 2:
Input: n = 16
Output: true
Explanation: 24 = 16

Example 3:
Input: n = 3
Output: false

Example 4:
Input: n = 4
Output: true

Example 5:
Input: n = 5
Output: false */

class Solution {
public:
    /* 2^n:   1 0 0 0 0
     * 2^n-1: 0 1 1 1 1
     *
     * 2^n - 1 always be 1111111...
     * so, (2^n) & (2^n-1) always be zero */
    bool isPowerOfTwo(int n) {
        return n > 0 && (n & (n-1)) == 0;
    }

    /* -A = ~A + 1, +1 may overflow */
    bool isPowerOfTwo(int n) {
        long x = n;
        return (n != 0) && (x & (-x)) == x;
    }

    // The number which is power of two has only 1 bit of 1
    bool isPowerOfTwo(int n) {
        int cnt = 0;

        while (n > 0 && cnt < 2) {
            if (n & 1)
                ++cnt;
            n >>= 1;
        }

        return cnt == 1;
    }
};