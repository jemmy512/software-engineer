#include<iostream>
using namespace std;

class Base{
	private:
		Base *next;
	public:
		Base(Base *p):next(p){
			cout<<"Base()--构造--"<<endl;
		}
		virtual void fun(){
			if(next)
				next->fun();
		}
		virtual ~Base(){
			delete next;
		}
};

class Product_A:public Base{
	public :
		Product_A(Base *p):Base(p){
			cout<<"Prodcut_A()--构造--"<<endl;
		}
		void fun(){
			cout<<"Product_A........"<<endl;
			Base::fun();
			cout<<"Product_A++++"<<endl;
		}
		~Product_A(){
			cout<<"~Product_A_____________"<<endl;
		}
};


class Decorator:public Base{
	public :
		Decorator(Base *p):Base(p) {
			cout<<"Decorator()--构造--"<<endl;
		}
		virtual void fun()=0;
		virtual ~Decorator(){}
};

class Decorator_A:public Decorator{
	public:
		Decorator_A(Base *p):Decorator(p){
			cout<<"Decorator_A()--构造--"<<endl;
		}
		void fun(){
			cout<<"Decoratror_A......................."<<endl;
			Base::fun();
			cout<<"Decorator_A++++"<<endl;
		}
		~Decorator_A(){
			cout<<"~Deocrator__A__________"<<endl;
		}
};

class Decorator_B:public Decorator{
	public:
		Decorator_B(Base *p):Decorator(p){
			cout<<"Decorator_B()--构造--"<<endl;
		}
		void fun(){
			cout<<"Decoratror_B......................."<<endl;
			Base::fun();
			cout<<"Decorator_B++++"<<endl;
		}
		~Decorator_B(){
			cout<<"~Deocrator__B__________"<<endl;
		}
};

int main(void){
	Base * head=NULL;
	head=new Decorator_B(head);
	head=new Decorator_A(head);
	head=new Product_A(head);
	head->fun();
	delete head;
}
