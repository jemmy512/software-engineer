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

class Solution {
private:
    map<char, string> umap;
    void mapInit() {
        umap.insert(make_pair('2', "abc"));
        umap.insert(make_pair('3', "def"));
        umap.insert(make_pair('4', "hgi"));
        umap.insert(make_pair('5', "jkl"));
        umap.insert(make_pair('6', "mno"));
        umap.insert(make_pair('7', "pqrs"));
        umap.insert(make_pair('8', "tuv"));
        umap.insert(make_pair('9', "wxyz"));
    }
    
public:
    void combine(string digits, int i, string strCur, vector<string> &vec) {
        if (i < digits.size()) {
            string str = umap[digits[i]];
            int len = str.size();
            for (int j = 0; j < len; ++j) {
                strCur += str[j];
                    combine(digits, i + 1, strCur, vec);
                if (i == digits.size() - 1) {
                    vec.push_back(strCur);    
                }
                strCur.pop_back();
            }            
        }
    }
    
    vector<string> letterCombinations(string digits) {
        mapInit();
        vector<string> vec;
        string str = "";
        combine(digits, 0, str, vec);
        
        return vec;
    }
};