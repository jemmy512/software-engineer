/*
    This is demonstration of using custom Hash function and equal criterion to unordered_set
*/

#include<iostream>
#include<unordered_set>
#include<string>
#include<algorithm>
#include<functional>
#include<iterator>

using namespace std;

size_t hash_val(string f, string l, int age) {
    size_t const h1 (std::hash<string>{}(f));
    size_t const h2 (std::hash<string>{}(l));
    size_t const h3 (std::hash<int>{}(age));
    return h1 ^ h2;
}

class Customer {
public:
    friend class CustomerEqual;
    friend class CustomerHash;
    friend ostream& operator<<(ostream &os, const Customer &cs) {
        return os << "fname: " << cs.fname << ", lname: " << cs.lname << ", no: " << cs.no << endl;
    }
    
    Customer() {}
    Customer(string name, string na, int no): fname(name), lname(na), no(no){}
    int getNo() const {
        return no;
    }
    string getFname() const {
        return fname;
    }
    string getLname() const {
        return lname;
    }
private:
    string fname;
    string lname;
    int no;
};

class CustomerEqual {
public:
    bool operator()(const Customer &cs1, const Customer &cs2) const {
        return cs1.getNo() == cs2.getNo();
    }
};


class CustomerHash {
public:
    size_t operator()(const Customer &cs) const {
        return hash_val(cs.getFname(), cs.getLname(), cs.getNo());
    }
};

// lambda hash and equal function:
function<size_t(Customer)> hash_ = [](const Customer &cs) {     // auto
    return hash_val(cs.getFname(), cs.getLname(), cs.getNo());
};

function<bool(Customer, Customer)> equal_ = [](const Customer &c, const Customer &s) {
    return c.getNo() == s.getNo();
};

int main(void) {
    unordered_set<Customer, CustomerHash, CustomerEqual> uset;
    uset.insert({Customer("Jemmy", "Wong", 1001), Customer("Wu", "Yan", 1002)});
    copy(uset.begin(), uset.end(), ostream_iterator<Customer>(cout, " "));
    cout << endl;
    
    unordered_set<Customer, decltype(hash_), decltype(equal_)> uuset(10, hash_, equal_);
    uuset.insert({Customer("a", "aa", 2001), Customer("b", "bb", 2002)});
    copy(uuset.begin(), uuset.end(), ostream_iterator<Customer>(cout, " "));
    
    cout << "type of hash_: " << typeid(hash_).name() << endl; 
    
    return 0;
}
