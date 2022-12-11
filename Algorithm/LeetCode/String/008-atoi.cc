/* Medium
Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer
(similar to C/C++'s atoi function).

The algorithm for myAtoi(string s) is as follows:
1. Read in and ignore any leading whitespace.
2. Check if the next character (if not already at the end of the string) is '-' or '+'.
    Read this character in if it is either. This determines if the final result is negative or positive respectively.
    Assume the result is positive if neither is present.
3. Read in next the characters until the next non-digit charcter or the end of the input is reached.
    The rest of the string is ignored.
4. Convert these digits into an integer (i.e. "123" -> 123, "0032" -> 32).
    If no digits were read, then the integer is 0. Change the sign as necessary (from step 2).
5. If the integer is out of the 32-bit signed integer range [-2^31, 2^31 - 1],
    then clamp the integer so that it remains in the range.
    Specifically, integers less than -2^31 should be clamped to -2^31,
    and integers greater than 2^31 - 1 should be clamped to 2^31 - 1.
6. Return the integer as the final result.

Note:
Only the space character ' ' is considered a whitespace character.
Do not ignore any characters other than the leading whitespace or the rest of the string after the digits.

Constraints:
0 <= s.length <= 200
s consists of English letters (lower-case and upper-case), digits (0-9), ' ', '+', '-', and '.'.

Relatives:
007. Reverse Integer
008. String to Integer (atoi)
065. Valid Number */

#include <cstdio>
#include <climits>
#include <string>

using namespace std;

int myAtoi(string str) {
    if (str.empty())
        return 0;

    int ret = 0;

    // 1. strip white space
    int i = str.find_first_not_of(' ');

    // 2. process sign
    bool isPositive = true;
    if (i < str.size() && (str[i] == '+' || str[i] == '-')) {
        isPositive = str[i++] == '-' ? false : true;
    }

    // 3. process each num
    while(i < str.size() && str[i] <= '9' && str[i] >= '0') {
        if (ret > INT_MAX / 10 || (ret == INT_MAX / 10 && str[i] - '0' > INT_MAX % 10)) {
            return isPositive ? INT_MAX : INT_MIN;
        }
        ret = ret * 10 + (str[i++] - '0');
    }

    return isPositive ? ret : -ret;
}

int main() {
    printf("[%s] = %d\n", "123", myAtoi("123"));
    printf("[%s] = %d\n", "   123", myAtoi("    123"));
    printf("[%s] = %d\n", "+123", myAtoi("+123"));
    printf("[%s] = %d\n", " -123", myAtoi(" -123"));
    printf("[%s] = %d\n", "123ABC", myAtoi("123ABC"));
    printf("[%s] = %d\n", "12 3 ABC", myAtoi("123ABC"));
    printf("[%s] = %d\n", " abc123ABC", myAtoi(" abc123ABC"));
    printf("[%s] = %d\n", "2147483649", myAtoi("2147483647"));
    printf("[%s] = %d\n", "-2147483648", myAtoi("-2147483648"));
    printf("[%s] = %d\n", "2147483648", myAtoi("2147483648"));
    printf("[%s] = %d\n", "-2147483649", myAtoi("-2147483649"));
}