#include<list>
#include<iostream>
#include<algorithm>
#include<iterator>

using namespace std;

void printList(const list<int> &l1, const list<int> &l2) {
    cout << endl << "list 1: ";
    copy(l1.cbegin(), l1.cend(), ostream_iterator<int>(cout, " "));
    cout << endl << "list 2: ";
    copy(l2.cbegin(), l2.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

int main(void) {
    
    list<int> list1, list2;
    
    for (int i = 0; i < 5; ++i) {
        list1.push_back(i);
        list2.push_front(i);
    }
    printList(list1, list2);
    
    list2.splice(find(list2.begin(), list2.end(), 3), list1); // can not use cbegin()
    printList(list1, list2);
    
    list2.sort();
    printList(list1, list2);
    
    list2.unique();
    printList(list1, list2);
    
    return 0;
}