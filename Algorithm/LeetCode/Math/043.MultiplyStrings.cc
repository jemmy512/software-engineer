/* Medium
Given two non-negative integers num1 and num2 represented as strings,
return the product of num1 and num2, also represented as a string.
Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.

Example 1:
Input: num1 = "2", num2 = "3"
Output: "6"

Example 2:
Input: num1 = "123", num2 = "456"
Output: "56088"

Constraints:
1 <= num1.length, num2.length <= 200
num1 and num2 consist of digits only.
Both num1 and num2 do not contain any leading zero, except the number 0 itself.

Relatives:
002. Add Two Numbers
445. Add Two Numbers II
415. Add Strings
043. Multiply Strings
066. Plus One
067. Add Binary
371. Sum of Two Integers
989. Add to Array-Form of Integer
1634. Add Two Polynomials Represented as Linked Lists */*/

#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

class Solution {
public:
    string multiply(string multiplicand, string multiplier) {
        vector digit(multiplicand.size() + multiplier.size(), 0);

        for (int i = multiplicand.size() - 1; i >= 0; --i) {
            for (int j = multiplier.size() - 1; j >= 0; --j) {
                const auto mult = (multiplicand[i] - '0') * (multiplier[j] - '0');
                const auto pos = i + j + 1;
                const auto posCarry = i + j;
                const auto sum = mult + digit[pos];

                digit[pos] = sum % 10;
                digit[posCarry] += sum / 10;
            }
        }

        int i = 0;
        while (i < digit.size() && digit[i] == 0) {
            ++i;
        }

        string result;
        result.reserve(digit.size() - 1);

        std::transform(digit.cbegin() + i, digit.cend(), back_inserter(result), [](auto num) {
            return '0' + num;
        });

        return result.empty() ? "0" : result;
    }
};