//1.用一个基准数将数组分成两个子数组
//2.将大于基准数的移到右边，小于的移到左边
//递归的对子数组重复执行1，2，直到整个数组有序

#include<iostream>
#include<vector>
using namespace std;

void quick_sort(vector<int>& nums, int b, int e, vector<int>& temp)
{
    int m = (b + e) / 2;
    if (m != b) {
        int lb = b, rb = e - 1;

        for (int i = b; i < e; i++) {
            if (i == m)
                continue;
            if (nums[i] < nums[m])
                temp[lb++] = nums[i];
            else
                temp[rb--] = nums[i];
        }
        temp[lb] = nums[m];

        for (int i = b; i < e; i++)
            nums[i] = temp[i];

        quick_sort(nums, b, lb-1, temp);
        quick_sort(nums, lb + 1, e, temp);
    }
}


int main(void)
{
	vector<int> ivec={3,2,5,8,4,7,6,9};
	vector<int> temp(8);

	quick_sort(ivec,0,7,temp);
	for(auto a:ivec)
		cout<<a<<" ";
    return 0;
}
