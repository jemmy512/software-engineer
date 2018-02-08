#include<iostream>
#include<unordered_set>
#include<numeric>
#include<iterator>
#include<algorithm>
#include<functional>

using namespace std;

int main(void) {
    
    unordered_set<int> coll2 = {1, 2, 3, 4, 5, 6, 7, 8};
    
    unordered_set<int> coll(coll2);
    
    cout << "coll created:" << endl;
    copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    
    coll.insert({-1, -3, -4, -6, -7});
    
    cout << "coll insert negative values: " << endl;
    copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    
    unordered_set<int>::iterator pos;
    for (pos = coll.begin(); pos != coll.end(); ) {
        if (*pos < 0) 
            coll.erase(pos); // return following position
        else 
            ++pos;
    }
    coll.insert(accumulate(coll.begin(), coll.end(), 0));
    
    cout << "coll erase negative value: " << endl;
    copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    
    if (coll.find(8) != coll.end())
        printf("19 found, current bucket: %d, max_load_factor: %d\n",
            coll.bucket_count(), coll.max_load_factor());
    
    return 0;
}