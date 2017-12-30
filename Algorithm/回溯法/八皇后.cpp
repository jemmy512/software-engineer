#include<iostream>
using namespace std;

int row[8]={0};
int col[8]={0};
int lef[15]={0};
int rig[15]={0};

void PrintQueen()
{
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(j==row[i])
                cout<<" O ";
            else
                cout<<" X ";
        }
        cout<<endl;

    }
    cout<<endl<<endl;
}

void Queen(int i)
{
    for(int j=0;j<8;j++){
        if(!col[j]&&!lef[i+j]&&!rig[i-j+7]){
            row[i]=j;
            col[j]=lef[i+j]=rig[i-j+7]=1;
            if(i<7) Queen(i+1);
            else PrintQueen();
            col[j]=lef[i+j]=rig[i-j+7]=0;
        }
    }

}

int main(void)
{
    Queen(0);

    return 0;
}
