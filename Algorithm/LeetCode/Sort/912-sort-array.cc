/* Medium
Given an array of integers nums, sort the array in ascending order and return it.

You must solve the problem without using any built-in functions in O(nlog(n))
time complexity and with the smallest space complexity possible.

Example 1:
Input: nums = [5,2,3,1]
Output: [1,2,3,5]
Explanation: After sorting the array, the positions of some numbers are not changed
(for example, 2 and 3), while the positions of other numbers are changed (for example, 1 and 5).

Example 2:
Input: nums = [5,1,1,2,0,0]
Output: [0,0,1,1,2,5]
Explanation: Note that the values of nums are not necessairly unique.

Constraints:
1 <= nums.length <= 5 * 104
-5 * 104 <= nums[i] <= 5 * 104 */

/* * * * * * * * * * * * * * * heap sort * * * * * * * * * * * * * * * * */
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        heapSort(nums);
        return nums;
    }

private:
    void heapSort(vector<int>& vec) {
        const auto size = vec.size();
        // build max heap
        // auto i = (size - 1); deduce unsigned int, error for i >= 0
        for (int i = (size - 1) / 2; i >= 0; --i) {
            heapifyDown(vec, i, size);
        }

        for (int i = size - 1; i >= 0; --i) {
            swap(vec[0], vec[i]);
            heapifyDown(vec, 0, i);
        }
    }

    void heapifyDown(vector<int>& vec, int beg, int end) {
        for (int parent = beg, child = 2 * parent + 1;
            child < end;
            parent = child, child = 2 * parent + 1) {

            if (child + 1 < end && vec[child+1] > vec[child]) {
                ++child;
            }

            if (vec[parent] >= vec[child]) {
                break;
            }

            swap(vec[parent], vec[child]);
        }
    }
};

/* * * * * * * * * * * * * * * * merge sort * * * * * * * * * * * * * * * */
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        mergeSort(nums, 0, nums.size() - 1);
        return nums;
    }

private:
    // [beg, end]
    void mergeSort(vector<int>& vec, int beg, int end) {
        if (beg < end) {
            int mid = beg + (end - beg) / 2;
            mergeSort(vec, beg, mid);
            mergeSort(vec, mid + 1, end);
            merge(vec, beg, mid, end);
        }
    }

    void merge(vector<int>& vec, int beg, int mid, int end) {
        vector<int> tmp(end - beg + 1);
        auto i = beg, j = mid + 1, k = 0;

        while (i <= mid && j <= end) {
            tmp[k++] = (vec[i] < vec[j]) ? vec[i++] : vec[j++];
        }

        while (i <= mid) {
            tmp[k++] = vec[i++];
        }
        while (j <= end) {
            tmp[k++] = vec[j++];
        }

        std::copy(tmp.begin(), tmp.end(), vec.begin() + beg);
    }
};

/* * * * * * * * * * * * * * * quick sort * * * * * * * * * * * * * * * * */
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }

private:
    // [beg, end]
    void quickSort(vector<int>& nums, int beg, int end) {
        if (beg < end) {
            int pivot = partition(nums, beg, end);
            quickSort(nums, beg, pivot - 1);
            quickSort(nums, pivot + 1, end);
        }
    }

    int partition(vector<int>& nums, int beg, int end) {
        auto key = nums[end];
        auto i = beg;

        for (int j = beg; j < end; ++j) {
            if (nums[j] <= key) {
                std::swap(nums[i++], nums[j]);
            }
        }

        std::swap(nums[i], nums[end]);

        return i;
    }
};

/* * * * * * * * * * * * * * * insert sort * * * * * * * * * * * * * * * * */
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        insertSort(nums);
        return nums;
    }

private:
    void insertSort(vector<int>& vec) {
        for (auto i = 1; i < vec.size(); ++i) {
            auto key = vec[i];
            int j = i - 1;
            while (j >= 0 && vec[j] > key) {
                vec[j+1] = vec[j];
                --j;
            }
            vec[j+1] = key;
        }
    }
};

/* * * * * * * * * * * * * * select sort * * * * * * * * * * * * * * * * * */
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        selectSort(nums);
        return nums;
    }

private:
    void selectSort(vector<int>& vec) {
        const auto sz = vec.size();

        for (auto i = 0; i < sz; ++i) {
            int k = i;
            for (auto j = i + 1; j < sz; ++j) {
                if (vec[j] < vec[k]) {
                    k = j;
                }
            }
            swap(vec[i], vec[k]);
        }
    }
};

/* * * * * * * * * * * * * * * bubble sort * * * * * * * * * * * * * * * * */
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        bubbleSort(nums);
        return nums;
    }

private:
    void bubbleSort(vector<int>& vec) {
        auto isSwapped = true;
        const auto size = vec.size();

        for (auto i = 0; isSwapped && i < size - 1; ++i) {
            isSwapped = false;
            for (auto j = 0; j < size - 1 - i; ++j) {
                if (vec[j] > vec[j+1]) {
                    isSwapped = true;
                    swap(vec[j], vec[j+1]);
                }
            }
        }
    }
};