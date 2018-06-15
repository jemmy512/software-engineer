/**
 * Difficulty: Easy
 *
 * Write a function to find the longest common prefix string amongst an array of strings.
 * If there is no common prefix, return an empty string "".
 *
 * Example 1:
 * Input: ["flower","flow","flight"]
 * Output: "fl"
 *
 * Example 2:
 * Input: ["dog","racecar","car"]
 * Output: ""
 * Explanation: There is no common prefix among the input strings.
 * Note:
 * All given inputs are in lowercase letters a-z.
 */

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty())
            return "";

        int len = strs.size();
        int le = strs[0].size();
        for (int i = 0; i < le; ++i) {
            for (int j = 1; j < len; ++j) {
                if (strs[0][i] != strs[j][i]) {
                    // string ret(strs[0].begin(), strs[0].begin() + i);
                    // return ret;
                    return strs[0].substr(0, i);
                }
            }
        }
        return strs[0];
    }
};

