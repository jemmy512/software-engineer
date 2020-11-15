/* Easy
Implement int sqrt(int x).

Compute and return the square root of x, where x is guaranteed to be a non-negative integer.

Since the return type is an integer, the decimal digits are truncated and only
    the integer part of the result is returned.
Example 1:
    Input: 4
    Output: 2
    Example 2:

Input: 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since
             the decimal part is truncated, 2 is returned.
*/
#include<iostream
using namespace std;

/* Newton's Method
 * Time complexity : O(logN) since the set converges quadratically.
 * Space complexity :  O(1). */
int mySqrt(int x) {
    if (x == 0) return 0;
    double last = 0;
    double rest = 1;
    while (rest != last) {
        last = rest;
        rest = (rest + x / rest) / 2;
    }

    return (int)rest;
}

/* Pocket Calculator Algorithm
 * Time complexity : O(1).
 * Space complexity : O(1). */
int mySqrt(int x) {
    if (x < 2) return x;

    int left = (int)Math.pow(Math.E, 0.5 * Math.log(x));
    int right = left + 1;
    return (long)right * right > x ? left : right;
}

/* Binary Search
 * Time complexity : O(logN)
 * Space complexity :  O(1). */
int mySqrt(int x) {
    if (x < 2) return x;

    long left = 2, right = x / 2;
    while (left <= right) {
        long pivot = left + (right - left) / 2;
        long num = pivot * pivot;
        if (num > x)
            right = pivot - 1;
        else if (num < x)
            left = pivot + 1;
        else
            return pivot;
    }

    return right;
}

/* Recursion + Bit Shifts
 * Time complexity : O(logN)
 * Space complexity :  O(1). */
int mySqrt(int x) {
    if (x < 2) return x;

    int left = mySqrt(x >> 2) << 1;
    int right = left + 1;
    return (long)right * right > x ? left : right;
}