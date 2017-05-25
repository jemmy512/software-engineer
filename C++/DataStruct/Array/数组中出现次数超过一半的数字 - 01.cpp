
//数组中有一个数字出现的次数超过数组长度的一半，找出这个数字

#include<iostream>
using namespace std;

void Swap(int* a,int* b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

int Partition(int data[],int length,int start,int end)
{
    if(data=NULL&&length<=0&&start<0&&end>=length)
        throw ("Invalid Parameters");

    int index=RandomInRange(start,end);
    Swap(&data[index],&data[end]);

    int small=start-1;
    for(index=start;index<end;index++){
        if(data[index]<data[end]){
            ++small;
            if(small!=index)
                Swap(&index[index],&index[small]);
        }
    }
    ++samll;
    Swap(&data[small],&data[end]);
    return small;
}

int main(void)
{



    return 0;
}
