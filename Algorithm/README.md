# LeetCode Algorithm

## DP
No | Title | Difficulty | Notes
-- | -- | ---  | ---
032 | Longet Valid Paretheses | :star: :star: :star: | :two: :heavy_plus_sign: `stack`
010 | Regular Expression Matching | :star: :star: :star: |
062 | Unique Paths | :star: :star: | :two:
063 | Unique Paths II | :star: :star: | :two:
980 | Unique Paths III | :star: :star: :star: | `TODO`
064 | Minimum Path Sum | :star: :star: | :two:
070 | Climbing Stairs | :star: | :two:
746 | MinCost Climb Stair | :star: | :two:
084 | Largest Rectangle in Histogram | :star: :star: :star: | :two: `Monotonic stack`
085 | Maximal Rectangle | :star: :star: :star: | :two:
221 | Maximal Square | :star: :star: | :two: :thinking:
091 | Decode Ways | :star: :star: | :two:
121 | Best Time to Buy and Sell Stock | :star: | :two:  `Prefix Sum`
122 | Best Time to Buy and Sell Stock II | :star: | :two: `Greedy`
123 | Best Time to Buy and Sell Stock III | :star: :star: :star: | :two: `2 times`
188 | Best Time to Buy and Sell Stock IV | :star: :star: :star: | :two: :thinking: `N times`
309 | Best Time to Buy and Sell Stock with Cooldown | :star: :star: | :two:[Stock Problems Solution](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/discuss/108870/Most-consistent-ways-of-dealing-with-the-series-of-stock-problems)
714 | Best Time to Buy and Sell Stock with Transaction Fee | :star: :star: |:two:
139 | Word Break | :star: :star: | :two: :thinking: `Bottom Up`
152 | Maximum Product Subarry | :star: :star: | :two: `Prefix Sum`
174 | Dungeon Game | :star: :star: :star: | :two:
198 | House Robber | :star: | :two:
213 | House Robber II | :star: :star: | :two:
337 | House Robber III | :star: :star: | :two:
241 | Different Ways to Add Parentheses | :star: :star: | :two:
264 | Ugly Number II | :star: :star: | :two:
292 | Nim Game | :star: | :one:
338 | Counting Bits | :star: :star: | :one: :thinking: `Bit`
392 | Is Subsequence | :star: :star: | :two:
509 | Fibonacci Number| :star: | :two:
514 | Freedom Trail  | :star: :star: :star: | :two:
523 | Continuous Subarray Sum  | :star: :star: | :two: :thinking: `Prefix Sum` `Map`
546 | Remove Boxes | :star: :star: :star: | `TODO`
650 | 2 Keys Keyboard | :star: :star: | :one:
651 | 4 Keys Keyboard | :star: :star: | :one:
718 | Maximum Length of Repeated Subarray | :star: :star: | :two:
787 | Cheapest Flights Within K Stops | :star: :star: | :two:
1137 | N-th Tribonacci Number | :star: | :two:
005 | Longest Palindromic Substring | :star: :star: | :two:
647 | Palindromic Substrings | :star: :star: | :two:
1312 | Minimum Insertion Steps to Make a String Palindrome | :star: :star: :star: | :two:
1025 | Divisor Game | :star: | :two:
887 | Super Egg Drop | :star: :star: :star: | :two:
1884 | Egg Drop With 2 Eggs and N Floors  | :star: :star: | :two:
931 | Minimum Falling Path Sum | :star: :star: | :two:
1289 | Minimum Falling Path Sum II | :star: :star: :star: | :two:
877 | Stone Game | :star: :star: | :two:
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

### knapsack
No | Title | Difficulty | Notes
-- | -- | ---  | ---
322 | Coin Change | :star: :star: | :one:
518 | Coin Change 2 | :star: :star: | :one: :thinking:
416 | Partition Equal Subset Sum | :star: :star: | :one:
494 | Target Sum | :star: :star: | :one:
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

Two type of the problem:
1. Can the goods fill the knapsack?
2. How many ways to put the goods into knapsack?

### substring
No | Title | Difficulty | Notes
-- | -- | ---  | ---
053 | Maximum Subarray | :star: | :two: `Prefix Sum` `kadane` `Divide Conquer`
072 | Edit Distance | :star: :star: :star: | :one:
300 | Longest Increasing Subsequence | :star: :star: | :one:
354 | Russian Doll Envelopes | :star: :star: :star: | :one:
516 | Longest Palindromic Subsequence | :star: :star: | :two:
1143 | Longest Common Subsequence | :star: :star: | :two:
1048 | Longest String Chain | :star: :star: | :one:
583 | Delete Operation for Two Strings | :star: :star: | :one:
712 | Minimum ASCII Delete Sum for Two Strings | :star: :star: | :one:
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

```c++
for (state1 : state1_options)
    for (state2 : state2_options)
        for (... : ...)
            dp[state1][state2][...] = max(state1, state2, ...)
```

## BackTrack
No | Title | Difficulty | Notes
-- | -- | ---  | ---
017 | Letter Combination of a Phone Number | :star: :star: | :one:
022 | Generate Parenthesis | :star: :star: | :one: :thinking:
037 | Sudoku Solver | :star: :star: :star: | :one:
039 | Combination Sum | :star: :star: | :one:
040 | Combination Sum II | :star: :star: | :one:
046 | Permutations | :star: :star: | :one: :thinking:
047 | Permutations II | :star: :star: | :one:
077 | Combinations | :star: :star: | :one:
078 | Subsets  | :star: :star: | :one:
090 | Subsets II  | :star: :star: | :one:
079 | Word Search | :star: :star: | :one: `Matrix` `DFS`
212 | Word Search II | :star: :star: :star: | :one: `Matrix` `DFS`
291 | Word Pattern II | :star: :star: | :one: :heavy_plus_sign:
698 | Partition to K Equal Sum Subsets | :star: :star: | :one:
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
    ```c++
    // 40. Combination Sum II
    sort(candidates.begin(), candidates.end());

    void backtrack(const vector<int>& candidates, int pos) {
        if (remain == 0) {
            Result.emplace_back(Track);
            return;
        }

        for (auto i = pos; i < candidates.size(); ++i) {
            if (i > pos && candidates[i] == candidates[i-1])
                continue;

            Track.emplace_back(candidates[i]);
            backtrack(candidates, i+1);
            Track.pop_back();
        }
    }
    ```

* Remove duplicates in permutation
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

## Greedy
No | Title | Difficulty | Notes
-- | -- | ---  | ---
055 | Jump Game | :star: :star: | :one:
045 | Jump Game II | :star: :star: | :one:
122 | Best Time to Buy and Sell Stock II | :star: | :one:
134 | Gas Station | :star: :star: | :one:
435 | Non-overlapping Intervals | :star: :star: | :one: `Interval`
452 | Minimum Number of Arrows to Burst Balloons | :star: :star: | :one: `Interval`
763 | Partition Labels | :star: :star: | :one: `Interval`
1024 | Video Stitching | :star: :star: | :one: `Interval`
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

## Divide Conquer
No | Title | Difficulty | Notes
-- | -- | ---  | ---
023 | Merge K Sorted List | :star: :star: :star: | :one: `K-way Merge`
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

## Two Pointers

**Fast Slow Pointers**
No | Title | Difficulty | Notes
-- | -- | ---  | ---
011 | Container With Most Water | :star: :star: :star: | :one:
027 | Remove Element | :star: | :one:
026 | Remove Duplicates from Sorted Array | :star: | :one:
083 | Remove Duplicates from Sorted List | :star: | :one:
042 | Trapping Rain Water | :star: :star: :star: | :one:
407 | Trapping Rain Water II | :star: :star: :star: | `TODO`
141 | linked List Cycle | :star: | :one: `Cycle`
142 | Linked List Cycle II | :star: :star: | :one: `Cycle`
283 | Move Zeroes | :star: :star: | :one:
287 | Find the Duplicate Number | :star: :star: | :one: `Cycle` `?`
992 | Subarrays with K Different Integers | :star: :star: :star: | `TODO`
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

**Sliding Window**
No | Title | Difficulty | Notes
-- | -- | ---  | ---
076 | Minimum Window Substring | :star: :star: :star: | :one:
003 | Longest Substring Without Repeating Characters | :star: :star: | :one:
159 | Longest Substring with At Most Two Distinct Characters | :star: :star: | :one:
340 | Longest Substring with At Most K Distinct Characters | :star: :star: :star: | :one:
239 | Sliding Window Maximum | :star: :star: :star: | :two: `Monotonic deque` `DP` `L-R vec`
438 | Find All Anagrams in a String | :star: :star: | :one:
567 | Permutation in String | :star: :star: | :one:
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

```c++
void slidingWindow(string src, string tar) {
    int beg = 0, end = 0;
    int winSize = 0;
    unordered_map<char, int> dict, window;

    for (char chr : tar) {
        ++dict[chr];
    }

    while (end < src.size()) {
        char chr = src[end];
        ++end;
        // 1. rigt shift, expanding, update data

        // 2. when to shrink
        while (window needs shrink) {
            chr = src[beg];
            ++beg;
            // 3. left shift, shrinking, upate data
        }

        // 4. update the reuslt: at expanding or shrinking?
    }
}
```

## Search
No | Title | Difficulty | Notes
-- | -- | ---  | ---
004 | Median of Two Sorted Arrays | :star: :star: :star: | `BS`
034 | Search For a Range | :star: :star: | :one: `BS`
035 | Search Insert Position | :star: | :one: `BS`
074 | Search a 2D Matrix | :star: :star: | :one: `BS` `Matrix`
240 | Search a 2D Matrix II | :star: :star: | :one: :thinking: `BS` `Matrix`
278 | First Bad Version | :star: | :one: `BS`
130 | Surrounded Regions | :star: :star: | :one: `DFS` `BFS` `Opposite` `Matrix`
200 | Number of Islands | :star: :star: | :one: `DFS` `BFS` `Matrix`
286 | Walls and Gates | :star: :star: | :one: :thinking: `BFS` `Matrix`
323 | Number of Connected Components in an Undirected Graph | :star: :star: | :thinking: `Union Find` `DFS` `Matrix`
547 | Number of Provinces | :star: :star: | :one: `DFS` `Matrix`
694 | Number of Distinct Islands | :star: :star: | :one: `DFS` `Matrix` `Serialization`
410 | Split Array Largest Sum | :star: :star: :star: | `BS`
695 | Max Area of Island | :star: :star: | :one: `DFS` `Matrix`
1020 | Number of Enclaves | :star: :star: | :one: `DFS` `Matrix`
1254 | Number of Closed Islands | :star: :star: | :one: `DFS` `Matrix`
1905 | Count Sub Islands | :star: :star: | :one: `DFS` `Matrix`
374 | Guess Number Higher Or Lower | :star: | :one: `BS`
378 | Kth Smallest Element in a Sorted Matrix | :star: :star:| :thinking: `BS` `Matrix`
973 | K Closest Points to Origin | :star: :star:| :thinking: `Quick Select` `BS`
752 | Open the Lock | :star: :star:| :one: `BFS`
875 | Koko Eating Bananas | :star: :star:| :one: :thinking: `BS`
1011 | Capacity To Ship Packages Within D Days | :star: :star:| :one: :thinking: `BS`
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

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
No | Title | Difficulty | Notes
-- | -- | ---  | ---
215 | Kth Largest Element in an Array | :star: :star: | :one: `Heap Sort` `Quick Sort`
295 | Find Median from Data Stream | :star: :star: :star: | :one: `Heap Sort`
347 | Top K Frequent Elements | :star: :star: | :one: `Heap Sort` `Quick Sort`
414 | Third Maximum Number | :star: | :one: `Heap Sort`
937 | Reorder Data in Log Files | :star: | :one:
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |


Algorithm | Best Time Complexity | Average Time Complexity | Worst Time Complexity | Worst Space Complexity | Stable
--- | --- | --- | --- | --- | ---
Quick Sort | O(nlogn) | O(nlogn) | O(n^2) | O(logn) | Depends
Merge Sort | O(nlogn) | O(nlogn) | O(nlogn) | O(n) | Y
Selection Sort | O(n^2) | O(n^2) | O(n^2) | O(1) | N
Heap Sort | O(nlogn) | O(nlogn) | O(nlogn) | O(n) | N
Insertion Sort | O(n) | O(n^2) | O(n^2) | O(1) | Y
Bubble Sort | O(n) | O(n^2) | O(n^2) | O(1) | Y
Bucket Sort | O(n+k) | O(n+k) | O(n^2) | O(n) | Y
Radix Sort | O(nk) | O(nk) | O(nk) | O(n+k) | N
Tim Sort | O(n) | O(nlogn) | O(nlogn) | O(n) |
Shell Sort | O(n) | O((nlogn)^2) | O((nlogn)^2) | O(1) |

## Design
No | Title | Difficulty | Notes
-- | -- | ---  | ---
146 | LRU Cache | :star: :star: | :one: `Map + List (O(1) + Date Move)`
460 | LFU Cache  | :star: :star: :star: | :one:
380 | Insert Delete GetRandom O(1) | :star: :star: | :one: `Map + Vec (O(1) + Random Access)`
1396 | Design Underground System | :star: :star: |
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

## Array
No | Title | Difficulty | Notes
-- | -- | ---  | ---
011 | Container With Most Water | :star: :star: :star: | :one: `Two Pointers`
041 | First Missing Positive | :star: :star: :star: |
054 | Spiral Matrix | :star: :star: | `Matrix`
056 | Merge Intervals | :star: :star: | :one: `Interval`
057 | Insert Intervals | :star: :star: | :one: `Interval`
252 | Meeting Rooms | :star: | :one: `Interval`
253 | Meeting Rooms II | :star: :star: | :one: `Interval`
986 | Interval List Intersections | :star: :star: | :one: `Interval`
1288 | Remove Covered Intervals | :star: :star: | :one: `Interval`
027 | Remove Element | :star: | :one: `Two Pointers`
026 | Remove Duplicates from Sorted Array | :star: | :one: `Two Pointers`
080 | Remove Duplicates from Sorted Array II | :star: :star: | :one: `Can dup N`
083 | Remove Duplicates from Sorted List | :star: | :one: `Two Pointers`
082 | Remove Duplicates from Sorted List II | :star: :star: | :one: :heavy_plus_sign: `Two Pointers`
316 | Remove Duplicate Letters | :star: :star: :star: | :one: :heavy_plus_sign:
048 | Rotate Image | :star: :star: |
088 | Merge Sorted Array | :star: | :two:
169 | Majority Element | :star: | [:link: Boyer-Moore Voting Algorithm](http://www.cs.utexas.edu/~moore/best-ideas/mjrty/index.html)
189 | Rotate Array | :star: :star: | :one:
209 | Minimum Size Subarray Sum | :star: :star: | :one: `Prefix Sum` `BS` `Two Pointers`
303 | Range Sum Query Immutable | :star: | `Prefix Sum`
307 | Range Sum Query Mutable | :star: :star: | `Segment Tree`
304 | Range Sum Query 2D Immutable | :star: :star: | `Prefix Sum`
325 | Maximum Size Subarray Sum Equals k | :star: :star: | :two: `Prefix Sum` `Map`
370 | Range Addition | :star: :star: | :one: `Diff Array` `Prefix Sum`
598 | Range Addition II | :star: | :one: `Diff Array`
1094 | Car Pooling | :star: :star: | :one: `Diff Array`
1109 | Corporate Flight Bookings | :star: :star: | :one: `Diff Array` `Prefix Sum`
560 | Subarray Sum Equals K | :star: :star: | :two: `Prefix Sum` `Map`
217 | Contains Duplicate I | :star: | :one:
219 | Contains Duplicate II | :star: | :one:
220 | Contains Duplicate III | :star: :star: | :one: :heavy_plus_sign: `bucket sort`
238 | Product of Array Except Self  | :star: :star: | :one: `L-R vec`
283 | Move Zeroes | :star: :star: | :one: `Two Pointers`
448 | Find All Numbers Disappeared in An Array | :star: | :one:
870 | Advantage Shuffle | :star: :star: |
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

## List
No | Title | Difficulty | Notes
-- | -- | ---  | ---
002 | Add Two Numbers | :star: :star: | :one:
445 | Add Two Numbers II | :star: :star: | :one:
019 | Remove Nth Node From End of List | :star: :star: | :one:
203 | Remove Linked List Element | :star: | :one:
021 | Merge Two Sorted Lists | :star: | :two:
023 | Merge K Sorted List | :star: :star: :star: | :two: `K-way Merge` `Divide Conquer`
024 | Swap Nodes in Pairs | :star: :star: | :one:
025 | Reverse Nodes in K-Group | :star: :star: :star: | :one:
206 | Reverse Linkded List | :star: | :one: `3 solutions`
092 | Reverse Linked List II | :star: :star: | :one:
061 | Roate List By K | :star: :star: | :one:
086 | Partition List | :star: :star: | :one:
138 | Copy List With Random Pointer  | :star: | :one: :thinking:
141 | linked List Cycle | :star: | :one: `Two Pointers` `Cycle`
142 | Linked List Cycle II | :star: :star: | :one: `Two Pointers` `Cycle`
287 | Find the Duplicate Number | :star: :star: | :one: `Two Pointers` `Cycle`
143 | Reorder List | :star: :star: | :one:
147 | Insertion Sorted List | :star: :star: | :two: `Insertion sort`
148 | Sort List | :star: :star: | :two: `Div-Conq` `Merge sort`
160 | Intersection of Two Linked Lists | :star: | :one:
234 | Palindrome Linked List | :star: | :one:
237 | Delete Node In A Linked List | :star: | :one:
328 | Odd Even Linked List | :star: :star: | :one:
725 | Split Linked List in Parts | :star: :star: | :one:
817 | Linked List Components | :star: :star: | :one:
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

## Tree
No | Title | Difficulty | Notes
-- | -- | ---  | ---
095 | Unique Binary Search Trees II | :star: :star: | `DP`
096 | Unique Binary Search Trees  | :star: :star: | `DP`
098 | Validate Binary Search Tree | :star: |
100 | Same Tree | :star: | :one:
101 | Symmetric Tree | :star: | :one:
102 | Binary Tree Level Order Traversal | :star: :star: | :one: `BFS: recursion, level loop, sentinel`
107 | Binary Tree Level Order Traversal II | :star: | :one:
103 | Bianry Tree Zig Zag Level Tree Traverse | :star: :star: | :one:
104 | Maximum Depth of Binary Tree | :star: | :one:
111 | Minimum Depth of Binary Tree | :star: | :one: `DFS` `BFS`
105 | Construct Binary Tree from Preorder and Inorder Traversal | :star: :star: | :one: :thinking:
106 | Construct Binary Tree from Inorder and Postorder Traversal | :star: :star: | :one:
654 | Maximum Binary Tree | :star: :star: | :one:
108 | Convert Sorted Array to Binary Search Tree | :star: :star: | :one:
109 | Convert Sorted List to Binary Search Tree | :star: | :one:
110 | Balanced Bianry Tree | :star: | :one: `DFS`
112 | Path Sum | :star: | :one: `DFS`
113 | Path Sum II | :star: :star: | :one: `DFS`
437 | Path Sum III | :star: :star: | :one: `Prefix Sum` `DFS`
666 | Path Sum IV | :star: :star: | :one: `DFS`
129 | Sum Root to Leaf Numbers | :star: :star: | :one:
124 | Binary Tree Maximum Path Sum | :star: :star: :star: | :one: `DFS` `Prefix Sum`
257 | Binary Tree Paths | :star: | :one: `DFS`
687 | Longest Univalue Path | :star: :star: | :one: `DFS`
114 | Flatten Binary Tree To Linked List | :star: :star: | :one: `Preorder`
116 | Populating Next Right Pointers in Each Node | :star: :star: | :one: `BFS`
117 | Populating Next Right Pointers in Each Node II  | :star: :star: | :one: `BFS-non-queue`
173 | Binary Search Tree Iterator | :star: :star: | :one: `Inorder`
199 | Binary Tree Right Side View | :star: :star: | :one:
222 | Count Complete Tree Nodes | :star: :star: | :one:
226 | Invert Binary Tree | :star: | :one:
230 | kth Smallest Element In The BST | :star: :star: | :one: `Inorder`
671 | Second Minimum Node in a Binary Tree | :star: | :one:
235 | Lowest Common Ancestor of a Binary Search Tree | :star: | :two:
236 | Lowest Common Ancestor of a Binary Tree | :star: :star: | :two: :thinking:
1644 | Lowest Common Ancestor of a Binary Tree II | :star: :star: | :two: `p, q may be null`
1650 | Lowest Common Ancestor of a Binary Tree III | :star: :star: | :two: `List Common Node`
1676 | Lowest Common Ancestor of a Binary Tree IV | :star: :star: | :two: `Multiple-nodes`
1123 | Lowest Common Ancestor of Deepest Leaves | :star: :star: | `TODO`
1214 | Two Sum BSTs | :star: :star: | :one: `Inorder` `Complement Map`
1257 | Smallest Common Region | :star: :star: | `TODO`
297 | Serialize and Deserialize Binary Tree | :star: :star: :star: | `preorder` `postorder` `level`
341 | Flatten Nested List Iterator | :star: :star: | :one: `Lazy Evaluation` `Iterator`
404 | Sum of Left Leaves | :star: | :one:
501 | Find Mode in Binary Search Tree | :star: | :one: :heavy_plus_sign: `inorder`
513 | Find Bottom Left Tree Value | :star: | :one: `BFS-Queue`
652 | Find Duplicate Subtrees | :star: :star: | :one: `Serialization`
538 | Convert BST to Greater Tree | :star: :star: | :one: `Inorder` `Descending`
637 | Average of Levels in Binary Tree | :star: | :one: `BFS` `BFS-Recursion`
450 | Delete Node in a BST | :star: :star: | :one:
700 | Search in a Binary Search Tree | :star: | :one:
701 | Insert into a Binary Search Tree | :star: :star: | :one:
814 | Binary Tree Pruning | :star: | :one: `DFS`
1373 | Maximum Sum BST in Binary Tree | :star: :star: :star: | :one:
1803 | Count Pairs With XOR in a Range | :star: :star: :star: | `XOR` `Prefix Sum`
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

## String
No | Title | Difficulty | Notes
-- | -- | ---  | ---
008 | atoi | :star: | :one:
014 | Longest Common Prefix | :star: |
028 | Implement Strstr | :star: | `KMP`
058 | Length of Last Word | :star: |
125 | Valid Palindrome | :star: | :one:
680 | Valid Palindrome II | :star: | :one:
151 | Reverse Words in a String | :star: :star: |
161 | One Edit Distance | :star: :star: | :one:
205 | Isomorphic Strings | :star: |
242 | Valid Anagra | :star: | :one:
389 | Find the Difference | :star: | :one:
409 | Longest Palindrome | :star: | :one:
415 | Adding Strings | :star: |
443 | String Compression | :star: :star: |
468 | Validate IP Address | :star: :star: | `TODO`
344 | Reverse String | :star: |
345 | Reverse Vowels of a String | :star: |
796 | Rotate String | :star: |
1062 | Longest Repeating Substring | :star: :star: | :two: `BS + Hash` `Rabin-Karp`
1784 | Check if Binary String Has at Most One Segment of Ones | :star: |
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

## Map
No | Title | Difficulty | Notes
-- | -- | ---  | ---
001 | Two Sum | :star: | :two:
167 | Two Sum II | :star: | :two: `Two Pointers`
170 | Two Sum III - Data structure | :star: | :two:
653 | Two Sum IV | :star: | :two: `Inorder + Two Pointers` `Complement Map`
1214 | Two Sum BSTs | :star: :star: | :two: `Inorder + Complement Map` `Tree`
266 | Palindrome Permutation | :star: | :two:
267 | Palindrome Permutation II | :star: :star: | :two: `Backtracking`
290 | Word Pattern | :star: | :one: :heavy_plus_sign:
383 | Ransom Note | :star: | :one:
412 | Fizz Buzz | :star: | :one:
771 | Jewelsand Stones | :star: | :one:
811 | Subdomain Visit Count | :star: | :one:
953 | Verifying an Alien Dictionary  | :star: | :one:
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

## Stack
No | Title | Difficulty | Notes
-- | -- | ---  | ---
020 | valid Parentheses | :star: | :one:
032 | Longet Valid Paretheses | :star: :star: :star: | :one: :heavy_plus_sign: `DP`
155 | MinStack | :star: | :one:
225 | Implement Stack using Queues | :star: | :one:
232 | Implement Queue using Stacks | :star: | :one:
316 | Remove Duplicate Letters | :star: :star: :star: | :two: :heavy_plus_sign: `Monotonic Stack`
394 | DecodeString | :star: :star: | :one: :heavy_plus_sign:
496 | Next Greater Element I | :star: | :two: `Monotonic Stack`
503 | Next Greater Element II | :star: :star: | :two: `Monotonic Stack` `Circular`
556 | Next Greater Element III | :star: :star: | `TODO` `Monotonic Stack`
739 | Daily Temperatures | :star: :star: | :two: `Monotonic Stack`
921 | Minimum Add to Make Parentheses Valid | :star: :star: | :one:
1249 | Minimum Remove to Make Valid Parentheses | :star: :star: | :one: `Bit Set`
1541 | Minimum Insertions to Balance a Parentheses String | :star: :star: | :one: :heavy_plus_sign:
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

## Queue
No | Title | Difficulty | Notes
-- | -- | ---  | ---
641 | Design Circular Deque | :star: :star:
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

## Math
No | Title | Difficulty | Notes
-- | -- | --- | ---
006 | Zig Zag Conversion | :star: :star: |
007 | Reverse Integer | :star: | :one:
009 | Palindrom Number | :star: | :one:
015 | 3 Sum | :star: :star: | :one:
016 | 3 Sum Closest | :star: :star: | :one:
018 | 4 Sum | :star: :star: | :one:
043 | Multiply Strings | :star: :star: | :one:
050 | pow-x-n | :star: :star: | `TODO`
065 | Valid Number | :star: :star: :star: |
066 | Plus One | :star: | :one:
067 | Add Binary | :star: | :one:
069 | Sqrt(x) | :star: | :one:
168 | Excel Sheet Colum Title | :star: | :one:
171 | Excel Sheet Colum Number | :star: | :one:
172 | Factorial Trailing Zeros | :star: :star: |
367 | Valid Perfect Square | :star: |
136 | Single Number | :star: | :one:
137 | Single Number II | :star: :star: | :one: :heavy_plus_sign:
260 | Single Number III | :star: :star: | :one:
179 | Largest Number | :star: :star: | :one: `(a+b) > (b+a)`
190 | Reverse Bits | :star: | :one:
191 | Numberof 1 Bits | :star: | :one:
202 | Happy Number | :star: |
204 | Count Primes | :star: |
224 | Basic Calculator | :star: :star: :star: | `stack`
227 | Basic Calculator II | :star: :star: |
772 | Basic Calculator II  | :star: :star: |
231 | Power Of Two | :star: |
263 | Ugly Number | :star: | :one:
268 | Missing Number | :star: | :one:
292 | Nim Game | :star: |
326 | Power of Three | :star: |
371 | Sum of Two Integers | :star: :star: |
400 | Nth Digit | :star: :star: |
780 | Reaching Points | :star: :star: :star: |
1041 | Robot Bounded In Circle | :star: :star: | :thinking:
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

## Bit
No | Title | Difficulty | Notes
-- | -- | ---  | ---
036 | Valid Sudoku | :star: :star: | :one:
0000 | 0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0--0 | :star: :star: :star: |

# Dynamic Programming
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

# DFS BFS
1. Recursion
2. Deque

# List
* Add/delete head, middle or tail node
* Reverse
    * solution one: 206. Reverse Linked List (reverse whole list)
    * solution two: 092. Reverse Linked List II (reverse partial list)
* Copy list
    * 138. Copy List with Ramdom Pointer
* Cycle in List

# Union Find
* [:link: Disjoint Set (Or Union-Find) | Set 1 (Detect Cycle in an Undirected Graph)](https://www.geeksforgeeks.org/union-find/)
* [:link: Union-Find Algorithm | Set 2 (Union By Rank and Path Compression)](https://www.geeksforgeeks.org/union-find-algorithm-set-2-union-by-rank/)

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
* [labuladong (CN)](https://mp.weixin.qq.com/s/AWsL7G89RtaHyHjRPNJENA)