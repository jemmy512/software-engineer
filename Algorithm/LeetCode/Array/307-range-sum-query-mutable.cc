/* Medium
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

The update(i, val) function modifies nums by updating the element at index i to val.

Example:
Given nums = [1, 3, 5]
sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8

Constraints:
The array is only modifiable by the update function.
You may assume the number of calls to update and sumRange function is distributed evenly.
0 <= i <= j <= nums.length - 1

Relatives:
303. Range Sum Query Immutable
307. Range Sum Query Mutable
304. Range Sum Query 2D Immutable */

#include <vector>

using namespace std;

/* Approach 2: The following idea is using `Binary Index Tree`
 * There are two articles explaine this technique quite well:
 * 1) http://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/
 * 2) http://cs.stackexchange.com/questions/10538/bit-what-is-the-intuition-behind-a-binary-indexed-tree-and-how-was-it-thought-a */
class NumArray {
public:
    NumArray(vector<int> &nums)  {
        _sz = nums.size();
        _nums.resize(_sz+1, 0);
        _sums.resize(_sz+1, 0);

        for (int i = 0; i < _sz; i++) {
            update(i, nums[i]);
        }
    }

    void update(int i, int val) {
        int oldv = _nums[i+1];
        // Move index to ancestors node
        for (int idx = i+1; idx <= _sz; idx += (idx & (-idx))) {
            _sums[idx] = _sums[idx] - oldv + val;
        }
        _nums[i+1] = val;
    }

    int sumRange(int i, int j) {
        return sumRange(j+1) - sumRange(i);
    }

    int sumRange(int i) {
        int ret = 0;
        // Move index to parent node
        for (int idx = i; idx > 0; idx -= (idx & (-idx))) {
            ret += _sums[idx];
        }
        return ret;
    }

private:
    int _sz;
    vector<int> _nums;
    vector<int> _sums;
};

/* Approach 1: segment tree:
 * is a very flexible data structure, because it is used to solve numerous range query problems
 * like finding minimum, maximum, sum, greatest common divisor, least common denominator
 * in array in logarithmic time. */
class NumArray {
public:
    NumArray(vector<int>& nums) : _Size(nums.size()), _Tree(2*nums.size()) {
        for (int i = _Size, j = 0; i < 2*_Size; ++i, ++j) {
            _Tree[i] = nums[j];
        }
        for (int i = _Size-1; i > 0; --i) {
            _Tree[i] = _Tree[2*i] + _Tree[2*i+1];
        }
    }

    void update(int pos, int val) {
        pos += _Size;
        _Tree[pos] = val;
        while (pos > 0) {
            int left = pos;
            int right = pos;
            if (pos % 2 == 0) {
                right = pos + 1;
            } else {
                left = pos - 1;
            }
            _Tree[pos/2] = _Tree[left] + _Tree[right];
            pos /= 2;
        }
    }

    int sumRange(int i, int j) {
        int left = i + _Size;
        int right = j + _Size;
        int sum = 0;

        while (left <= right) {
            if (left % 2 == 1) {
                sum += _Tree[left];
                ++left;
            }
            if (right % 2 == 0) {
                sum += _Tree[right];
                --right;
            }
            left /= 2;
            right /= 2;
        }

        return sum;
    }

private:
    int _Size;
    vector<int> _Tree;
};

/* Approach 3: brut force*/
class NumArray {
public:
    NumArray(vector<int>& nums) : _Nums(nums), _Sum(nums.size()+1, 0) {
        for (int i = 0; i < _Nums.size(); ++i) {
            _Sum[i+1] = _Sum[i] + _Nums[i];
        }
    }

    void update(int i, int val) {
        int diff = val - _Nums[i];
        _Nums[i] = val;
        for (; i < _Sum.size()-1; ++i) {
            _Sum[i+1] += diff;
        }
    }

    int sumRange(int i, int j) {
        return _Sum[j+1] - _Sum[i];
    }

private:
    vector<int> _Nums;
    vector<long long> _Sum;
};

/* Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(_Nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j); */