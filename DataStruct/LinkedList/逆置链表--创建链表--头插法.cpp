#include<iostream>
#include<cstdlib>
using namespace std;

typedef struct node{
	int data;
	struct node *next;
}ElemSN;

ElemSN *PreCreatLink(int *a,int n){
	ElemSN *h=NULL,*t,*newp;//Warning:头结点初始化
	for(int i=n-1;i>=0;i--){
		newp=(ElemSN  *)malloc(sizeof(ElemSN));
		newp->data=a[i];
		newp->next=h;
		h=newp;
	}
	return h;
}

ElemSN *Rverse(ElemSN *h){
	ElemSN *p,*hn=NULL;
	while(h){
		p=h;
		h=h->next;
		p->next=hn;
		hn=p;
	}
	return hn;
}
int main(void){
	int a[8]={3,2,5,8,4,7,6,9};
	ElemSN *h=PreCreatLink(a,8);
	h=Rverse(h);
	while(h){
		cout<<h->data<<" ";
		h=h->next;
	}
	return 0;
}
