/*
Difficulty: Easy

Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

Examples:
    pattern = "abba", str = "dog cat cat dog" should return true.
    pattern = "abba", str = "dog cat cat fish" should return false.
    pattern = "aaaa", str = "dog cat cat dog" should return false.
    pattern = "abba", str = "dog dog dog dog" should return false.
Notes:
You may assume pattern contains only lowercase letters, and str contains lowercase letters separated by a single space.

Related Problem: 205. Isomorphic Strings
*/
#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<unordered_map>
using namespace std;

// 33 test cases, 2ms, beat 100%
// optimized version of Solution_
class Solution{
public:
    bool wordPattern(string pattern, string str) {
        istringstream ss(str);
        string s;
        vector<string> vec;
        while (ss >> s) {
            vec.push_back(s);
        }
        
        if (vec.size() != pattern.size()) {
            return false;
        }
        
        unordered_map<string, char> s2c;
        unordered_map<char, string> c2s;
        int len = vec.size();
        for (int i = 0; i < len; ++i) {
            if (s2c[vec[i]] == 0 && c2s[pattern[i]] == "") { 
                s2c[vec[i]] = pattern[i];
                c2s[pattern[i]] = vec[i];
                continue;
            }
            if (s2c[vec[i]] != pattern[i]) {
                return false;
            }
        }
        
        return true;
    }
};

// 33 test cases, 2ms, beat 100%
class Solution_ {
public:
    bool wordPattern(string pattern, string str) {
        unordered_map<string, string> ucmap;
        unordered_map<string, string> usmap;
        vector<string> vec;
        int j = 0;
        int len = str.size();
        for (int i = 0; i < len; ++i) {
            if (str[i] == ' ') {
                vec.push_back(string(str.begin() + j, str.begin() + i));
                j = i + 1;
            }
        }
        vec.push_back(string(str.begin() + j, str.end()));
        
        if (pattern.size() != vec.size()) 
            return false;
        
        string keyC = "";
        string keyS = "";
        len = vec.size();
        for (int i = 0; i < len; ++i) {
            keyC = pattern[i];      // parameter of find() and make_pair() is reference
            keyS = vec[i];
            if (ucmap.find(keyC) == ucmap.end() && usmap.find(keyS) == usmap.end()) {
                ucmap.insert(make_pair(keyC, vec[i]));
                usmap.insert(make_pair(vec[i], keyC));
                continue;
            }
            if (ucmap[keyC] == vec[i] && usmap[vec[i]] == keyC) {
                continue;
            }
            return false;
        }
        return true;
    }
};

int main() {
    Solution sl;
    string pattern = "abba";
    string str = "dog cat cat dog";
    cout << sl.wordPattern(pattern, str) << endl;
}