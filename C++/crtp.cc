#include <iostream>
#include <string>

using namespace std;

/* Curiously Recurring Template Pattern (CRTP)
 * https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
 *
 * The main usage of the CRTP is to add a generic functionality to a particular class.
 *
 * In general, a class deriving from another class expresses
 * that the derived class somehow conceptually “is a” base class.
 * The purpose is to use the base class in generic code,
 * and to redirect calls to the base class over to code in the derived class.
 *
 * With the CRTP the situation is radically different.
 * The derived class does not express the fact it “is a” base class.
 * Rather, it expands its interface by inherting from the base class, in order to add more functionality.
 *
 * Therefore the base class is not the interface, and the derived class is not the implementation */
namespace crtp {
template <typename T>
struct crtp
{
    T& derive() { return static_cast<T&>(*this); }
    const T& derive() const { return static_cast<const T&>(*this); }
private:
    /* private constructor prevents the case: class Derived2 : public Base<Derived1> */
    crtp() = default;
    friend T;
};

/* phantom type is used to solve diamond inheritance problem */
template <typename T, template<typename> class crtpType>
struct crtp
{
    T& derive() { return static_cast<T&>(*this); }
    const T& derive() const { return static_cast<const T&>(*this); }
private:
    crtp() = default;
    friend crtpType<T>;
};


template<typename Printable>
struct RepeatPrint
{
    void repeat(unsigned int n) const {
        while (n-- > 0) {
            static_cast<Printable const&>(*this).print();
        }
    }
};


class Name : public RepeatPrint<Name>
{
public:
    Name(std::string firstName, std::string lastName)
    :   firstName_(std::move(firstName)),
        lastName_(std::move(lastName))
    {}

    void print() const {
        std::cout << lastName_ << ", " << firstName_ << '\n';
    }

private:
    std::string firstName_;
    std::string lastName_;
};

int main() {
    Name ned("Eddard", "Stark");
    ned.repeat(10);
}
} // namspace crtp


/* Mixin classes are template classes that define a generic behaviour,
 * and are designed to inherit from the type you wish to plug their functionality onto.
 *
 * The idea of the mixin class is to isolate the generic functionality into its own class,
 * template this class on the type we want to plug in onto, and derive from that type.
 *
 * Mixin classes involve a mix of template and inheritance in order to
 * plug a generic functionality onto an existing class.
 *
 * Mixin classes are like the CRTP, but upside down */
namespace mixin {
class Name {
public:
    Name(std::string firstName, std::string lastName)
    :   firstName_(std::move(firstName)),
        lastName_(std::move(lastName))
    {}

    void print() const {
        std::cout << lastName_ << ", " << firstName_ << '\n';
    }

private:
    std::string firstName_;
    std::string lastName_;
};

template<typename Printable>
struct RepeatPrint : Printable {
    explicit RepeatPrint(Printable const& printable) : Printable(printable) {}

    void repeat(unsigned int n) const {
        while (n-- > 0) {
            this->print();
        }
    }
};

int main() {
    Name ned("Eddard", "Stark");
    RepeatPrint<Name>(ned).repeat(10);
}

} // namespace mixin


/* CRTP and mixin classes provide two approaches to the same problem:
 * adding a generic functionality to an existing class, but with different trade-offs.
 *
 * Here are the points where they differ:
 *
 * The CRTP:
 * • impacts the definition of the original class, because it has to inherit from the CRTP,
 * • client code uses the original class directly and benefits from its augmented functionalities.
 *
 * The mixin class:
 * • leaves the original class unchanged,
 * • client code doesn’t use the original class directly,
 *      it needs to wrap it into the mixin to use the augmented functionality,
 * • inherits from a the original class even if it doesn’t have a virtual destructor. This is ok
 *      unless the mixin class is deleted polymorphically through a pointer to the original class.
 *
 * References:
 * [Curiously Recurring Template Pattern (CRTP)](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern)
 * [The CRTP, episode One: Definition](https://www.fluentcpp.com/2017/05/12/curiously-recurring-template-pattern/
 * [The CRTP, episode Two: What the CRTP can bring to your code](https://www.fluentcpp.com/2017/05/16/what-the-crtp-brings-to-code/)
 * [The CRTP, episode Three: An implementation helper for the CRTP](https://www.fluentcpp.com/2017/05/19/crtp-helper/)
 * [Mixin Classes: The Yang of the CRTP](https://www.fluentcpp.com/2017/12/12/mixin-classes-yang-crtp/)
 * [How to replace virtual methods by a CRTP](https://www.fluentcpp.com/2018/05/22/how-to-transform-a-hierarchy-of-virtual-methods-into-a-crtp/)
 * [How to make a CRTP inherit from another CRTP](https://www.fluentcpp.com/2020/09/11/replacing-crtp-static-polymorphism-with-concepts/) */