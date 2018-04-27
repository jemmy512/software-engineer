/*
Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving 
the order of characters. No two characters may map to the same character but a character may map to itself.

For example,
Given "egg", "add", return true.

Given "foo", "bar", return false.

Given "paper", "title", return true.

Note:
You may assume both s and t have the same length.
*/
#include<iostream>
// 30 test cases, 7ms, beat 98.58%
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.size()!=t.size()) return false;

        int len = s.size();
        const int MAXCHAR = 256;
        char maps[MAXCHAR]={0}, mapt[MAXCHAR]={0};
        //memset(maps, 0, sizeof(maps));
        //memset(mapt, 0, sizeof(mapt));

        for(int i = 0; i < len; i++){
            if(maps[s[i]] == 0 && mapt[t[i]] == 0){
                maps[s[i]] = t[i];
                mapt[t[i]] = s[i];
                continue;
            }
            if(maps[s[i]] == t[i] && mapt[t[i]] == s[i]) {
                continue;
            }
            return false;
        }
        return true;
    }
};

// 30 test cases, 16ms, beat 27.23%
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s == "" && t == "")
            return true;
        
        int len = s.size();
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j <= i; ++j) {
                if (s[i] == s[j] && t[i] == t[j]) {
                    break;
                } else  if (s[i] != s[j] && t[i] != t[j]) {
                    continue;
                } else {
                    return false;
                }
            }
        }
        
        return true;
    }
};