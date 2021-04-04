#include <iostream>
#include <vector>
#include <map>
#include <string>


using std::vector;
using std::map;
using std::string;

class Solution {
public:
    int searchInsert(vector<int> &nums, int target) {
        for (int i = 0; i < nums.size(); ++i)
            if ((nums[i] == target) || (nums[i] > target)) return i;
        return nums.size();
    }
};

class SolutionBinarySearch {
public:
    int searchInsert(vector<int> &nums, int target) {
        int lo = 0, hi = (int)nums.size();
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] < target) lo = mid + 1;
            else hi = mid;
        }
        return lo;
    }
};

// Comparison:
//   linear:  O(n) time, O(1) space
//   binary:  O(log n) time, O(1) space — much faster for large sorted arrays
// Edge cases:
//   - target smaller than all elements -> insert at 0
//   - target larger than all elements -> insert at end
//   - target exists in array -> return its index
//   - empty array -> return 0
//   - single element array

int main() {
    vector<vector<int>> test_nums = {
        {1, 3, 5, 6},
        {1, 3, 5, 6},
        {1, 3, 5, 6},
        {1, 3, 5, 6},
        {},
        {5}
    };
    vector<int> test_targets = {5, 2, 7, 0, 1, 3};

    for (size_t i = 0; i < test_nums.size(); ++i) {
        Solution s1;
        SolutionBinarySearch s2;
        int r1 = s1.searchInsert(test_nums[i], test_targets[i]);
        int r2 = s2.searchInsert(test_nums[i], test_targets[i]);
        std::cout << "target=" << test_targets[i] << " => linear:" << r1 << " binary:" << r2;
        std::cout << (r1 == r2 ? " OK" : " MISMATCH") << std::endl;
    }

    return 0;
}
