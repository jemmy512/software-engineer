#include<iostream>
using namespace std;
class A{
	public:
	virtual void fun()=0;
	virtual ~A()
	{
		cout<<"~A"<<endl;	
	}
};
class A1:public A{
	public:
		void fun()
		{
			cout<<"Derived A1"<<endl;
		}
};
class A2:public A{
	public:
		void fun()
		{
			cout<<"Derived A2"<<endl;
		}
};
class A3:public A{
	public:
		void fun()
		{
			cout<<"Derived A3"<<endl;
		}
};
class B{
	public:
	virtual void fun()=0;
	virtual ~B()
	{
		cout<<"~B"<<endl;	
	}
};
class B1:public B{
	public:
		void fun()
		{
			cout<<"Derived B1"<<endl;
		}
};
class B2:public A{
	public:
		void fun()
		{
			cout<<"Derived B2"<<endl;
		}
};
class My{
	protected:
		A *pa;
		B *pb;
	public:
		My(A *a,B *b)
		{
			pa=a;
			pb=b;
		}
	 	virtual	void Do()
		{
			pa->fun();
			pb->fun();
			cout<<"Derived My"<<endl;
		}
		virtual ~My()
		{
			cout<<"~My"<<endl;
		}
};
class My1:public My{
	public:
		My1(A *a,B *b):My(a,b)
		{}

		~My1()
		{
			cout<<"~My1"<<endl;
		}
}; 
class My2:public My{
	public:
		My2(A *a,B *b):My(a,b)
		{}

		~My2()
		{
			cout<<"~My2"<<endl;
		}
}; 
int main(void)
{
	A2 *a2=new A2();
	B1 *b1=new B1();
	My1 *my=new My1(a2,b1);
	my->Do();
	delete a2;
	delete b1;
	delete my; 
	
}
