#include<iostream>
using namespace std;

typedef struct {
	char word;
	int weight;
	int left;
	int right;
	int parents;
	int *code;
}HulfTree;

void CreatHulfTree(HulfTree *F,int n){
	int i,k1,k2;
	for(int loop=0;loop<n-1;loop++){
		for(k1=0;k1<n+loop&&F[k1].parents!=-1;k1++);//查找第一个可用结点
		for(k2=k1+1;k2<n+loop&&F[k2].parents!=-1;k2++);//查找第二个可用结点
		for(i=0;i<n+loop;i++){
            if(F[i].parents==-1){
                if(F[i].weight<F[k1].weight){
                    k2=k1;
                    k1=i;
                }
                else if(F[i].weight==F[k1].weight){}
                else if(F[i].weight<F[k2].weight){
                    k2=i;
                }
            }

		}

		F[i].word='X';//当上一个循环结束后，i ++ 的了 n+loop;
		F[i].left=k1;
		F[i].right=k2;
		F[i].parents=-1;
		F[i].code=NULL;
		F[i].weight=F[k1].weight+F[k2].weight;
		F[k1].parents=F[k2].parents=i;
	}

}

void HulfTreeCode(HulfTree *F,int n){
	for(int i=0;i<n;i++){
		F[i].code=(int *)malloc(n*sizeof(int));
		F[i].code[0]=0;
		int c=i;
		while(F[c].parents!=-1){
			int p=F[c].parents;
			if(F[p].left==c) F[i].code[++F[i].code[0]]=0;
			else  F[i].code[++F[i].code[0]]=1;
			c=p;
		}
	}
}

void PrintHulfTree(HulfTree *F,int n){
	for(int i=0;i<n;i++){
		cout<<F[i].word<<" 的编码为：";
		for(int j=F[i].code[0];j>0;j--){
			cout<<F[i].code[j]<<" ";
		}
		cout<<endl;
	}
}
int main(void)
{
	int n;
	cin>>n;
	HulfTree *F;
	F=(HulfTree *)malloc((2*n-1)*sizeof(HulfTree));
	for(int i=0;i<n;i++){
		fflush(stdin);//刷新缓存
		cin>>F[i].word>>F[i].weight;
		F[i].left=F[i].right=F[i].parents=-1;
		F[i].code=NULL;
	}
	CreatHulfTree(F,n);
	HulfTreeCode(F,n);
	PrintHulfTree(F,n);
	return 0;
}
/*
4
A 9
B 2
C 4
D 7

8
A 3
B 2
C 5
D 8
E 4
F 7
G 6
H 9
*/

