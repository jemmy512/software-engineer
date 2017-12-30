#include<iostream>
using namespace std;
class MyClass{
	private:
		int x,y;
		static int z;
	public:
		MyClass(int x=0,int y=0)
		{
			this->x=x;
			this->y=y;
		}
		static void print(MyClass *t)
		{
			cout<<"z="<<z+t->x+t->y<<endl;
		}
		void out()
		{
			cout<<"x="<<x<<",y="<<y<<endl;
		}		
};
int MyClass::z=3;
int main(void)
{
	MyClass *pm=new MyClass(7,8);
	MyClass::print(pm);
	pm->out();
}
