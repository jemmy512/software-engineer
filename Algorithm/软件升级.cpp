#include<iostream>
#include<limits.h>
#include<vector>
using namespace std;

typedef struct {
    int beg;
    int end;
    int val;
}Data;


/*

1000 1050
6
1000 1020 50
1000 1030 70
1020 1030 15
1020 1040 30
1030 1050 40
1040 1050 20

*/



vector<int> vecc;
int sizeE=INT_MAX;

void pa(vector<Data> vec,int b,int e,int n,int& size,vector<int>& result)
{

    for(int i=0;i<n;i++){
        if(vec[i].beg==b&&vec[i].end==e&&size<sizeE){
            cout<<"3 ";
            size+=vec[i].val;
            result.push_back(i);

            vecc.clear();
            vecc.assign(result.begin(),result.end());
            sizeE=size;


            result.pop_back();
            size-=vec[i].val;
        }

        else if(vec[i].beg==b){
            cout<<"2 ";
            result.push_back(i);
            size+=vec[i].val;

            pa(vec,vec[i].end,e,n,size,result);

            result.pop_back();
            size-=vec[i].val;
        }
    }
}

void path(vector<Data> vec,int b,int e,int n,int& size,vector<int>& result)
{
    for(int i=0;i<n;i++){
        if(vec[i].beg==b){
            cout<<"1 ";
            size+=vec[i].val;
            result.push_back(i);

            pa(vec,b,e,n,size,result);

            size-=vec[i].val;
            result.pop_back();
        }
    }
}


int main(void)
{

    vector<Data> vec;
    int a,b,n;
    cin>>a>>b>>n;
    vector<int> result;
    for(int i=0;i<n;i++){
        Data d;
        cin>>d.beg>>d.end>>d.val;
        vec.push_back(d);
    }

    int size=0;

    path(vec,a,b,n,size,result);

    for(auto d:vecc){
        cout<<vec[d].beg<<"->";
    }
    cout<<sizeE;

    return 0;
}
