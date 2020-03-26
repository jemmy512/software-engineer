#include<iostream>
using namespace std;

struct Tree{
    int data;
    Tree* left;
    Tree* right;
};

Tree *createTree(Tree *root, int key) {
    if (!root) {
        Tree *node = (Tree *)malloc(sizeof(Tree));
        node->data = key;
        node->left = node->right = NULL;
        return node;
    } else if (root->data > key) {
        root->left = createTree(root->left, key);
    } else if (root->data < key) {
        root->right = createTree(root->right, key);
    } else {
        return root;
    }
}

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

bool HaveTree(Tree *root1, Tree *root2) {
    if (!root2) return true;
    if (!root1) return false;
    if (root1->data != root2->data) return false;
    
    return HaveTree(root1->left, root2->left) && HaveTree(root1->right, root2->right);
}

bool HasSubTree(Tree* root1,Tree* root2)
{
    bool result = false;
    if(root1 && root2){
        if(root1->data == root2->data)
            result = HaveTree(root1, root2);
        else if(root1->data > root2->data)
            result = HasSubTree(root1->left, root2);
        else
            result = HasSubTree(root1->right, root2);
        
        // if(!root2)
            // result = HasSubTree(root1->right, root2);
    }
    return result;
}



void PrePrint(Tree* root) {
    if(root!=NULL){
        cout<<root->data<<" ";
        PrePrint(root->left);
        PrePrint(root->right);
    }
}

int main(void) {
    int a[8]={3,2,5,8,4,7,6,9};
    int b[4]={8,7,6,7};

    // Tree* root1 = CreateTree(a,8);
    // Tree* root2 = CreateTree(b,4);
    Tree *root1 = NULL;
    Tree *root2 = NULL;
    for (int i = 0; i < 8; ++i) {
        root1 = createTree(root1, a[i]);
    }
    for (int i = 0; i < 4; ++i) {
        root2 = createTree(root2, b[i]);
    }

    PrePrint(root1);
    cout << endl;
    
    PrePrint(root2);
    cout << endl;
    
    bool result = HasSubTree(root1, root2);
    cout<<(result ? "Congratulations,Tree1 has Tree2." : "Sorry,Tree1 doesn't has Tree2.") << endl;
    return 0;

}
