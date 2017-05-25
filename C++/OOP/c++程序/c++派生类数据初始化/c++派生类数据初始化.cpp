#include<Iostream>
using namespace std;
class A{
private:
	int x,y;
public:
	A(int x=0,int y=0)
	{
		this->x=x;
		this->y=y;
	}
	void out()
	{
		cout<<"x="<<x<<endl;
		cout<<"y="<<y<<endl;
	}
};
class B:public A{
	private:
		int z;
		A *pa; 
	public:
		B(int i):A(i-4,i-2)
		{
			pa=new A();
			z=i;
		}
		B()
		{
			z=0;
		}
		void out()
		{
			A::out();
			cout<<"z="<<z<<endl;
			pa->out();
		}
};
int main(void)
{
	B *pb1=new B(7);
	pb1->out();
}
