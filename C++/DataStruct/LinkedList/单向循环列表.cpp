#include<iostream>
using namespace std;

typedef struct node{
	int data;
	struct node *next;

}ElemSN ;

ElemSN* CreatLink(int *a,int n){
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

ElemSN *DelKey(ElemSN *h,int key){
	ElemSN *p;
	for(p=h->next;p->next&&p->next->data-key;p=p->next);
	if(p->next) p->next=p->next->next;
	else cout<<"NOt Found!"<<endl;
	return h;
}

int main(void){
	int a[8]={3,2,5,8,4,7,6,9};
	ElemSN *head=CreatLink(a,8);
	cout<<head->next->data<<endl;
	ElemSN *del=DelKey(head,9);

	while(del){
		cout<<del->data<<" ";
		del=del->next;
	}
	return 0;
}
