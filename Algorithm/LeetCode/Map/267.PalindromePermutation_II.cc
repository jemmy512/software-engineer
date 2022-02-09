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
005. Longest Palindromic Substring
009. Palindrom Number
125. Valid Palindrome
680. Valid Palindrome II
409. Longest Palindrome
234. Palindrome Linked List
266. Palindrome Permutation
267. Palindrome Permutation II
516. Longest Palindromic Subsequence
647. Palindromic Substrings

214. Shortest Palindrome
336. Palindrome Pairs
1312. Minimum Insertion Steps to Make a String Palindrome */

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> generatePalindromes(string s) {
        unordered_map<char, int> hashMap;
        vector<char> chars;
        chars.reserve(s.length()/2);

        if (!canPermutePalindrome(s, hashMap))
            return {};

        char singleChar = 0;
        for (const auto& [key, cnt] : hashMap) {
            singleChar = (cnt % 2 == 1) ? key : singleChar;
            chars.insert(chars.end(), cnt/2, key);
        }
        permute(chars, 0, singleChar);

        return result;
    }

private:
    bool canSwap(vector<char>& str, int beg, int end) {
        for (; beg < end; ++beg) {
            if (str[beg] == str[end])
                return false;
        }
        return true;
    }

    void permute(vector<char>& s, int pos, char singleChar) {
        if (pos == s.size()) {
            result.emplace_back(
                string(s.begin(), s.end())
                .append(singleChar == 0 ? string() : string(1, singleChar))
                .append(s.rbegin(), s.rend()));
        } else {
            for (int i = pos; i < s.size(); i++) {
                if (canSwap(s, pos, i)) {
                    swap(s[pos], s[i]);
                    permute(s, pos + 1, singleChar);
                    swap(s[pos], s[i]);
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
    vector<string> result;
};