#include<iostream>
#include<iomanip> // setw
#include<unordered_set>
#include<iterator>
#include<typeinfo>

using namespace std;


template<typename T>
void printfSet(const T &uset) {
    cout << "size: " << uset.size() << endl;
    cout << "bucket count: " << uset.bucket_count() << endl;
    cout << "bucket count max: " << uset.max_bucket_count() << endl;
    cout << "load factor: " << uset.load_factor() << endl;
    cout << "max load factor: " << uset.max_load_factor() << endl;
    
    if (typeid(typename iterator_traits<typename T::iterator>::iterator_category) ==
        typeid(bidirectional_iterator_tag)) {
        cout << "chianing style: " << "doubly-linked \n";
    } else {
        cout << "chianing style: " << "single-linked \n";     
    }
    
    cout << endl << "data: " << endl;
    for (int i = 0; i < uset.bucket_count(); ++i) {
        cout << "bucket[" << std::setw(2) << i << "]: ";
        for (auto pos = uset.cbegin(i); pos != uset.cend(i); ++pos) {
            cout << *pos << " ";
        }
        cout << endl;
    }
    
}

int main(void) {
    unordered_set<int> uset({1, 2, 3, 4, 5, 6, 7});
    uset.insert({-1, -2, -5, -8, -9});
    
    printfSet(uset);
    
    cout << endl << "unordered_set after rehash with 10 bucket: " << endl;
    uset.rehash(10);
    printfSet(uset);
    
    return  0;
}