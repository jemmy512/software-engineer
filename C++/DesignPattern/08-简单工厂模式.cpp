#include<iostream>
using namespace std;

class Product{
	public:
		virtual void Do()=0;
		virtual ~Product(){
			
		}
}; 

class P_A:public Product{
	public:
		void Do(){
			cout<<"P_A......."<<endl;
		}
		~P_A(){
			cout<<"~P_A"<<endl;
		}
};

class P_B:public Product{
	public:
		void Do(){
			cout<<"P_B......."<<endl;
		}
		~P_B(){
			cout<<"~P_B"<<endl;
		}
};

class Factory{
	private:
		Product *pro;
	public:
		Factory(int n){
			switch(n){
				case 1:pro=new P_A();break;
				case 2:pro=new P_B();break;
			}
		} 
		void send(){
			pro->Do();
		}
		~Factory(){
			cout<<"~Factory"<<endl;
			delete pro;
		}
};

int main(void){
	Factory *Fac=new Factory(2);
	Fac->send();
	delete Fac;
	return 0; 
}
