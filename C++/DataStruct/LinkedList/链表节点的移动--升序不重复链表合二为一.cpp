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

//递归
ElemSN* Merge(ElemSN* head1,ElemSN* head2)
{
    if(head1==NULL&&head2==NULL)
        return NULL;
    else if(head1==NULL)
        return head2;
    else if(head2==NULL)
        return head1;

    ElemSN* MergeHead=NULL;

    if(head1->data<head2->data){
        MergeHead=head1;
        MergeHead->next=Merge(head1->next,head2);
    }
    else{
        MergeHead=head2;
        MergeHead->next=Merge(head1,head2->next);
    }
    return MergeHead;
}

//非递归
ElemSN *MoveNode(ElemSN *h1,ElemSN *h2){//将两个升序排列的链表按照升序合二为一
	ElemSN *p,*h=NULL,*t;
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
		else t=t->next=p;
	}
	if(h1) p=h2;
	else p=h1;
	t->next=p;
	return h;
}
int main(void){

	int a[8]={1,3,5,7,9,12,14,18};
	int b[8]={2,4,6,8,10,11,13,15};
	ElemSN *h1=CreatLink(a,8);
	ElemSN *h2=CreatLink(b,8);
	//ElemSN *d=MoveNode(h1,h2);
	ElemSN* d=Merge(h1,h2);
	while(d){
		cout<<d->data<<" ";
		d=d->next;
	}

	return 0;
}
