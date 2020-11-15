/*
Given a 32-bit signed integer, reverse digits of an integer.

Example 1:
    Input: 123  Output:  321
    Input: -123 Output: -321
    Input: 120  Output: 21
Note:
Assume we are dealing with an environment which could only hold integers within the 32-bit signed integer range.
For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
*/

#include<iostream>
using namespace std;

// 100%
int reverse(int x) {
    int rev = 0;
    while (x != 0) {
        int pop = x % 10;
        // -2147483648 2147483647
        if (rev > INT_MAX/10 || (rev == INT_MAX/10 && pop > 7)) return 0;
        if (rev < INT_MIN/10 || (rev == INT_MIN/10 && pop < -8)) return 0;
        x /= 10;
        rev = rev * 10 + pop;
    }
    return rev;
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

int main(void) {

    return 0;
}