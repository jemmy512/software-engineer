/* Easy
Implement int sqrt(int x).

Compute and return the square root of x,
where x is guaranteed to be a non-negative integer.

Since the return type is an integer,
the decimal digits are truncated and only the integer part of the result is returned.

Example 1:
Input: 4
Output: 2

Example 2:
Input: 8
Output: 2
Explanation: The square root of 8 is 2.82842...,
and since the decimal part is truncated, 2 is returned. */


#include<iostream>

using namespace std;

/* Newton's Method
 * Time complexity : O(logN) since the set converges quadratically.
 * Space complexity :  O(1). */
int mySqrt(int x) {
    if (x == 0) {
        return 0;
    }

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
    if (x < 2) {
        return x;
    }

    long beg = 2;
    long end = x / 2;

    while (beg <= end) {
        long mid = beg + (end - beg) / 2;
        long product = mid * mid;

        if (product == x) {
            return mid;
        } else if (product < x) {
            beg = mid + 1;
        } else {
            end = mid - 1;
        }
    }

    // note: end, not beg
    return end;
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