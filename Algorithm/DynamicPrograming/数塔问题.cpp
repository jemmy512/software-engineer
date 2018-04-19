#include<iostream>
using namespace std;


int main(void)
{
    int a[6][6] = {
            {9,0,0,0,0},
            {12,15,0,0,0},
            {10,6,8,0,0},
            {2,18,9,5,0},
            {19,7,10,4,16},
            {0,0,0,0,0}
        };
    int n=5,m=5;
    int data[n][m]={0};
    for(int i=n-1;i>0;i--){
        for(int j=0;j<i;j++){
            a[i-1][j]+=a[i][j]>a[i][j+1]?a[i][j]:a[i][j+1];
            cout<<a[i-1][j]<<" ";
        }
    }
//    int i,j,m;
//    i=j=0;
//    while(i<5&&j<5){
//        m=a[i][j];
//
//        if(a[i+1][j]<a[i+1][j+1]){
//            ++i;
//            ++j;
//        }
//        else {
//            ++i;
//        }
//
//        a[i][j]+=m;
//    }
    cout<<"ÊýËþ£º "<<a[0][0]<<endl;
    return 0;
}
