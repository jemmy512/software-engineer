#include<iostream>
using namespace std;

int max(int a,int b)
{
    return a>b?a:b;
}

int MaxApple(int A[3][3],int m,int n)
{
    int t[m][n];
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            t[i][j]=A[i][j]+max((j>0?t[i][j-1]:0),(i>0?t[i-1][j]:0));
            cout<<i<<" "<<j<<" " <<t[i][j]<<endl;
        }

    }
    return t[m-1][n-1];
}

int main(void)
{
    int t[3][3];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
            t[i][j]=1;
    }
    t[1][0]=3;
    t[1][1]=2;
    t[2][1]=8;

    int result=MaxApple(t,3,3);
    cout<<result<<endl;
    return 0;
}
