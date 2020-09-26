#include <iostream>
#include <vector>

int knapsack(const std::vector<int>& vec, int weight) {
    std::vector<bool> states(weight+1, false);
    if (vec[0] < weight) {
        states[0] = false;
    }

    for (int i = 0; i < vec.size(); ++i) {
        for (int j = weight-vec[i]; j >=0; --j) {
            if (states[j]) {
                states[j+vec[i]] = true;
            }
        }
    }

    for (int i = weight; i >= 0; --i) {
        if (states[i]) {
            return i;
        }
    }

    return 0;
}

int knapsack_(const std::vector<int>& vec, const int weight) {
    auto len = vec.size();
    std::vector<std::vector<bool>> states(len, std::vector<bool>(weight+1, false));
    states[0][0] = true;
    if (vec[0] <= weight) {
        states[0][vec[0]] = true;
    }

    for (int i = 1; i < len; ++i) {
        /* 1. don't push packet[i] */
        for (int j = 0; j <= weight; ++j) {
            if (states[i-1][j] == true)
                states[i][j] = states[i-1][j];
        }

        /* 2. push packet[i] */
        for (int j = 0; j <= weight-vec[i]; ++j) {
            if (states[i-1][j] == true)
                states[i][j+vec[i]] = true;
        }
    }

    for (int i = weight; i >= 0; --i) {
        if (states[len-1][i] == true) {
            int w = i;
            for (int k = len-1; k > 0; --k) {
                if (w - vec[k] >= 0 && states[k-1][w-vec[k]]) {
                    std::cout << vec[k] << " -> ";
                    w = w - vec[k];
                }
            }
            std::cout << std::endl;
            return i;
        }
    }

    return 0;
}

int main() {
    std::vector<int> data{2, 2, 4, 6, 3};
    knapsack_(data, 9);

    return 0;
}