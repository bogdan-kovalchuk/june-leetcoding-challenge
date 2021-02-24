#include <iostream>
#include <vector>
#include <map>


using std::vector;
using std::map;

class Solution {
public:
    int change(int amount, vector<int> &coins) {
        vector<vector<int>> dp(coins.size() + 1, vector<int>(amount + 1, 0));

        for (int i = 0; i <= coins.size(); ++i) dp[i][0] = 1;

        for (int i = 1; i <= coins.size(); ++i) {
            for (int j = 1; j <= amount; ++j) {
                if (j < coins[i - 1]) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i - 1]];
                }
            }
        }

        return dp.back().back();
    }
};

class Solution1D {
public:
    int change(int amount, vector<int> &coins) {
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;

        for (const auto &coin : coins) {
            for (int j = coin; j <= amount; ++j) {
                dp[j] += dp[j - coin];
            }
        }

        return dp[amount];
    }
};

// Comparison:
//   2D DP: O(n*amount) time, O(n*amount) space
//   1D DP: O(n*amount) time, O(amount) space — same speed, less memory
// Edge cases:
//   - amount=0 -> 1 way (use no coins)
//   - empty coins, amount>0 -> 0 ways
//   - single coin that divides amount -> 1 way
//   - coin larger than amount -> skipped
// Complexity:
//   Both: time O(coins.size() * amount), 1D space O(amount) vs 2D space O(coins.size() * amount)

int main() {
    vector<vector<int>> test_coins = {
        {1, 2, 5},
        {2},
        {},
        {1},
        {3, 5, 7}
    };
    vector<int> test_amounts = {5, 3, 0, 1, 11};

    Solution solution;
    Solution1D solution1d;

    for (size_t i = 0; i < test_coins.size(); ++i) {
        int r1 = solution.change(test_amounts[i], test_coins[i]);
        int r2 = solution1d.change(test_amounts[i], test_coins[i]);
        std::cout << "amount=" << test_amounts[i] << " coins={";
        for (size_t j = 0; j < test_coins[i].size(); ++j) {
            if (j) std::cout << ",";
            std::cout << test_coins[i][j];
        }
        std::cout << "} => 2D:" << r1 << " 1D:" << r2;
        std::cout << (r1 == r2 ? " OK" : " MISMATCH") << std::endl;
    }

    return 0;
}
