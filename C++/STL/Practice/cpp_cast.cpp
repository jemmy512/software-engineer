#include<iostream>

using namespace std;

void cast(const int *a, const int &b) {
    int *aa = const_cast<int *>(a);
    int &bb = const_cast<int &>(b);
    
    cout << (*aa) << " " << ++bb << endl;
}

class Base {
public:
    Base (int aa = 10): a(aa) {}
    virtual void funA() {
        cout << "A" << endl;
    }
protected:
    int a;
};

class Derive: public Base {
public:
    Derive(int bb = 20): b(bb) {}
    void funA() {
        cout << "This is derive A" << endl;
    }
    void funB() {
        cout << "B" << endl;
    }
    void printAll() {
        cout << a << "<>" << b << endl;
    }
private:
    int b;
};

int main(void) {
    
    const int a = 10;
    int b = 20;
    cast(&a, b);
    
    Derive *base = new Derive();
    //Derive *derive = dynamic_cast<Derive *>(base);
    base->funB();
    base->funA();
    base->printAll();
    
    return 0;
}