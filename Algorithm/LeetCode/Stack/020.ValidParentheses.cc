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
#include <unordered_map>
#include <stack>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> stk;
        
        for (const auto& chr : s) {
            if (_HashMap.find(chr) != _HashMap.end()) {
                const auto top = stk.empty() ? '#' : stk.top();
                if (top != _HashMap.at(chr)) {
                    return false;
                } else if (top == '#') {
                    stk.push(chr);
                } else {
                    stk.pop();
                }
            } else {
                stk.push(chr);
            }
        }
        
        return stk.empty();
    }
    
private:
    const unordered_map<char, char> _HashMap {
      {')', '('},
      {'}', '{'},
      {']', '['}  
    };
};

class Solution {
public:
    bool isValid(string s) {
        std::stack<char> stack;

        for (const auto& chr : s) {
            if (stack.empty()) {
                stack.push(chr);
            } else {
                if (stack.top() == '[' && chr == ']')
                    stack.pop();
                else if (stack.top() == '{' && chr == '}')
                    stack.pop();
                else if (stack.top() == '(' && chr == ')')
                    stack.pop();
                else
                    stack.push(chr);
            }
        }

        return stack.empty();
    }
};