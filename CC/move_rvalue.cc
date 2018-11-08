#include<iostream>

using namespace std;

class A {
public:
    A() {
        cout << "A()" << endl;
    }    

    ~A() {
        cout << "~A()" << endl;
    }
};

A f() {
    return A();
}

int main() {
    A &&x = f();
    cout << "~~~~~~" << endl;
}
