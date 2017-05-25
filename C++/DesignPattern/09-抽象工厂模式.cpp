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

class Factory:public  Product{
	
};
