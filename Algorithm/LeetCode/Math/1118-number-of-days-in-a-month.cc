/* Easy
Given a year year and a month month, return the number of days of that month.

Example 1:
Input: year = 1992, month = 7
Output: 31

Example 2:
Input: year = 2000, month = 2
Output: 29

Example 3:
Input: year = 1900, month = 2
Output: 28

Constraints:
1583 <= year <= 2100
1 <= month <= 12 */

#include <vector>

using namespace std;

class Solution {
public:
    int numberOfDays(int year, int month) {
        return (month == 2 && isLeapYear(year)) ? 29 : DaysPerMonth[month];
    }

private:
    bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    }

private:
    const vector<int> DaysPerMonth = {0,31,28,31,30,31,30,31,31,30,31,30,31};
};