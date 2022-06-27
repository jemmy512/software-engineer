/* Easy
Related to question 171.Excel Sheet Column Number

Given a positive integer, return its corresponding column title as appear in an Excel sheet.

For example:
1 -> A
2 -> B
3 -> C
...

26 -> Z
27 -> AA

Example 1:
Input: columnNumber = 1
Output: "A"

Example 2:
Input: columnNumber = 28
Output: "AB"

Example 3:
Input: columnNumber = 701
Output: "ZY"

Example 4:
Input: columnNumber = 2147483647
Output: "FXSHRXW"

Constraints:
1 <= columnNumber <= 2^31 - 1

Relatives:
168. Excel Sheet Column Title
171. Excel Sheet Column Number */

#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
public:
    string convertToTitle(int n) {
        return n ? (convertToTitle(n / 26) + (char)(--n % 26 + 'A')) : "";
    }
};

class Solution {
public:
    string convertToTitle(int n) {
        return base26_int2str(n);
    }

private:
    string base26_int2str(long n) {
        string str;

        while (n > 0) {
            --n; // n staring at 1
            auto off = n % 26;
            str += 'A' + off;
            n /= 26;
        }
        std::reverse(str.begin(), str.end());

        return str;
    }

    long long base26_str2int(string s) {
        long long ret = 0;

        for (auto chr : s) {
            ret = ret * 26 + (chr - 'A' + 1);
        }

        return ret;
    }
};