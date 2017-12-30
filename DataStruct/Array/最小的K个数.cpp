#include<iostream>
#include<set>
#include<vector>
using namespace std;

typedef multiset<int,greater<int>> intSet;
typedef multiset<int,greater<int>>::iterator setIterator;

void GetLeastNumbers(vector<int>& data,intSet& leastNumbers,int k)
{
    if(data.size()<k||k<1||data.size()){
        cout<<"Invalid input"<<endl;
        return ;
    }

    vector<int>::const_iterator iter=data.begin();
    for(;iter<data.end();iter++){
        if(leastNumbers.size()<k)
            leastNumbers.insert(*iter);
        else{
            setIterator IterGreat=leastNumbers.begin();
            if(*iter<*(leastNumbers.begin())){
                leastNumbers.erase(IterGreat);
                leastNumbers.insert(*iter);
            }
        }
    }
}

int main(void)
{
    int a[8]={3,2,5,8,4,7,6,9};
    vector<int> data;
    for(int i=0;i<8;i++)
        data.push_back(a[i]);

    intSet mySet;
    GetLeastNumbers(data,mySet,10);

    for(auto c:mySet){
        cout<<c<<" ";
    }
}
