/* Hard
Given a string s, remove duplicate letters so that every letter appears once and only once.
You must make sure your result is the smallest in lexicographical order among all possible results.

Example 1:
Input: s = "bcabc"
Output: "abc"

Example 2:
Input: s = "cbacdcbc"
Output: "acdb"

Constraints:
1 <= s.length <= 10^4
s consists of lowercase English letters.

Relatives:
316. Remove Duplicate Letters
496. Next Greater Element I
503. Next Greater Element II
556. Next Greater Element III
739. Daily Temperatures */

#include <set>
#include <map>
#include <stack>
#include <string>

using namespace std;

class Solution {
public:
    string removeDuplicateLetters(string s) {
        stack<char> stk;
        set<char> hashSet;
        map<char, int> lastSeen;

        for (auto i = 0; i < s.size(); ++i) {
            lastSeen[s[i]] = i;
        }

        for (auto i = 0; i < s.size(); ++i) {
            if (hashSet.find(s[i]) == hashSet.end()) {
                while (!stk.empty() && s[i] < stk.top() && lastSeen[stk.top()] > i) {
                    hashSet.erase(stk.top());
                    stk.pop();
                }
                hashSet.emplace(s[i]);
                stk.push(s[i]);
            }
        }

        string result;
        result.reserve(stk.size());

        while (!stk.empty()) {
            result += stk.top();
            stk.pop();
        }

        return string(result.rbegin(), result.rend());
    }
};