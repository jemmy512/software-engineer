#include<iostream>

using namespace std;

class Base {
public:
    virtual void method() = 0;
    virtual ~Base() {}
};

class Source: public Base {
public:
    Source() {}
    void method() {
        cout << "Hi, this source" << endl;
    }
};

class Proxy: public Base {
public:
    Base *base;
    Proxy() {}
    Proxy(Base *b): base(b) {}
    void method() {
        cout << "I'm Proxy:" << endl;
        base->method();
    }
    virtual ~Proxy() {
        delete base;
    }
};

int main() {
    Source *src = new Source();
    Proxy *proxy = new Proxy(src);
    proxy->method();
    
    delete proxy;
    
    return 0;
}