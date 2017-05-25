#include<iostream>
using namespace std;

int fabonacci(int n)
{
    if(n==0||n==1)
        return n;
    int a=0,b=1,m;
    //×´Ì¬×ªÒÆ·½³Ì f[i]=f[i-1]+f[i-2];
    for(int i=1;i<n;i++){
        m=a+b;
        a=b;
        b=m;
    }
    return m;
}

int main(void)
{
    cout<<fabonacci(20)<<endl;
    return 0;
}
