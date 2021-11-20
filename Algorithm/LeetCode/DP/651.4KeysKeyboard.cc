/* Medium
Imagine you have a special keyboard with the following keys:

Key 1: (A): Print one ‘A’ on screen.

Key 2: (Ctrl-A): Select the whole screen.

Key 3: (Ctrl-C): Copy selection to buffer.

Key 4: (Ctrl-V): Print buffer on screen appending it after what has already been printed.

Now, you can only press the keyboard for N times (with the above four keys),
find out the maximum numbers of ‘A’ you can print on screen.

Example 1:
Input: N = 3
Output: 3
Explanation:
We can at most get 3 A's on screen by pressing following key sequence:
A, A, A

Example 2:
Input: N = 7
Output: 9
Explanation:
We can at most get 9 A's on screen by pressing following key sequence:
A, A, A, Ctrl A, Ctrl C, Ctrl V, Ctrl V

Note:
1 <= N <= 50
Answers will be in the range of 32-bit signed integer. */

#include <vector>

using namespace std;

/* O(N^2)
There must be two cases for the optimal key sequnce:
1. Always print 'A' when N is small
2. A A A ... { C-A C-C C-V C-V ... } ... { C-A C-C C-V C-V ... } when N is large */

class Solution {
public:
    int maxA(int N) {
        vector dp(N+1, 0);

        for (auto i = 1; i <= N; ++i) {
            dp[i] = dp[i-1] + 1;
            for (auto j = 2; j <= i; ++j) {
                // Ctrl-A & Ctrl-C dp[j-2] (i-j) times + dp[j-2] itself
                dp[i] = max(dp[i], dp[j-2] * (i-j+1));
            }
        }

        return dp[N];
    }
};

/* O(N^3) Time Limit Exceed
This solution can form unefficient sequences:
1. C-A C-C C-A C-C ... whiout C-V, the number of 'A' never changes
2. C-V C-V ... C-V whitout C-A & C-C */

class Solution {
public:
    int maxA(int N) {
        return dp(N-1, 0, 0);
    }

private:
    int dp(int n, int aNum, int copySize) {
        if (n <= 0)
            return aNum;

        if (Memo[n][aNum][copySize] != -1)
            return Memo[n][aNum][copySize];

        const auto ctrlA = dp(n-1, aNum + 1, copySize);
        const auto ctrlV = dp(n-1, aNum + copySize, copySize);
        const auto ctrlAC = dp(n-2, aNum, aNum);
        Memo[n][aNum][copySize] = max(ctrlA, max(ctrlV, ctrlAC));

        return Memo[n][aNum][copySize];
    }

private:
    vector<vector<vector<int>>> Memo;
};