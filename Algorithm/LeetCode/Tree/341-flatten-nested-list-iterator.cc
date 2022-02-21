/* Medium
You are given a nested list of integers nestedList.
Each element is either an integer or a list whose elements may also be integers or other lists.
Implement an iterator to flatten it.

Implement the NestedIterator class:
NestedIterator(List<NestedInteger> nestedList) Initializes the iterator with the nested list nestedList.
int next() Returns the next integer in the nested list.
boolean hasNext() Returns true if there are still some integers in the nested list and false otherwise.

Your code will be tested with the following pseudocode:
initialize iterator with nestedList
res = []
while iterator.hasNext()
    append iterator.next() to the end of res
return res
If res matches the expected flattened list, then your code will be judged as correct.


Example 1:
Input: nestedList = [[1,1],2,[1,1]]
Output: [1,1,2,1,1]
Explanation: By calling next repeatedly until hasNext returns false,
the order of elements returned by next should be: [1,1,2,1,1].

Example 2:
Input: nestedList = [1,[4,[6]]]
Output: [1,4,6]
Explanation: By calling next repeatedly until hasNext returns false,
the order of elements returned by next should be: [1,4,6].


Constraints:
1 <= nestedList.length <= 500
The values of the integers in the nested list is in the range [-10^6, 10^6].

Relatives:
251. Flatten 2D Vector
281. Zigzag Iterator
385. Mini Parser
565. Array Nesting */

#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

// You should not implement it, or speculate about its implementation
class NestedInteger {
  public:
    bool isInteger() const;
    int getInteger() const;
    const vector<NestedInteger>& getList() const;
};

// lazy evaluation
class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList)
    :   Nodes(Nodes.end(), nestedList.begin(), nestedList.end()) { }

    int next() {
        auto ret = Nodes.front().getInteger();
        Nodes.pop_front();
        return ret;
    }

    bool hasNext() {
        while (!Nodes.empty() && !Nodes.front().isInteger()) {
            const auto list = Nodes.front().getList();
            Nodes.pop_front();

            std::transform(list.crbegin(), list.crend(), front_inserter(Nodes), [](const auto& item) {
                return item;
            });
        }

        return !Nodes.empty();
    }

private:
    deque<NestedInteger> Nodes;
};

// full evaluation
class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        for (const auto& node : nestedList) {
            dfs(node);
        }
        Iter = Result.begin();
    }

    int next() {
        return *Iter++;
    }

    bool hasNext() {
        return Iter != Result.end();
    }

private:
    void dfs(const NestedInteger& node) {
        if (node.isInteger()) {
            Result.emplace_back(node.getInteger());
        } else {
            for (const auto& child : node.getList()) {
                dfs(child);
            }
        }
    }

private:
    vector<int> Result;
    vector<int>::iterator Iter;
};

/* Your NestedIterator object will be instantiated and called as such:
NestedIterator i(nestedList);
while (i.hasNext()) cout << i.next(); */