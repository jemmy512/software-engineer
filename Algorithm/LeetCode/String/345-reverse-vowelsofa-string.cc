/*
Difficulty: Easy

Write a function that takes a string as input and reverse only the vowels of a string.

Example 1:
Given s = "hello", return "holle".

Example 2:
Given s = "leetcode", return "leotcede".

Note:
The vowels does not include the letter "y".
*/

#include<iostream>
#include<string>
using namespace std;

// 484 test cases, 10ms, beat 99.90%
class Solution {
public:
    bool isVowel(char ch) {
        ch = tolower(ch);
        return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u');
    }
    
    string reverseVowels(string s) {
        int len = s.size();
        for (int i = 0, j = len - 1; i < j;) {
            while (i < j && !isVowel(s[i])) ++i;
            while (i < j && !isVowel(s[j])) --j;
            swap(s[i++], s[j--]);
        }
        return s;
    }
};

int main(){
    Solution sl;
    cout << sl.reverseVowels("leetcode") << endl;
}