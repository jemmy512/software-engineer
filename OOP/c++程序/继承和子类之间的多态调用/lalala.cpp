#include<iostream>
using namespace std;
class Base{
	public:
		virtual void fun()=0;
		virtual ~Base(){}
};
class A :public Base{
	public:
		void fun()
		{
			cout<<"Derived A"<<endl;
		}
};
class B:public Base{
	private:
		int z;
	public:
		B(int z=0)
		{
			this->z=z;
		}
		void fun(){
			cout<<"Derived B"<<endl;
		}
};
class C:public Base{
	public:
		void fun(){
			cout<<"Derived C"<<endl;
		}
};
class My{
	private:
		Base *p;
	public:
		My(Base *t)
		{
			p=t;
		}
		void fun()
		{
			p->fun();
		}
};
int main (void)
{
	My *my=new My(new B());
	my->fun();	
	return 0;
}
