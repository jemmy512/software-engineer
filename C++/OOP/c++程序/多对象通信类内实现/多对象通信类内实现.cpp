#include<iostream>
#include<vector>
using namespace std;
class A{
	private:
		int x;
	public:
		A(int x=0){
			this->x=x;
		}
		void Do(){ 
			cout<<"x="<<x<<endl;
		}
		~A(){
			
		}
};
class B{
private:
	vector <A*> objv;
public:
	void Add(A*t)
	{
		objv.push_back(t);
	}
	void show()
	{
		vector<A*>::iterator it;
		it=objv.begin();
		while(it!=objv.end());
		{
			(*it)->Do();
			it++; 
		}
	}
};
int main(void)
{
	A*pa1=new A(3);
	A*pa2=new A(5);
	A*pa3=new A(7);
	B*pb=new B();
	pb->Add(pa3);
	pb->Add(pa2);
	pb->Add(pa1);
	pb->show();
	delete pa1;
	delete pa2;
	delete pa3;
	delete pb;
}
