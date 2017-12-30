#include<iostream>
#include<vector>
#include"Observer.h"
using namespace std;


class concreatSubject_A:public Subject{
	private:
		int x,y;
	public:
		void Notify(){
			for(auto c:vec)
				c->Updata(x,y);
		}
		concreatSubject_A(int x,int y){
			this->x=x;
			this->y=y;
			Notify();
		}

		void DataChange(int x,int y){
			this->x=x;
			this->y =y;
			Notify();
		}
		~concreatSubject_A(){

		}
};


class concreatObserver_A:public Observer{
	private:
		int x,y;
	public:
//		concreatObserver_A(){
//			this->x=0;
//			this->y=0;
//		}
		concreatObserver_A(int x  = 0,int y = 0){
			this->x=x;
			this->y=y;
		}
		concreatObserver_A(Subject *t):Observer(t){ }

		void Updata(int x,int y){
			this->x=x;
			this->y=y;
		}
		void get(){
			cout<<x<<"   "<<y<<endl;
		}
		~concreatObserver_A(){
			delete sub;
		}
};

int main(void){

	concreatSubject_A *s=new concreatSubject_A(2,3);
	concreatObserver_A *ob1=new concreatObserver_A(s);
	s->DataChange(4,3);
	ob1->get();
	return 0;
}






