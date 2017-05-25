//输入一个整数（<1000），求求两质数之和等于该数的质数对数    ·1阿强2

#include <stdio.h>
#include<iostream>
using namespace std;

int main(void)
{

  int
  cin>>num;

  int a[1000]={0};
  int k=0;
  int i=0,j=0;

  for(i=2;i<1000;i++){
    for(j=2;j<i&&(i%j!=0);j++);

    if(j==i){
        a[k++]=i;
    }
  }

  int result = 0;


  i=0;
  for(j=0;a[j]<num;j++);
  while(i<=j){
  	if(a[i]+a[j]==num){
        result++;
        i++;
        j--;
  	}
    else if(a[i]+a[j]>num)
      j--;
    else
      i++;
  }

  cout<<result<<endl;

    return 0;
}




