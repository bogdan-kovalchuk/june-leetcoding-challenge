#include <iostream>
#include <vector>
#include <set>
#include <algorithm>


using std::vector;
using std::set;

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int> &nums) {
        if (nums.size() == 0 || nums.size() == 1) return nums;

        int max_elem = 0;
        vector<int> dp(nums.size(), 1);
        vector<int> result;

        sort(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (nums[i] % nums[j] == 0) {
                    if (dp[i] < 1 + dp[j]) dp[i] = 1 + dp[j];
                }
            }
            if (dp[i] > max_elem)
                max_elem = dp[i];
        }

        for (int i = nums.size() - 1; i >= 0; i--) {
            if (dp[i] == max_elem) {
                result.push_back(nums[i]);
                max_elem--;
            }
        }

        return result;
    }
};

class SolutionParentPtr {
public:
    vector<int> largestDivisibleSubset(vector<int> &nums) {
        if (nums.empty()) return {};
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<int> dp(n, 1);
        vector<int> parent(n, -1);
        int maxLen = 1, maxIdx = 0;

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] % nums[j] == 0 && dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                    parent[i] = j;
                }
            }
            if (dp[i] > maxLen) {
                maxLen = dp[i];
                maxIdx = i;
            }
        }

        vector<int> result;
        int cur = maxIdx;
        while (cur != -1) {
            result.push_back(nums[cur]);
            cur = parent[cur];
        }
        return result;
    }
};


int main() {
    vector<int> nums = {4, 8, 10, 240};

    Solution solution;
    auto out = solution.largestDivisibleSubset(nums);
    for (const auto &n : out) std::cout << n << " ";
    std::cout << std::endl;

    SolutionParentPtr solutionPP;
    auto out2 = solutionPP.largestDivisibleSubset(nums);
    for (const auto &n : out2) std::cout << n << " ";
    std::cout << std::endl;

    return 0;
}
