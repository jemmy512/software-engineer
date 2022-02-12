/* Easy
Given two strings s and t, write a function to determine if t is an anagram of s.

For example,
s = "anagram", t = "nagaram", return true.
s = "rat", t = "car", return false.

Note:
You may assume the string contains only lowercase alphabets.

Follow up:
What if the inputs contain unicode characters? How would you adapt your solution to such case?

Relativeness:
049. Group Anagrams
242. Valid Anagram
438. Find All Anagrams in a String
760. Find Anagram Mappings
1347. Minimum Number of Steps to Make Two Strings Anagram */

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

        unordered_map<char, int> hashMap;
        for (int i = 0; i < lenS; ++i) {
            ++hashMap[s[i]];
            --hashMap[t[i]];
        }

        for (const auto& [ch, cnt] : hashMap) {
            if (cnt)
                return false;
        }

        return true;
    }

    bool isAnagram(string s, string t) {
        // unordered_multiset<char> sset(s.begin(), s.end());
        // unordered_multiset<char> tset(t.begin(), t.end());

        // sort(s.begin(), s.end());
        // sort(t.begin(), t.end());

        int lenS = s.size();
        int lenT = t.size();

        int hashMap[26] = {0};
        for (int i = 0; i < lenS; ++i)
            hashMap[s[i]- 'a']++;
        for (int i = 0; i < lenT; ++i)
            hashMap[t[i] -'a']--;

        for (int i = 0; i < sizeof(hashMap) / sizeof(hashMap[0]); ++i) {
            if (hashMap[i])
                return false;
        }
        return true;
    }
};

int main() {
    Solution sl;
    cout << sl.isAnagram_unicode("test", "tset") << endl;
}