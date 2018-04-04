#include<iostream>
#include<string>

using namespace std;

class Person {
private:
    Person *prevPerson;
public:
    Person() { prevPerson = nullptr; }
    Person(Person *p): prevPerson(p) {}
    virtual void show() {
         if (prevPerson != nullptr)
            prevPerson->show();
    }
    virtual ~Person() {
        delete prevPerson;
    }
};

class ConcreatPerson: public Person {
private:
    string name;
    int age;
public:
    ConcreatPerson(string n, int a, Person *p): name(n), age(a), Person(p) {}
    virtual void show() {
        cout << "***** Decorate person: " << name << endl;
        Person::show();
    }
};

class Finery: public Person {
public:
    Finery() {}
    Finery(Person *p): Person(p) {}
    virtual void show() = 0;
};

class BigTrouser: public Finery {
public:
    BigTrouser() {}
    BigTrouser(Person *p): Finery(p) {}
    void show() {
        Person::show();
        cout << "BigTrouser ";
    }
};

class Sneakers: public Finery {
public:
    Sneakers() {}
    Sneakers(Person *p): Finery(p) {}
    void show() {
        Person::show();
        cout << "Sneakers ";
    }
};

class TShirts: public Finery {
public:
    TShirts() {}
    TShirts(Person *p): Finery(p) {}
    void show() {
        Person::show();
        cout << "TShirts ";
    }
};

int main() {
    Person *Jonny = new Person();
    Jonny = new TShirts(Jonny);
    Jonny = new BigTrouser(Jonny);
    Jonny = new Sneakers(Jonny);
    Jonny = new ConcreatPerson("Jonny", 22, Jonny);
    Jonny->show();
    delete Jonny;
}
