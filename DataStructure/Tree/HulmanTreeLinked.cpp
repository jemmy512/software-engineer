#include<iostream>
using namespace std;

typedef struct node{
	char word;
	int weight;
	struct node *left,*right;
}HulfNode;
void CreatHulTree(HulfNode **F,int n){
	int k1,k2;
	for(int loop=0;loop<n;loop++){
		for(k1=0;k1<n&&F[k1];k1++);
		for(k2=k1+1;k2<n&&F[k2];k2++);
		for(int j=0;j<n;j++){
			if(F[j]){
				if(F[j]->weight<F[k1]->weight){
					k2=k1;
					k1=j;
				}
				else if(F[j]->weight<F[k1]->weight) k2=j;	
			}
			HulfNode *pa=(HulfNode *)malloc(sizeof(HulfNode));
			pa->word='x';
			pa->left=F[k1];
			pa->right=F[k2];
			pa->weight=F[k1]->weight+F[k2]->weight;
			F[k1]=pa;
			F[k2]=NULL;	
		}	
	}
} 

int main(void)
{
	int n;
	cin>>n;
	HulfNode **F;
	F=(HulfNode **)malloc(n*sizeof(HulfNode *));
	for(int i=0;i<n;i++){
		F[i]->right=F[i]->left=NULL;
		cin>>F[i]->word>>F[i]->weight;
	}
}
