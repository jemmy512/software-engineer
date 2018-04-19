#include<iostream>
#include<vector>
#include<iterator>
using namespace std;

// 37.05%
int removeDuplicates_2(vector<int>& nums) {
    int len = nums.size();
    if (nums.size() < 2)
        return len;
    int idx = 1;
    for (int i = 1; i < len; ++i)
        if (nums[i - 1] != nums[i])
            nums[idx++] = nums[i];
    return idx;
}

// 30.08%
int removeDuplicates_1(vector<int>& nums) {
    if (nums.empty())
        return 0;
    vector<int>::iterator ite;
    for (ite = nums.end() - 1; ite > nums.begin(); --ite) {
        if (*(ite - 1) == *ite)
            nums.erase(ite);
    }
    return nums.size();
}

int main() {
    vector<int> vec;
    cout << removeDuplicates(vec) << endl;
}