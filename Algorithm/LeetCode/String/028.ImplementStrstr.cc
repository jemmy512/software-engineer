/* Easy
Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Example 1:
Input: haystack = "hello", needle = "ll"
Output: 2
Example 2:

Input: haystack = "aaaaa", needle = "bba"
Output: -1 */

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int strStr(string str, string pattern) {
        if (pattern.empty()) {
            return 0;
        }

        const auto matchTable = getMatchTable(pattern);

        for (int i = 0, j = 0; i < str.size(); ++i) {
            while (j > 0 && str[i] != pattern[j]) {
                j = matchTable[j-1] + 1;
            }
            if (str[i] == pattern[j]) {
                ++j;
            }
            if (j == pattern.size()) {
                return i - j + 1;
            }
        }

        return -1;
    }

private:
    vector<int> getMatchTable(const string& pattern) {
        if (pattern.empty()) {
            return {};
        }

        vector matchTable(pattern.size(), 0);
        matchTable[0] = -1;
        int k = -1;

        for (int i = 1; i < pattern.size(); ++i) {
            while (k != -1 && pattern[k+1] != pattern[i]) {
                k = matchTable[k];
            }
            if (pattern[k+1] == pattern[i]) {
                ++k;
            }
            matchTable[i] = k;
        }

        return matchTable;
    }
};

int main() {
    Solution slu;
    std::cout << slu.strStr("", "") << std::endl;;
}