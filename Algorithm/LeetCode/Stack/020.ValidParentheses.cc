/* Easy
 * Given a string containing just the characters '(', ')', '{', '}', '[' and ']',
 * determine if the input string is valid.
 * The brackets must close in the correct order, "()" and "()[]{}" are all valid
 * but "(]" and "([)]" are not
 *
 * Relatives:
 * 017. Letter Combination of a Phone Number
 * 020. validParentheses
 * 022. Generate Parentheses*/

#include <iostream>
#include <iterator>
#include <stack>

using namespace std;

// 4ms, beat 95.53% submissions
bool isValid(string s) {
    std::stack<char> stack;

    for (int i = 0; i < s.size(); ++i) {
        /* Calling top(back) on an empty container causes undefined behavior. */
        if (s[i] == ']' && !stack.empty() && '[' ==  stack.top())
            stack.pop();
        else if (s[i] == '}' && !stack.empty() && '{' ==  stack.top())
            stack.pop();
        else if (s[i] == ')' && !stack.empty() && '(' ==  stack.top())
            stack.pop();
        else
            stack.push(s[i]);
    }

    return  stack.empty();
}

int main() {
    cout << isValid("([{}])") << endl;
    return 0;
}