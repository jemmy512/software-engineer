#include<iostream>
using namespace std;

//全局变量区分 最大和为 0 和无效输入返回值为 0
int g_InvalidInput=false;

int FindGreatestSumOfSubArray(int* data,int length)
{
    if(data==NULL||length<=0){
        g_InvalidInput=true;
        return 0;
    }
    int CurSum=0;
    int GreatestSum=0;
//    for(int i=0;i<length;i++){
//        if(CurSum<=0)
//            CurSum=data[i];
//        else
//            CurSum+=data[i];
//        if(CurSum>GreatestSum)
//            GreatestSum=CurSum;
//    }
    for(int i=0;i<length;i++){
        CurSum+=data[i];
        if(CurSum<=0)
            CurSum=0;
        else if(CurSum>GreatestSum)
            GreatestSum=CurSum;
    }
    return GreatestSum;
}

int GreatestSumOfSubArray(int* data,int length)
{
    int result = FindGreatestSumOfSubArray(data,length);
    if(result==0&&g_InvalidInput==false)
        return 0;
    else if(result==0&&g_InvalidInput==true)
        return-1;
    else
        return result;
}

int main(void)
{
    int a[8]={9,-6,0,0,0,0,0,0};
    int result=GreatestSumOfSubArray(a,8);
    cout<<result<<endl;
    return 0;
}
