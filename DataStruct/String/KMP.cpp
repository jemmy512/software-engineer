#include<iostream>
#include<string>
using namespace std;

int* GetNext(string ps)
{
    int len=ps.size();
    int* next=new int[len];
    cout<<"len size :"<<len<<endl;
    next[0]=-1;
    int k=-1;
    int j=0;
    while(j<len-1){
        if(k==-1||ps[j]==ps[k]){
            next[++j]=++k;
        }else{
            k=next[k];
        }
    }
    return next;
}

int KMP(string ts,string ps)
{
    int len_t=ts.size();
    int len_p=ps.size();
    int *next=GetNext(ps);
    int i=0;
    int j=0;

    while(i<len_t&&j<len_p){
        if(j==-1||ts[i]==ps[j]){
            i++;
            j++;
        }else{
            j=next[j];
        }
    }
    if(j==len_p)
        return i-j;
    else
        return -1;
}

int main(void)
{
    string target="abacaaababc";
    string pattern="abab";
    int result=KMP(target,pattern);
    cout<<result<<endl;

    return 0;
}
