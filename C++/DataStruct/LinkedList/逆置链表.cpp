#include<iostream>
using namespace std;

typedef struct ListNode{
    int data;
    struct ListNode * pNext;
}ElemSN;

ListNode *ReverseList(ListNode *head){//方法1
    ListNode *pReverseHead=NULL;
    ListNode *pNode=head;
    ListNode *pPre=NULL;

    while(pNode!=NULL){
        ListNode *Next=pNode->pNext;
        if(Next==NULL)
            pReverseHead=pNode;
        pNode->pNext=pPre;
        pPre=pNode;
        pNode=Next;
    }
    return pReverseHead;
}
ListNode* Reverse(ListNode* head)//方法2-FS
{
    ListNode* hn=NULL,* p;
    while(head){
        p=head;
        head=head->pNext;
        p->pNext=hn;
        hn=p;
    }
    return hn;
}

ListNode *CreateList(int *a,int n){
    ElemSN *head=NULL;
    ElemSN *newp,*t;
    for(int i=0;i<n;i++){
        newp=(ElemSN *)malloc(sizeof(ElemSN));
        newp->data=a[i];
        newp->pNext=NULL;
        if(!head) head=t=newp;
        else t=t->pNext=newp;
    }
    return head;
}

void OutList(ElemSN *head){
    ElemSN *t=head;
    while(t!=NULL){
        cout<<t->data;
        t=t->pNext;
        if(t!=NULL)
            cout<<"->";
    }
}
int main(void){

    int a[8]={3,2,5,8,4,7,6,9};
    ElemSN *head=CreateList(a,8);
    OutList(head);

    ElemSN *NewHead=ReverseList(head);
    cout<<endl;
    OutList(NewHead);
    return 0;
}
