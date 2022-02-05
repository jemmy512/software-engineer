/* Easy
Given a binary string s ​​​​​without leading zeros, return true​​​ if s contains at most one contiguous segment of ones.
Otherwise, return false.

Example 1:
Input: s = "1001"
Output: false
Explanation: The ones do not form a contiguous segment.

Example 2:
Input: s = "110"
Output: true

Constraints:
1 <= s.length <= 100
s[i]​​​​ is either '0' or '1'.
s[0] is '1'. */

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool checkOnesSegment(string s) {
        for (auto i = 1; i < s.size(); ++i) {
            if (s[i-1] == '0' && s[i] == '1')
                return false;
        }
        return true;
    }
};

class Solution {
public:
    bool checkOnesSegment(string s) {
        int i = 0, len = s.size();
        bool hasSegment = false;

        while (i < len) {
            while (i < len && s[i] == '1') {
                hasSegment = true;
                i++;
            }
            i++;
            if (i < len && s[i] == '1' && hasSegment)
                return false;
        }

        return true;
    }
};

class Solution {
public:
    bool checkOnesSegment(string s) {
        int cnt = 0;
        int beg = 0, end = 0;

        for (auto i = 1; i < s.size() && cnt < 2; ++i) {
            if (s[i-1] == '1' && s[i] == '1') {
                ++end;
                if (i+1 == s.size())
                    ++cnt;
                std::cout << beg << " : " << end << endl;
            } else if (s[i-1] == '1' && s[i] == '0') {
                ++end;
                if (end != beg) {
                     ++cnt;
                    cout << cnt << endl;
                }

            } else if (s[i-1] == '0' && s[i] == '1') {
                beg = end = i;
                if (i+1 == s.size())
                    ++cnt;

            } else {
                beg = end = i;
            }
        }

        return cnt == 1 || (s.size() == 1 && s[0] == '1');
    }
};