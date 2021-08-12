/* Medium
There are n cities. Some of them are connected, while some are not.
If city a is connected directly with city b, and city b is connected directly with city c,
then city a is connected indirectly with city c.

A province is a group of directly or indirectly connected cities and no other cities outside of the group.

You are given an n x n matrix isConnected where isConnected[i][j] = 1
if the ith city and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.

Return the total number of provinces.

Example 1:
Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
Output: 2

Example 2:
Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3


Constraints:
1 <= n <= 200
n == isConnected.length
n == isConnected[i].length
isConnected[i][j] is 1 or 0.
isConnected[i][i] == 1
isConnected[i][j] == isConnected[j][i]

Relatives:
Number of Connected Components in an Undirected Graph
Robot Return to Origin
Sentence Similarity
Sentence Similarity II
The Earliest Moment When Everyone Become Friends */

#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        if (isConnected.empty())
            return 0;

        int count = 0;
        visited = vector<bool>(isConnected.size(), false);

        for (int row = 0; row < isConnected.size(); ++row) {
            if (!visited[row]) {
                dfs(isConnected, row);
                ++count;
            }
        }

        return count;
    }

private:
    void dfs(const vector<vector<int>>& matrix, int row) {
        for (int col = 0; col < matrix.size(); ++col) {
            if (matrix[row][col] && !visited[col]) {
                visited[col] = true;
                dfs(matrix, col);
            }
        }
    }

private:
    vector<bool> visited;
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        if (isConnected.empty())
            return 0;

        int count = 0;
        size = isConnected.size();
        bitset = vector<bool>(size, false);

        for (int row = 0; row < size; ++row) {
            for (int col = 0; col < size && !bitset[row]; ++col) {
                if (isConnected[row][col]) {
                    bitset[row] = true;
                    deq.push_back(row);
                    handleConnection(isConnected);
                    ++count;
                }
            }

            if (row == size-1 && !bitset[row]) {
                ++count;
            }
        }

        return count;
    }

private:
    void handleConnection(vector<vector<int>>& isConnected) {
        while (!deq.empty()) {
            for (int i = 0; i < size; ++i) {
                if (!bitset[i] && isConnected[deq.front()][i]) {
                    bitset[i] = true;
                    deq.push_back(i);
                }
            }
            deq.pop_front();
        }
    }

private:
    int count{0};
    int size;
    deque<int> deq;
    vector<bool> bitset;
};