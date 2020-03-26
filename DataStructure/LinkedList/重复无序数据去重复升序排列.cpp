#include<iostream>
using namespace std;

typedef struct node{
	int data;
	struct node *next;
}ElemSN;

ElemSN * CreatLink(int * a,int n){
	ElemSN *h=NULL,*p,*q,*ins,*t;
	h=t=(ElemSN *)malloc (sizeof(ElemSN));
	h->data=a[0];
	h->next=NULL;
	for(int i=1;i<n;i++){
		for(p=h;p&&p->data<a[i];q=p,p=p->next);
		if(p==NULL||p->data-a[i]){  //perfect
			ins=(ElemSN *)malloc(sizeof(ElemSN));
			ins->data=a[i];
			ins->next=p;    //perfect
			if(p==h) h=ins;
			else q->next=ins;
		}

	}
	return h;
}

int main(void)
{
	int a[8]={3,2,3,8,2,7,6,9};
	ElemSN *h=CreatLink(a,8);
	while(h){
		cout<<h->data<<" ";
		h=h->next;
	}
	return 0;
}

