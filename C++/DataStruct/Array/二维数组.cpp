#include<iostream>
using namespace std;

void Find(const int (&a)[4][4],int rows,int colums,int number){
	int row=0;
	bool found=false;
	
	int colum=colums-1;
	if(a!=NULL&&rows>0&&colums>0){
		while(row<rows&&colum>=0){
			if(a[row][colum]==number){
				found=true;
				cout<<"Congratulations,find number:"<<number<<endl;
				break;
			}
			else if(a[row][colum]>number)
					--colum;
				else 
					++row;
		}
	}
	if(!found)
		cout<<"Sorry.Not find!"<<endl;
}
int main(void)
{
	int a[4][4]={
		1,2,8,9,
		2,4,9,12,
		4,7,10,13,
		6,8,10,15
		};
		Find(a,4,4,9);
	return 0;
}

