//将现有的方法或功能功过第三方类实现
#include<iostream> 
using namespace std;

class Adapter{
	public:
		void fun(){
			cout<<"Adapter......"<<endl;
		}
		~Adapter(){
			
		}
};

class Base{
	public:
		virtual void fun(){}
		virtual ~Base(){}
};

class D1:public Base{
	public:
		void fun(){
			cout<<"D1...."<<endl;
		}
		~D1(){
			cout<<"~D1......"<<endl;
		}
};

class D2:public Base{
	public:
		void fun(){
			cout<<"D2...."<<endl;
		}
		~D2(){
			cout<<"~D2......"<<endl;
		}
};

class Adaptee:public Base{
	private:
		Adapter *ap;	
	public:
		Adaptee():Base(),ap(new Adapter){
			
		};
		void fun(){
			ap->fun();
			cout<<"Adaptee...."<<endl;
		}
		~Adaptee(){
			delete ap;
			cout<<"~Adapter......"<<endl;
			cout<<"~Adaptee......"<<endl;
		}
};



int main(void){
	Base *pb=new Adaptee();
	pb->fun();
	delete pb;
	return 0;
}


