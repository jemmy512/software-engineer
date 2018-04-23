/*

*/
#include<iostream>
#include<vector>
#include<iterator>
using namespace std;

// 34 test case, 21ms, beat 85.77%
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int len = nums.size();
        int newK = len - k % len;
        int lenTail = len - newK;
        nums.insert(nums.begin(), nums.begin() + newK, nums.end());
        nums.erase(nums.end() - lenTail, nums.end());
    }
};

int main() {
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8};
    Solution sl;
    sl.rotate(vec, 3);
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}