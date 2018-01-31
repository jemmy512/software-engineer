#include<iostream>
#include<iterator>
#include<algorithm>
#include<list>

//using namespace std;

/* function object*/
class IntSequence {
public:
    IntSequence(int init = 0) : value(init) {}
    int operator()() {
        return ++value;
    }
private:
    int value;
};

/* can not use the same name with STL, koenig lookup rule can match the STL generate_n
    function rather that custom functions with the same name
*/ 
template <class T, class M, class N>
void generate_nn (T iterator, M amount, N gen) {
    for (int i = 0; i < amount; ++i) {
        iterator = gen();
    }
}
/*
void generate_n (std::back_insert_iterator<std::list<int>> first, int n,
    IntSequence& gen) {
    for (int i = 0; i < n; ++i) {
        first = gen();
    }
}
*/
int main(void) {
    std::list<int> coll;
    IntSequence seq(1);
    // refrence usage of IntSequnce
    generate_nn<std::back_insert_iterator<std::list<int>>, int, IntSequence&>(back_inserter(coll), 9, seq);
    std::copy(coll.begin(), coll.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    generate_nn<std::back_insert_iterator<std::list<int>>, int, IntSequence>(back_inserter(coll), 3, IntSequence(40));
    std::copy(coll.begin(), coll.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    // reference usage of IntSequence again
    generate_nn<std::back_insert_iterator<std::list<int>>, int, IntSequence&>(back_inserter(coll), 4, seq);
    std::copy(coll.begin(), coll.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    return 0;
}