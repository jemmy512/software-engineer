/* Author: Jemmy
 * Date: 2020-04-12 */

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <limits>
#include "../../Algorithm/Sort/HeapSort.cc"

template<typename T>
struct Vertex {
    using key_type = typename std::hash<T>::result_type;

    Vertex(const T& val, int w) : value(val), weight(w) { }

    T value;
    int weight;
    std::vector<key_type> inDegree;
    std::vector<key_type> outDegree;
};

template<typename T, class VertexT = Vertex<T>>
class Graph {
public:
    using value_type = T;
    using vertex_type = VertexT;
    using key_type = typename std::hash<T>::result_type;

private:
    struct DistanceVertex {
        key_type key;
        key_type predecessor;
        bool visited{false};
        int distance{std::numeric_limits<int>::max()};

        bool operator==(const DistanceVertex& other) {
            return this == &other;
        }
    };
public:
    int size() const {
        return mVertexes.size();
    }

    void addEdge(const T& from, const T& to, int weight) {
        auto fromKey = mHasher(from);
        auto toKey = mHasher(to);

        mVertexes.try_emplace(fromKey, from, weight);
        mVertexes.try_emplace(toKey, to, weight);

        mVertexes.at(fromKey).outDegree.emplace_back(toKey);
        mVertexes.at(toKey).inDegree.emplace_back(fromKey);
    }

    void bfs(const T& val) {
        std::map<key_type, bool> visited;
        std::vector<key_type> prev;
        prev.reserve(size());

        for (const auto& [key, vertex] : mVertexes) {
            if (vertex.inDegree.size() != 0) {
                continue;
            }

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

    void shortestPathByDijkstra(const value_type& from, const value_type& to) {
        const auto& fromKey = mHasher(from);

        std::map<key_type, DistanceVertex> distanceMap;
        distanceMap.insert_or_assign(fromKey, DistanceVertex{fromKey, fromKey, true, 0});


        struct Compare {
            bool operator()(const std::reference_wrapper<const DistanceVertex>& left, const std::reference_wrapper<const DistanceVertex>& right) {
                    return left.get().distance < right.get().distance;
            };
        };
        Heap<std::reference_wrapper<const DistanceVertex>, Compare> heap;

        const auto& fromVer = mVertexes.at(fromKey);
        for (const auto& outKey : fromVer.outDegree) {
            distanceMap[outKey].key = outKey;
        }

        heap.push(std::cref(distanceMap.at(fromKey)));

        while (!heap.empty()) {
            const auto& top = heap.pop();
            auto& minVer = top.get();
            const auto& ver = mVertexes.at(minVer.key);
            if (ver.value == to)
                break;

            for (const auto& kk : ver.outDegree) {
                auto& childVer = mVertexes.at(kk);
                if (minVer.distance + ver.weight < distanceMap[kk].distance) {
                    auto& kkVer = distanceMap[kk];
                    kkVer.key = kk;
                    kkVer.distance = minVer.distance + ver.weight;
                    kkVer.predecessor = minVer.key;

                    if (kkVer.visited) {
                        heap.update(top);
                    } else {
                        kkVer.visited = true;
                        heap.push(std::cref(kkVer));
                    }
                }
            }
        }

        printShortestPath(distanceMap, mHasher(to));
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

    void printShortestPath(const std::map<key_type, DistanceVertex>& distanceMap, const key_type& target) {
        const auto& ver = distanceMap.at(target);
        if (ver.key == ver.predecessor) {
            std::cout << mVertexes.at(ver.key).value << " +> ";
        } else {
            printShortestPath(distanceMap, ver.key);
            std::cout << mVertexes.at(target).value << " +> ";
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

void Test() {
    Graph<int> graph;

    graph.addEdge(0, 1, 0);
    graph.addEdge(1, 2, 0);
    graph.addEdge(2, 3, 0);
    graph.addEdge(3, 2, 0);

    graph.addEdge(6, 7, 0);
    graph.addEdge(7, 8, 0);
    graph.addEdge(8, 9, 0);
    graph.addEdge(9, 10, 0);
    graph.addEdge(10, 11, 0);
    graph.addEdge(11, 10, 0);

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
}

void TestDijkstra() {
    Graph<int> graph;

    graph.addEdge(1, 3, 10);
    graph.addEdge(3, 4, 50);
    graph.addEdge(4, 5, 20);
    graph.addEdge(5, 6, 60);
    graph.addEdge(1, 6, 100);
    graph.addEdge(2, 3, 5);

    graph.shortestPathByDijkstra(1, 5);
}

int main() {

    TestDijkstra();

    return 0;
}