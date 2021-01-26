#include <utility>
#include <iostream>

namespace detail {
    /* if Output has same type with Input, matche this specific verison first */
    template<typename Output, typename... Input>
    void foo(Output& out, const Input&... inputs) {
        (std::cout << ... << inputs) << " | " << out << std::endl;
    }

    template<typename... InputsThenOutput, size_t... InputIndex>
    void foo(std::tuple<InputsThenOutput...>&& inputsOutput, std::index_sequence<InputIndex...>&&) {
        auto constexpr outputIndex = sizeof...(InputsThenOutput) - 1;
        foo(std::get<outputIndex>(inputsOutput), std::get<InputIndex>(inputsOutput)...);
    }
}

template<typename... InputsThenOutput>
void foo(InputsThenOutput&&... inputsOutput) {
    detail::foo(std::forward_as_tuple(inputsOutput...), std::make_index_sequence<sizeof...(inputsOutput)-1>{});
}

int main() {
    foo("a" , "b", "c", "last");
}