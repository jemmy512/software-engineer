#include <iostream>
#include <vector>

int knapsack(const std::vector<int>& vec, int weight) {
    auto len = vec.size();
    std::vector<std::vector<bool>> states(len, std::vector<bool>(weight+1, false));
    states[0][0] = true;
    if (vec[0] <= weight) {
        states[0][vec[0]] = true;
    }

    for (int i = 1; i < len; ++i) {
        for (int j = 0; j <= weight; ++j) {
            if (states[i-1][j] == true)
                states[i][j] = states[i-1][j];
        }

        for (int j = 0; j <= weight-vec[i]; ++j) {
            if (states[i-1][j] == true)
                states[i][j+vec[i]] = true;
        }
    }

    for (int i = weight; i >= 0; --i) {
        if (states[len-1][i] == true) return i;
    }

    return 0;
}

int main() {

    return 0;
}