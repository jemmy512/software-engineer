/*
Given a list of non negative integers, arrange them such that they form the largest number.

Example 1:

Input: [10,2]
Output: "210"
Example 2:

Input: [3,30,34,5,9]
Output: "9534330"
Note: The result may be very large, so you need to return a string instead of an integer.
*/

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using std::string;
using std::vector;

class Solution {
public:
    string largestNumber(vector<int> &nums) {
        vector<string> vec;
        vec.reserve(nums.size());

        std::transform(nums.begin(), nums.end(), std::back_inserter(vec), [](auto& num) {
            return std::to_string(num);
        });

        std::sort(vec.begin(), vec.end(), [] (const auto& a, const auto& b) {
            return (a+b) > (b+a);
        });

        if (vec[0][0] == '0') // for case "00"
            return "0";

        std::stringstream ss;
        // std::for_each(vec.begin(), vec.end(), [&ss](const auto& str) {
        //     ss << str;
        // });
        std::move(vec.begin(), vec.end(), std::ostream_iterator<string>(ss));

        return ss.str();
    }
};

int main() {

}