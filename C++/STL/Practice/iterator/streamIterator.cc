#include<iostream>
#include<string>
#include<algorithm>
#include<iterator>

using namespace std;

int main(void) {
    cout << "usage: \"end\" to end program\n" << endl;
    
    istream_iterator<string> is(cin);
    ostream_iterator<string> os(cout, " ");
    
    while (is != istream_iterator<string>()) {
        if (*is == "end")
            break;
        if (is != istream_iterator<string>())
            *os++ = *is++;
    } 
    cout << endl;
    
    
    return 0;
}