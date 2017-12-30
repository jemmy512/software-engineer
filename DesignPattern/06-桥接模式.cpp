#include<iostream>
using namespace std;

class Implementor {
public:
    virtual void operation()=0;
};

class ConcreateImplementor_A:public Implementor {
public:
    void operation() {
        cout<<"ConcreateImplementor_A..."<<endl;
    }
    ~ConcreateImplementor_A() {
    }

};

class ConcreateImplementor_B:public Implementor {
public:
    void operation() {
        cout<<"ConcreateImplementor_B...."<<endl;
    }
    ~ConcreateImplementor_B() {

    }
};

class Abstraction {
protected:
    Implementor *pi;
public:
    Abstraction() {

    }
    Abstraction(Implementor *pi) {
        this->pi=pi;
        cout<<"Abstraction 初始化。。。。"<<endl;
    }
    virtual void operation()=0;
    virtual ~Abstraction() {
        delete pi;
        cout<<"~Abxtraction.."<<endl;
    }

};

class RefindAbstraction_A:public Abstraction {
public:
    RefindAbstraction_A() {

    }
    RefindAbstraction_A(Implementor * pi):Abstraction(pi) {
        cout<<"RefindAbstrction_A 初始化..."<<endl;
    }
    void operation() {
        pi->operation();
        cout<<"RefindAbstrction_A..."<<endl;
    }
    ~RefindAbstraction_A() {
//			delete pi;
        cout<<"~RefindAbstrction_A.."<<endl;
    }
};

class RefindAbstraction_B:public Abstraction {
public:
    RefindAbstraction_B() {

    }
    RefindAbstraction_B(Implementor * pi):Abstraction(pi) {
        cout<<"RefindAbstrction_B 初始化..."<<endl;
    }
    void operation() {
        pi->operation();
        cout<<"RefindAbstrction_B..."<<endl;
    }
    ~RefindAbstraction_B() {
//			delete pi;
        cout<<"~RefindAbstrction_B.."<<endl;
    }
};

int main(void) {
    Abstraction* pa=new RefindAbstraction_A(new ConcreateImplementor_A());
    Abstraction* pb=new RefindAbstraction_B(new ConcreateImplementor_B());
    pb -> operation();
    pa -> operation();
    delete pb;
    delete pa;
    return 0;
}

