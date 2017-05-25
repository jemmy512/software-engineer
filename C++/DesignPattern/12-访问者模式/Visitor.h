#ifndef VISITOR_H
#define VISITOR_H
#include<vector>
using namespace std;

class LibraryVisitor;
class LibraryInterface{
	public:
		virtual void Accept(LibraryVisitor *lv)=0;
		virtual void Do()=0;
		virtual  ~LibraryInterface(){
			
		}
		
};

class LibraryVisitor{
	public:
		virtual void visit(LibraryInterface *pl)=0;
}; 

class Manager{
	private:
		vector<LibraryInterface *>vec;
	public:
		void Add(LibraryInterface *t);
		void Request(LibraryInterface *t);
};


#endif
