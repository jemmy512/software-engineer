#include<iostream>
#include<cstdlib>
using namespace std;

typedef struct node{
	int data;
	struct node *next;
}ElemSN;

ElemSN *PreCreatLink(int *a,int n){
	ElemSN *h=NULL,*newp;//Warning:头结点初始化
	for(int i=n-1;i+1;i--){
		newp=(ElemSN  *)malloc(sizeof(ElemSN));
		newp->data=a[i];
		newp->next=h;
		h=newp;
	}
	return h;
}

int main(void){
	int a[8]={3,2,5,8,4,7,6,9};
	ElemSN *h=PreCreatLink(a,8);
	while(h){
		cout<<h->data<<" ";
		h=h->next;
	}

	return 0;
}
