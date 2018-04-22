/*
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
#include<iostream>
#include<stack>

class Solution {
public:
    string base26_int2str(long n) {
        string str = "";
        char ch;
        while (n > 0) {
            ch = 'A' + (n - 1) % 26;
            str.insert(str.begin(), ch);
            n -= (n - 1) % 26;
            n /= 26;
        }
        return str;
    }
    
    long long base26_str2int(string s) {
        long long ret = 0;
        int tmp;
        for (int i = 0; i < s.size(); ++i) {
            tmp = s[i] - 'A' + 1;
            ret = ret * 26 + tmp;
        }
        return ret;
    }
    static int titleToNumber(string s) {
       return base26_str2int(s);
    }
};

int main() {
    
    return 0;
}