#include<iostream>
using namespace std;

class Base{
	public:
		virtual void method()=0;
		virtual ~Base(){

		}
};

class source:public Base{
	public:
		void method(){
			cout<<"source..."<<endl;
		}
		~source(){

		}
};

class proxy:public Base{
	private:
		Base *pb;
	public:
		proxy(){

		}
		proxy(Base *pb){
			this->pb=pb;

		}
		void method(){
			pb->method();
			cout<<"proxy.."<<endl;
		}
		~proxy(){
			delete pb;
		}
};


int main(void){
	proxy *pp=new proxy(new source());
	pp->method();
	delete pp;
	return 0;
}
