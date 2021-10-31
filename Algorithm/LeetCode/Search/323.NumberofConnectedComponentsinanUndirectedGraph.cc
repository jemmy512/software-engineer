/* Medium
You have a graph of n nodes. You are given an integer n and an array edges 
where edges[i] = [ai, bi] indicates that there is an edge between ai and bi in the graph.

Return the number of connected components in the graph.

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

Constraints:
1 <= n <= 2000
1 <= edges.length <= 5000
edges[i].length == 2
0 <= ai <= bi < n
ai != bi
There are no repeated edges.

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
        init(n, edges);
        doUnion(edges);
        
        return _Count;
    }

private:
    void init(int n, const vector<vector<int>>& edges) {
        _Count = n;
        _Parent = vector(n, 0);
        _Size = vector(n, 1);

        for (auto i = 0; i < n; ++i) {
            _Parent[i] = i;
        }
    }

    void doUnion(const const vector<vector<int>>& edges) {
        for (const auto& edge : edges) {
            auto rootX = find(edge[0]);
            auto rootY = find(edge[1]);

            if (rootX != rootY) {
                if (_Size[rootX] > _Size[rootY]) {
                    _Parent[rootY] = rootX;
                    _Size[rootX] += _Size[rootY];
                } else {
                    _Parent[rootX] = rootY;
                    _Size[rootY] += _Size[rootX];
                }

                --_Count;
            }
        }
    }

    int find(int id) {
        while (_Parent[id] != id) {
            id = _Parent[id] = _Parent[_Parent[id]];  // optional: path compression
        }
        return id;
    }

private:
    int _Count;
    vector<int> _Parent;
    vector<int> _Size;
};

// DFS
class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        if (n == 0)
            return 0;

        _Visited = vector<bool>(n, false);
        _Adjacency = vector<vector<int>>(n);

        for (const auto& edge : edges) {
            _Adjacency[edge[0]].emplace_back(edge[1]);
            _Adjacency[edge[1]].emplace_back(edge[0]);
        }

        int result = 0;

        for (auto i = 0; i < n; ++i) {
            if (_Visited[i] == false) {
                ++result;
                dfs(i);
            }
        }

        return result;
    }
    
private:
    void dfs(int idx) {
        _Visited[idx] = true;
        
        for (auto i = 0; i < _Adjacency[idx].size(); ++i) {
            if (_Visited[_Adjacency[idx][i]] == false) {
                dfs(_Adjacency[idx][i]);
            }
        }
    }
    
private:
    vector<bool> _Visited;
    vector<vector<int>> _Adjacency;
};

/*
[[0,1],[0,2],[1,2]]

*/