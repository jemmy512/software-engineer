/*
Given a non-empty array of integers, return the third maximum number in this array.
 If it does not exist, return the maximum number. The time complexity must be in O(n).

Example 1:
Input: [3, 2, 1]

Output: 1

Explanation: The third maximum is 1.
Example 2:
Input: [1, 2]

Output: 2

Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
Example 3:
Input: [2, 2, 3, 1]

Output: 1

Explanation: Note that the third maximum here means the third maximum distinct number.
Both numbers with value 2 are both considered as second maximum.
*/
#include <vector>

using std::vector;

class Solution {
public:
    int thirdMax(vector<int>& nums) {
        int len = nums.size();
        long max[3] = {LONG_MIN, LONG_MIN, LONG_MIN};

        for (int i = 0; i < len; ++i) {
            if (nums[i] == max[0] || nums[i] == max[1] || nums[i] == max[2])
                continue;
            if (nums[i] > max[0]) {
                max[2] = max[1];
                max[1] = max[0];
                max[0] = nums[i];
            } else if (nums[i] > max[1]) {
                max[2] = max[1];
                max[1] = nums[i];
            } else if (nums[i] > max[2]) {
                max[2] = nums[i];
            }
        }

        if (max[2] != LONG_MIN)
            return max[2];
        else
            return max[0];
    }
};

class Solution {
public:
    int thirdMax(vector<int>& nums) {
        return heapSort(nums, 3);
    }

private:
    template<typename Iter, typename T = typename std::iterator_traits<Iter>::value_type, typename Compare = std::less<T>>
    void heapifyDown(Iter begin, Iter cur, Iter end, Compare comp) {
        auto parent = cur;
        auto child = cur;
        for (std::advance(child, std::distance(begin, child)+1);
            child < end;
            std::advance(child, std::distance(begin, child)+1)
        ) {
            if (child + 1 < end && comp(*(child+1), *child))
                ++child;
            if (!comp(*child, *parent))
                break;
            std::swap(*child, *parent);
            parent = child;
        }
    }

    template<typename Container, typename T = typename Container::value_type, typename Comparator = std::less<T>>
    T heapSort(Container& cont, int n, Comparator comp = Comparator()) {
        std::unordered_set<T> set(cont.begin(), cont.end());
        cont.assign(set.begin(), set.end());

        int kth = n > cont.size() ? cont.size() : n;

        for (int i = n/2-1; i >=0 && i < cont.size(); --i) {
            heapifyDown(cont.begin(), cont.begin()+i, cont.begin()+kth, comp);
        }

        for (int i = kth; i < cont.size(); ++i) {
            if (cont[i] >= cont[0]) {
                std::swap(cont[0], cont[i]);
                heapifyDown(cont.begin(), cont.begin(), cont.begin()+kth, comp);
            }
        }

        return (n > cont.size()) ? cont[kth-1] : cont[0];
    }
};