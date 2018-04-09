#include<iostream>

using namespace std;

class AbstractClass {
public:
    virtual void primitiveOperation1() = 0;
    virtual void primitiveOperation2() = 0;
    void TemplateMethod() {
        primitiveOperation1();
        primitiveOperation2();
    }
};

class ConcreteClass: public AbstractClass {
public:
    void primitiveOperation1() {
        cout << "1" << endl;
    }
    
    void primitiveOperation2() {
        cout << "2" << endl;
    }
};

int main() {
    AbstractClass *method = new ConcreteClass();
    method->TemplateMethod();
}