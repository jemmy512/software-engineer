#include<iostream>
#include<vector>
#include<map>
using namespace std;

class Solution {
public:
    static int majorityElement(vector<int>& nums) {
        multimap<int, int> data;
        int len = nums.size();
        for (int i = 0; i < len; ++i) {
            cout << data.count(nums[i]) << endl;
            if (data.count(nums[i]) > len / 2)
                return nums[i];
            else 
                data.insert(make_pair(nums[i], data.count(nums[i]) + 1));
        }
    }
};

int main() {
    vector<int> vec = {1,2,3,2,2,2,4,2,2,4};
    cout << Solution::majorityElement(vec);
}