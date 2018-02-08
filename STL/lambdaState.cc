#include <iostream>
#include <list>
#include <algorithm>
#include<iterator>

using namespace std;

int main() {
    list<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    // remove third element
    list<int>::iterator pos;
    int count=0; // call counter
    /*
        lambda operator() is const function so we must mutable to modify the 
        captured data members.
    */
    pos = remove_if(coll.begin(),coll.end(), // range
        [&count] (int)  /*mutable*/ { // remove criterion
        return ++count == 3;
    });
    //coll.erase(pos,coll.end());

    cout << "3rd removed: " << endl;
    copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}