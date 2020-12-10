/*
Validate if a given sing is numeric.
Some examples:
"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
Note: It is intended for the problem statement to be ambiguous.
    You should gather all requirements up front before implementing one.

Cases need to care:
    1. digit
    2. point. prevous and next situation
    3. 'e'.   prevous and next situation
*/

#include<iostream>
#include<string>
using namespace std;

bool isNumber(string s) {

    if (s == "" || s == " ")
        return false;
    int len = s.size();
    int i = 0;
    bool isFloat = false;
    bool isE = false;

    while (s[i] == ' ') ++i;            // disgard prefix and postfix space
    if (s[i] == '+' || s[i] == '-') ++i;
    if (s[i] == 'e') return false;      // "00" ok
    while (s[len - 1] == ' ') --len;

    int head = i;   // position of the first valid digit
    while (i < len) {
        if (isdigit(s[i])) ++i;
        else {
            if (s[i] == 'e') {
                if (isE || i == head) return false; // prefix issue
                ++i;
                if (s[i] == '+' ||s[i] == '-') ++i;
                if (!isdigit(s[i])) return false;   // postfix issue
                isE = true;
            } else if (s[i++] == '.') {
                if (isFloat || isE || !isdigit(s[i]) && head == i - 1)
                    return false;                   // prefix and posefix issue
                isFloat = true;
            } else
                return false;
        }
    }
    return true;
}

#define TEST(s) cout << "\"" << s << "\"" << " : " << isNumber(s) << endl

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

    return 0;
}
