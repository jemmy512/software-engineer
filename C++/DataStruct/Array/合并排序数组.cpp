#include<iostream>
using namespace std;

int Merge(int a[],int b[],int a_len,int b_len)
{
    int total=a_len+b_len-1;
    int alen=a_len-1;
    int blen=b_len-1;
    while(alen>=0&&blen>=0){
        if(a[alen]>b[blen])
            a[total--]=a[alen--];
        else
            a[total--]=b[blen--];
    }
    if(alen<0)
        while(blen>=0)
            a[total--]=b[blen--];
    else
        while(alen>=0)
            a[total--]=a[alen--];


    cout<<"Merge complate:"<<endl;
    for(int i=total+1;i<a_len+b_len;i++){
        cout<<a[i]<<" ";
    }
}

int main(void)
{
    int a[15]={1,3,5,7,8,9};
    int b[4]={2,4,6,10};
    Merge(a,b,6,4);


    return 0;
}
