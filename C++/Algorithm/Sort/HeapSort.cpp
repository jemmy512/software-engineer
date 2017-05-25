#include<iostream>
using namespace std;

void adjustHeap(int (&a)[8],int beg,int end)//调整堆
{
    int temp;
    int child;
    for(temp=a[beg];2*beg+1<=end;beg=child){
        child=2*beg+1;
        if(child<end&&a[child]<a[child+1])
            child++;
        if(a[child]>temp)
            a[beg]=a[child];
        else
            break;
    }
    a[beg]=temp;
}

void HeapSort(int (&a)[8])//创建堆
{
    int len=8;
    for(int i=len/2-1;i>=0;i--)
        adjustHeap(a,i,len-1);
    for(int i=len-1;i>0;i--){
        int temp=a[i];
        a[i]=a[0];
        a[0]=temp;
        adjustHeap(a,0,i-1);
    }

}

int main(void)
{
    int a[]={3,2,5,8,4,7,6,9};
    HeapSort(a);
    for(auto i:a)
        cout<<i<<" ";
    return 0;
}
