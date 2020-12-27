/* Medium
Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square
brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white spaces,
square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any
digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].

Example 1:
Input: s = "3[a]2[bc]"
Output: "aaabcbc"

Example 2:
Input: s = "3[a2[c]]"
Output: "accaccacc"


Example 3:
Input: s = "2[abc]3[cd]ef"
Output: "abcabccdcdcdef"

Example 4:
Input: s = "abc3[cd]xyz"
Output: "abccdcdcdxyz"


Example 5:
"3[a2[c]]"

Constraints:
1 <= s.length <= 30
s consists of lowercase English letters, digits, and square brackets '[]'.
s is guaranteed to be a valid input.
All the integers in s are in the range [1, 300]. */

#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    string decodeString(string s) {
        int index = 0;
        return decodeString(s, index);
    }

private:
    string decodeString(const string& s, int& index) {
        string result;
        while (index < s.size() && s[index] != ']') {
            if (isdigit(s[index])) {
                int cnt = 0;
                while (index < s.length() && isdigit(s[index])) {
                    cnt = cnt * 10 + s[index++] - '0';
                }

                ++index; // ignore the opening bracket '['
                string decodedString = decodeString(s, index);
                ++index; // ignore the closing bracket ']'

                while (cnt--) {
                    result += decodedString;
                }
            } else {
                result += s[index++];
            }
        }
        return result;
    }
};

/* not work */
class Solution {
public:
    string decodeString(string s) {
        // result.reserve(s.size()*2);

        int i = 0;
        while (i < s.size()) {
            if (isalpha(s[i])) {
                result += s[i++];
            } else if (isdigit(s[i])) {
                i = pushStack(s, i);
            }
        }

        return result;
    }

private:
    int pushStack(const string& s, int i) {
        int end = i;

        bool numPushed = false;
        bool charPushed = false;

        while (isdigit(s[i])) {
            if (!numPushed) {
                numPushed = true;
                numStack.push(s[i] - '0');
            } else {
                int num = numStack.top() * 10 + s[i] - '0';
                numStack.pop();
                numStack.push(num);
            }
            ++i;
        }

        assert(s[i] == '[');
        ++i;

        while (isalpha(s[i])) {
            if (!charPushed) {
                charPushed = true;
                charStack.push({s[i]});
            } else {
                string newStr = charStack.top() + s[i];
                charStack.pop();
                charStack.emplace(move(newStr));
            }
            ++i;
        }

        if (isdigit(s[i]))
            i = pushStack(s, i);

        if (s[i] == ']')
            end = i + 1;

        string curStr;
        for (int i = 0; i < numStack.top(); ++i) {
            curStr += charStack.top();
        }
        numStack.pop();
        charStack.pop();

        if (numStack.empty()) {
            result += curStr;
        } else {
            string tmp = charStack.top() + curStr;
            charStack.pop();
            charStack.push(tmp);
        }

        return end;
    }

private:
    string result;
    stack<int> numStack;
    stack<string> charStack;
};

int main() {
    string str{"3[z]2[2[y]pq4[2[jk]e1[f]]]ef"};
    Solution s;
    s.decodeString(str);
}