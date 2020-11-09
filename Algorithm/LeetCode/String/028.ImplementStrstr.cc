/*
Implement strStr().

Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Example 1:

Input: haystack = "hello", needle = "ll"
Output: 2
Example 2:

Input: haystack = "aaaaa", needle = "bba"
Output: -1
*/
#include <string>
#include <vector>
#include <iostream>

using std::string;

class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty())
            return 0;

        auto next = getNext(needle);
        for (int i = 0, j = 0; i < haystack.size(); ++i) {
            while (j > 0 && haystack[i] != needle[j])
                j = next[j-1] + 1;

            if (haystack[i] == needle[j])
                ++j;

            if (j == needle.size())
                return i-j+1;
        }

        return -1;
    }

private:
    std::vector<int> getNext(const std::string& needle) {
        std::vector<int> next(needle.size(), 0);

        next[0] = -1;
        int k = -1;
        for (int i = 1; i < needle.size(); ++i) {
            while (k != -1 && needle[k+1] != needle[i])
                k = next[k];

            if (needle[k+1] == needle[i])
                ++k;

            next[i] = k;
        }

        return next;
    }
};

int main() {
    Solution slu;
    std::cout << slu.strStr("", "") << std::endl;;
}