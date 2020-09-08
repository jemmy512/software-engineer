#include<stdio.h>
#include<stdlib.h>
#define v 10
typedef struct {//定义物品结构体 
	int gno,gv;
}Goods;
typedef struct gnode{//定义物品结点结构体 
	int gno;
	struct gnode *link;
}Gnode;
typedef struct bnode{//定义箱子结点结构体 
	int remainder;
	Gnode *hg;
	struct bnode *next;
}Bnode;
void SortD(Goods *g,int n)//输入数据降序排序 
{
	int i,j;
	Goods t;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(g[i].gv>g[j].gv){
				t=g[i];
				g[i]=g[j];
				g[j]=t;
			}
		}
	}
 } 
Bnode *CreatBnode(Goods *g,int n)
{
 	int i;
 	Bnode *hbox,*tb,*p;
 	Gnode *tg,*pg;
 	hbox=NULL;
	 
	 for(i=0;i<n;i++){
 		
	 	pg=tg=(Gnode *)malloc(sizeof(Gnode));//创建0～n物品结点 
		pg->gno=g[i].gno;
		pg->link=NULL;
	
		for(p=hbox;p&&p->remainder<g[i].gv;p=p->next);//寻找插入点 
		if(!p){
 			p=(Bnode *)malloc(sizeof(Bnode));
 			p->remainder=v;
 			p->hg=pg;
			p->next=NULL;
			if(!hbox)	hbox=tb=p;	
			else tb=tb->next=p;
		}
		else {
			for(tg=p->hg;tg->link;tg=tg->link);
			tg->link=pg; 
		 }
		p->remainder-=g[i].gv; 			
	}
	return hbox;
 }
 int main(void)
 {
	int i,n,x;
	Goods *g;
	Gnode *G;
	Bnode *B,*c;
	printf("请输入物品个数n,以及其体积：\n");
	scanf("%d",&n);
	g=(Goods *)malloc(n*sizeof(Goods));
	for(i=0;i<n;i++){
		g[i].gno=i+1;
		scanf("%d",&g[i].gv);
	}
	SortD(g,n);
	for(i=0;i<n;i++) printf("%5d%5d\n",g[i].gno,g[i].gv);
	B=CreatBnode(g,n);
	i=0;
	for(c=B;c;c=c->next){
		printf("第%d个箱子：",++i);
		for(G=c->hg;G;G=G->link) printf("%3d",G->gno);
		printf("\n");
	} 
	return 0;
 }
