#include<iostream> 
#include<cstdlib>
using namespace std;

typedef struct node{
	int data;
	struct node *next;
}ElemSN;

ElemSN *CreatLink(int *a,int n){
	ElemSN *h=NULL,*newp,*t;
	for(int i=0;i<n;i++){
		newp=(ElemSN *)malloc(sizeof(ElemSN));
		newp->data=a[i];
		newp->next=NULL;
		if(!h) h=t=newp;
		else t=t->next=newp;
	}
	return h;
} 

ElemSN *DelNode(ElemSN *h,int key){
	ElemSN *p,*q;
	for(p=h;p&&p->data-key;q=p,p=p->next);
	if(!p) cout<<"Sorry.Not found!"<<endl;
	else {
		if(p==h) h=h->next;
		else q->next=p->next;
		free(p);
	}
	return h;
}
int main(void){
	int a[8]={3,2,5,8,4,7,6,9};
	ElemSN *h=CreatLink(a,8);
	ElemSN *d=DelNode(h,8);
	while(d){
		cout<<d->data<<" ";
		d=d->next;
	} 
	return 0;
}
