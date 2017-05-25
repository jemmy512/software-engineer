#include<iostream>
using namespace std;

int main(void)
{
    int min[12];
    for(int i=0;i<12;i++)
        min[i]=56789;
    min[0]=0;
    int yb[3]={1,3,5};
    for(int i=1;i<12;i++){
        cout<<i<<"元硬币：";
        for(int j=0;j<3;j++){
            if(j<=i&&min[i-yb[j]]+1<min[i]){
                min[i]=min[i-yb[j]]+1;
                cout<<yb[j]<<"\t";
            }

        }
         cout<<"  最少为 "<<min[i]<<endl;
    }

    return 0;
}
