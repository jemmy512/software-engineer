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
			cout<<"Derived Base"<<endl;
		}
		virtual ~Base()
		{
			cout<<"~Base"<<endl;
			delete next;
		}
};
class A:public Base{
		public:
		A(Base *t):Base(t){}
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
		void fun()
		{
			cout<<"Derived B"<<endl;
		}
		~B()
		{
			cout<<"~B"<<endl;
		}
}; 
class Decorator:public Base{
	public:
		Decorator(Base *t):Base(t)	{ }
		virtual ~Decorator()
		{
			cout<<"~Decorator"<<endl;
		}
}; 
class D1:public Decorator{
		public:
		D1(Base *t):Decorator(t){}
		void fun()
		{
			cout<<"Derived D1"<<endl;
			Base::fun();
		}
		~D1()
		{
			cout<<"~D1"<<endl;
		}
};
class D2:public Decorator{
	public:
		D2(Base *t):Decorator(t)
		{}
		void fun()
		{
			cout<<"Derived D2"<<endl;
			Base::fun();
		}
		~D2()
		{
			cout<<"~D2"<<endl;
		}
};
class D3:public Decorator{
	public:
		D3(Base *t):Decorator(t)
		{}
		void fun()
		{
			cout<<"Derived D3"<<endl;
			Base::fun();
		}
		~D3()
		{
			cout<<"~D3"<<endl;
		}
};
class My{
	private:
		Decorator *d;
		Base *pbase;
	public:
		My(Decorator *t)
		{
			t=d;
		}
		void  Add()
		{
			d=new D3(NULL);
			d=new D2(d);
			d=new D1(d);
			pbase=new Decorator(d);
			pbase=new A(d);
		}
		void fun()
		{	
			cout<<"Derived My"<<endl;	
			pbase->fun();
		}
		~My()
		{
			cout<<"~My"<<endl;
			delete pbase;
			delete d;
		}
};
int main(void)
{
	Decorator *d=new D3(NULL);	
	My *my=new My(d);
	my->Add();
	my->fun();
	delete my;
//	Base *pbase;
//	pbase=new D3(NULL);
//	pbase=new D2(pbase);
//	pbase=new D1(pbase);
//	pbase=new A(pbase);
//	pbase->fun();
//	delete pbase;
	return 0;
 } 

