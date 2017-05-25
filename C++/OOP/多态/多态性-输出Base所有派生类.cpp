#include<vector>
#include<iostream>
using namespace std;

class Base{
	public:
		virtual void fun()=0;
		~Base(){
			cout<<"~Base()"<<endl;	
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
		vector<Base *> obj;
	public:
		void add(Base * b){
			obj.push_back(b);
		}
		void Do(){
			for(auto it:obj)
				it->fun();//-> 优先级高于 * 
		}
		~my(){
			cout<<"~my()"<<endl;	
			for(auto it:obj){			//类内申明类内释放 
				delete it;
			}
				
		}
};
int main(void)
{
	my * m=new my();
	m->add(new A());
	m->add(new B());
	m->Do();
	delete m;
	return 0;
}

