#include<stdio.h>
#include<string.h>
#include<string>
#include<iostream>
#include<vector>

using namespace std;
void swapChar(char* a,char* b)
{
    char temp=*a;
    *a=*b;
    *b=temp;
}

//去重的原则就是：该字符与它后面不重复的字符交换
bool IsSwap(char* a,int begin,int end)
{
    for(;begin<end;begin++){
        if(a[begin]==a[end]){
            return false;
        }
    }
    return true;

}
void AllRange(char* str,int  begin,int len)
{
    if(begin+1==len)
        printf("%s\n",str);
    else{
        for(int i=begin;i<len;i++){
            if(IsSwap(str,begin,i)){
                swapChar(&str[begin],&str[i]);
                AllRange(str,begin+1,len);
                swapChar(&str[begin],&str[i]);
            }

        }
    }
}

void Permutation(char* s)
{
    if(s==NULL)
        return ;
    range(s,0,strlen(s));
    //AllRange(s,0,strlen(s));
}




int main(void)
{

    char a[]="abb";
    char b[]="abc";
    Permutation(b);
    return 0;
}
