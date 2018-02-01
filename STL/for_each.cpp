#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

/*
    template<class InputIt, class UnaryFunction>
    UnaryFunction for_each(InputIt iterator, UnaryFunction func); (until C++20)
*/

class MeanValue {
public:
    MeanValue(int n = 0, int s = 0) : num(n), sum(s) {}
    void operator()(int elem) {
        ++num;
        sum += elem;
    }
    double value() {
        return static_cast<double>(sum) / static_cast<double>(num);
    }
private:
    int num;
    int sum;
};

int main() {
    vector<int> coll = {1, 2, 3, 4, 5};
    MeanValue mv = for_each(coll.begin(), coll.end(), MeanValue());
    cout << "MeanValue value: " << mv.value() << endl;
    
    return 0;
}