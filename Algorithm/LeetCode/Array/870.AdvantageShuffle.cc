/* Medium
You are given two integer arrays src and tar both of the same length.
The advantage of src with respect to tar is the number of indices i for which src[i] > tar[i].

Return any permutation of src that maximizes its advantage with respect to tar.


Example 1:
Input: src = [2,7,11,15], tar = [1,10,4,11]
Output: [2,11,7,15]

Example 2:
Input: src = [12,24,8,32], tar = [13,25,32,11]
Output: [24,32,8,12]
Constraints:
1 <= src.length <= 105
tar.length == src.length
0 <= src[i], tar[i] <= 109 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> advantageCount(vector<int>& src, vector<int>& tar) {
        const auto Comp = [](const auto& lhs, const auto& rhs) {
            return lhs.second < rhs.second;
        };
        using T = pair<int, int>;
        priority_queue<T, vector<T>, decltype(Comp)> maxQueue(Comp);

        for (auto i = 0; i < tar.size(); ++i) {
            maxQueue.emplace(i, tar[i]);
        }

        std::sort(src.begin(), src.end());

        vector<int> result(src.size(), 0);
        auto beg = 0;
        auto end = src.size() - 1;

        while (!maxQueue.empty()) {
            const auto [idx, maxTar] = maxQueue.top();
            maxQueue.pop();

            const auto& maxSrc = src[end];
            result[idx] = maxSrc > maxTar ? src[end--] : src[beg++];
        }

        return result;
    }
};