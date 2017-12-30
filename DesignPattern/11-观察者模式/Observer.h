#ifndef OBSERVER_H
#define OBSERVER_H

#include<iostream>
#include<vector>
using namespace std;

class Observer;


class Subject{
	protected:
		vector<Observer *>vec;
	public:
		void AddObserver(Observer *o){
			vec.push_back(o);
		}
		virtual void Notify()=0;
		virtual ~Subject(){

		}
};


class Observer{
	protected:
		Subject *sub;
	public:
		Observer(){

		}
		Observer(Subject *s){
			this->sub=s;
			sub->AddObserver(this);
		}
		virtual void Updata(int x,int y)=0;
		virtual ~Observer(){

		}
};


#endif





