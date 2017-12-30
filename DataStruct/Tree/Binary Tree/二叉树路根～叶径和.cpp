/*
    从根结点到叶子结点的路径之和为所求之和
*/
#include<iostream>
#include<vector>
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
void FindPath(Tree* root,int expectedSum,int currentSum,vector<int>& path)
{
    currentSum+=root->data;
    path.push_back(root->data);

    bool isLeaf=root->left==NULL&&root->right==NULL;
    if(currentSum==expectedSum&&isLeaf){
        cout<<"A path is found"<<endl;
        for(auto s:path){
            cout<<s<<" ";
        }
        cout<<endl;
    }

    if(root->left!=NULL)
        FindPath(root->left,expectedSum,currentSum,path);
    if(root->right!=NULL)
        FindPath(root->right,expectedSum,currentSum,path);
    path.pop_back();
}

void FindPath(Tree* root,int expectedSum)
{
    if(root==NULL)
        return;
    vector<int> path;
    int currentSum=0;
    FindPath(root,expectedSum,currentSum,path);
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
    int a[5]={10,5,12,4,7};

    Tree* root=CreateTree(a,5);

    FindPath(root,22);
    return 0;

}
