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
	ElemSN *p,*q,*Ins,*h1=NULL,*t;
	p=h;
	while(p){
		if(p->data%2){
			Ins=p;
			//分离奇数节点 
			if(p==h) h=p=h->next;
			else q->next=p=p->next;
			Ins->next=NULL;
			//奇数节点插入到新建链表 
			if(!h1) h1=t=Ins;
			else t=t->next=Ins; 
		}
		else {
			q=p;
			p=p->next; 
		}
		if(!h1) h1=h;
		else t->next=h;
		return h1;
	}
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
