/* Medium
Given a string containing digits from 2-9 inclusive, return all possible letter
combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.
Note that 1 does not map to any letters.

Example:
Input: "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
Note:

Although the above answer is in lexicographical order, your answer could be in any order you want

017. Letter Combination of a Phone Number
020. valid Parentheses
022. Generate Parentheses */

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        string curStr;
        curStr.reserve(digits.size());
        combination(digits, 0, curStr);

        return _Result;
    }

    void combination(const string& digits, int idx, string& curStr) {
        if (idx == digits.size()) {
            if (!curStr.empty()) {
                _Result.emplace_back(curStr);
            }
            return;
        }

        for (const auto& chr : _HashMap[digits[idx]]) {
            curStr.push_back(chr);
            combination(digits, idx+1, curStr);
            curStr.pop_back();
        }
    }

private:
    vector<string> _Result;
    unordered_map<char, string> _HashMap = {
        { '2', "abc" },
        { '3', "def" },
        { '4', "ghi" },
        { '5', "jkl" },
        { '6', "mno" },
        { '7', "pqrs" },
        { '8', "tuv" },
        { '9', "wxyz" }
    };
};

// void combination(const string& digits, int idx, string& strCur, vector<string>& vec) {
//     // error prone when digits is empty
//     if (idx == digits.size()) {
//         vec.emplace_back(strCur);
//         return;
//     }

//     string str = hashMap[digits[idx]];
//     for (int i = 0; i < str.size(); ++i) {
//         strCur += str[i];

//         combination(digits, idx+1, strCur, vec);

//         strCur.pop_back();
//     }
// }