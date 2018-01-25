#include<iostream>
#include<string>
#include<map>
#include<algorithm>
#include<cctype>
#include<iterator>
#include<iomanip>

using namespace std;

// user fined soring criterion
class RunTimeStringCMP {
public:
    enum cmp_mode {normal, nocase};
private:
    const cmp_mode mode;
    static bool nocase_cmp(const char c1, const char c2) {
        return toupper(c1) < toupper(c2);
    }
public:
    RunTimeStringCMP(cmp_mode m = normal): mode(m) {}
    bool operator()(const string &s1, const string &s2) const {
        if (mode == normal)
            return s1 < s2;
        else 
            return lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), nocase_cmp);
    }
};

typedef map<string, string, RunTimeStringCMP> StringStringMap;

void fillAndPrint(StringStringMap& coll) {
    // insert elements in random order
    coll["Deutschland"] = "Germany";
    coll["deutsch"] = "German";
    coll["Haken"] = "snag";
    coll["arbeiten"] = "work";
    coll["Hund"] = "dog";
    coll["gehen"] = "go";
    coll["Unternehmen"] = "enterprise";
    coll["unternehmen"] = "undertake";
    coll["gehen"] = "walk";
    coll["Bestatter"] = "undertaker";
    // print elements
    cout.setf(ios::left, ios::adjustfield);
    for (const auto& elem : coll) {
        cout << setw(15) << elem.first << " " << elem.second << endl;
    }
    cout << endl;
}

int main(void) {
    StringStringMap coll;
    fillAndPrint(coll);
    
    RunTimeStringCMP ignorecase(RunTimeStringCMP::nocase);
    
    StringStringMap coll2(ignorecase);
    fillAndPrint(coll2);
    
    return 0;
}