#include<iostream>
using namespace std;
class Base{
	public:
		virtual void fun()=0;
		~Base(){
			
		}
};

class A:public Base{
	public:
		void fun(){
			cout<<"Derived A"<<endl;
		}
		~A(){
			cout<<"~A()"<<endl;
		}
};
class B:public Base{
	public:
		void fun(){
			cout<<"Derived B"<<endl;
		}
		~B(){
			cout<<"~B()"<<endl;
		}
};
class my{
	private:
		Base *sp;
	public:
		my(Base *sp=NULL){
			this->sp=sp;
		}
		void Do(){
			sp->fun();
		}
		~my(){
			delete sp;
		}
};


int main(void)
{
	my *m=new my(new B());
	m->Do();
	my *mi=new my(new A());
	mi->Do();
	
	return 0;
}

