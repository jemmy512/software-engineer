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

int main(void){
	int a[8]={3,2,5,8,4,7,6,9};
	ElemSN *h=CreatLink(a,8);
	while(h!=NULL){
		cout<<h->data<<" ";
		h=h->next;
	}
	return 0;
}
