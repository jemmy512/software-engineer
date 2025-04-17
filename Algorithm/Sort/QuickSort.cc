#include <iostream>
#include <vector>

using namespace std;

/* Relatives:
215. Kth Largest Element in an Array
324. Wiggle Sort II
347. Top K Frequent Elements
414. Third Maximum Number
692. Top K Frequent Words
703. Kth Largest Element in a Stream
973. K Closest Points to Origin
1471. The k Strongest Values in an Array
1985. Find the Kth Largest Integer in the Array */

/* Hoare partition scheme
The pivot's final location is not necessarily at the index that is returned,
as the pivot and elements equal to the pivot can end up anywhere within the partition after a partition step,
and may not be sorted until the base case of a partition with a single element is reached via recursion. */

namespace SearchForward {
    void quickSort(vector<int>& nums, int beg, int end) {
        if (beg < end) {
            int pivot = partition(nums, beg, end);
            quickSort(nums, beg, pivot - 1);
            quickSort(nums, pivot + 1, end);
        }
    }

    int partition(vector<int>& nums, int beg, int end) {
        auto pivot = nums[end];
        auto i = beg;

        for (int j = beg; j < end; ++j) {
            if (nums[j] <= pivot) {
                std::swap(nums[i++], nums[j]);
            }
        }

        std::swap(nums[i], nums[end]);

        return i;
    }
}

namespace SearchBidirectional {
    template<typename T>
    int partition(T& data, int beg, int end) {
        auto pivot = data[(beg + end) / 2];

        while (beg <= end) {
            while (data[beg] < pivot)
                ++beg;
            while (data[end] > pivot)
                --end;
            if (beg <= end)
                std::swap(data[beg++], data[end--]);
        }

        // beg points to the position past the pivot
        return beg;
    }

    template<typename T> // [beg, end]
    void quickSort(T& data, int beg, int end) {
        if (beg < end) {
            auto pivot = partition(data, beg, end);
            /* dead loop if pivot not -1 +1 when beg = 0 end = 7 pivot = 3
            0 1 2 3 4 5 6 7 8 9 10 11 12
            3 3 2 3 3 3 3 4 7 6 5  9  8 */
            quickSort(data, beg, pivot-1);
            quickSort(data, pivot, end);
        }
    }

    template<typename T> // [beg, end]
    void quickSelectK(T& data, int beg, int end, int k) {
        while (beg < end) {
            auto pivot = partition(data, beg, end);
            if (pivot < k)
                beg = pivot;
            else if (pivot > k)
                end = pivot - 1;
            else
                return;
        }
    }
}

int main(void) {
    using namespace SearchForward;
    // using namespace SearchBidirectional;

    {
        vector<vector<int>> datas {
            { 3, 3, 2, 5, 3, 3, 8, 4, 7, 6, 9, 3, 3},
            { 2, 4, 5, 4, 3, 4, 7 },
            { -1, 2, 0 },
            { 7, 5, 2 },
            { 5, 2 },
            { 2, 5 }
        };

        for (auto& data : datas) {
            quickSort(data, 0, data.size()-1);
            copy(data.begin(), data.end(), ostream_iterator<int>(cout," "));
            std::cout << std::endl;

        }
    }

    {
        for (auto i = 1; i < 13; ++i) {
            vector<int> data {
                3, 3, 2, 5, 3, 3, 8, 4, 7, 6, 9, 3, 3
            };

            quickSelectK(data, 0, data.size()-1, i);
            data.resize(i);
            copy(data.begin(), data.end(), ostream_iterator<int>(cout," "));
            std::cout <<  "- " << i << std::endl;
        }
    }

}

/* left <= pivot < right
This solution doesn't chagne the first data, which will cause dead loop

beg = 0 end = 7 pivot = 3
0 1 2 3 4 5 6 7 8 9 10 11 12
3 3 2 3 3 3 3 4 7 6 5  9  8 */
template<typename T>
int partition_2(T& data, int beg, int end) {
    int i = beg + 1;
    int pivot = data[beg];

    for (int j = i; j < end; ++j) {
        if (data[j] <= pivot) {
            swap(data[i++], data[j]);
        }
    }

    return i;
}