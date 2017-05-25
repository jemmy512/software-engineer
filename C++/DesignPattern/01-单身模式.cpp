#include<iostream>
using namespace std;

class Myclass{
	private:
		int x,y;
		static Myclass *Instance;
		Myclass(int x=0,int y=0){
			this->x=x;
			this->y=y;
		}
	public :
		static Myclass * My(int x,int y){
			if(!Instance){
				Instance=new Myclass(x,y);
			}
			return Instance;
		}
		void out(){
			cout<<"X="<<x<<" "<<"Y="<<y<<endl;
		}
};

Myclass * Myclass::Instance=NULL; 

int main(void){
	Myclass *p,*m,*n;
	p=Myclass::My(8,7);
	m=Myclass::My(5,6);
	n=Myclass::My(5,7);
	p->out();
	m->out();
	n->out();
	cout<<p<<endl<<m<<endl<<n<<endl; 
	return 0;
}
