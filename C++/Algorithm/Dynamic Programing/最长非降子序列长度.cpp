#include <iostream>
using namespace std;

int lis(int A[], int n){
    int *p=new int[n];
    int len=1;
    for(int i=0;i<n;i++){
        p[i]=1;
        for(int j=0;j<i;j++){
            if(A[j]<=A[i]&&p[j]+1>p[i])
                p[i]=p[j]+1;
        }
        if(p[i]>len)
            len=p[i];
    }

    delete[] p;
    return len;
}
int main(){
    int A[] = {2, 3, 8, 4, 5, 7};
    cout<<lis(A, 6)<<endl;
    return 0;
}
