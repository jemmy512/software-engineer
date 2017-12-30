#include<iostream>
#include<vector>
using namespace std;

int main(void)
{
	vector<int> obj;
	int x=10;
	obj.push_back(x);
	for(int i=0;i<3;i++)
	{
		obj.push_back(i*x);
	}
	vector<int>::iterator it;
	it=obj.begin();
	while(it!=obj.end())
	{
		cout<<*it<<endl;
		it++;
	}

}
