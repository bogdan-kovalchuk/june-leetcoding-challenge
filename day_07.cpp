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


int main() {
    int amount = 5;
    vector<int> coins = {1, 2, 5};

    Solution solution;
    Solution1D solution1d;
    std::cout << "2D:" << solution.change(amount, coins) << std::endl;
    std::cout << "1D:" << solution1d.change(amount, coins) << std::endl;

    return 0;
}
