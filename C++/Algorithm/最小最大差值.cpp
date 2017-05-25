//有n个数，两两组成二元组，差最小的有多少对呢？差最大呢？
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(void)
{
    int N;
    while(cin>>N){
        int maxNum=0,minNum=0;
        vector<int> nums(N);
        for(int i=0;i<N;i++){
            cin>>nums[i];
        }

        sort(nums.begin(),nums.end());

        int m1=1,m2=N-1,a=1,b=1;
        while(nums[m1]==nums[m1-1]){
            a++;
            m1++;
        }
        while(nums[m2]==nums[m2-1]){
            b++;
            m2--;
        }

        maxNum=a*b;

        int minTemp=nums[N-1];
        for(int i=1;i<N;i++){
            if(nums[i]-nums[i-1]<minTemp)
                minTemp=nums[i]-nums[i-1];
        }

        if(minTemp>0){
            for(int i=1;i<N;i++){
                if(nums[i]-nums[i-1]==minTemp)
                    minNum++;
            }
        }
        else{
            for(int i=1;i<N;i++){
                int j=i-1;
                while(nums[j]==nums[i]&&j>=0){
                    minNum++;
                    j--;
                }
            }
        }

        cout<<minNum<<" "<<maxNum<<endl;

    }



    return 0;
}
