/* Easy
Given a string columnTitle that represents the column title as appear in an Excel sheet,
return its corresponding column number.

For example:
A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28
...


Example 1:
Input: columnTitle = "A"
Output: 1

Example 2:
Input: columnTitle = "AB"
Output: 28

Example 3:
Input: columnTitle = "ZY"
Output: 701

Example 4:
Input: columnTitle = "FXSHRXW"
Output: 2147483647

Constraints:
1 <= columnTitle.length <= 7
columnTitle consists only of uppercase English letters.
columnTitle is in the range ["A", "FXSHRXW"].

Relatives:
168. Excel Sheet Column Title
171. Excel Sheet Column Number */

#include <string>

using std::string;

class Solution {
public:
    string convertToNumber(int n) {
        return base26_int2str(n);
    }

private:
    long long base26_str2int(string s) {
        long long ret = 0;
        std::for_each(s.begin(), s.end(), [&ret](const auto& ch) {
            ret = ret * 26 + (ch - 'A' + 1);
        });
        return ret;
    }

    string base26_int2str(long n) {
        string str;

        while (n > 0) {
            auto off = (n - 1) % 26;
            char ch = 'A' + off;
            str += ch;
            n -= off; // n = 26
            n /= 26;
        }

        return string(str.rbegin(), str.rend());
    }
};