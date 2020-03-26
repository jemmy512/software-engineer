#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

Node* CreateNode(int a[],int length)
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

Node* FindK_Node(Node* head,unsigned int k)
{
    if(head==NULL||k==0)
        return NULL;
    Node* Ahead=head;

    Node* Bhead=NULL;

    for(unsigned int i=0;i<k-1;i++){
        if(Ahead->next!=NULL)
            Ahead=Ahead->next;
        else
            return NULL;
    }
    Bhead=head;

    while(Ahead->next!=NULL){
        Ahead=Ahead->next;
        Bhead=Bhead->next;
    }
    return Bhead;
}

    Node* FindKthToTail(Node* pListHead, unsigned int k) {
    	Node* cur=pListHead;
        Node* pre=pListHead;
        for(unsigned int i=0;i<k-1;i++){
            cur=cur->next;
        }
        while(cur->next!=NULL){
            cur=cur->next;
            pre=pre->next;
        }
        return pre;
    }

int main(void)
{
    int a[8]={3,2,5,8,4,7,6,9};
    Node* head=CreateNode(a,8);
//    while(head){
//        cout<<head->data<<" ";
//        head=head->next;
//    }
    Node* k_Node=FindK_Node(head,6);
    Node* m=FindKthToTail(head,6);
    if(m==NULL)
        cout<<"Sorry,not found!"<<endl;
    else
        cout<<"倒数第K个结点为："<<k_Node->data<<endl;
    return 0;
}
