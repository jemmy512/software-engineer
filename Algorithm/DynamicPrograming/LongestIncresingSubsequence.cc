#include <iostream>
#include <vector>

int length(const std::vector<int>& nums) {
    if (nums.size() < 1)
        return 0;

    int result = 0;
    std::vector<int> dp(nums.size(), 1);

    for (auto i = 0; i < nums.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[j] < nums[i]) {
                dp[i] = std::max(dp[j]+1, dp[i]);
            }
        }

        result = std::max(dp[i], result);
    }

    return result;
}

void Test() {
    std::vector<int> nums{1, 9, 5, 4, 2, 9, 3};

    std::cout << length(nums) << std::endl;
}

int main() {
    Test();

    return 0;
}