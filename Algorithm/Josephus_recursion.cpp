#include<iostream>
using namespace std;

void Josphus_Ring(int *Q,int n,int s)
{
	int frant=0,real=n;
	while(frant-real){
		for(int i=0;i<s-1;i++){//行走 s-1 步
			frant=(frant+1)%n;//每次前进一步，直到 s-1 步
			real=(real+1)%n; //real 同步前进
			Q[real]=Q[frant];//保存 frant 所走的每一步
		}
		frant=(frant+1)%n;// 走到第 s 步
		cout<<Q[frant]<<" "; //第 s 步输出
	}
 }

int main(void)
{
	int *Q;
	int n,s;
	cin>>n>>s;
	Q=(int *)malloc((n+1)*sizeof(int));
	for(int i=1;i<n+1;i++)
		Q[i]=i;
    Q[0]=n;// %n 只能得到0～n-1 的结果，Q[0]需要单独初始化
	Josphus_Ring(Q,n,s);
	return 0;
}
