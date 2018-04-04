#include<iostream>

using namespace std;

class Operate {
public:
    int a, b;
    Operate() {}
    Operate(int aa, int bb): a(aa), b(bb) {}
    virtual int getResult() = 0;
    virtual setFirst(int data) {
        this->a = data;
    }
    virtual setSecond(int data) {
        this->b = data;
    }
};

class AddOperate: public Operate {
public: 
    AddOperate() {}
    AddOperate(int aa, int bb): Operate(aa, bb) {}
    int getResult() {
        return a + b;
    }
};

class SubOperate: public Operate {
public:
    SubOperate() {}
    SubOperate(int aa, int bb): Operate(aa, bb) {}
    int getResult() {
        return a - b;
    }
};


class Factory {
public:
    virtual Operate *createOperate() = 0;
};

class FactoryAdd: public Factory {
public:
    Operate *createOperate() {
        return new AddOperate();
    }
};

class FactorySub: public Factory {
public:
     Operate *createOperate() {
         return new SubOperate();
     }
}; 

int main() {
    Factory *factory = new FactoryAdd();
    Operate *addOp = factory->createOperate();
    addOp->setFirst(4);
    addOp->setSecond(8);
    cout << "Add Op: " << addOp->getResult() << endl;
    delete factory;
    delete addOp;
    
    return 0;
}

