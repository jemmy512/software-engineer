# LeetCode Algorithm

## DP
No | Title | Difficulty | Note
-- | -- | :-:  | ---
010 | Regular Expression Matching | :star: :star: :star: |
032 | Longet Valid Paretheses | :star: :star: :star: | :heavy_plus_sign: `stack`
062 | Unique Paths | :star: :star: |
063 | Unique Paths II | :star: :star: |
980 | Unique Paths III | :star: :star: :star: | `TODO`
064 | Minimum Path Sum | :star: :star: |
070 | Climbing Stairs | :star: |
746 | MinCost Climb Stair | :star: |
085 | Maximal Rectangle | :star: :star: :star: |
221 | Maximal Square | :star: :star: | :thinking:
091 | Decode Ways | :star: :star: |
121 | Best Time to Buy and Sell Stock | :star: |  `Prefix Sum`
122 | Best Time to Buy and Sell Stock II | :star: | `Greedy`
123 | Best Time to Buy and Sell Stock III | :star: :star: :star: | `2 times`
188 | Best Time to Buy and Sell Stock IV | :star: :star: :star: | :thinking: `N times`
309 | Best Time to Buy and Sell Stock with Cooldown | :star: :star: | [Stock Problems Solution](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/discuss/108870/Most-consistent-ways-of-dealing-with-the-series-of-stock-problems)
714 | Best Time to Buy and Sell Stock with Transaction Fee | :star: :star: |
139 | Word Break | :star: :star: | :thinking: `Bottom Up`
152 | Maximum Product Subarry | :star: :star: | `Prefix Sum`
174 | Dungeon Game | :star: :star: :star: |
198 | House Robber | :star: |
213 | House Robber II | :star: :star: |
337 | House Robber III | :star: :star: |
241 | Different Ways to Add Parentheses | :star: :star: |
292 | Nim Game | :star: |
338 | Counting Bits | :star: :star: | :thinking: `Bit`
392 | Is Subsequence | :star: :star: |
509 | Fibonacci Number| :star: |
514 | Freedom Trail  | :star: :star: :star: |
523 | Continuous Subarray Sum  | :star: :star: | :thinking: `Prefix Sum` `Map`
546 | Remove Boxes | :star: :star: :star: | `TODO`
650 | 2 Keys Keyboard | :star: :star: |
651 | 4 Keys Keyboard | :star: :star: |
718 | Maximum Length of Repeated Subarray | :star: :star: |
787 | Cheapest Flights Within K Stops | :star: :star: | `Graph`
1137 | N-th Tribonacci Number | :star: |
1312 | Minimum Insertion Steps to Make a String Palindrome | :star: :star: :star: |
1025 | Divisor Game | :star: |
887 | Super Egg Drop | :star: :star: :star: |
1884 | Egg Drop With 2 Eggs and N Floors  | :star: :star: |
931 | Minimum Falling Path Sum | :star: :star: |
1289 | Minimum Falling Path Sum II | :star: :star: :star: |
877 | Stone Game | :star: :star: | :heavy_plus_sign:
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

### knapsack
No | Title | Difficulty | Note
-- | -- | :-:  | ---
322 | Coin Change | :star: :star: |
518 | Coin Change 2 | :star: :star: | :thinking:
416 | Partition Equal Subset Sum | :star: :star: |
494 | Target Sum | :star: :star: | `Knapsack` `DP` `Backtrack`
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

Three type of the problem:
1. What's the maximum value of the knapsack when it is fulfilled?
    <details>
    <summary>Collapse</summary>

    ```c++
    int knapsack(int W, const vector<int>& vals, const vector<int>& weights) {
        const auto N = weights.size();
        vector<vector<int>> dp(N+1, vectror(W+1, 0));

        for (auto n = 1; n <= N; ++n) {
            for (auto w = 1; w <= W; ++w) {
                if (w >= weights[n-1]) {
                    dp[n][w] = max(
                        dp[n-1][w],
                        dp[n-1][w - weights[n-1]] + vals[n-1];
                    );
                } else {
                    dp[n][w] = dp[n-1][w];
                }
            }
        }

        return dp[N][W];
    }
    ```
    </details>

2. [Can the goods fulfill the knapsack?](./LeetCode/DP/416-partition-equal-subset-sum.cc)
    <details>
    <summary>Collapse</summary>

    ```c++
    bool knapsack(int W, const vector<int>& weights) {
        const auto N = weights.size();
        vector<vector<bool>> dp(N+1, vectror(W+1, false));

        for (auto n = 0; n <= N; ++n) {
            dp[n][0] = true;
        }

        for (auto n = 1; n <= N; ++n) {
            for (auto w = 1; w <= W; ++w) {
                if (w >= weights[n-1]) {
                    dp[n][w] = dp[n-1][w] || dp[n-1][w - weights[n-1]];
                } else {
                    dp[n][w] = dp[n-1][w];
                }
            }
        }

        return dp[N][W];
    }
    ```

    </details>

3. [How many ways to put the goods into knapsack?](./LeetCode/DP/518-coin-change-ii.cc)
    <details>
    <summary>Collapse</summary>

    ```c++
    int knapsack(int W, const vector<int>& weights) {
        const auto N = weights.size();
        vector<vector<int>> dp(N+1, vectror(W+1, 0));

        for (auto n = 0; n <= N; ++n) {
            dp[n][0] = 1;
        }

        for (auto n = 1; n <= N; ++n) {
            for (auto w = 1; w <= W; ++w) {
                if (w >= weights[n-1]) {
                    dp[n][w] = dp[n-1][w] + dp[n-1][w - weights[n-1]];
                } else {
                    dp[n][w] = dp[n-1][w];
                }
            }
        }

        return dp[N][W];
    }
    ```

    </details>

### substring
No | Title | Difficulty | Note
-- | -- | :-:  | ---
053 | Maximum Subarray | :star: | `Prefix Sum` `kadane` `Divide Conquer`
072 | Edit Distance | :star: :star: :star: |
300 | Longest Increasing Subsequence | :star: :star: |
354 | Russian Doll Envelopes | :star: :star: :star: | :heavy_plus_sign: `BS`
005 | Longest Palindromic Substring | :star: :star: |
516 | Longest Palindromic Subsequence | :star: :star: |
647 | Palindromic Substrings | :star: :star: |
1143 | Longest Common Subsequence | :star: :star: |
1048 | Longest String Chain | :star: :star: |
583 | Delete Operation for Two Strings | :star: :star: |
712 | Minimum ASCII Delete Sum for Two Strings | :star: :star: |
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

```c++
for (state1 : state1_options)
    for (state2 : state2_options)
        for (... : ...)
            dp[state1][state2][...] = max(state1, state2, ...)
```

## BackTrack
No | Title | Difficulty | Note
-- | -- | :-:  | ---
017 | Letter Combination of a Phone Number | :star: :star: |
022 | Generate Parenthesis | :star: :star: | :thinking:
037 | Sudoku Solver | :star: :star: :star: |
077 | Combinations | :star: :star: |
039 | Combination Sum | :star: :star: |
040 | Combination Sum II | :star: :star: |
046 | Permutations | :star: :star: |
047 | Permutations II | :star: :star: |
078 | Subsets  | :star: :star: |
090 | Subsets II  | :star: :star: |
079 | Word Search | :star: :star: | `Matrix` `DFS`
212 | Word Search II | :star: :star: | `Matrix` `DFS`
290 | Word Pattern | :star: |
291 | Word Pattern II | :star: :star: | :heavy_plus_sign:
698 | Partition to K Equal Sum Subsets | :star: :star: |
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

```c++
void backtrack(path, options) {
    if (reach_boundary) {
        result.emplace_back(path);
    } else {
        for (const auto& option : options) {
            do_select(option);
            backtrack(path + 1, options);
            undo_select(option);
        }
    }
}
```

* Remove duplicates in combination
    <details>
    <summary>Collapse</summary>

    ```c++
    // 40. Combination Sum II
    sort(candidates.begin(), candidates.end());

    void backtrack(const vector<int>& candidates, int pos) {
        if (remain == 0) {
            Result.emplace_back(Track);
            return;
        }

        for (auto i = pos; i < candidates.size(); ++i) {
            if (i == pos || candidates[i] != candidates[i-1]) {
                Track.emplace_back(candidates[i]);
                backtrack(candidates, i+1);
                Track.pop_back();
            }
        }
    }
    ```

    </details>

* Remove duplicates in permutation
    <details>
    <summary>Collapse</summary>

    ```c++
    // 47. Permutations II
    void permute(vector<int>& nums, int pos) {
        if (pos == nums.size()) {
            Result.emplace_back(nums);
            return;
        }

        for (int i = pos; i < nums.size(); ++i) {
            if (canSwap(nums, pos, i)) {
                swap(nums[pos], nums[i]);
                permute(nums, pos + 1);
                swap(nums[pos], nums[i]);
            }
        }
    }

    bool canSwap(vector<int>& vec, int beg, int end) {
        while (beg < end && vec[beg] != vec[end]) {
            ++beg;
        }

        return beg == end;
    }
    ```

    </details>

## Greedy
No | Title | Difficulty | Note
-- | -- | :-:  | ---
055 | Jump Game | :star: :star: |
045 | Jump Game II | :star: :star: |
134 | Gas Station | :star: :star: |
435 | Non-overlapping Intervals | :star: :star: | `Interval` `Sort End`
452 | Minimum Number of Arrows to Burst Balloons | :star: :star: | `Interval` `Sort End`
763 | Partition Labels | :star: :star: | `Interval`
1024 | Video Stitching | :star: :star: | `Interval`
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

## Divide Conquer
No | Title | Difficulty | Note
-- | -- | :-:  | ---
023 | Merge K Sorted List | :star: :star: :star: | `K-way Merge`
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

## Two Pointers

**Fast Slow Pointers**
No | Title | Difficulty | Note
-- | -- | :-:  | ---
011 | Container With Most Water | :star: :star: :star: |
042 | Trapping Rain Water | :star: :star: :star: |
407 | Trapping Rain Water II | :star: :star: :star: | `TODO`
151 | Reverse Words in a String | :star: :star: | :heavy_plus_sign:
344 | Reverse String | :star: |
027 | Remove Element | :star: | :one:
026 | Remove Duplicates from Sorted Array | :star: | :one:
083 | Remove Duplicates from Sorted List | :star: |
141 | linked List Cycle | :star: | `Cycle`
142 | Linked List Cycle II | :star: :star: | `Cycle`
283 | Move Zeroes | :star: :star: |
287 | Find the Duplicate Number | :star: :star: | `Cycle Detection`
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

**Sliding Window**
No | Title | Difficulty | Note
-- | -- | ---  | ---
076 | Minimum Window Substring | :star: :star: :star: |
003 | Longest Substring Without Repeating Characters | :star: :star: |
159 | Longest Substring with At Most Two Distinct Characters | :star: :star: |
340 | Longest Substring with At Most K Distinct Characters | :star: :star: :star: |
992 | Subarrays with K Different Integers | :star: :star: :star: | `TODO`
239 | Sliding Window Maximum | :star: :star: :star: | `Monotonic deque` `DP` `L-R vec`
438 | Find All Anagrams in a String | :star: :star: |
567 | Permutation in String | :star: :star: |
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

```c++
void slidingWindow(string src, string tar) {
    int beg = 0, end = 0;
    int winSize = 0;
    unordered_map<char, int> dict, window;

    // 0. init dict
    for (char chr : tar) {
        ++dict[chr];
    }

    while (end < src.size()) {
        // 1. right shift, expanding, update data
        char chr = src[end++];
        if (dict.count(chr)) {
            if (++window[chr] == dict[chr]) {
                ++winSize;
            }
        }

        // 2. when to shrink
        while (winSize == dict.size()) {
            // 3. left shift, shrinking, upate data
            chr = src[beg++];
            if (dict.count(chr)) {
                if (window[chr]-- == dict[chr]) {
                    --winSize;
                }
            }
        }

        // 4. update the reuslt: at expanding or shrinking?
    }
}
```

## Search
No | Title | Difficulty | Note
-- | -- | :-:  | ---
004 | Median of Two Sorted Arrays | :star: :star: :star: | :heavy_plus_sign: `BS`
034 | Search For a Range | :star: :star: | `BS`
035 | Search Insert Position | :star: | `BS`
074 | Search a 2D Matrix | :star: :star: | `BS` `Matrix`
240 | Search a 2D Matrix II | :star: :star: | :thinking: `BS` `Matrix`
278 | First Bad Version | :star: | `BS`
130 | Surrounded Regions | :star: :star: | `DFS` `BFS` `Opposite` `Matrix`
200 | Number of Islands | :star: :star: | `DFS` `BFS` `Matrix`
286 | Walls and Gates | :star: :star: | :thinking: `BFS` `Matrix`
323 | Number of Connected Components in an Undirected Graph | :star: :star: | :thinking: `Union Find` `DFS` `Matrix`
547 | Number of Provinces | :star: :star: | `DFS` `Matrix`
694 | Number of Distinct Islands | :star: :star: | `DFS` `Matrix` `Serialization`
410 | Split Array Largest Sum | :star: :star: :star: | :thinking: `BS`
695 | Max Area of Island | :star: :star: | `DFS` `Matrix`
1020 | Number of Enclaves | :star: :star: | `DFS` `Matrix`
1254 | Number of Closed Islands | :star: :star: | `DFS` `Matrix`
1905 | Count Sub Islands | :star: :star: | `DFS` `Matrix`
374 | Guess Number Higher Or Lower | :star: | `BS`
378 | Kth Smallest Element in a Sorted Matrix | :star: :star:| :thinking: `BS` `Matrix`
973 | K Closest Points to Origin | :star: :star:| :thinking: `Quick Select` `BS`
752 | Open the Lock | :star: :star:| `BFS`
875 | Koko Eating Bananas | :star: :star:| :thinking: `BS`
1011 | Capacity To Ship Packages Within D Days | :star: :star:| :thinking: `BS`
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

[:link: Binary Search, Search `1st`, `last`, `not less`, `not great`](./Search/binary-search.cc)

```c++
int fn(int x, int[] nums) {
    return nums[x];
}

int beg_bound(int[] nums, int target) {
    if (nums.length == 0)
        return -1;
    int beg = 0
    int end = nums.length;

    while (beg < end) {
        int mid = beg + (end - beg) / 2;
        if (fn(mid, nums) == target) {
            end = mid;
        } else if (fn(mid, nums) < target) {
            beg = mid + 1;
        } else if (fn(mid, nums) > target) {
            end = mid;
        }
    }

    if (beg >= nums.lengh || nums[beg] != target)
        return -1;
    else
        return beg;
}

int end_bound(int[] nums, int target) {
    if (nums.length == 0)
        return -1;
    int beg = 0, end = nums.length;

    while (beg < end) {
        int mid = (beg + end) / 2;
        if (fn(mid, nums) == target) {
            beg = mid + 1;
        } else if (fn(mid, nums) < target) {
            beg = mid + 1;
        } else if (fn(mid, nums) > target) {
            end = mid;
        }
    }

    if (end < 0 || nums[beg-1] != target)
        return -1;
    else
        return beg - 1;
}
```

```c++
int bfs(Node start, Node target) {
    Queue<Node> que;
    Set<Node> visited;

    que.push(start);
    visited.add(start);
    int step = 0;

    while (que not empty) {
        // search current line
        int sz = que.size();
        for (int i = 0; i < sz; i++) {
            Node cur = que.pop();

            // can return
            if (cur is target)
                return step;

            // add children of current node
            for (Node x : cur.children()) {
                if (x not in visited) {
                    que.push(x);
                    visited.add(x);
                }
            }
        }

        ++step;
    }
}
```

## Sort
No | Title | Difficulty | Note
-- | -- | :-:  | ---
215 | Kth Largest Element in an Array | :star: :star: | `??` `Heap Sort` `Quick Sort` :one:
295 | Find Median from Data Stream | :star: :star: :star: | `Heap Sort`
347 | Top K Frequent Elements | :star: :star: | `Heap Sort` `Quick Sort` :one:
414 | Third Maximum Number | :star: | `Heap Sort`
912 | Sort Array | :star: :star: | :one:
937 | Reorder Data in Log Files | :star: |
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

heapifyUp is designed for inserting a single element into an w heap, not for building a heap from scratch.

Algorithm | Best O(x) | Average O(x) | Worst O(x) | Space O(x) | Stable | No.
:-: | :-: | :-: | :-: | :-: | :-: | :-
Quick Sort | O(nlogn) | O(nlogn) | O(n^2) | O(logn) | Depends | 912, 75, 215, 347
Insertion Sort | O(n) | O(n^2) | O(n^2) | O(1) | Y | 912, 21, 147
Selection Sort | O(n^2) | O(n^2) | O(n^2) | O(1) | N | 912, 215, 905
Bubble Sort | O(n) | O(n^2) | O(n^2) | O(1) | Y | 912, 283, 315, 344
Merge Sort | O(nlogn) | O(nlogn) | O(nlogn) | O(n) | Y | 912, 23, 148
Heap Sort | O(nlogn) | O(nlogn) | O(nlogn) | O(n) | N | 912, 215, 347, 295
Bucket Sort | O(n+k) | O(n+k) | O(n^2) | O(n) | Y
Radix Sort | O(nk) | O(nk) | O(nk) | O(n+k) | N
Tim Sort | O(n) | O(nlogn) | O(nlogn) | O(n) |
Shell Sort | O(n) | O((nlogn)^2) | O((nlogn)^2) | O(1) |

## Design
| No | Title | Difficulty | Note |
| -- | ----------------------------------------------------------------| :-:  | --- |
| 146 | LRU Cache | :star: :star: | `Map + List (O(1) + Date Move)` |
| 460 | LFU Cache  | :star: :star: :star: | |
| 155 | Min Stack | :star: | :heavy_plus_sign: |
| 380 | Insert Delete GetRandom O(1) | :star: :star: | `Map + Vec (O(1) + Random Access)` |
| 1396 | Design Underground System | :star: :star: | |

## Array
No | Title | Difficulty | Note
-- | -- | :-:  | ---
041 | First Missing Positive | :star: :star: :star: |
448 | Find All Numbers Disappeared in An Array | :star: |
048 | Rotate Image | :star: :star: | `Matrix`
054 | Spiral Matrix | :star: :star: | `Matrix`
059 | Spiral Matrix II | :star: :star: | `Matrix`
189 | Rotate Array `right by k steps` | :star: :star: | :one:
056 | Merge Intervals | :star: :star: | `Interval`
057 | Insert Intervals | :star: :star: | `Interval`
252 | Meeting Rooms | :star: | `Interval`
253 | Meeting Rooms II | :star: | `Interval`
986 | Interval List Intersections | :star: :star: | `Interval`
1288 | Remove Covered Intervals | :star: :star: | `Interval`
027 | Remove Element | :star: | `Two Pointers`
026 | Remove Duplicates from Sorted Array | :star: | `Two Pointers`
080 | Remove Duplicates from Sorted Array II `dup N` | :star: :star: | :one:
083 | Remove Duplicates from Sorted List `dup once` | :star: | `Two Pointers` :one:
082 | Remove Duplicates from Sorted List II `no dup` | :star: :star: | :heavy_plus_sign: `Two Pointers` :one:
316 | Remove Duplicate Letters | :star: :star: :star: | :heavy_plus_sign:
442 | Find All Duplicates in an Array | :star: :star: |
1081 | Smallest Subsequence of Distinct Characters | :star: :star: |
088 | Merge Sorted Array | :star: | :one:
169 | Majority Element | :star: | [:link: Boyer-Moore Voting Algorithm](http://www.cs.utexas.edu/~moore/best-ideas/mjrty/index.html)
209 | Minimum Size Subarray Sum | :star: :star: | `Prefix Sum` `BS` `Two Pointers`
325 | Maximum Size Subarray Sum Equals k | :star: :star: | `Prefix Sum` `Map`
560 | Subarray Sum Equals K | :star: :star: | `Prefix Sum` `Map`
303 | Range Sum Query Immutable | :star: | `Prefix Sum`
307 | Range Sum Query Mutable | :star: :star: | `Segment Tree` `Binary indexed Tree`
304 | Range Sum Query 2D Immutable | :star: :star: | `Prefix Sum`
370 | Range Addition | :star: :star: | `Diff Array` `Prefix Sum`
598 | Range Addition II | :star: | `Diff Array`
1094 | Car Pooling | :star: :star: | `Diff Array`
1109 | Corporate Flight Bookings | :star: :star: | `Diff Array` `Prefix Sum`
217 | Contains Duplicate I | :star: |
219 | Contains Duplicate II `nums[i]=nums[j] i-j<=k` | :star: | `Set`
220 | Contains Duplicate III `nums[i]-nums[j]<=t i-j<=k` | :star: :star: | :heavy_plus_sign: `bucket sort`
238 | Product of Array Except Self  | :star: :star: | `L-R vec`
870 | Advantage Shuffle | :star: :star: |
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

## List
No | Title | Difficulty | Note
-- | -- | :-:  | ---
002 | Add Two Numbers | :star: :star: | :one:
445 | Add Two Numbers II | :star: :star: | :one:
019 | Remove Nth Node From End of List | :star: :star: | :one:
203 | Remove Linked List Element `remove all val` | :star: | :one:
237 | Delete Node In a Linked List | :star: | :one:
021 | Merge Two Sorted Lists | :star: | :one:
023 | Merge K Sorted List | :star: :star: :star: | `K-way Merge` `Divide Conquer` :one:
024 | Swap Nodes in Pairs | :star: :star: | :one:
025 | Reverse Nodes in K-Group | :star: :star: :star: | :heavy_plus_sign: :one:
206 | Reverse Linkded List | :star: | :one:
092 | Reverse Linked List II | :star: :star: | :one:
061 | Roate List By K | :star: :star: | :one:
086 | Partition List `< x <` | :star: :star: | :one:
138 | Copy List With Random Pointer  | :star: | :thinking: :one:
141 | linked List Cycle | :star: | `Two Pointers` `Cycle` :one:
142 | Linked List Cycle II | :star: :star: | `Two Pointers` `Cycle` :one:
287 | Find the Duplicate Number | :star: :star: | `Two Pointers` `Cycle Detection`
143 | Reorder List `L0 Ln L1 Ln-1 L2 Ln-2` | :star: :star: | :one:
147 | Insertion Sorted List | :star: :star: | `Insertion sort` :one:
148 | Sort List | :star: :star: | `Div-Conq` `Merge sort` :one:
160 | Intersection of Two Linked Lists | :star: | :one:
234 | Palindrome Linked List | :star: | :one:
328 | Odd Even Linked List | :star: :star: | :one:
725 | Split Linked List in Parts `k length equal parts`| :star: :star: | :one:
817 | Linked List Components | :star: :star: | :one:
876 | Middle of the Linked List | :star: | :one:
1836 | Remove Duplicates From an Unsorted Linked List | :start: :star: | :one:
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

```c++
/* Even nodes
    Node -> Node -> Node -> Node ->   ^
                      |               |
                    slow            fast

 * Odd nodes
    Node -> Node -> Node -> Node -> Node
                     |               |
                    slow            fast */

ListNode *mid = head, *fast = head; /* fast = head->next; 'mid' will be the previous before real mid node */
while (fast != tail && fast->next != tail) {
    mid = mid->next;
    fast = fast->next->next;
}
```

Reverse List:
* reverseListForward()
* reverseListBackward()
* reverseListRecursive()

Get List Median:
* getMidPrev(). The previous one of real median.
* getMidOrNext(). The middle or next one of real median. [Could dead loop](./LeetCode/List/148-sort-list.cc)

## Tree
No | Title | Difficulty | Note
-- | -- | :-:  | ---
096 | Unique Binary Search Trees  | :star: :star: | `DP`
095 | Unique Binary Search Trees II | :star: :star: | `DP`
098 | Validate Binary Search Tree | :star: |
100 | Same Tree | :star: |
101 | Symmetric Tree | :star: |
102 | Binary Tree Level Order Traversal | :star: :star: | `BFS: recursion, level loop, sentinel`
107 | Binary Tree Level Order Traversal II | :star: |
103 | Bianry Tree Zig Zag Level Tree Traverse | :star: :star: |
104 | Maximum Depth of Binary Tree | :star: |
111 | Minimum Depth of Binary Tree | :star: | `DFS` `BFS`
105 | Construct Binary Tree from Preorder and Inorder Traversal | :star: :star: | :thinking:
106 | Construct Binary Tree from Inorder and Postorder Traversal | :star: :star: |
654 | Maximum Binary Tree | :star: :star: |
108 | Convert Sorted Array to Binary Search Tree | :star: :star: |
109 | Convert Sorted List to Binary Search Tree | :star: |
110 | Balanced Bianry Tree | :star: | `DFS`
112 | Path Sum `root to leaf` | :star: | `DFS`
113 | Path Sum II `root to leaf sum` | :star: :star: | `DFS`
437 | Path Sum III `nums of sum paths` | :star: :star: | :heavy_plus_sign: `Prefix Sum` `DFS`
666 | Path Sum IV | :star: :star: | `DFS`
129 | Sum Root to Leaf Numbers | :star: :star: |
124 | Binary Tree Maximum Path Sum | :star: :star: :star: | `DFS` `Prefix Sum`
257 | Binary Tree Paths | :star: | `DFS`
543 | Diameter of Binary Tree | :star: |
687 | Longest Univalue Path | :star: :star: | `DFS`
114 | Flatten Binary Tree To Linked List | :star: :star: | `Preorder`
116 | Populating Next Right Pointers in Each Node | :star: :star: | `BFS`
117 | Populating Next Right Pointers in Each Node II  | :star: :star: | `BFS-non-queue`
173 | Binary Search Tree Iterator | :star: :star: | `Inorder`
199 | Binary Tree Right Side View | :star: :star: |
222 | Count Complete Tree Nodes | :star: :star: |
226 | Invert Binary Tree | :star: |
230 | kth Smallest Element In The BST | :star: :star: | `Inorder`
671 | Second Minimum Node in a Binary Tree | :star: |
235 | Lowest Common Ancestor of a Binary Search Tree | :star: |
236 | Lowest Common Ancestor of a Binary Tree | :star: :star: | :thinking:
1644 | Lowest Common Ancestor of a Binary Tree II | :star: :star: | `p, q may be null`
1650 | Lowest Common Ancestor of a Binary Tree III | :star: :star: | `List Common Node`
1676 | Lowest Common Ancestor of a Binary Tree IV | :star: :star: | `Multiple-nodes`
1123 | Lowest Common Ancestor of Deepest Leaves | :star: :star: | `TODO`
1214 | Two Sum BSTs | :star: :star: | `Inorder` `Complement Map`
1257 | Smallest Common Region | :star: :star: | `TODO`
297 | Serialize and Deserialize Binary Tree | :star: :star: :star: | `preorder` `postorder` `level`
341 | Flatten Nested List Iterator | :star: :star: | `Lazy Evaluation` `Iterator`
404 | Sum of Left Leaves | :star: |
501 | Find Mode in Binary Search Tree | :star: | :heavy_plus_sign: `inorder`
513 | Find Bottom Left Tree Value | :star: | `BFS-Queue`
652 | Find Duplicate Subtrees | :star: :star: | `Serialization`
538 | Convert BST to Greater Tree | :star: :star: | `Inorder Descending`
637 | Average of Levels in Binary Tree | :star: | `BFS` `BFS-Recursion`
662 | Maximum Width of Binary Tree | :star: :star: | `TODO: overflow`
450 | Delete Node in a BST | :star: :star: |
700 | Search in a Binary Search Tree | :star: |
701 | Insert into a Binary Search Tree | :star: :star: |
814 | Binary Tree Pruning | :star: | `DFS`
1373 | Maximum Sum BST in Binary Tree | :star: :star: :star: | :heavy_plus_sign:
1803 | Count Pairs With XOR in a Range | :star: :star: :star: | `XOR` `Prefix Sum` `Trie`
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

## String
No | Title | Difficulty | Note
-- | -- | :-:  | ---
008 | atoi | :star: |
014 | Longest Common Prefix | :star: |
028 | Implement Strstr | :star: | `KMP`
058 | Length of Last Word | :star: |
125 | Valid Palindrome | :star: |
680 | Valid Palindrome II | :star: |
345 | Reverse Vowels of a String | :star: |
161 | One Edit Distance | :star: :star: |
242 | Valid Anagram | :star: |
389 | Find the Difference | :star: |
409 | Longest Palindrome | :star: |
415 | Adding Strings | :star: |
394 | Decode String | :star: :star: | :heavy_plus_sign: `Two Pointers`
443 | String Compression | :star: :star: | :heavy_plus_sign: `Two Pointers`
468 | Validate IP Address | :star: :star: | `TODO`
796 | Rotate String | :star: |
1062 | Longest Repeating Substring | :star: :star: | :heavy_plus_sign: `BS + Hash` `Rabin-Karp`
1784 | Check if Binary String Has at Most One Segment of Ones | :star: |
1869 | Longer Contiguous Segments of Ones than Zeros | :star: |
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

## Map
No | Title | Difficulty | Note
-- | -- | :-:  | ---
001 | Two Sum | :star: |
167 | Two Sum II | :star: | `Two Pointers`
170 | Two Sum III - Data structure | :star: |
653 | Two Sum IV | :star: | `Inorder + Two Pointers` `Complement Map`
1214 | Two Sum BSTs | :star: :star: | `Inorder + Complement Map` `Tree`
266 | Palindrome Permutation | :star: |
267 | Palindrome Permutation II | :star: :star: | `Backtracking`
205 | Isomorphic Strings | :star: |
383 | Ransom Note | :star: |
412 | Fizz Buzz | :star: |
771 | Jewels and Stones | :star: |
811 | Subdomain Visit Count | :star: |
953 | Verifying an Alien Dictionary  | :star: |
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

## Stack
No | Title | Difficulty | Note
-- | -- | :-:  | ---
020 | valid Parentheses | :star: |
032 | Longet Valid Parentheses | :star: :star: :star: | :heavy_plus_sign: `DP`
225 | Implement Stack using Queues | :star: |
232 | Implement Queue using Stacks | :star: |
084 | Largest Rectangle in Histogram | :star: :star: :star: | `Monotonic stack`
316 | Remove Duplicate Letters | :star: :star: :star: | :heavy_plus_sign: `Monotonic Stack`
496 | Next Greater Element I | :star: | `Monotonic Stack`
503 | Next Greater Element II | :star: :star: | `Monotonic Stack` `Circular`
556 | Next Greater Element III | :star: :star: | `TODO` `Monotonic Stack`
739 | Daily Temperatures | :star: :star: | `Monotonic Stack`
921 | Minimum Add to Make Parentheses Valid | :star: :star: | :heavy_plus_sign:
1249 | Minimum Remove to Make Valid Parentheses | :star: :star: | :heavy_plus_sign: `Bit Set`
1541 | Minimum Insertions to Balance a Parentheses String | :star: :star: | :heavy_plus_sign:
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

## Queue
No | Title | Difficulty | Note
-- | -- | :-:  | ---
641 | Design Circular Deque | :star: :star:|
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

## Math
No | Title | Difficulty | Note
-- | -- | :-: | ---
006 | ZigZag Conversion | :star: :star: |
007 | Reverse Integer | :star: |
009 | Palindrom N voiumber | :star: |
015 | 3 Sum | :star: :star: |
016 | 3 Sum Closest | :star: :star: |
018 | 4 Sum | :star: :star: |
043 | Multiply Strings | :star: :star: |
050 | pow-x-n | :star: :star: | `TODO`
065 | Valid Number | :star: :star: :star: |
066 | Plus One | :star: |
067 | Add Binary | :star: |
069 | Sqrt(x) | :star: |
168 | Excel Sheet Colum Title | :star: |
171 | Excel Sheet Colum Number | :star: |
172 | Factorial Trailing Zeros | :star: :star: |
367 | Valid Perfect Square | :star: |
136 | Single Number | :star: |
137 | Single Number II | :star: :star: | :heavy_plus_sign:
260 | Single Number III | :star: :star: |
179 | Largest Number | :star: :star: | `(a+b) > (b+a)`
190 | Reverse Bits | :star: |
191 | Numberof 1 Bits | :star: |
202 | Happy Number | :star: |
204 | Count Primes | :star: |
224 | Basic Calculator | :star: :star: :star: | `stack`
227 | Basic Calculator II | :star: :star: |
772 | Basic Calculator II  | :star: :star: |
231 | Power Of Two | :star: |
233 | Number of Digit One | :star: :star: :star: |
263 | Ugly Number | :star: |
264 | Ugly Number II | :star: :star: |
268 | Missing Number | :star: |
292 | Nim Game | :star: |
326 | Power of Three | :star: |
371 | Sum of Two Integers | :star: :star: |
400 | Nth Digit | :star: :star: |
405 | Convert a Number to Hexadecimal | :star: |
592 | Fraction Addition and Subtraction | :star: :star: |
\- | Sum of N Fractions ||
780 | Reaching Points | :star: :star: :star: |
1041 | Robot Bounded In Circle | :star: :star: | :thinking:
 \- | [Least Common Multiple & Greatest Common Disisor](./Leetcode/Math/lcm-gcd.cc) | |
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

## Bit
No | Title | Difficulty | Note
-- | -- | :-:  | ---
036 | Valid Sudoku | :star: :star: |
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

# Dynamic Programming

* [20 Patterns to Master Dynamic Programming](https://blog.algomaster.io/p/20-patterns-to-master-dynamic-programming)

* There are two different techniques we can use to implement a dynamic programming solution:
    * **Memoization** is where we add caching to a function (that has no side effects). In dynamic programming, it is typically used on `recursive` functions for a `top-down` solution that starts with the initial problem and then recursively calls itself to solve smaller problems.
    * **Tabulation** uses a table to keep track of subproblem results and works in a `bottom-up` manner: solving the smallest subproblems before the large ones, in an `iterative` manner. Often, people use the words "tabulation" and "dynamic programming" interchangeably.

## For problems:
1. Counting Problem
2. Optimum value (maximum or minimum)
3. Existing Problem

## Steps:
1. Define last step status and subproblems
2. Define the state transition equation
3. Define initializers and boundary
4. Define calculating order

## Solution
1. Define state and selection
2. Define the meaning of dp array
3. Define transition equation from selection
4. Define initializers and boundary

## Catogories
1. Coordinate
2. Sequence
3. Divide
4. Interval
5. Backpack
6. Longest sequence
7. Game

# Graph

* [Master Graph Algorithms for Coding Interviews](https://blog.algomaster.io/p/master-graph-algorithms-for-coding)
    1. Depth First Search (DFS)
    2. Breadth First Search (BFS)
    3. Topological Sort
    4. Union Find
        * [:link: Disjoint Set (Or Union-Find) | Set 1 (Detect Cycle in an Undirected Graph)](https://www.geeksforgeeks.org/union-find/)
        * [:link: Union-Find Algorithm | Set 2 (Union By Rank and Path Compression)](https://www.geeksforgeeks.org/union-find-algorithm-set-2-union-by-rank/)
    5. Cycle Detection
    6. Connected Components
    7. Bipartite Graphs
    8. Flood Fill
    9. Minimum Spanning Tree
    10. Shortest Path

# List
* Add/delete head, middle or tail node
* Reverse
    * solution one: 206. Reverse Linked List (reverse whole list)
    * solution two: 092. Reverse Linked List II (reverse partial list)
* Copy list
    * 138. Copy List with Ramdom Pointer
* Cycle in List

# Bit Operations
Name | Operation
--- | ---
set union | A \| B
set intersection | A & B
set subtraction  | A & ~B
set negation | ALL_BITS ^ A or ~A
set bit | A \|= 1 << bit
clear bit | A &= ~(1 << bit)
test bit | (A & 1 << bit) != 0
extract last bit | A&-A or A&~(A-1) or x^(x&(x-1))
remove last bit | A & (A-1)
get all | 1-bits ~0
-A | ~A + 1

* 0 ^ x == x
* XOR is a sum of two integers in the binary form without taking carry into account
* Carry is logical AND of two input numbers, shifted one bit to the left: carry=(x&y)<<1.

# Patterns
* Pattern: Sliding Window
    * 325\. Maximum Sum Subarray of Size K (easy)
    * Smallest Subarray with a given sum (easy)
    * 340\. Longest Substring with K Distinct Characters (medium)
    * Fruits into Baskets (medium)
    * 3\. No-repeat Substring (hard)
    * Longest Substring with Same Letters after Replacement (hard)
    * Longest Subarray with Ones after Replacement (hard)

* Pattern: Two Pointers
    * Pair with Target Sum (easy)
    * 26\. Remove Duplicates (easy)
    * Squaring a Sorted Array (easy)
    * Triplet Sum to Zero (medium)
    * Triplet Sum Close to Target (medium)
    * Triplets with Smaller Sum (medium)
    * Subarrays with Product Less than a Target (medium)
    * Dutch National Flag Problem (medium)

* Pattern: Fast & Slow Pointers
    * 141\. Linked List Cycle (easy)
    * Start of Linked List Cycle (medium)
    * Middle of the Linked List (easy)
    * Happy Number (medium)

* Pattern: Merge Intervals
    * 056\. Merge Intervals
    * 057\. Insert Interval
    * 252\. Meeting Rooms
    * 253\. Metting Rooms II
    * 452\. Minimum Number of Arrows to Burst Balloons
    * 435\. Non-overlapping Intervals
    * 763\. Partition Labels
    * Intervals Intersection (medium)
    * Conflicting Appointments (medium)

* Pattern: Cyclic Sort
    * Cyclic Sort (easy)
    * 268\. Find the Missing Number (easy)
    * 287\. Find the Duplicate Number (easy)
    * Find all Duplicate Numbers (easy)

* Pattern: In-place Reversal of a Linked List
    * 206\. Reverse a Linked List (easy)
    * Reverse a Sub-list (medium)
    * Reverse every K-element Sub-list (medium)

* Pattern: Tree Breadth First Search (BFS)
    * 102\. Binary Tree Level Order Traversal (easy)
    * Reverse Level Order Traversal (easy)
    * Zigzag Traversal (medium)
    * Level Averages in a Binary Tree (easy)
    * Minimum Depth of a Binary Tree (easy)
    * Level Order Successor (easy)
    * Connect Level Order Siblings (medium)

* Pattern: Tree Depth First Search (DFS)
    * 124\. Binary Tree Path Sum (easy)
    * All Paths for a Sum (medium)
    * Sum of Path Numbers (medium)
    * Path With Given Sequence (medium)
    * Count Paths for a Sum (medium)

* Pattern: Two Heaps
    * Find the Median of a Number Stream (medium)
    * Sliding Window Median (hard)
    * Maximize Capital (hard)

* Pattern: Subsets
    * 78\. Subsets (easy)
    * 90\. Subsets With Duplicates (easy)
    * 46\. Permutations (medium)
    * String Permutations by changing case (medium)
    * Balanced Parentheses (hard)
    * Unique Generalized Abbreviations (hard)

* Pattern: Modified Binary Search
    * Order-agnostic Binary Search (easy)
    * Ceiling of a Number (medium)
    * Next Letter (medium)
    * Number Range (medium)
    * Search in a Sorted Infinite Array (medium)
    * Minimum Difference Element (medium)
    * Bitonic Array Maximum (easy)

* Pattern: Bitwise XOR
    * 136\. Single Number (easy)
    * Two Single Numbers (medium)
    * Complement of Base 10 Number (medium)

* Pattern: Top 'K' Elements
    * Top 'K' Numbers (easy)
    * Kth Smallest Number (easy)
    * 'K' Closest Points to the Origin (easy)
    * Connect Ropes (easy)
    * 347\. Top 'K' Frequent Numbers (medium)
    * Frequency Sort (medium)
    * 179\. Kth Largest Number in a Stream (medium)
    * 'K' Closest Numbers (medium)
    * Maximum Distinct Elements (medium)
    * Sum of Elements (medium)
    * Rearrange String (hard)

* Pattern: K-way merge
    * 23\. Merge K Sorted Lists (medium)
    * Kth Smallest Number in M Sorted Lists (Medium)
    * Kth Smallest Number in a Sorted Matrix (Hard)
    * Smallest Number Range (Hard)

* Pattern : 0/1 Knapsack (Dynamic Programming)
    * 0/1 Knapsack (medium)
    * Equal Subset Sum Partition (medium)
    * Subset Sum (medium)
    * Minimum Subset Sum Difference (hard)

* Pattern: Topological Sort (Graph)
    * Topological Sort (medium)
    * 621\. Tasks Scheduling (medium)
    * Tasks Scheduling Order (medium)
    * All Tasks Scheduling Orders (hard)
    * Alien Dictionary (hard)

* Palindrome
    * 005\. Longest Palindromic Substring
    * 009\. Palindrom Number
    * 125\. Valid Palindrome
    * 680\. Valid Palindrome II
    * 409\. Longest Palindrome
    * 234\. Palindrome Linked List
    * 266\. Palindrome Permutation
    * 267\. Palindrome Permutation II
    * 516\. Longest Palindromic Subsequence
    * 647\. Palindromic Substrings
    * 214\. Shortest Palindrome
    * 336\. Palindrome Pairs
    * 1312\. Minimum Insertion Steps to Make a String Palindrome

* Parentheses
    * 20\. Valid Parentheses
    * 22\. Generate Parentheses
    * 32\. Longest Valid Parentheses
    * 241\. Different Ways to Add Parentheses
    * 301\. Remove Invalid Parentheses
    * 678\. Valid Parenthesis String
    * 856\. Score of Parentheses
    * 921\. Minimum Add to Make Parentheses Valid
    * 1021\. Remove Outermost Parentheses
    * 1111\. Maximum Nesting Depth of Two Valid Parentheses Strings
    * 1190\. Reverse Substrings Between Each Pair of Parentheses
    * 1249\. Minimum Remove to Make Valid Parentheses
    * 1541\. Minimum Insertions to Balance a Parentheses String
    * 1614\. Maximum Nesting Depth of the Parentheses
    * 2116\. Cheeck if a Parentheses String Can Be Valid

# Reference
* [labuladong (:cn: CN)](https://mp.weixin.qq.com/s/AWsL7G89RtaHyHjRPNJENA)