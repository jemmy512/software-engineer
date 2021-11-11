#include <vector>

using namespace std;

int knapsack(int W, int N, const vector<int>& wt, const vector<int>& val) {
    vector<vector<int>> dp(N+1, vector(W+1, 0));

    for (auto i = 1; i <= N; ++i) {
        for (auto w = 1; w <= W; ++w) {
            if (w - wt[i-1] < 0) {
                dp[i][w] = dp[i-1][w];
            } else {
                dp[i][w] = max(dp[i-1][w-wt[i-1]] + val[i-1], dp[i-1][w]);
            }
        }
    }

    return dp[N][W];
}