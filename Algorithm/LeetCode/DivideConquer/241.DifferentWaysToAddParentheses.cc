/* Medium
Given a string expr of numbers and operators,
return all possible results from computing all the different possible ways
to group numbers and operators. You may return the answer in any order.

Example 1:
Input: expr = "2-1-1"
Output: [0,2]
Explanation:
((2-1)-1) = 0
(2-(1-1)) = 2

Example 2:
Input: expr = "2*3-4*5"
Output: [-34,-14,-10,-10,10]
Explanation:
(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10


Constraints:
1 <= expr.length <= 20
expr consists of digits and the operator '+', '-', and '*'.
All the integer values in the input expr are in the range [0, 99]. */

#include <string>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    vector<int> diffWaysToCompute(string expr) {
        vector<int> result;

        if (_Memo.find(expr) != _Memo.end())
            return _Memo[expr];

        for (auto i = 0; i < expr.size(); ++i) {
            const auto chr = expr[i];
            if (chr == '+' || chr == '-' || chr == '*') {
                const auto left = diffWaysToCompute(expr.substr(0, i));
                const auto right = diffWaysToCompute(expr.substr(i+1));

                for (const auto& lhs : left) {
                    for (const auto& rhs : right) {
                        result.emplace_back([lhs, rhs, chr]() {
                            switch (chr) {
                                case '+': return lhs + rhs;
                                case '-': return lhs - rhs;
                                default:  return lhs * rhs;
                            }
                        }());
                    }
                }
            }
        }

        if (result.empty()) {
            result.emplace_back(std::stoi(expr));
        }

        _Memo.emplace(expr, result);

        return result;
    }

private:
    map<string, vector<int>> _Memo;
};