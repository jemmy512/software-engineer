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

ElemSN *MoveNode(ElemSN *h1,ElemSN *h2){//将两个升序排列的链表按照升序合二为一 
	ElemSN *h=NULL,*t,*p;
	while(h1&&h2){
		if(h1->data<h2->data){
			p=h1;
			h1=h1->next;
		}
		else {
			p=h2;
			h2=h2->next;
		}
		p->next=NULL;
		if(!h) h=t=p;
		else {
			if(t->data-p->data){
				t=t->next=p;
			}
			else free(p);
		}
	} 
	if(!h1) h1=h2;
	while(h1){
		p=h1;
		h1=h1->next;
		p->next=NULL;
		if(p->data-t->data) t=t->next=p;
		else free(p);
	}
	return h;
}
int main(void){
	
	int a[8]={1,2,5,7,7,10,14,18};
	int b[8]={2,2,6,6,10,11,13,14}; 
	ElemSN *h1=CreatLink(a,8);
	ElemSN *h2=CreatLink(b,8);
	ElemSN *d=MoveNode(h1,h2);
	while(d){
		cout<<d->data<<" ";
		d=d->next;
	} 
	return 0;
}
