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


int main() {
    vector<int> nums = {2, 0, 2, 1, 1, 0};

    Solution solution;
    solution.sortColors(nums);
    for (const auto &n : nums) std::cout << n << " ";
    std::cout << std::endl;

    vector<int> nums2 = {2, 0, 2, 1, 1, 0};
    SolutionDutchFlag solutionDF;
    solutionDF.sortColors(nums2);
    for (const auto &n : nums2) std::cout << n << " ";
    std::cout << std::endl;

    return 0;
}
