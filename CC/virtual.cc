#include<iostream>
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
    virtual void fun1()           //
    {
        cout << "Derive::func1()" << endl;
    }

    virtual void fun3() {
        cout << "Derive::func3()" << endl;
    }
    void fun4()
    {
        cout << "Derive::func4()" << endl;
    }
private:
    int d;
};

typedef void (*FUNC)();        //
void PrintVTable(int* vTable)  // print virutal function table
{
    if (vTable == NULL)
    {
        return;
    }
    cout << "V_Table Addr:" << vTable << endl;
    int  i = 0;
    for (; vTable[i] != 0; ++i)
    {
        printf(" %dth virutal function: 0X%x,->", i, vTable[i]);
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
    Test1();
}