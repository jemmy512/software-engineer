/* Easy
Given a string, determine if a permutation of the string could form a palindrome.

Example 1:
Input: "code"
Output: false

Example 2:
Input: "aab"
Output: true
Example 3:

Input: "carerac"
Output: true

Relatives:
266. Palindrome Permutation
516. Longest Palindromic Subsequence
647. Palindromic Substrings

214. Shortest Palindrome
336. Palindrome Pairs */

#include <string>
#include <unordered_map>

using namespace std;


/* hash map with single pass*/
class Solution {
public:
    bool canPermutePalindrome(string s) {
        int count = 0;
        unordered_map<char, int> hashMap;

        for (int i = 0; i < s.size(); ++i) {
            ++hashMap[s[i]];
            count += (hashMap[s[i]] % 2 == 0) ? -1 : 1;
        }

        return count <= 1;
    }
};

/* hash map */
class Solution {
public:
    bool canPermutePalindrome(string s) {
        int count = 0;
        unordered_map<char, int> hashMap;

        for (const char& ch : s) {
            ++hashMap[ch];
        }

        for (auto iter = hashMap.begin(); iter != hashMap.end() && count <= 1; ++iter) {
            const auto& [ch, cnt] = *iter;
            count += cnt % 2;
        }

        return count <= 1;
    }
};