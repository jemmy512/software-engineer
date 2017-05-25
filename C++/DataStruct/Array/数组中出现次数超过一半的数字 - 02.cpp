
//数组中有一个数字出现的次数超过数组长度的一半，找出这个数字

#include<iostream>
using namespace std;


bool CheckInvalidArray(int* numbers,int length)
{
    if(numbers==NULL||length<=0)
        return false;
    return true;
}
bool CheckMoreThanHalf(int* numbers,int length,int result)
{
    int times=0;
    for(int i=0;i<length;i++){
        if(numbers[i]==result)
            times++;
    }
    if(times*2<=length)
        return false;
    return true;
}

int MoreThanHalfNum(int* numbers,int length)
{
    if(!CheckInvalidArray(numbers,length))
        return 0;

    int result=numbers[0];
    int times=1;
    for(int i=1;i<length;i++){
        if(times==0){
            result=numbers[i];
            times=1;
        }
        else if(numbers[i]==result)
            times++;
        else
            times--;
    }
//    if(!CheckMoreThanHalf(numbers,length,result))
//        result=0;
    return result;
}

int main(void)
{
    int a[6]={3,2,2,4,2,2};
    int result=MoreThanHalfNum(a,6);
    cout<<result<<endl;
    return 0;
}
