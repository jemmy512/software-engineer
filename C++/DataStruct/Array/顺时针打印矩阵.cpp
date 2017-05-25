#include<iostream>
using namespace std;

int main(void)
{
    int arr[5][5]={1,2,3,4,5,
                   6,7,8,9,10,
                   11,12,13,14,15,
                   16,17,18,19,20,
                   21,22,23,24,25};

    int i=0;
    int j=0;
    for(int k=0;k<2;k++){
        while(j<=4-k){
            cout<<arr[i][j]<<" ";
            j++;
        }
        cout<<endl;
        while(i<=4-k){
            cout<<arr[i][j]<<" ";
            i++;
        }
        cout<<endl;
        while(j>=k){
            cout<<arr[i][j]<<" ";
            j--;
        }
        cout<<endl;
        while(i>=k){
            cout<<arr[i][j]<<" ";
            i--;
        }
        cout<<endl;

    }
    return 0;
}
