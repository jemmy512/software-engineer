/*

   一；组合通信
   		单一通信
		指针通信
		多对象通信（集合列表通信）

	二：继承通信

*/
#include<iostream>
#include<vector>
using namespace std;

class A{
	private :
		int x,y;
	public :
		A(int x=0,int y=0){
			this->x=x;
			this->y=y;
		}
		void out(){
			cout<<"A:"<<x<<" "<<y<<endl;
		}
		~A(){
			cout<<"~A()"<<endl;
		}
};
class B:public A{
	private :
		int z;
	public:
		B(int z=0):A(z+1,z+2){
			this->z=z;
		}
		void out(){
			A::out();
			cout<<"B:"<<z<<endl;
		}
		~B(){
			cout<<"~B()"<<endl;
		}
};

int main(void){
	B b(6);
	b.out();
	return 0;
}
