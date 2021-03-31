#include <cstdio>
#include <iostream>

using namespace std;

/******************************** Single Inheritance **************************/

class Base {
public:
    virtual void fun1() {
        cout << "Base::func1()" << endl;
    }

    virtual void fun2() {
        cout << "Base::func2()" << endl;
    }

private:
    int b;
};

class Derive :public Base {
public:
    virtual void fun1() override {
        cout << "Derive::func1()" << endl;
    }

    virtual void fun3() {
        cout << "Derive::func3()" << endl;
    }

    void fun4() {
        cout << "Derive::func4()" << endl;
    }

private:
    int d;
};

typedef void (*FUNC)();
void PrintVTable(int* vTable)  // print virutal function table
{
    if (vTable == NULL) {
        return;
    }
    cout << "V_Table Addr:" << vTable << endl;

    for (int  i = 0; vTable[i] != 0; ++i) {
        printf(" %dth virutal function: 0X%x -> ", i, vTable[i]);
        FUNC f = (FUNC)vTable[i];
        f();         // invoke virtual function
    }
    cout << endl;
}

void Test1()
{
    Base b;
    Derive d;
    int* tmp = (int*)(*(int*)&b);     // get vptr addr
    PrintVTable(tmp);

    int* tmp1 = (int*)(*(int*)&d);
    PrintVTable(tmp1);
}

/******************************** Multiple Inheritance ************************/

/******************************** Virual Inheritance **************************/

int main() {
/* 1. Taking the address of a `nonstatic member function` yields its `address` in memory.
 * 2. Taking the address of a `virtual member function` yields its `index` into it's associated virtual table.
 * So, C++ can imeplement po like:
 * (((int)pmf) & ~127)
    ? (pmf)(ptr)                  // non-virtual invocation
    : (ptr->vptr[(int)pmf](ptr)); // virtual invocation */
    printf("%d\n", &Derive::fun1); // 1
    printf("%d\n", &Derive::fun2); // 9
    printf("%d\n", &Derive::fun3); // 17
    printf("%d\n", &Derive::fun4); // 4198368

    Test1();
}