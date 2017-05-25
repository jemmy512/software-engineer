#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;

void Combination(char *str)
{
	if(str == NULL)
		return ;
	int len = strlen(str);
	int n = 1<<len;
	for(int i=0;i<n;i++)    //从 1 循环到 2^len -1，空串是任何字符串的子串
	{
		for(int j=0;j<len;j++)
		{
			int temp = i;
			if(temp & (1<<j)){   //对应位上为1，则输出对应的字符
				printf("%c",*(str+j));
            }
		}
		printf("\n");
	}
}

int main(void)
{
	char str[] = "abc";
	Combination(str);
//	for(int i=0;i<3;i++){
//        cout<<str[i]<<endl;
//	}

	return 0;
}
