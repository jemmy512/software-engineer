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
*/

#include<iostream>
#include<string>
using namespace std;

bool isNumber(string s) {
    
    if (s == "" || s == " ")
        return false;
    if (s[0] == '0' && s[1] == '0' || s[0] == 'e')
        return false;
    int len = s.size();
    int i = 0;
    bool isInt = false;
    bool isFloat = false;
    bool isE = false;
    bool isLeft = false;
    while (s[i] == ' ')
        ++i;
    while (s[len - 1] == ' ')
        --len;
    if (s[i] == '+' || s[i] == '-')
        ++i;
    while (i < len) {
        if (isdigit(s[i]))
            ++i;
        else {
            if (s[i] == 'e') {
                if (isE || s[++i] == '0') return false;
                if (s[i] == '+' ||s[i] == '-')
                    ++i;
                isE = true;
                if (i < len) isLeft = true;
            } else if (s[i++] == '.') {
                if (isFloat || isE) return false;
                isFloat = true;
                if (i < len) isLeft = true;
            } else 
                return false;
        }
    }
    if ((isE || isFloat) && !isLeft) 
        return false;
    return true;
}

#define TEST(s) cout << "\"" << s << "\"" << " : " << isNumber(s) << endl

int main() {
    
    TEST(".1  ");
    TEST("1.044  ");
    TEST(" 1.044 ");
    TEST("1.a");
    TEST("abc");
    TEST("e");
    TEST("1e");
    TEST("1e2");
    TEST("");
    TEST(" ");
    TEST("1.");
    TEST(".2");
    TEST(" . ");
    TEST(".");
    TEST("1.2.3");
    TEST("1e2e3");
    TEST("1..");
    TEST("+1.");
    TEST(" -1.");
    TEST("6e6.5");
    TEST("05047e+6");
    
    return 0;
}
    
    