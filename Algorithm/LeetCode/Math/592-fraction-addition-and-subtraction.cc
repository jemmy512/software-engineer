/* [592] Fraction Addition and Subtraction
 *
 * https://leetcode.com/problems/fraction-addition-and-subtraction/description/
 *
 * algorithms
 * Medium (52.07%)
 * Likes:    333
 * Dislikes: 471
 * Total Accepted:    31K
 * Total Submissions: 59.6K
 * Testcase Example:  '"-1/2+1/2"'
 *
 * Given a string expression representing an expression of fraction addition
 * and subtraction, return the calculation result in string format.
 *
 * The final result should be an irreducible fraction. If your final result is
 * an integer, change it to the format of a fraction that has a denominator 1.
 * So in this case, 2 should be converted to 2/1.
 *
 * Example 1:
 * Input: expression = "-1/2+1/2"
 * Output: "0/1"
 *
 * Example 2:
 * Input: expression = "-1/2+1/2+1/3"
 * Output: "1/3"
 *
 * Example 3:
 * Input: expression = "1/3-1/2"
 * Output: "-1/6"
 *
 * Constraints:
 * The input string only contains '0' to '9', '/', '+' and '-'. So does the
 * output.
 * Each fraction (input and output) has the format ±numerator/denominator. If
 * the first input fraction or the output is positive, then '+' will be
 * omitted.
 * The input only contains valid irreducible fractions, where the numerator and
 * denominator of each fraction will always be in the range [1, 10]. If the
 * denominator is 1, it means this fraction is actually an integer in a
 * fraction format defined above.
 * The number of given fractions will be in the range [1, 10].
 * The numerator and denominator of the final result are guaranteed to be valid
 * and in the range of 32-bit int. */

#include <string>
#include <vector>
#include <numeric>
#include <sstream>

using namespace std;


class Solution {
public:
    string fractionAddition(string expression) {
        istringstream iss(expression);
        int numerator = 0, denominator = 1, num, den;
        char slash;

        while (iss >> num >> slash >> den) {
            numerator = numerator * den + num * denominator;
            denominator *= den;
            int divisor = gcd(numerator, denominator);
            numerator /= divisor;
            denominator /= divisor;
        }

        return to_string(numerator) + '/' + to_string(denominator);
    }
};

class Solution {
public:
    string fractionAddition(string expr) {
        if (expr.empty()) {
            return "";
        }

        vector<string> fractions;
        int i = expr.size() - 1;
        int end = expr.size();

        for (; i >= 0; --i) {
            if (expr[i] == '+' || expr[i] == '-' || i == 0) {
                fractions.emplace_back(expr.substr(i, end - i));
                end = i;
            }
        }

        long numerator = 0;
        long denominator = 1;

        for (auto i = 0; i < fractions.size(); ++i) {
            auto [num, den] = parse(fractions[i]);

            numerator = numerator * den + num * denominator;
            denominator *= den;
            auto divisor = abs(_gcd(numerator, denominator));

            numerator /= divisor;
            denominator /= divisor;
        }

        stringstream ss;
        ss << numerator << "/" << denominator;
        return ss.str();
    }

    pair<int, int> parse(const string& str) {
        auto pos = str.find('/');
        return { std::stoi(str.substr(0, pos)), std::stoi(str.substr(pos+1)) };
    }

    long long _gcd(int a, int b) {
        while (b != 0) {
            auto t = b;
            b = a % b;
            a = t;
        }

        return a;
    }
};
