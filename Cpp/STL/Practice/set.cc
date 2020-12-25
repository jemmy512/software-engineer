#include<iostream>
#include<set>
#include<algorithm>
#include<iterator>

using namespace std;

int main() {
    
    set<int, greater<int>> coll;
    coll.insert({4, 3, 1, 7, 8, 2, 6});
    
    for (auto elem : coll)
        cout << elem << " ";
    cout << endl;
    
    
    auto ret = coll.insert(5);
    if (ret.second) {
        cout << "4 inserted success: " << distance(coll.begin(), coll.end()) + 1 << endl;
    } else {
        cout << "4 already exited" << endl;
    }
    
    
    set<int, greater<int>> coll2(coll.begin(), coll.end());
    cout << "coll2: \n"; 
    copy(coll2.begin(), coll2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    
    coll2.erase(coll2.begin(), coll2.find(3));
    int rett = coll2.erase(5);
    cout << rett << " elements has been removed" << endl;
    copy(coll2.begin(), coll2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    
    return 0;
}