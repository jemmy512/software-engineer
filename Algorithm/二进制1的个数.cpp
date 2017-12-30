#include<iostream>
using namespace std;

/*
计算和n的二进制中1的个数一样，且最接近的数字

*/

int getNext(int n){
    int c=n;
    int c0=0;
    int c1=0;
//
    while((c&1)==0&&(c!=0)){
        c0++;
        c>>=1;
    }

    while((c&1)==1){
        c1++;
        c>>=1;
    }

    if(c0+c1==31||c0+c1==0)//c0+c1+1=32,1表示p所在位。
        return -1;

    int p=c0+c1;//最右边处，非拖尾0的位置。
    n|=(1<<p);//翻转0为1
    n&=~((1<<p)-1);//将p右边的所有位清零
    n|=(1<<(c1-1))-1;//在右边填入（c1-1）个1

    return n;
}

int main(void)
{
    int n;
    cin>>n;
    cout<<getNext(n)<<endl;

    return 0;
}
