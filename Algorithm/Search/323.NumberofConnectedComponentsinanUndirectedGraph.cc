/* Medium
Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes),
write a function to find the number of connected components in an undirected graph.

Example 1:
Input: n = 5 and edges = [[0, 1], [1, 2], [3, 4]]
     0          3
     |          |
     1 --- 2    4

Output: 2

Example 2:
Input: n = 5 and edges = [[0, 1], [1, 2], [2, 3], [3, 4]]
     0           4
     |           |
     1 --- 2 --- 3

Output:  1
Note:
You can assume that no duplicate edges will appear in edges.
Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.

Relatives:
130. Surrounded Regions
200. Number of Islands
286. Walls and Gates
305. Number of Islands II
323. Number of Connected Components in an Undirected Graph
694. Number of Distinct Islands
695. Max Area of Island */

#include <vector>
#include <unordered_map>

using namespace std;

/* Union Find */
class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
    vector<int> roots(n);
    for (int i = 0; i < n; ++i)
        roots[i] = i;

    for (const auto& e : edges) {
        int root1 = find(roots, e[0]);
        int root2 = find(roots, e[1]);
        if (root1 != root2) {
            roots[root1] = root2;  // union
            --n;
        }
    }

    return n;
}

private:
    int find(vector<int>& roots, int id) {
        while (roots[id] != id) {
            id = roots[id] = roots[roots[id]];  // optional: path compression
        }
        return id;
    }
};

// not work
class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        visited = vector<bool>(n, false);

        for (const auto& node : edges) {
            hashMap[node[0]].emplace_back(node[1]);
        }

        for (const auto& node : edges) {
            if (visited[node[0]] == false) {
                dfs(edges, node[0]);
                ++count;
            }
        }

        return count;
    }

private:
    void dfs(const vector<vector<int>>& edges, int node) {
        if (hashMap.find(node) != hashMap.end() && !visited[node]) {
            for (const auto& point : hashMap[node]) {
                dfs(edges, point);
            }
        }
        visited[node] = true;
    }

private:
    int count{0};
    vector<bool> visited;
    unordered_map<int, vector<int>> hashMap;
};

/*
[[0,1],[0,2],[1,2]]

*/