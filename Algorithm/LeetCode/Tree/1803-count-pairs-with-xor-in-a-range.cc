/* Hard
Given a (0-indexed) integer array nums and two integers low and high, return the number of nice pairs.
A nice pair is a pair (i, j) where 0 <= i < j < nums.length and low <= (nums[i] XOR nums[j]) <= high.

Example 1:
Input: nums = [1,4,2,7], low = 2, high = 6
Output: 6
Explanation: All nice pairs (i, j) are as follows:
- (0, 1): nums[0] XOR nums[1] = 5
- (0, 2): nums[0] XOR nums[2] = 3
- (0, 3): nums[0] XOR nums[3] = 6
- (1, 2): nums[1] XOR nums[2] = 6
- (1, 3): nums[1] XOR nums[3] = 3
- (2, 3): nums[2] XOR nums[3] = 5

Example 2:
Input: nums = [9,8,4,2,1], low = 5, high = 14
Output: 8
Explanation: All nice pairs (i, j) are as follows:
​​​​​- (0, 2): nums[0] XOR nums[2] = 13
- (0, 3): nums[0] XOR nums[3] = 11
- (0, 4): nums[0] XOR nums[4] = 8
- (1, 2): nums[1] XOR nums[2] = 12
- (1, 3): nums[1] XOR nums[3] = 10
- (1, 4): nums[1] XOR nums[4] = 9
- (2, 3): nums[2] XOR nums[3] = 6
- (2, 4): nums[2] XOR nums[4] = 5


Constraints:
1 <= nums.length <= 2 * 10^4
1 <= nums[i] <= 2 * 10^4
1 <= low <= high <= 2 * 10^4

Relatives:
001. Two Sum
167. Two Sum II - Input array is sorted
170. Two Sum III - Data structure design
653. Two Sum IV - Input is a BST
1214. Two Sum BSTs
1803. Count Pairs with XOR in a Range */

/*
1. Base idea is similar to Two Sum, but instead of using a hash map, we use a trie to store checked numbers.
2. Every node in the trie is 1 bit. Since nums[i] <= 20000, we only need up to 15 bits.
3. At every node, we store a count: number of numbers that has the same prefix in binary form until this node.
4. For each number in nums, we count numbers in the trie that x^nums[i] >= low (c1) and x^nums[i] > high (c2),
    and add c1 - c2 to the result. (note one count is inclusive, the other is exclusive,
    so we actually do Count(n, low - 1) - Count(n, high))
5. For each bit, if the lowerBound is 0 at that bit, and in n at that bit is b,
    any number has bit ~b at that bit will make the XOR result > lowerBound,
    since b ^ ~b = 1, so we add the count at child[~b].
6. Then we repeatedly continue on the branch that makes the XOR result the same to lowerBound.

Side note:
1. to turn a bit at random position to 0/1 index - !!b.
    !!(0) => 0, !!(0b00...00100...0) => 1
2. x ^ y == z equals z ^ x == y */

#include <array>
#include <vector>

using namespace std;

/* solution 1: [count > low-1] - [count > high] */
class Solution {
public:
    int countPairs(vector<int>& nums, int low, int high) {
        int ret = 0;

        for (const auto& num : nums) {
            ret += count(num, low - 1) - count(num, high);
            add(num);
        }

        return ret;
    }

    // ~Solution() {
    //     destructNode(&root);
    // }

private:
    const int BitNum = 14;

    struct TrieNode {
        int cnt{0};
        array<TrieNode*, 2> child{nullptr, nullptr};
    };

    void add(int num) {
        auto* node = &root;

        for (int bit = 1 << BitNum; bit; bit >>= 1) {
            int idx = !!(num & bit);
            if (!node->child[idx]) {
                node->child[idx] = new TrieNode();
            }
            node = node->child[idx];
            ++(node->cnt);
        }
    };

    int count(int num, int lowerBound) {
        int res = 0;
        const auto* node = &root;

        for (int bit = 1 << BitNum; node && bit; bit >>= 1) {
            int numBit = num & bit;
            int lowBit = lowerBound & bit;
            if (!lowBit && node->child[!numBit]) {
                res += node->child[!numBit]->cnt;
            }
            node = node->child[!!(numBit^lowBit)];
        }

        return res;
    };

    void destructNode(TrieNode* node) {
        if (!node) {
            return;
        }

        destructNode(node->child[0]);
        destructNode(node->child[1]);

        if (node->child[0])
            delete node->child[0];
        if (node->child[1])
            delete node->child[1];
    }

private:
    TrieNode root;
};

/* solution 2.0: [count < high+1] - [count < low] */
class Solution {
public:
    int countPairs(vector<int>& nums, int low, int high) {
        int cnt = 0;

        for (const auto& num : nums) {
            cnt += count(num, high+1) - count(num, low);
            add(num);
        }

        return cnt;
    }

private:
    const int BitNum = 14;

    struct TrieNode {
        int cnt{0};
        array<TrieNode*, 2> child{nullptr, nullptr};
    };

    void add(int num) {
        auto* node = &root;

        for (int bit = 1 << BitNum; bit; bit >>= 1) {
            int idx = !!(num & bit);
            if (!node->child[idx]) {
                node->child[idx] = new TrieNode();
            }
            node = node->child[idx];
            ++(node->cnt);
        }
    }

    int count(int num, int upperBound) {
        int cnt = 0;
        const auto* node = &root;

        for (int bit = 1 << BitNum; node && bit; bit >>= 1) {
            int numBit = num & bit;
            int upBit = upperBound & bit;
            if (upBit && node->child[!!numBit]) {
                cnt += node->child[!!numBit]->cnt;
            }
            node = node->child[!!(numBit^upBit)];
        }

        return cnt;
    }

private:
    TrieNode root;
};

/* solution 2.1: [count < high+1] - [count < low] */
class Solution {
public:
    int countPairs(vector<int>& nums, int low, int high) {
        int hi = cntSmallerPairs(nums, high+1);
        int lo = cntSmallerPairs(nums, low);
        return hi - lo;
    }

private:
    struct TrieNode {
        int cnt{0};
        TrieNode* child[2]{nullptr, nullptr};
    };

    void insertTrie(TrieNode* root, int N) {
        for (int i = 31; i >=0; --i) {
            bool x = (N) & (1 << i);
            if (!root->child[x]) {
                root->child[x] = new TrieNode();
            }
            root->child[x]->cnt += 1;
            root = root->child[x];
        }
    }

    // count elements in Trie whose XOR with N less than K
    int cntSmaller(TrieNode* root, int N, int K) {
        int cntPairs = 0;

        for (int i = 31; i >= 0 && root; --i) {
            bool x = N & (1 << i);
            bool y = K & (1 << i);
            /* if ith bit of K is 1, not matter ith bit of N is 0 or 1, M^N <= K
             * else M^N > K */
            if (y) {
                if (root->child[x]) {
                    cntPairs += root->child[x]->cnt;
                }
                root = root->child[1-x];
            } else {
                root = root->child[x];
            }
        }

        return cntPairs;
    }

    int cntSmallerPairs(const vector<int>& nums, int K) {
        int cntPairs = 0;
        auto* root = new TrieNode();

        for (int i = 0; i < nums.size(); ++i) {
            cntPairs += cntSmaller(root, nums[i], K);
            insertTrie(root, nums[i]);
        }

        return cntPairs;
    }
};