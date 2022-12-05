/* Easy
Given an integer num, return a string representing its hexadecimal representation.
For negative integers, two’s complement method is used.

All the letters in the answer string should be lowercase characters,
and there should not be any leading zeros in the answer except for the zero itself.

Note: You are not allowed to use any built-in library method to directly solve this problem.

Example 1:
Input: num = 26
Output: "1a"

Example 2:
Input: num = -1
Output: "ffffffff"

Constraints:
-231 <= num <= 231 - 1 */

char* toHex(int num) {
    int p = 0;
    int cnt = 0;
    char* str = malloc(9);
    memset(str, 0, 9);

    if (num == 0) {
        *str = '0';
        return str;
    }

    while (num && cnt++ < 8) {
        int remain = num & 0xf;

        if (remain < 10) {
            str[p++] = remain + '0';
        } else {
            str[p++] = remain - 10 + 'a';
        }

        num >>= 4;
    }

    for (int i = 0; i < p/2; ++i) {
        char chr = str[i];
        str[i] = str[p-1-i];
        str[p-1-i] = chr;
    }

    return str;
}

class Solution {
public:
    string toHex(int num) {
        if (num == 0)
            return "0";

        string result;
        const string HEX = "0123456789abcdef";

        int count = 0;
        while (num && count++ < 8) {
            result = HEX[num & 0xf] + result;
            num >>= 4;
        }

        return result;
    }
};