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

ElemSN *Sort(ElemSN *h){//无序非空链表升序排列（头插法） 
	ElemSN *pmax,*qmax,*p,*q,*hn=NULL;
	while(h){
		for(pmax=q=h,p=h->next;p;q=p,p=p->next)
		if(p->data>pmax->data){
			pmax=p;
			qmax=q;
		} 
		if(pmax==h) h=h->next;
		else qmax->next=pmax->next;
		pmax->next=hn;
		hn=pmax;
	}
	return hn;
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
