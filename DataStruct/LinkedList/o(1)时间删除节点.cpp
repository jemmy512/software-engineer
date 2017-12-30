#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

Node* CreateNode(int *a,int length)
{
    Node* head=NULL,* p;
    for(int i=length-1;i>=0;i--){
        p=(Node*)malloc(sizeof(Node));
        p->data=a[i];
        p->next=head;
        head=p;
    }
    return head;
}

void DeleteNode(Node** head,Node* tobeDelete)
{
    if(!head||!tobeDelete)
        return ;
    if(tobeDelete->next!=NULL){//不是尾节点
        Node* pNext=tobeDelete->next;
        tobeDelete->data=pNext->data;
        tobeDelete->next=pNext->next;
        delete pNext;
        pNext=NULL;
    }
    else if(*head==tobeDelete){//是尾节点，且是头结点
        delete tobeDelete;
        tobeDelete=NULL;
        *head=NULL;
    }
    else{//是尾节点
        Node* pNext=*head;
        while(pNext->next!=tobeDelete){
            pNext=pNext->next;
        }
        pNext->next=NULL;
        delete tobeDelete;
        tobeDelete=NULL;
    }
}

Node* ToBeDelete(Node* head,int value)
{
    while(head->data!=value){
        head=head->next;
    }
    return head;
}

int main(void)
{

    int a[8]={3,2,5,8,4,7,6,9};
    Node* head=CreateNode(a,8);
    DeleteNode(&head,ToBeDelete(head,3));
    while(head){
        cout<<head->data<<" ";
        head=head->next;
    }s
    return 0;
}
