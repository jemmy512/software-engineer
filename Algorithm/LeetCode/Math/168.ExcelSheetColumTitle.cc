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
1 <= columnNumber <= 2^31 - 1 */

#include <iostream>
#include <stack>

using namespace std;

// 18 test caes, 2ms, beat 100%
class Solution {
public:
    string convertToTitle(int n) {
        return base26_int2str(n);
    }

private:
    string base26_int2str(long n) {
        string str;
        while (n > 0) {
            char ch = 'A' + (n - 1) % 26;
            str += ch;
            n -= (n - 1) % 26; // n = 26
            n /= 26;
        }
        return string(str.rbegin(), str.rend());
    }

    long long base26_str2int(string s) {
        long long ret = 0;
        std::for_each(s.begin(), s.end(), [&ret](const auto& ch) {
            ret = ret * 26 + (ch - 'A' + 1);
        });
        return ret;
    }
};