#include<iostream>
#include<vector>
using namespace std;

void merge_array(vector<int> &nums, int b, int m, int e, vector<int> &temp)
{
    int lb = b, rb = m, tb = b;
    while (lb != m && rb != e)
        if (nums[lb] < nums[rb])
            temp[tb++] = nums[lb++];
        else
            temp[tb++] = nums[rb++];

    while (lb < m)
        temp[tb++] = nums[lb++];
    
    while (rb < e)
        temp[tb++] = nums[rb++];

    for (int i = b;i < e; i++)
        nums[i] = temp[i];
}

void merge_sort(vector<int> &nums, int b, int e, vector<int> &temp)
{
    int m = (b + e) / 2;
    if (m != b) {
        merge_sort(nums, b, m, temp);
        merge_sort(nums, m, e, temp);
        merge_array(nums, b, m, e, temp);
    }
}

int main(void)
{
	vector<int> ivec={3,2,5,8,4,7,6,9};
	vector<int> temp(8);
	
	merge_sort(ivec,0,7,temp);
	for(auto a:ivec)
		cout<<a<<" ";
		return 0;
}
