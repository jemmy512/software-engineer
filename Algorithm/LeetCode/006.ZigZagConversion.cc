/*
Difficulty: Easy

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

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
*/

class Solution {
public:
    string convert(string s, int nRows) {
        //The cases no need to do anything
        if (nRows<=1 || nRows>=s.size()) return s;

        vector<string> r(nRows);
        int row = 0;
        int step = 1;
        for(int i = 0; i < s.size(); ++i) {
            if (row == nRows-1) step = -1;
            if (row == 0) step = 1;
            //cout << row <<endl;
            r[row] += s[i];
            row += step;
        }

        string result;
        for (int i=0; i<nRows; i++){
            result += r[i];
        }
        return result;
    }
    
    string convert__(string s, int numRows) {
        int len = s.size();
        int interval = (numRows - 1) * 2;
        interval = interval ? interval : 1;
        string ret(len, ' ');
        int k = 0;
        
        
        ret[k++] = s[0];
        if (len > 1) {
            int i = interval;
            while (i < len) {
                ret[k++] = s[i];
                i += interval;
            }
    cout << ret << endl;
            for (int i = 1; i < numRows- 1; ++i) {
                int j = i;
                while (j < len) {
                    j += interval;
                    if (j < len) {
                        ret[k++]= s[j - i - 1];
                        ret[k++]= s[j];
                    }
                }
            }

            ret[k++]= s[numRows - 1];
            i = numRows - 1 + interval;
            while (i < len) {
                ret[k++]= s[i];
                i += interval;
            }
        }
        
        if (ret[len - 1] == ' ')
            ret.pop_back();
        return ret;
    }
};