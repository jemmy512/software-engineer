/* Hard
A valid number can be split up into these components (in order):
1. A decimal number or an integer.
2. (Optional) An 'e' or 'E', followed by an integer.

A decimal number can be split up into these components (in order):
1. (Optional) A sign character (either '+' or '-').
2. One of the following formats:
    1. At least one digit, followed by a dot '.'.
    2. At least one digit, followed by a dot '.', followed by at least one digit.
    3. A dot '.', followed by at least one digit.

An integer can be split up into these components (in order):
1. (Optional) A sign character (either '+' or '-').
2. At least one digit.

For example, all the following are valid numbers:
["2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7",
"+6e-1", "53.5e93", "-123.456e789"],

while the following are not valid numbers:
["abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53"]. */

#include <cctype>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
    bool isNumber(string s) {
        if (s == "" || s == " ")
            return false;

        int len = s.size();
        int i = 0;
        bool hasDot = false;
        bool hasE = false;

        while (s[i] == ' ')
            ++i;        // disgard prefix and postfix space
        if (isSign(s[i]))
            ++i;
        if (isE(s[i]))
            return false;      // "00" ok
        while (s[len - 1] == ' ')
            --len;

        int head = i;   // position of the first valid digit
        while (i < len) {
            if (isdigit(s[i])) {
                ++i;
            } else {
                if (isE(s[i])) {
                    if (hasE || i == head) {
                        return false;   // prefix issue
                    }
                    ++i;
                    if (isSign(s[i])) {
                        ++i;
                    }
                    if (!isdigit(s[i])) {
                        return false;   // postfix issue
                    }
                    hasE = true;
                } else if (isDot(s[i++])) {
                    if (hasDot || hasE || !isdigit(s[i]) && head == i - 1) {
                        return false;   // prefix and posefix issue
                    }
                    hasDot = true;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
private:
    bool isDot(const char& chr) {
        return chr == '.';
    }

    bool isE(const char& chr) {
        return chr == 'e' || chr == 'E';
    }

    bool isSign(const char& chr) {
        return chr == '+' || chr == '-';
    }
};

#define TEST(s) cout << "\"" << s << "\"" << " : " << std::declval<Solution>().isNumber(s) << endl

int main() {

    TEST("");
    TEST(" ");
    TEST("00");     // true
    TEST("abc");
    TEST("1.a");
    TEST("1.");     // true
    TEST(".2");
    TEST(".");
    TEST(" . ");
    TEST("1..");
    TEST("+1.");
    TEST(" -1.");
    TEST(".1  ");   // true
    TEST("1.2.3");
    TEST(" 1.044 ");
    TEST("2e0");    // true
    TEST("e");
    TEST("1e");     // false
    TEST("1e2");
    TEST("-e58");
    TEST("6e6.5");
    TEST("1e2e3");
    TEST("05047e+6");
    TEST("05047E+6");
}
