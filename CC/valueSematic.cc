/*
 * Created by Jemmy on 2018/7/3.
 *
 */
#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

class Parent;
class Child;
typedef shared_ptr<Parent> ParentPtr;
typedef shared_ptr<Child> ChildPtr;

class Parent {
public:
    Parent() {}
    Parent(const ParentPtr &sp) : spouse(sp) {}
    ~Parent() {
        cout << "~Parent()..." << endl;
    }

    void setName(const string na) {
        name = na;
    }
    string getName() {
        return name;
    }
    void addChild(const ChildPtr &child) {
        children.push_back(child);
    }
    void setSpouse(const ParentPtr &sp) {
        spouse = sp;
    }
    vector<weak_ptr<Child>> getChild() {
        return children;
    }
private:
    string name;
    weak_ptr<Parent> spouse;
    vector<weak_ptr<Child>> children;
};

class Child {
public:
    Child(const ParentPtr &m, const ParentPtr &d) : mom(m), dad(d) {}
    void setName(const string na) {
        name = na;
    }
    string getName() {
        return name;
    }
    ~Child() {
        cout << "~Child()___" << endl;
    }
private:
    string name;
    weak_ptr<Parent> mom;
    weak_ptr<Parent> dad;
};

int main() {
    ParentPtr mom(new Parent);
    ParentPtr dad(new Parent);
    mom->setSpouse(dad);
    mom->setName("a");
    dad->setSpouse(mom);
    dad->setName("b");
    {
        ChildPtr ch(new Child(mom, dad));
        ch->setName("ab");
        mom->addChild(ch);
        dad->addChild(ch);
        vector<weak_ptr<Child>> children = mom->getChild();
        int cnt = 0;
        for (auto it = children.begin(); it != children.end(); ++it) {
            shared_ptr<Child> wchild = it->lock();
            if (!wchild) {
                cout << ++cnt << " :child not exist..." << endl;
            } else {
                cout << ++cnt << " :child exist..." << endl;
            }
        }
    }
    cout << "*******************" << endl;
    {
        ChildPtr ch(new Child(mom, dad));
        ch->setName("cd");
        mom->addChild(ch);
        dad->addChild(ch);
        int cnt = 0;
        vector<weak_ptr<Child>> children = mom->getChild();
        for (auto it = children.begin(); it != children.end(); ++it) {
            shared_ptr<Child> wchild = it->lock();
            if (!wchild) {
                cout << ++cnt << " :child not exist..." << endl;
            } else {
                cout << ++cnt << " :child exist..." << endl;
            }
        }
    }
    cout << "*******************" << endl;
    int cnt = 0;
    vector<weak_ptr<Child>> children = mom->getChild();
//    vector<weak_ptr<Child>>::iterate it;
    for (auto it = children.begin(); it != children.end(); ++it) {
        shared_ptr<Child> wchild = (*it).lock();
        if (!wchild) {
            cout << ++cnt << " :child not exist..." << endl;
        } else {
            cout << ++cnt << " :child exist..." << endl;
        }
    }
}


