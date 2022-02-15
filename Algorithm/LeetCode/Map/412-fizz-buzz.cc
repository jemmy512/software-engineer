/**
 * Write a program that outputs the string representation of numbers from 1 to n.
 * But for multiples of three it should output “Fizz” instead of the number and for the multiples
 * of five output “Buzz”. For numbers which are multiples of both three and five output “FizzBuzz”.
 *
 * Example:
 * Return:
[
    "1",
    "2",
    "Fizz",
    "4",
    "Buzz",
    "Fizz",
    "7",
    "8",
    "Fizz",
    "Buzz",
    "11",
    "Fizz",
    "13",
    "14",
    "FizzBuzz"
]
 */
#include <map>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> vec;
        vec.reserve(n);

        for (int i = 1; i <= n; ++i) {
            string str;
            for (const auto& [key, val] : hashMap) {
                if (i % key == 0) {
                    str += val;
                }
            }

            auto newStr = str.empty() ? to_string(i) : str;
            vec.emplace_back(std::move(newStr));
        }

        return vec;
    }

private:
    map<int, string> hashMap{
        {3, "Fizz"},
        {5, "Buzz"},
        {15, ""}
    };
};

class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> vec;
        vec.reserve(n);

        for (int i = 1; i <= n; ++i) {
            if (i % 15 == 0) {
                vec.push_back("FizzBuzz");
            } else if (i % 3 == 0) {
                vec.push_back("Fizz");
            } else if (i % 5 == 0) {
                vec.push_back("Buzz");
            } else {
                vec.push_back(to_string(i));
            }
        }

        return vec;
    }
};