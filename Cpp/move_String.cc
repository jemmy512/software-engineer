#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <vector>

using namespace std;

class String {
private:
    char* _str;

public:
    String();
    String(const char* cstr);
    String(const String& other);
    String& operator=(const String& other);
    String(String&& other);
    String& operator=(String&& other);
    String operator+(const String& other);
    int length() const;
    ~String();
    friend ostream& operator<<(ostream& s, const String& other);
};

String::String() {
    _str = new char[1];
    *_str = '\0';
}

String::String(const char* cstr) {
    _str = new char[strlen(cstr)+1];
    strcpy(_str, cstr);
}

String::String(const String& other) {
    cout << "copy constructor" << endl;
    _str = new char[other.length()+1];
    strcpy(_str, other._str);
}

String& String::operator=(const String& other) {
    cout << "copy assignment operator=" << endl;
    if (&other == this)
        return *this;
    delete [] _str;
    _str = new char[other.length() + 1];
    strcpy(_str, other._str);
    return *this;
}

String::String(String&& other) {
    cout << "move constructor" << endl;
    _str = other._str;
    other._str = nullptr;
}

String& String::operator=(String&& other) {
    cout << "move assignment operator=" << endl;
    if (&other == this)
        return *this;
    _str = other._str;
    other._str = nullptr;
    return *this;
}

String String::operator+(const String& other) {
    cout << "operator+" << endl;
    String tmp;
    delete tmp._str;
    tmp._str = new char[other.length() + this->length() + 1];
    strcpy(tmp._str, _str);
    strcat(tmp._str, other._str);
    return tmp;
}

int String::length() const {
    return (strlen(_str));
}

ostream& operator<<(ostream& s, const String& other) {
    return s << other._str;
}

String::~String() {
    delete _str;
}

String f(){
  String tmp("tmp");
  return tmp;
}

int main() {
String a("hello");
String b("world");
vector<String> v;
v.reserve(4);
cout << "~~~~~~~" << endl;
//v.push_back(a);               // copy constructor
//v.push_back(String("hi"));    // move constructor
//std::move(b);
//v.push_back(std::move(b));



// named rvalue is a lvalue, can't invoke move construcctor
String &&c = std::move(b);
//v.push_back(std::move(c));
v.push_back(std::forward<String>(c));
//v.push_back(std::move(b));




std::string &str = std::string("Hello") = std::string("hi");
cout << str << endl;
cout << a << endl;
// cout << b << endl;

}

