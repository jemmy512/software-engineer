#include<iostream>
using namespace std;


void print(int a[], int n){  
    for(int j= 0; j<n; j++){  
        cout<<a[j] <<"  ";  
    }  
    cout<<endl;  
}  
  
void swap(int *a, int *b)  
{  
    int tmp = *a;  
    *a = *b;  
    *b = tmp;  
}  
  
int partition(int a[], int low, int high)  
{  
    int privotKey = a[low];                             //基准元素  
    while(low < high){                                   //从表的两端交替地向中间扫描  
        while(low < high  && a[high] >= privotKey) --high;  //从high 所指位置向前搜索，至多到low+1 位置。将比基准元素小的交换到低端  
        swap(&a[low], &a[high]);  
        while(low < high  && a[low] <= privotKey ) ++low;  
        swap(&a[low], &a[high]);  
    }  
    print(a,10);  
    return low;  
}  
  
  
void quickSort(int a[], int low, int high){  
    if(low < high){  
        int privotLoc = partition(a,  low,  high);  //将表一分为二  
        quickSort(a,  low,  privotLoc -1);          //递归对低子表递归排序  
        quickSort(a,   privotLoc + 1, high);        //递归对高子表递归排序  
    }  
}  
  
int main(){  
    int a[10] = {3,1,5,7,2,4,9,6,10,8};  
    cout<<"初始值：";  
    print(a,10);  
    quickSort(a,0,9);  
    cout<<"结果：";  
    print(a,10);  
  return 0; 
}  
