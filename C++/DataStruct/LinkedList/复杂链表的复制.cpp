#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* pNext;
    Node* pSibling;
};

Node* CreateNode(int a[],int length)
{
    Node* head=NULL,* p;
    for(int i=length-1;i>=0;i--){
        p=(Node*)malloc(sizeof(Node));
        p->data=[i];
        p->pNext=head;
        head=p;
    }
}
