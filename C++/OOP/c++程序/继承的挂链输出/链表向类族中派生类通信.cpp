#include<iostream>
using namespace std;
class Base{
	protected:
		Base *next;
	public:
		Base(Base *t)
		{
			next=t;
		}
		virtual void fun()
		{
			if(next)
				next->fun();
		}
		virtual ~Base()
		{
			cout<<"~Base"<<endl;
			delete next;
		}
};
class A:public Base{
	public:
		A(Base *t):Base(t)
		{}
		void fun()
		{
			cout<<"Derived A"<<endl;
			Base::fun();
		}
		~A()
		{
			cout<<"~A"<<endl;
		}
};
class B:public Base{
	public:
		B(Base *t):Base(t)
		{}
		void fun()
		{
			cout<<"Derived B"<<endl;
			Base::fun();
		}
		~B()
		{
			cout<<"~B"<<endl;
		}
};
class C:public Base{
	public:
		C(Base *t):Base(t)
		{}
		void fun()
		{
			cout<<"Derived C"<<endl;
			Base::fun();
		}
		~C()
		{
			cout<<"~C"<<endl;
		}
};
class My{
	private:
		Base *pbase;
	public:
		My(Base *t)
		{
			pbase=t;
		}
		void Add()
		{
			pbase=new B(pbase);
			pbase=new A(pbase);
		}
		void fun()
		{
			
			pbase->fun();	
		}
		~My()
		{
			cout<<"~My"<<endl;
			delete pbase;
		}
		
}; 
int main (void)
{
	Base*pbase=new C(NULL);
	My *my=new My(pbase);
	my->Add();
	my->fun();

	delete my;
	/*Base *pbase;
	pbase=new C(NULL);
	pbase=new B(pbase);
	pbase=new A(pbase);
	pbase->fun();
	delete pbase;*/
	return 0;
}
