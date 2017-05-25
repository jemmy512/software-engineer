#include<iostream>
#include<deque>
using namespace std;

typedef struct BinaryTreeNode{
    int m_nValue;
    struct BinaryTreeNode* m_npLeft;
    struct BinaryTreeNode* m_npRight;
}BTree;

BTree* CreateBinaryTree(int a[],int n ){
    BTree* root,* p,* c,* pa;
    root=(BTree*)malloc(sizeof(BTree));
    root->m_nValue=a[0];
    root->m_npLeft=root->m_npRight=NULL;
    for(int i=1;i<n;i++){
        p=(BTree*)malloc(sizeof(BTree));
        p->m_nValue=a[i];
        p->m_npLeft=p->m_npRight=NULL;
        c=root;
        while(c-NULL){
            pa=c;
            if(c->m_nValue>p->m_nValue) c=c->m_npLeft;
            else c=c->m_npRight;
        }
        if(pa->m_nValue>p->m_nValue) pa->m_npLeft=p;
        else pa->m_npRight=p;
    }
    return root;
}

void PrintFromTopToBottom(BTree* root){
    if(!root)
        return ;
    deque<BTree* >dequeTreeNode;
    dequeTreeNode.push_back(root);
    while(dequeTreeNode.size()){
        BTree* pNode=dequeTreeNode.front();
        dequeTreeNode.pop_front();
        cout<<pNode->m_nValue<<" "<<endl;

        if(pNode->m_npLeft)
            dequeTreeNode.push_back(pNode->m_npLeft);
        if(pNode->m_npRight)
            dequeTreeNode.push_back(pNode->m_npRight);
    }
}

void PrePrint(BTree* root){
    if(root){
        printf("%d  ",root->m_nValue);
        PrePrint(root->m_npLeft);
        PrePrint(root->m_npRight);
    }

}


int main(void)
{
    int a[8]={1,2,3,4,5,6,7,8};
    BTree* root=CreateBinaryTree(a,8);
    PrintFromTopToBottom(root);
    return 0;
}
