/*
    二维数组每行递增，每类递增
    杨氏矩阵查找法
*/
#include<iostream>
using namespace std;

bool Find(int *a,int rows,int colums,int number)
{
    bool found=false;

    if(a!=NULL&&rows>0&&colums>=0){
        int row=0;
        int colum=colums-1;
        while(row<rows&&colum>=0){
            if(a[row*colums+colum]==number){
                found=true;
                break;
            }
            else if(a[row*colums+colum]>number)
                --colum;
            else
                ++row;
        }
    }
    return found;
}

int main(void)
{
    int cnt=1;
    int a[5][5];
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            a[i][j]=cnt++;
            cout<<a[i][j]<<"\t";
        }
        cout<<endl;
    }
    for(int i=0;i<35;i++){
        cout<<"result of Find("<<i<<") :"<<Find(&(a[0][0]),5,5,i)<<endl;
    }

    return 0;

}
