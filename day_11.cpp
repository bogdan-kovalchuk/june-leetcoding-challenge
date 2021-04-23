#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>


using std::vector;
using std::map;
using std::string;

class Solution {
public:
    void sortColors(vector<int> &nums) {
        int colors[3] = {};
        for (const auto &n : nums)
            colors[n]++;

        int k = 0;
        for (int i = 0; i < sizeof(colors) / sizeof(colors[0]); ++i) {
            for (int j = 0; j < colors[i]; ++j) {
                nums[k] = i;
                k++;
            }
        }
    }
};

class SolutionDutchFlag {
public:
    void sortColors(vector<int> &nums) {
        int lo = 0, mid = 0, hi = (int)nums.size() - 1;
        while (mid <= hi) {
            if (nums[mid] == 0) {
                std::swap(nums[lo++], nums[mid++]);
            } else if (nums[mid] == 1) {
                mid++;
            } else {
                std::swap(nums[mid], nums[hi--]);
            }
        }
    }
};

// Comparison:
//   counting sort:   O(n) time, O(1) space — two passes, stable
//   dutch flag:      O(n) time, O(1) space — one pass, in-place swaps
// Edge cases:
//   - all same color -> no swaps needed (dutch flag) or single bucket (counting)
//   - already sorted -> both handle correctly
//   - reverse sorted -> both handle correctly
//   - single element -> trivial
//   - two colors only -> both work
// Complexity:
//   Both O(n) time, O(1) extra space; dutch flag does fewer writes on average

int main() {
    vector<vector<int>> tests = {
        {2, 0, 2, 1, 1, 0},
        {0, 0, 0},
        {2, 2, 2},
        {1, 1, 1},
        {0, 1, 2},
        {2, 1, 0},
        {1, 0, 2, 0, 1, 2, 0, 1, 2}
    };

    for (const auto &test : tests) {
        vector<int> a = test, b = test;
        Solution s1;
        SolutionDutchFlag s2;
        s1.sortColors(a);
        s2.sortColors(b);
        std::cout << "input: ";
        for (int x : test) std::cout << x << " ";
        std::cout << "=> count:";
        for (int x : a) std::cout << x << " ";
        std::cout << " flag:";
        for (int x : b) std::cout << x << " ";
        std::cout << (a == b ? " OK" : " MISMATCH") << std::endl;
    }

    return 0;
}
