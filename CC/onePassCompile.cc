/*
 * Created by Jemmy on 2018/7/4.
 *
 * C++ follows the one pass compile model of C which means the result
 * of function bar() follows with foo(int) or follows with foo(char) will
 * be different
 */

#include <iostream>

using namespace std;

/* use forward declaration we can get unified result */
//void foo(int);
//void foo(char);

void foo(int a) {
    cout << "foo(int)" << endl;
}

void bar() {
    foo('a');
}

void foo(char c) {
    cout << "foo(char)" << endl;
}


int main() {
    bar();  /* foo(int) */
}