/*
    求满足要求和的任意路径
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

    if(currentSum==expectedSum){
        cout<<"A path is found: "<<endl;
        for(auto s:path){
            cout<<s<<" ";
        }
        cout<<endl;
        //找到一条路径返回继续查找
        path.pop_back();
        return;
    }

    if(root->left!=NULL)
        FindPath(root->left,expectedSum,currentSum,path);
    if(root->right!=NULL)
        FindPath(root->right,expectedSum,currentSum,path);

    path.pop_back();
}

void Path(Tree* root,int expectedSum)
{
    if(root){
        vector<int> path;
        int currentSum=0;
        FindPath(root,expectedSum,currentSum,path);

        Path(root->left,expectedSum);

        Path(root->right,expectedSum);

    }

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
    int a[8]={3,2,5,8,4,7,6,9};

    Tree* root=CreateTree(a,8);

    Path(root,29);
    return 0;

}
