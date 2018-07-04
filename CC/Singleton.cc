/*
 * Created by Jemmy on 2018/7/4.
 *
 */
#include <iostream>
#include <pthread.h>

using namespace std;

template<typename T>
class Singleton {
public:
    static T &instance() {
        pthread_once(&ponce_, &Singleton::init);
        return *value_;
    }
private:
    Singleton();
    ~Singleton();

    static void init() {
        value_ = new T();
    }

    static pthread_once_t ponce_;
    static T *value_;
};

template<typename T>
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template<typename T>
T *Singleton<T>::value_ = NULL;

class FOO {
public:
    void out() {
        cout << "FOO..." << endl;
    }
};

int main() {
    FOO &f = Singleton<FOO>::instance();
    FOO &fo = Singleton<FOO>::instance();

    cout << &f << " : " << &fo << endl;
}

