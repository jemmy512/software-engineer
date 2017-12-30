#include<iostream>
#include<vector>
using namespace std;

class Observer;
class Subject{
	public:
		virtual void Add(Observer *)=0;
		virtual void Notify()=0;
}; 

class ConcreatSubject_A:public Subject{
	private:
		int x,y;
		vector<Observer *>vec;
	public :
		ConcreatSubject(){
			x=0;
			y=0;
		}
		ConcreatSubject(int x,int y){
			this->x=x;
			this->y=y;
		}
		void Add(Observer *t){
			vec.push_back(t);
		}
		void Notify(){
			vector<Observer *>::iterator it;
			for(it=vec.begin();it<vec.end();it++){
				(*it)->updata(x,y);
			}
		}
		void DataChange(int x,int y){
			this->x=x;
			this->y=y;
			Notify();
		} 
};

class Observer{
	protected:
		Subject *s;
	public:
		Observer(Subject *t){
			this->s=t;
			this->s->Add(this);
		}
		virtual void updata(int x,int y)=0;
		
};

class ConcreatObserver:public Observer{
	private:
		int x,y;
	public:
		ConcreatObserver(Subject *t):Observer(t){
			
		}
		void updata(int x,int y){
			this->x=x;
			this->y=y;
		}
};


