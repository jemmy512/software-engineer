/* Easy
Given two binary strings, return their sum (also a binary string).

The input strings are both non-empty and contains only characters 1 or 0.

Example 1:
Input: a = "11", b = "1"
Output: "100"

Example 2:
Input: a = "1010", b = "1011"
Output: "10101"

Constraints:
1 <= a.length, b.length <= 10^4
a and b consist only of '0' or '1' characters.
Each string does not contain leading zeros except for the zero itself.

Relatives:
002. Add Two Numbers
043. Multiply Strings
066. Plus One
067. Add Binary
989. Add to Array-Form of Integer */

#include <iostream>
#include <string>
#include <iterator>

using namespace std;

string addBinary(string a, string b) {
    int lenA = a.length();
    int lenB = b.length();
    string ret(std::max(lenA, lenB), '0');

    int idx = std::max(lenA, lenB);
    int carry = 0;
    for (int i = lenA-1, j = lenB-1; i >=0 || j >= 0; --i, --j) {
        int ca = i >= 0 ? a[i] - '0' : 0;
        int cb = j >= 0 ? b[j] - '0' : 0;
        carry += ca + cb;
        ret[--idx] = (carry % 2) + '0';
        carry /= 2;
    }

    if (carry)
        ret = "1" + ret;

    return ret;
}