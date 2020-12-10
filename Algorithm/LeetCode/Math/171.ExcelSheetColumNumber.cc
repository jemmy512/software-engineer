/* Easy
Related to question 168.Excel Sheet Column Title

Given a column title as appear in an Excel sheet, return its corresponding column number.

For example:

    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28
*/

class Solution {
public:
    string convertToNumber(int n) {
        return base26_str2int(n);
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
            char ch = 'A' + (n - 1) % 26;
            str.insert(str.begin(), ch);
            n -= (n - 1) % 26;
            n /= 26;
        }
        return str;
    }
};