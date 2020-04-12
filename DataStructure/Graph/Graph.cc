/* Author: Jemmy
 * Date: 2020-04-12 */

#include <iostream>
#include <vector>
#include <queue>
#include <map>

template<typename T>
struct Vertex {
    using key_type = typename std::hash<T>::result_type;

    Vertex(const T& val) : value(val) { }

    T value;
    std::vector<key_type> inDegree;
    std::vector<key_type> outDegree;
};

template<typename T, class VertexT = Vertex<T>>
class Graph {
public:
    using value_type = T;
    using vertex_type = VertexT;
    using key_type = typename std::hash<T>::result_type;

public:
    int size() const {
        return mVertexes.size();
    }

    void addEdge(const T& from, const T& to) {
        auto fromKey = mHasher(from);
        auto toKey = mHasher(to);

        mVertexes.try_emplace(fromKey, from);
        mVertexes.try_emplace(toKey, to);

        mVertexes.at(fromKey).outDegree.emplace_back(toKey);
        mVertexes.at(toKey).inDegree.emplace_back(fromKey);
    }

    void bfs(const T& val) {
        std::map<key_type, bool> visited;
        std::vector<key_type> prev;
        prev.reserve(size());

        for (const auto& [key, vertex] : mVertexes) {
            if (vertex.inDegree.size() == 0) {
                std::queue<key_type> queue;

                if (vertex.value != val)
                    queue.push(key);
                else
                    return;

                while (!queue.empty()) {
                    const auto& key = queue.front();
                    queue.pop();
                    const auto& ver = mVertexes.at(key);

                    for (auto i = 0; i < ver.outDegree.size(); ++i) {
                        const auto& kk = ver.outDegree.at(i);
                        if (visited[kk])
                            continue;

                        prev.emplace_back(key);

                        if (mVertexes.at(kk).value == val) {
                            prev.emplace_back(val);

                            std::cout << "Found: " << val << ", by bfs, search path:" << std::endl;
                            for (const auto& key : prev) {
                                std::cout << mVertexes.at(key).value << " ~ ";
                            }
                            std::cout << std::endl;

                            return;
                        }

                        visited[kk] = true;
                        queue.push(kk);
                    }
                }
            }
        }

        std::cout << "Not found: " << val << ", by bfs" << std::endl;
    }

    void dfs(const T& val) {
        bool isFound = false;
        std::map<key_type, bool> visited;
        std::vector<key_type> prev;
        prev.reserve(size());

        for (const auto& [key, vertex] : mVertexes) {
            if (vertex.inDegree.size() == 0)
                dfsRecursive(key, val, visited, prev, isFound);

            if (isFound)
                break;
        }

        if (isFound) {
            std::cout << "Found: " << val << ", by dfs, search path:" << std::endl;
            for (const auto& key : prev) {
                std::cout << mVertexes.at(key).value << " _> ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "Not found: " << val << ", by dfs" << std::endl;
        }
    }

    void topoSortByKahn() {
        std::vector<std::queue<key_type>> vecQueue;
        std::map<key_type, int> inDegree;

        for (const auto& [key, ver] : mVertexes) {
            inDegree.emplace(key, ver.inDegree.size());

            if (ver.inDegree.size() == 0) {
                std::queue<key_type> queue;
                queue.push(key);
                vecQueue.emplace_back(std::move(queue));
            }
        }

        for (auto& queue : vecQueue) {
            while (!queue.empty()) {
                auto key = queue.front();
                queue.pop();

                std::cout << mVertexes.at(key).value << " ~ ";

                for (const auto& outKey : mVertexes.at(key).outDegree) {
                    --inDegree.at(outKey);

                    if (inDegree.at(outKey) == 0) {
                        queue.push(outKey);
                    }
                }
            }

            std::cout << std::endl;
        }
    }

    void topoSortByDfs() {
        std::map<key_type, bool> visited;

        for (const auto& [key, vertex] : mVertexes) {
            visited[key] = true;
            topoSortByDfsRecursive(key, visited);
        }

        std::cout << std::endl;
    }

    void print() const {
        for (const auto& vertex : mVertexes) {
            std::cout << vertex.second.value << " -> ";
            for (const auto& out : vertex.second.outDegree) {
                std::cout << mVertexes.at(out).value << " -> ";
            }
            std::cout << std::endl;
        }
    }

private:
    void topoSortByDfsRecursive(const key_type& key, std::map<key_type, bool>& visited) {
        for (auto i = 0; i < mVertexes.at(key).inDegree.size(); ++i) {
            auto& kkey = mVertexes.at(key).inDegree.at(i);
            if (visited[kkey] == false) {
                visited.at(kkey) = true;
                topoSortByDfsRecursive(kkey, visited);
            }
        }

        std::cout << key << " + ";
    }

    void dfsRecursive(const key_type& key, const T& target, std::map<key_type, bool>& visited, std::vector<key_type>& prev, bool& isFound) {
        visited[key] = true;

        const auto& vertex = mVertexes.at(key);
        if (vertex.value == target) {
            isFound = true;
            return;
        }

        for (auto i = 0; i < vertex.outDegree.size() && !isFound; ++i) {
            const auto& kk = vertex.outDegree.at(i);
            if (!visited[kk]) {
                prev.emplace_back(key);
                dfsRecursive(kk, target, visited, prev, isFound);
            }
        }
    }

private:
    std::hash<T> mHasher;
    std::map<key_type, vertex_type> mVertexes;
};

int main() {

    Graph<int> graph;

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 2);

    graph.addEdge(6, 7);
    graph.addEdge(7, 8);
    graph.addEdge(8, 9);
    graph.addEdge(9, 10);
    graph.addEdge(10, 11);
    graph.addEdge(11, 10);

    graph.print();

    graph.bfs(3);
    graph.bfs(10);
    graph.bfs(13);

    graph.dfs(3);
    graph.dfs(10);
    graph.dfs(13);

    std::cout << "-- toSortByKahn: " << std::endl;
    graph.topoSortByKahn();

    std::cout << "-- topoSortByDfs: " << std::endl;
    graph.topoSortByDfs();

    return 0;
}