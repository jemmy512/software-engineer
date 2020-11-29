/*
Given a string containing digits from 2-9 inclusive, return all possible letter
combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.
 Note that 1 does not map to any letters.


Example:

Input: "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
Note:

Although the above answer is in lexicographical order, your answer could be in any order you want
*/

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> vec;
        string str;

        combine(digits, 0, str, vec);

        return vec;
    }

private:
    void combine(const string& digits, int idx, string& strCur, vector<string>& vec) {
        if (idx < digits.size()) {
            string str = hashMap[digits[idx]];
            for (int j = 0; j < str.size(); ++j) {
                strCur += str[j];
                combine(digits, idx + 1, strCur, vec);
                if (idx == digits.size() - 1) {
                    vec.push_back(strCur);
                }
                strCur.pop_back();
            }
        }
    }

    unordered_map<char, string> hashMap {
        {'2', "abc"},
        {'3', "def"},
        {'4', "hgi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}
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