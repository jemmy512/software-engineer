/*
Given two binary strings, return their sum (also a binary string).

The input strings are both non-empty and contains only characters 1 or 0.

Example 1:

Input: a = "11", b = "1"
Output: "100"
Example 2:

Input: a = "1010", b = "1011"
Output: "10101"
*/
#include<iostream>
#include<string>
#include<iterator>
using namespace std;

string addBinary(string a, string b) {
    int lena = a.length();
    int lenb = b.length();
    string ret(std::max(lena, lenb), '0');

    int idx = std::max(lena, lenb);
    int carry = 0;
    int i, j, ca, cb;
    for (i = lena - 1, j = lenb - 1; i >=0 || j >= 0; --i, --j) {
        ca = i >= 0 ? a[i] - '0' : 0;
        cb = j >= 0 ? b[j] - '0' : 0;
        carry += ca + cb;
        ret[--idx] = (carry % 2) + '0';
        carry /= 2;
    }

    if (carry)
        ret = "1" + ret;

    return ret;
}

int main() {
    string str = addBinary(string("101"), string("1"));
    cout << "~~~~~~~" << endl;
    for (char c : str)
        cout << c;
    cout << endl;
}