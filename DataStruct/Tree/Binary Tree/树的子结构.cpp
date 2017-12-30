#include<iostream>
using namespace std;

struct Tree{
    int data;
    Tree* left;
    Tree* right;
};

Tree* CreateTree(int a[],int n)
{
    Tree* root,* p,* c,*pa;
    root=(Tree*)malloc(sizeof(Tree));
    root->data=a[0];
    root->left=root->right=NULL;
    for(int i=1;i<n;i++){
        p=(Tree*)malloc(sizeof(Tree));
        p->data=a[i];
        p->left=p->right=NULL;
        c=root;
        while(c){
            pa=c;
            if(c->data>p->data)
                c=c->left;
            else
                c=c->right;
        }
        if(pa->data>p->data)
            pa->left=p;
        else
            pa->right=p;
    }
    return root;
}
bool HaveTree(Tree* root1,Tree* root2)
{
    if(root2==NULL)
        return true;
    if(root1==NULL)
        return false;
    if(root1->data!=root2->data)
        return false;
    return HaveTree(root1->left,root2->left)&&HaveTree(root1->right,root2->right);
}
bool HasSubTree(Tree* root1,Tree* root2)
{
    bool result=false;
    if(root1!=NULL&&root2!=NULL){
        if(root1->data==root2->data)
            result=HaveTree(root1,root2);
        if(!result)
            result=HasSubTree(root1->left,root2);
        if(!root2)
            result=HasSubTree(root1->right,root2);
    }
    return result;
}



void PrePrint(Tree* root)
{
    if(root!=NULL){
        cout<<root->data<<" ";
        PrePrint(root->left);
        PrePrint(root->right);
    }
}

int main(void)
{
    int a[7]={8,8,7,9,2,4,7};
    int b[4]={8,8,7,9};

    Tree* root1=CreateTree(a,7);
    Tree* root2=CreateTree(b,4);

    bool result=HasSubTree(root1,root2);
    cout<<(result?"Congratulations,Tree1 has Tree2.":"Sorry,Tree1 doesn't has Tree2.")<<endl;
    return 0;

}
