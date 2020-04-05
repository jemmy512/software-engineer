/*
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
*/

#include<iostream>
#include<iterator>
#include<vector>
using namespace std;

// 4ms, beat 95.53% submissions
bool isValid(string s) {
    int len = s.size();
    vector<char> vec(len);
    vec.clear();
    for (int i = 0; i < len; ++i) {
        if (s[i] == ']' && '[' == vec.back())
            vec.pop_back();
        else if (s[i] == '}' && '{' == vec.back())
            vec.pop_back();
        else if (s[i] == ')' && '(' == vec.back())
            vec.pop_back();
        else 
            vec.push_back(s[i]);
    }
    if (vec.empty())
        return true;
    return false;
}

int main() {
    cout << isValid("([{}])") << endl;
    return 0;
}