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

ElemSN *DelMaxNode(ElemSN *h){//输出最大值节点的值 
	ElemSN *p,*q,*pmax,*qmax;
	for(pmax=q=h,p=h->next;p;q=p,p=p->next){
		if(p->data>pmax->data){
			pmax=p;
			qmax=q;
		}
	}
	if(pmax==h) h=h->next;
	else  qmax->next=pmax->next;
	free(pmax);
	return h;
}
int main(void){
	int a[8]={3,2,5,8,4,7,6,9};
	ElemSN *h=CreatLink(a,8);
	ElemSN *d=DelMaxNode(h);
	while(d){
		cout<<d->data<<" ";
		d=d->next;
	} 
	return 0;
}
