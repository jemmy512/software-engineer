#include<stdio.h>
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

int main(void)
{
    int pow32[32];
    pow32[0]=1;
    for (int i =1 ;i<32;i++)
    {
        pow32[i]=2*pow32[i-1];
    }
    vector<string> str;
    int n;
    while (scanf("%d",&n)!=EOF)
    {

        //printf("please input a number: ");
        if (n<=0)
            break;
        n--; //start from 0
        int total_number =0;
        int remain =0;
        char szNumber[32]={0};
        for (int i =0 ;i< 32;i++)
        {
            if (pow32[i] >n+2)
            {
                total_number=i-1;
                remain = n-(pow32[total_number]-2);
                break;
            }
        }
        for (int i =0;i<total_number;i++)
        {
            if (remain & pow32[total_number -i-1])
                szNumber[i]='7';
            else
                szNumber[i]='4';

        }
        str.push_back(szNumber);

    }

    for(auto c:str)
        cout<<c<<endl;

    return 0;
}
