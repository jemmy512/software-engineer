#include<iostream>
#include<vector>
using namespace std;

void quick_sort(vector<int>& vec, int b, int e)
{

	int i,j,index;
	if(b>=e)
        return;
    i=b;
    j=e;
    index=vec[b];
	while(i<j){
        while(i<j&&vec[j]>=index)
            j--;
        if(i<j)
            vec[i++]=vec[j];
        while(i<j&&vec[i]<index)
            i++;
        if(i<j)
            vec[j--]=vec[i];
	}
	vec[i]=index;
	quick_sort(vec,b,i-1);
	quick_sort(vec,i+1,e);

}


int main(void)
{
	vector<int> ivec={3,2,5,8,4,7,6,9};
	vector<int> temp(8);

    quick_sort(ivec,0,7);
	for(auto a:ivec)
		cout<<a<<" ";
		return 0;
}
