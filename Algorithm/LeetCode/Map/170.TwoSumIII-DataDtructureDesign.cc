/* Easy
Design a data structure that accepts a stream of integers
and checks if it has a pair of integers that sum up to a particular value.

Implement the TwoSum class:

TwoSum() Initializes the TwoSum object, with an empty array initially.
void add(int number) Adds number to the data structure.
boolean find(int value) Returns true if there exists any pair of numbers
whose sum is equal to value, otherwise, it returns false.


Example 1:

Input
["TwoSum", "add", "add", "add", "find", "find"]
[[], [1], [3], [5], [4], [7]]
Output
[null, null, null, null, true, false]

Explanation
TwoSum twoSum = new TwoSum();
twoSum.add(1);   // [] --> [1]
twoSum.add(3);   // [1] --> [1,3]
twoSum.add(5);   // [1,3] --> [1,3,5]
twoSum.find(4);  // 1 + 3 = 4, return true
twoSum.find(7);  // No two integers sum up to 7, return false

Relatives:
001. Two Sum
167. Two Sum II - Input array is sorted
170. Two Sum III - Data structure design
653. Two Sum IV - Input is a BST
1214. Two Sum BSTs

015. 3 Sum
016. 3 Sum Closest
018. 4 Sum */

#include <unordered_map>

using namespace std;

/* Approaches:
 * 1. hash table
 * 2. sorted list */
class TwoSum {
public:
    TwoSum() {

    }

    void add(int number) {
        hashMap[number] += 1;
    }

    bool find(int value) {
       for (const auto& [num, cnt] : hashMap) {
            long complement = value - num; // -2147484648 - 1 overflow
            // if (hashMap.contains(complement)) { // c++20
            if (hashMap.find(complement) != hashMap.end()) {
                if (complement == num)
                    return cnt > 1;
                else
                    return true;
            }
        }

        return false;
    }

private:
    unordered_map<long, long> hashMap;
};

/**
 * Your TwoSum object will be instantiated and called as such:
 * TwoSum* obj = new TwoSum();
 * obj->add(number);
 * bool param_2 = obj->find(value);
 */