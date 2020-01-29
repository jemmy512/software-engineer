#include<iostream>

using namespace std;

void foo(int &x) {
    cout << "lvalue: x = " << x << endl;
}

void foo(const int &x) {
    cout << "const lvalue: x = " << x << endl;
}

void foo(int &&x) {
    cout << "rvalue: x = " << x << endl;
}

template<typename T> 
typename remove_reference<T>::type&& __move(T&& param) {
    using ReturnType = typename remove_reference<T>::type&&;
    return static_cast<ReturnType>(param);
}

// C++14 only; still in namespace std
template<typename T> 
decltype(auto) _move(T&& param) {
    using ReturnType = remove_reference_t<T>&&;
    return static_cast<ReturnType>(param); 
}


int main() {
    int i = 1;
    const int ci = 2;

    foo(i);         // foo(int &x)
    foo(ci);        // foo(const int &x)
    foo(3);         // foo(int &&x)
    foo(std::move(i));  // foo(int &&x)

    int &&x = 8;    // x itself a lvalue, it binds to a rvalue
    foo(x);         // foo(int &x), named rvalue is a lvalue. 
    foo(__move(x)); // foo(int &&x)

}
