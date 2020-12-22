/* Medium
Given a string s, return all the palindromic permutations (without duplicates) of it.
Return an empty list if no palindromic permutation could be form.

Example 1:

Input: "aabb"
Output: ["abba", "baab"]
Example 2:

Input: "abc"
Output: []

Relatives:
266. Palindrome Permutation
267. Palindrome Permutation II
516. Longest Palindromic Subsequence
647. Palindromic Substrings

214. Shortest Palindrome
336. Palindrome Pairs */

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> generatePalindromes(string s) {
        unordered_map<char, int> hashMap;
        vector<char> st(s.length() / 2, 0);

        if (!canPermutePalindrome(s, hashMap))
            return {};

        char ch = 0;
        int k = 0;
        for (int i = 0; i < hashMap.size(); i++) {
            if (hashMap[i] % 2 == 1)
                ch = (char) i;
            for (int j = 0; j < hashMap[i] / 2; j++) {
                st[k++] = (char) i;
            }
        }
        permute(st, 0, ch);
        return vector<string>(hashSet.begin(), hashSet.end());
    }

private:
    void permute(vector<char>& s, int l, char ch) {
        if (l == s.size()) {
            hashSet.insert(string(s.begin(), s.end()).append(ch == 0 ? string("") : string(ch)).append(string(s.rbegin(), s.rend())));
        } else {
            for (int i = l; i < s.size(); i++) {
                if (s[l] != s[i] || l == i) {
                    swap(s[l], s[i]);
                    permute(s, l + 1, ch);
                    swap(s[l], s[i]);
                }
            }
        }
    }

    bool canPermutePalindrome(string s, unordered_map<char, int>& hashMap) {
        int count = 0;
        for (int i = 0; i < s.length(); i++) {
            ++hashMap[s[i]];
            count += (hashMap[s[i]] % 2 == 0) ? -1 : 1;
        }
        return count <= 1;
    }

private:
    unordered_set<string> hashSet;
};
