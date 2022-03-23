/* Easy
Given two numbers, hour and minutes, return the smaller angle (in degrees) formed between the hour and the minute hand.

Answers within 10-5 of the actual value will be accepted as correct.

Example 1:
Input: hour = 12, minutes = 30
Output: 165

Example 2:
Input: hour = 3, minutes = 30
Output: 75

Example 3:
Input: hour = 3, minutes = 15
Output: 7.5

Constraints:
1 <= hour <= 12
0 <= minutes <= 59 */

#include <cmath>
#include <algorithm>

class Solution {
public:
    double angleClock(int h, int m) {
        if (h <0 || m < 0 || h >12 || m > 60)
            return 0;

        int OneHAngle = 30;
        int OneMAngle = 6;
        double HAnglePerM = (double)30 / 60;

        h = h % 12;
        double mAngle = m * OneMAngle;
        double hAngle = OneHAngle * h + HAnglePerM * m;
        double angle = abs(mAngle - hAngle);

        return std::min(360 - angle, angle);
    }
};