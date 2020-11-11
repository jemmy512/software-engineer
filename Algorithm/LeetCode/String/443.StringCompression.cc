/*
Difficulty: Easy

Given an array of characters, compress it in-place.

The length after compression must always be smaller than or equal to the original array.

Every element of the array should be a character (not int) of length 1.

After you are done modifying the input array in-place, return the new length of the array.


Follow up:
Could you solve it using only O(1) extra space?


Example 1:
Input:
['a','a','b','b','c','c','c']

Output:
Return 6, and the first 6 characters of the input array should be: ['a','2','b','2','c','3']

Explanation:
'aa' is replaced by 'a2'. 'bb' is replaced by 'b2'. 'ccc' is replaced by 'c3'.
Example 2:
Input:
['a']

Output:
Return 1, and the first 1 characters of the input array should be: ['a']

Explanation:
Nothing is replaced.
Example 3:
Input:
['a','b','b','b','b','b','b','b','b','b','b','b','b']

Output:
Return 4, and the first 4 characters of the input array should be: ['a','b','1','2'].

Explanation:
    Since the character 'a' does not repeat, it is not compressed. 'bbbbbbbbbbbb' is replaced by 'b12'.
    Notice each digit has it's own entry in the array.
Note:
    All characters have an ASCII value in [35, 126].
    1 <= len(chars) <= 1000.
*/
#include <iostream>
#include <vector>
#include <stack>

using std::vector;

// 70 test cases, 7ms, beat 99.63%
class Solution {
public:
    int compress(vector<char>& chars) {
        std::stack<int> stck;
        int len = chars.size();
        int step = 0;
        int cnt = 0;
        for (int j = 0; j < len;) {
            chars[step] = chars[j];
            while (j < len && chars[step] == chars[j]) {
                ++j;
                ++cnt;
            }
            if (cnt > 1) {
                while (cnt) {
                    stck.push(cnt % 10 + '0');
                    cnt /= 10;
                }
                while (stck.size() > 0) {
                    chars[++step] = stck.top();
                    stck.pop();
                }
            } else {
                cnt = 0;
            }
            ++step;
        }

        return step;
    }

    int compress_(vector<char>& chars) {
        chars.push_back('a');

        char chr{chars[0]};
        int cnt{1};
        int idx{0};

        for (int i = 1; i < chars.size(); ++i) {
           if (i+1 == chars.size() || chars[i] != chr) {
                chars[idx++] = chr;
                if (cnt > 1) {
                    for (const auto& c : std::to_string(cnt))
                        chars[idx++] = c;
                }

                chr = chars[i];
                cnt = 1;
            } else {
                ++cnt;
            }
        }

        return idx;
    }
};

int main() {
    Solution slution;
    std::vector<char> vec{'a','a','b','b','c','c','c'};
    slution.compress(vec);
}