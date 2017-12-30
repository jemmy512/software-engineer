#include<iostream>
using namespace std;

void Permutation(char* str,char* Begin)
{
    if(*Begin=='\0')
        printf("%s\n",str);
    else{
        for(char* p=Begin;*p!='\0';p++){

            //交换 p 和 Begin 指向的字符
            char temp=*p;
            *p=*Begin;
            *Begin=temp;


            //后面序列排序
            Permutation(str,Begin+1);
            for(char* pp=Begin;pp!=p+1;pp++){
                printf("%c",*pp);
            }
            printf("\n");
            //恢复原来序列
            temp=*p;
            *p=*Begin;
            *Begin=temp;
        }
    }
}

void Permutation(char* str)
{
    if(str==NULL)
        return;
    Permutation(str,str);
}

int main(void)
{
    char str[]="abc";
    Permutation(str);
    return 0;
}
