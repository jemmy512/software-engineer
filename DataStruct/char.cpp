#include<iostream>
using namespace std;

int main(void)
{
   char sz[]="string";
   char* const s1=sz;
   char const* s2=sz;
//   s1="W";
   //s1='W';
//   s2='W';
    //s2="W";
    char p='M';
    char j='E';
    s2=&p;
    s2=&j;
    cout<<*s1<<endl;//s
    cout<<s2<<endl;//Werererer
    cout<<*s2<<endl;//W


    char* pa = "abc";

    cout<<&pa<<endl;

    cout<<&pa[0]<<endl;

    cout<<pa<<endl;


    return 0;
}
