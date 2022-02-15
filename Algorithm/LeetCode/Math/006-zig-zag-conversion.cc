/* Medium
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this:
(you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:
string convert(string s, int numRows);

Example 1:
Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"

Example 2:
Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:

P     I    N
A   L S  I G
Y A   H R
P     I

Constraints:
1 <= s.length <= 1000
s consists of English letters (lower-case and upper-case), ',' and '.'.
1 <= numRows <= 1000 */

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using std::min;
using std::string;
using std::vector;

class Solution {
public:
    string convert(string str, int numRows) {
        if (numRows == 1)
            return str;

        int curRow = 0;
        bool isDown = false;
        vector<string> rows(min(numRows, int(str.size())));

        for (const auto& chr : str) {
            rows[curRow] += chr;
            isDown = (curRow == 0 || curRow == numRows - 1) ? !isDown : isDown;
            curRow += isDown ? 1 : -1;
        }

        std::stringstream ss;
        std::move(rows.begin(), rows.end(), std::ostream_iterator<string>(ss));

        return ss.str();
    }
};