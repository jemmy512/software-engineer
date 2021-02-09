#include <cstdio>
#include <iostream>

/********************************** tuple **********************************/

template <class... Ts> struct tuple {};

template <class T, class... Ts>
struct tuple<T, Ts...> : tuple<Ts...> {
    tuple(T t, Ts... ts) : tuple<Ts...>(ts...), _Data(t) {}

    T _Data;
};

/********************************** nth_type **********************************/

template <size_t, class> struct nth_type;

template <class T, class... Ts>
struct nth_type<0, tuple<T, Ts...>> {
    using type = T;
};

template <size_t k, class T, class... Ts>
struct nth_type<k, tuple<T, Ts...>> {
    using type = typename nth_type<k - 1, tuple<Ts...>>::type;
};

/********************************** get **********************************/

template <size_t k, class... Ts>
typename std::enable_if<k == 0, typename nth_type<0, tuple<Ts...>>::type&>::type
get(tuple<Ts...>& t) {
    return t._Data;
}

template <size_t k, class T, class... Ts>
typename std::enable_if<k != 0, typename nth_type<k, tuple<T, Ts...>>::type&>::type
get(tuple<T, Ts...>& t) {
    tuple<Ts...>& base = t;
    return get<k - 1>(base);
}


int main() {
    tuple<double, uint64_t, const char*> t1(12.2, 42, "big");

    std::cout << "0th elem is " << get<0>(t1) << "\n";
    std::cout << "1th elem is " << get<1>(t1) << "\n";
    std::cout << "2th elem is " << get<2>(t1) << "\n";

    get<1>(t1) = 103;
    std::cout << "1th elem is " << get<1>(t1) << "\n";
}