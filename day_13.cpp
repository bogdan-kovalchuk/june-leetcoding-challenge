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

// Complexity:
//   Both: O(n^2) time for DP, O(n) space
//   Original reconstructs by backward scan — may pick wrong elements if dp values repeat
//   Parent-pointer reconstructs exactly via chain — more reliable, same asymptotic cost
// Edge cases:
//   - empty input -> empty result
//   - single element -> that element alone
//   - all pairwise divisible (e.g. {1,2,4,8}) -> entire sorted array
//   - no pair divisible (e.g. {3,5,7}) -> any single element
//   - duplicates in input -> sort handles, but problem says distinct
//   - contains 1 -> 1 divides everything, always in largest subset

static bool isDivisibleSubset(const vector<int> &v) {
    for (size_t i = 1; i < v.size(); ++i)
        for (size_t j = 0; j < i; ++j)
            if (v[i] % v[j] != 0 && v[j] % v[i] != 0) return false;
    return true;
}

int main() {
    vector<vector<int>> tests = {
        {4, 8, 10, 240},
        {1, 2, 3},
        {1, 2, 4, 8},
        {3, 5, 7},
        {1},
        {},
        {2, 3, 6, 12, 24}
    };

    Solution s1;
    SolutionParentPtr s2;

    for (const auto &test : tests) {
        vector<int> a = test, b = test;
        auto r1 = s1.largestDivisibleSubset(a);
        auto r2 = s2.largestDivisibleSubset(b);
        std::cout << "size=" << test.size()
                  << " => orig:" << r1.size() << " parent:" << r2.size()
                  << " valid1:" << isDivisibleSubset(r1)
                  << " valid2:" << isDivisibleSubset(r2)
                  << (r1.size() == r2.size() ? " OK" : " SIZE_DIFF")
                  << std::endl;
    }

    return 0;
}
