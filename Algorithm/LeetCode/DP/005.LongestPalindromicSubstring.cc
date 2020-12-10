/* Medium
Given a string s, find the longest palindromic substring in s. You may assume that
 the maximum length of s is 1000.

Example 1:
Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.

Example 2:
Input: "cbbd"
Output: "bb" */

#include <string>
#include <utility>

using namespace std;

/* Dynamic Programming
 * P(i, j) = P(i-1, j-1) && S[i] == S[j]
 * O(N^2)
 * O(N^2)
 * the number between (left, right) is right-left-1
 * the number in [left, right]      is right-left+1 */
class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.size();
        int beg = 0, cnt = 0;

        for (int i = 0; i < len; ++i) {
            auto [left, right] = extend(s, i, i);       // aba
            auto [left_, right_] = extend(s, i, i+1);   // abba

            if (right-left > cnt) {
                beg = left;
                cnt = right-left;
            }

            if (right_-left_ > cnt) {
                beg = left_;
                cnt = right_-left_;
            }
        }

        return s.substr(beg, cnt);
    }

private:
    pair<int, int> extend(const string& str, int left, int right) {
        while (left >= 0 && right < str.size() && str[left] == str[right]) {
            --left;
            ++right;
        }

        return {left+1, right};
    }
};

string longestPalindrome_dp_opt_way(string s) {

    int n = s.size();
    if (n<=1) return s;

    //Construct a matrix, and consdier matrix[j][i] as s[i] -> s[j] is Palindrome or not.
    //                                 ------^^^^^^
    //                                 NOTE: it's [j][i] not [i][j]

    //Using vector  could cause the `Time Limit Error`
    //So, use the native array
    bool **matrix  = new bool* [n];
    int start=0, len=0;
    // Dynamic Programming
    //   1) if i == j, then matrix[i][j] = true;
    //   2) if i != j, then matrix[i][j] = (s[i]==s[j] && matrix[i-1][j+1])
    for (int i=0; i<n; i++){
        matrix[i] = new bool[i+1];
        memset(matrix[i], false, (i+1)*sizeof(bool));
        matrix[i][i]=true;
        for (int j=0; j<i; j++){
            // The following if statement can be broken to
            //   1) j==i, matrix[i][j] = true
            //   2) the length from j to i is 2 or 3, then, check s[i] == s[j]
            //   3) the length from j to i > 3, then, check s[i]==s[j] && matrix[i-1][j+1]
            if ( i==j || (s[j]==s[i] && (i-j<2 || matrix[i-1][j+1]) ) )  {
                matrix[i][j] = true;
                if (len < i-j+1){
                    start = j;
                    len = i-j+1;
                }
            }
        }
    }

    for (int i=0; i<n; i++) {
        delete [] matrix[i];
    }
    delete [] matrix;

    return s.substr(start, len);
}

class Solution {
public:
    std::string longestPalindrome(std::string s) {
        if (s.size() < 2)
            return s;
        int len = s.size(), max_left = 0, max_len = 1, left, right;
        for (int start = 0; start < len && len - start > max_len / 2;) {
            left = right = start;
            while (right < len - 1 && s[right + 1] == s[right])
                ++right;
            start = right + 1;
            while (right < len - 1 && left > 0 && s[right + 1] == s[left - 1]) {
                ++right;
                --left;
            }
            if (max_len < right - left + 1) {
                max_left = left;
                max_len = right - left + 1;
            }
        }

        return s.substr(max_left, max_len);
    }
};
