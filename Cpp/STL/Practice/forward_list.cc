#include<iostream>
#include<forward_list>
#include<iterator>

using namespace std;

int main(void) {
    
    forward_list<int> fwlist = {1, 2, 3};
    fwlist.insert_after(fwlist.before_begin(), 999); // iterator not support backward iterate
    
    for (auto iter = fwlist.begin(); iter != fwlist.end(); ++iter)
        cout << *iter << endl;
    
    return 0;
}