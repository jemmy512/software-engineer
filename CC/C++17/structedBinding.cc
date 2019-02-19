#include <iostream>
#include <utility>
#include <string>
#include <tuple>

class Customer {
public:
    Customer(std::string f, std::string s, long v) 
    :   first(std::move(f)), second(std::move(s)), val(std::move(v))
    { }
    
    const std::string& getFirst() const {
        return first;
    }
    
    const std::string& getSecond() const {
        return second;
    }
    
    const long& getVal() const {
        return val;
    }

    std::string& getFirst()  {
        return first;
    }
    
    std::string& getSecond()  {
        return second;
    }
    
    long& getVal()  {
        return val;
    }
        
private:
    std::string first;
    std::string second;
    long val;
};

template<>
struct std::tuple_size<Customer> {
    static constexpr int value = 3;
};

template<>
struct std::tuple_element<2, Customer> {
    using type = long;
};

template<std::size_t idx>
struct std::tuple_element<idx, Customer> {
    using type = std::string;
};

/*
template<std::size_t> auto get(const Customer &);
template<> auto get<0>(const Customer &c) { return c.getFirst(); }
template<> auto get<1>(const Customer &c) { return c.getSecond; }
template<> auto get<2>(const Customer &c) { return c.getVal(); }
*/

// To enable the return value to be a reference, you should use decltype(auto)

template<std::size_t I> decltype(auto) get(Customer &c) {       // non-const 
    static_assert(I < 3);
    if constexpr (I == 0) {
        return c.getFirst();
    } else if constexpr (I == 1) {
        return c.getSecond();
    } else {
        return c.getVal();
    }
}

template<std::size_t I> decltype(auto) get(const Customer &c) { // const 
    static_assert(I < 3);
    if constexpr (I == 0) {
        return c.getFirst();
    } else if constexpr (I == 1) {
        return c.getSecond();
    } else {
        return c.getVal();
    }
}

template<std::size_t I> decltype(auto) get(Customer &&c) {      // movable
    static_assert(I < 3);
    if constexpr (I == 0) {
        return std::move(c.getFirst());
    } else if constexpr (I == 1) {
        return std::move(c.getSecond());
    } else {
        return std::move(c.getVal());
    }
}


int main() {
    Customer c("Tim", "Starr", 42);
    auto [f, l, v] = c;
    std::cout << "f/l/v: " << f << ' ' << l << ' ' << v << '\n';
}
