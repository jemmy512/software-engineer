#include<iostream>
#include<vector>
using namespace std;
class Base{
	public:
		virtual void fun()=0;
		virtual ~Base()
		{
			cout<<"~Base"<<endl;
		}
};
class A:public Base{
	public:
		void fun()
		{
			cout<<"Derived A"<<endl;
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
class C:public Base{
	public:
		void fun()
		{
			cout<<"Derived C"<<endl;
		}
		~C()
		{
			cout<<"~C"<<endl;
		}
};
class My{
	private:
		vector<Base *>obj;
	public:
		void Add(Base *t)
		{
			obj.push_back(t);
		}
		void Do()
		{
			vector<Base *>::iterator it;
			it=obj.begin();
			while(it!=obj.end())
			{
				(*it)->fun();
				it++;
			}
		}
		~ My()
		{
			cout<<"~My"<<endl;
		}
};
int main(void)
{
	A*a=new A();
	B*b=new B();
	C*c=new C();
	My *my=new My();
	my->Add(a);
	my->Add(b);
	my->Add(c);
	my->Do();
	delete my;
	delete a;
	delete b;
	delete c;
	return 0;
}
