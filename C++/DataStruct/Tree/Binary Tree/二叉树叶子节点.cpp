#include<iostream >
#include<cstdlib>
using namespace std;

typedef struct node{
	int data;
	struct node *left,*right;
}BTnode;

BTnode * CreateBTree(int a[],int n){
	BTnode *root,*p,*c,*pa;
	root=(BTnode *)malloc(sizeof(BTnode));
	root->data=a[0];
	root->left=root->right=NULL;
	for(int i=1;i<n;i++){
		p=(BTnode *)malloc(sizeof(BTnode));
		p->data=a[i];
		p->left=p->right=NULL;
		c=root;
		while(c-NULL){
			pa=c;
			if(c->data>p->data) c=c->left;
			else c=c->right;
		}
		if(pa->data>p->data) pa->left=p;
		else pa->right=p;
	}
	return root;
}

//前序遍历

void Forder(BTnode *root){
	if(root){
		cout<<root->data<<" ";
		Forder(root->left);
		Forder(root->right);
	}
}

void Inorder(BTnode *root){
	if(root){
		Forder(root->left);
		cout<<root->data<<" ";
		Forder(root->right);
	}
}

void Horder(BTnode *root){
	if(root){
		Horder(root->left);
		Horder(root->right);
		cout<<root->data<<" ";
	}
}

BTnode MirrorTree(BTnode *root){
	BTnode *t;
	if(root){
		t=root->left;
		root->left=root->right;
		root->right=t;
		MirrorTree(root->left);
		MirrorTree(root->right);
	}
}

int LeafCount(BTnode *root){
	int L1,L2;
	if(!root) return 0;
	L1=LeafCount(root->left);
	L2=LeafCount(root->right);
	return L1+L2+(!root->left&&!root->right);
}
int NodeCount(BTnode* root){
    int L1,L2;
    if(!root) return 0;
    L1=NodeCount(root->left);
    L2=NodeCount(root->right);
    return L1+L2+1;
}

int LevelCount(BTnode *root){
	int L1,L2;
	if(!root) return 0;
	L1=LeafCount(root->left);
	L2=LeafCount(root->right);
	return L1>L2?(L1+1):(L2+1);
}

int main(void){
	BTnode *root;
	int numbers[8]={3,2,5,8,4,7,6,9};
	root=CreateBTree(numbers,8);
	cout<<"前序遍历: "<<endl;
	Forder(root);

	cout<<endl<<"中序遍历："<<endl;
	Inorder(root);

	cout<<endl<<"后续遍历: "<<endl;
	Horder(root);

	cout<<endl<<endl<<"查找叶子节点："<<endl;
	cout<<LeafCount(root)<<endl;

    cout<<endl<<"总结点个数："<<endl;
    cout<<NodeCount(root)<<endl;

	cout<<endl<<"层数"<<endl;
	cout<<LevelCount(root)<<endl;

	cout<<"root二叉树变为镜像树："<<endl;
	MirrorTree(root);
	Forder(root);
	return 0;
}


