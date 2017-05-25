#include<iostream>
#include"Visitor.h"
#include<vector>
using namespace std;


class Book:public LibraryInterface{
	public:
		void Accept(LibraryVisitor *v){
			v->visit(this);
		}
		void Do(){
			cout<<"Book -Do()....."<<endl;
		}
		~Book(){
			cout<<"~Book()...."<<endl;
		}
};

class Artical:public LibraryInterface{
	public:
		void Accept(LibraryVisitor *v){
			v->visit(this);
		}
		void Do(){
			cout<<"Artical -Do()....."<<endl;
		}
		~Artical(){
			cout<<"~Artical()...."<<endl;
		}
};

class visitor:public LibraryVisitor{
	public:
		void visit(LibraryInterface *v){
			v->Do();
		}
		~visitor(){
			cout<<"~visitor()..........."<<endl;
		}
};

int main(void){
	visitor *v=new visitor();
	Book *b=new Book();
	b->Accept(v);
	return 0;
}
