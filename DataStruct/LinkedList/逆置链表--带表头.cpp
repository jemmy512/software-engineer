#include<iostream>
using namespace std;

typedef struct node{
	int data;
	struct node *next;
	
}ElemSN ;

ElemSN *CreatLink(int *a,int n){
	ElemSN *h,*t,*P;
	h=t=(ElemSN *)malloc(sizeof(ElemSN ));
	h->next=NULL;
	for(int i=0;i<n;i++){
		t=t->next=(ElemSN *)malloc(sizeof(ElemSN));
		t->data=a[i];
		t->next=NULL;
	}
	return h;
} 

ElemSN *PreLink(ElemSN *h){
	ElemSN *p,*r;
	r=h->next;
	h->next=NULL;
	while(r){
		p=r;
		r=r->next;
		p->next=h->next;
		h->next=p;
	}
	return h;
} 

int main(void){
	int a[8]={3,2,5,8,4,7,6,9};
	ElemSN *head=CreatLink(a,8);
	cout<<head->next->data<<endl;
	ElemSN *pre=PreLink(head); 
	while(pre){
		cout<<pre->data<<" ";
		pre=pre->next;
	}
	return 0;
}
