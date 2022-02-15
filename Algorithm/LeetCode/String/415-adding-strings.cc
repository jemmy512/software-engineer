/* Easy
Given two non-negative integers, num1 and num2 represented as string,
return the sum of num1 and num2 as a string.

Example 1:
Input: num1 = "11", num2 = "123"
Output: "134"

Example 2:
Input: num1 = "456", num2 = "77"
Output: "533"

Example 3:
Input: num1 = "0", num2 = "0"
Output: "0"

Constraints:
1 <= num1.length, num2.length <= 10^4
num1 and num2 consist of only digits.
num1 and num2 don't have any leading zeros except for the zero itself.

Follow up: Could you solve it without using any built-in BigInteger library
or converting the inputs to integer directly?

Relatives:
002. Add Two Numbers
445. Add Two Numbers II
415. Add Strings
043. Multiply Strings
066. Plus One
067. Add Binary
371. Sum of Two Integers
989. Add to Array-Form of Integer
1634. Add Two Polynomials Represented as Linked Lists */

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string addStrings(string num1, string num2) {
        string ret(std::max(num1.size(), num2.size()), '0');

        int carry = 0;
        int i = num1.size()-1;
        int j = num2.size()-1;
        int cur = ret.size()-1;

        while (i >= 0 || j >=0) {
            int vi = i >= 0 ? num1[i--] - '0' : 0;
            int vj = j >= 0 ? num2[j--] - '0' : 0;
            int sum = vi + vj + carry;
            carry = sum / 10;
            sum %= 10;
            ret[cur--] = sum + '0';
        }

        if (carry) {
            ret = "1" + ret;
        }

        return ret;
    }
};