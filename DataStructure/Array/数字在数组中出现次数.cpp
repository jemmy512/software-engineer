//数字在排序数组中出现的次数
#include<iostream>
using namespace std;

int GetFirstIndex(int* data,int length,int k,int start,int end)
{
    if(data==NULL||length<=0)
        return -1;
    int middleIndex=(start+end)/2;
    int middleData=data[middleIndex];

    if(middleData==k){
        //前面数字不是K，middleData肯定是第一个K。否则第一个K在前面
        if(middleIndex>0&&data[middleIndex-1]!=k||middleIndex==0)
            return middleIndex;
        else
            end=middleIndex-1;
    }
    else if(middleData>k)
        end=middleIndex-1;
    else
        start=middleIndex+1;
    return GetFirstIndex(data,length,k,start,end);
}


int GetLastIndex(int* data,int length,int k,int start,int end)
{
    if(data==NULL||length<=0)
        return -1;
    int middleIndex=(start+end)/2;
    int middleData=data[middleIndex];

    if(middleData==k){
        if(data[middleIndex+1]!=k&&middleIndex<length-1||middleIndex==length-1)
            return middleIndex;
        else
            start=middleIndex+1;
    }
    else if(middleData>k)
        end=middleIndex-1;
    else
        start=middleIndex+1;
    return GetLastIndex(data,length,k,start,end);
}

int main(void)
{
    int a[8]={1,2,3,3,3,3,4,4};
    int first=GetFirstIndex(a,8,4,0,7);
    int last =GetLastIndex(a,8,4,0,7);

    cout<<"Length of 3 : "<<last-first+1<<endl;
    return 0;
}
