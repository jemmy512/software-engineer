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

ElemSN *MoveOddNode(ElemSN *h){//奇数节点移动到偶数节点之前 
	ElemSN *hn=NULL,*p,*q,*Del;
	p=h;
	while(p){
		if(p->data%2){
			Del=p;
			if(p==h) p=h=h->next;
			else q->next=p=p->next;
			Del->next=hn;
			hn=Del;
		}
		else {
			q=p;
			p=p->next;
		}
	}
	if(!hn) hn=h;
	else {
		ElemSN *t;
		for(t=hn;t->next;t=t->next);
		t->next=h;
	}
	return hn;
}
int main(void){
	int a[8]={3,2,5,8,4,7,6,9};
	ElemSN *h=CreatLink(a,8);
	ElemSN *d=MoveOddNode(h);
	while(d){
		cout<<d->data<<" ";
		d=d->next;
	} 
	return 0;
}
