#include<iostream>
#include<string>

using namespace std;

class Base {
  
public:
    Base() {}
    Base(int i) {
       
    }
    static const int a;
    static constexpr float name  = 3.25;
private:
  
};

int const Base::a = 20;

int main(void) {
    Base base;
    cout << base.a << endl;
    cout << base.name << endl;
    return 0;
}