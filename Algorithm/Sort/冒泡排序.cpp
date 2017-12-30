#include<iostream>
using namespace std;

void bubbleSort(int a[], int n){
    for(int i =0 ; i< n-1; ++i) {
        for(int j = 0; j < n-i-1; ++j) {
            if(a[j] > a[j+1])
            {
                int tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
            }
        }
    }
    for(int i=0;i<8;i++)
    	cout<<a[i]<<" ";
	cout<<endl;

}

//优化版 flag标志变量，一轮循环中没有交换数据则不再执行
void bubbleSort_plus(int a[], int n){
    bool flag=true;
    for(int i =0 ; i< n-1&&flag; ++i) {
        flag=false;
        for(int j = 0; j <n-i-1; ++j) {
            if(a[j] > a[j+1]){
                cout<<"j :"<<j<<endl;
                flag=true;
                int tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
            }
        }
    }
    for(int i=0;i<8;i++)
    	cout<<a[i]<<" ";
	cout<<endl;
}

int main(void)
{
	int a[]={3,2,5,8,4,7,6,9};
	//bubbleSort(a,8);
	bubbleSort_plus(a,8);


	return 0;
}
