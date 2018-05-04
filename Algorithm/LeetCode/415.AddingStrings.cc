/*
Difficulty: Easy

Given two non-negative integers num1 and num2 represented as string, return the sum of num1 and num2.

Note:

The length of both num1 and num2 is < 5100.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer directly.
*/
#include<iostream>
#include<string>
using namespace std;

// 312 test cases, 12ms, beat 83.64%
class Solution {
public:
// 315 test cases, 12ms, beat 83.94%
    string addStrings(string num1, string num2) {
        int len1 = num1.size();
        int len2 = num2.size();
        
        string ret = string(max(len1, len2), '0');
        int cnt = ret.size();
        int i, j, sum, carry = 0;
        for (i = len1 - 1, j = len2 - 1; i >=0 && j >= 0; --i, --j) {
            sum = (num1[i] - '0') + (num2[j] - '0') + carry;
            carry = sum / 10;
            sum %= 10;
            ret[--cnt] = (char)(sum + '0');
            // ret.insert(ret.begin(), (char)(sum + '0'));
        }
        
        i = i > j ? i : j;
        string str = i > j ? num1 : num2;
        for (; i >= 0; --i) {
            sum = (str[i] - '0') + carry;
            carry = sum / 10;
            sum %= 10;
            ret[--cnt] = (char)(sum + '0');
            // ret.insert(ret.begin(), (char)(sum + '0'));
        }
        if (carry)
            // ret.insert(ret.begin(), (char)(carry + '0'));
            ret = '1' + ret; 
        
        return ret;
    }
    
// 312 test cases, 12ms, beat 83.64%
    string addStrings(string &num1, string &num2) const {
		string result = "0";
		int l1 = (int)num1.length(), l2 = (int)num2.size();
		if (l1 > 0) {
			if (l2 > 0) {
				if (l1 != 1 || l2 != 1 || num1[0] != '0' || num2[0] != '0') {
					int carry = 0, maxLen = max(l1, l2);
					char *p1s = &num1[0], *p1e = p1s + l1 - 1;
					char *p2s = &num2[0], *p2e = p2s + l2 - 1;
					result = string(maxLen, '0');
					char *r = &result[0], *re = r + maxLen - 1;
					while (p1e >= p1s || p2e >= p2s) {
						int v1 = p1e >= p1s ? (*p1e-- - '0') : 0;
						int v2 = p2e >= p2s ? (*p2e-- - '0') : 0;
						int r = v1 + v2 + carry;
						if (r >= 10) { carry = 1; r -= 10; }
						else { carry = 0; }
						*re-- = '0' + r;
					}
					if (carry) { result = '1' + result; }
				}
			}
			else { result = num1; }
		}
		else { result = num2; }
		return result;
	};
};

int main() {
    Solution sl;
    cout << sl.addStrings("321", "4321") << endl;
}