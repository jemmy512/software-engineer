#include<iostream>
#include<stdio.h>
#include<math.h>
#include<cstring>
#include<algorithm>
using namespace std;

#define MAX 100
char s1[MAX];
char s2[MAX];

int distance(char *s1,char *s2)
{   int len1=strlen(s1);
    int len2=strlen(s2);

    if(len1==0||len2==0)
    {
       return max(len1,len2);
     }

      if(s1[0]==s2[0])
        return distance(s1+1,s2+1);
      else
        return min(distance(s1,s2+1),min(distance(s1+1,s2),distance(s1+1,s2+1)))+1;
}

int distance2(char *s1,char* s2)
{
    int len1=strlen(s1);
    int len2=strlen(s2);

    int len=abs(len1-len2);
    for(int i=0;i<min(len1,len2);i++){
        if(s1[i]!=s2[i])
            len++;
    }

    return len;
}

int main(void)
{
    cin>>s1>>s2;
    int length=distance(s1,s2);
    cout<<distance2(s1,s2)<<endl;
    double result=1.0/(length+1);
    cout<<result<<endl;
    return 0;
}
