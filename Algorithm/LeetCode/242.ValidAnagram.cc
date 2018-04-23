/*
Given two strings s and t, write a function to determine if t is an anagram of s.

For example,
s = "anagram", t = "nagaram", return true.
s = "rat", t = "car", return false.

Note:
You may assume the string contains only lowercase alphabets.

Follow up:
What if the inputs contain unicode characters? How would you adapt your solution to such case?
*/

#include<iostream>
#include<unordered_map>
using namespace std;

// 34 test cases, 10ms, beat 99.39%
class Solution {
public:
    bool isAnagram_unicode(string s, string t) {
        int lenS = s.size();
        int lenT = t.size();
        if (lenS != lenT)
            return false;
        unordered_map<char, int> umap;
        for (int i = 0; i < lenS; ++i) {
            umap[s[i]]++;
            umap[t[i]]--;
        }
        for (pair<char, int> pa : umap) {
            if (pa.second)
                return false;
        }
        
        return true;
    }
    
    bool isAnagram(string s, string t) {
        // unordered_multiset<char> sset(s.begin(), s.end());
        // unordered_multiset<char> tset(t.begin(), t.end());
        
        // sort(s.begin(), s.end());
        // sort(t.begin(), t.end());
        
        int map[26] = {0};
        for (int i = 0; i < s.size(); ++i)
            map[s[i]- 'a']++;
        for (int i = 0; i < t.size(); ++i)
            map[t[i] -'a']--;
        
        for (int i = 0; i < sizeof(map) / sizeof(map[0]); ++i) {
            if (map[i])
                return false;
        }
        return true;
    }
};

int main() {
    Solution sl;
    cout << sl.isAnagram_unicode("王杰", "杰王") << endl;
}