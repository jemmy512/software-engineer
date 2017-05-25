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

ElemSN *DelNode(ElemSN *h,int key){//删除重复值节点 
	ElemSN *p=h,*q,*Del;
	while(p){
		if(p->data-key){
			q=p;
			p=p->next;
		}
		else {
			Del=p;
			if(p==h) p=h=p->next;
			else p=q->next=p->next;
			free(Del);
		}
	}
	return h;
}
int main(void){
	int a[8]={3,2,5,8,5,7,5,9};
	ElemSN *h=CreatLink(a,8);
	ElemSN *d=DelNode(h,5);
	while(d){
		cout<<d->data<<" ";
		d=d->next;
	} 
	return 0;
}
