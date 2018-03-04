/*
*   overload new and delete operator
*   reference: https://kelvinh.github.io/blog/2014/04/19/research-on-operator-new-and-delete/
*       https://www.jianshu.com/p/4af119c44086
*       https://www.cnblogs.com/jkred369/p/8320734.html
*/

#include<iostream>
#include<string>

using namespace std;

class C {
public:
    C(int i = 0): data(i){}
    ~C() {
        cout << "destroucted..." << endl;
    }
    static void *operator new(size_t size, void *p, const string &str) {
        cout << "In our operator new: " << endl << "    " << str << endl;
        if (!p) {
            cout << "Hi man, are you aware what you are doing?" << endl;
            return ::operator new(size);
        }
        return p;
    }
    static void operator delete(void *p) {
        cout << "We should do nothing in operator delete" << endl;
        // program will crash if uncomment 
        // ::operator delete(p); // Q: why?
        // ::free(p);
    }
    void function() {
        cout << "Hello object, data: " << data << endl;
    }
private:
    int data;
};

int main(void) {
    char buf[sizeof(C)]; // allocate object in the stack
    // C *buf = (C *)malloc(sizeof(C));
    // char buf[sizeof(C) - 3]; // program crash
    C *pc = new (buf, "Yeah, I'm crazy")C(1024);
    pc->function();
    // We shouldn't call delete but we do nothing in our own operator delete, so it ok
    // global delete call destructor first and then call overload or global operator delete
    delete(pc);
}


/********         implementation of Clang
Category:
    new/delete/new[]/delete[] operator  // global, can not be overloaded
    operator new/delete/new[]/delete[]
    placement new/new[]                 // note: there are no placement delete/delete[]

Process of new and delete:
    new: call operator new malloc memory, call constructor construct object and return pointer
    delete: call destructor destruct object, free memory

void * operator new(std::size_t size) throw(std::bad_alloc) {
    if (size == 0)
        size = 1;
    void* p;
    while ((p = ::malloc(size)) == 0) {
        std::new_handler nh = std::get_new_handler();
        if (nh)
            nh();
        else
            throw std::bad_alloc();
    }
    return p;
}

void operator delete(void* ptr) {
    if (ptr)
        ::free(ptr);
}

*/