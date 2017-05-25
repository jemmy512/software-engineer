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
	private:
		int x;
	public:
		A(int x=0){
			this->x=x;
		} 
	void fun(){
		cout<<x<<endl;
	}
}; 

class B{
	private:
		vector<A> obj;
	public:
		void Add(A a){
			obj.push_back(a);
		}
		void out(){
			for(auto c:obj){
				c.fun();
			}
		}
};
int main(void)
{
	class B b;
	for(int i=0;i<5;i++){
		b.Add(A(i));
	}
	b.out();
	return 0;
}

