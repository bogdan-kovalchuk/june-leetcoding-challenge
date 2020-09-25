#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>

using std::vector;

class Solution {
public:
    Solution(vector<int> &w) {
        for (auto i : w) {
            sum += i;
            increment_sum.push_back(sum);
        }
    }
    int pickIndex() {
        int num = rand() % sum;
        return upper_bound(increment_sum.begin(), increment_sum.end(), num) - increment_sum.begin();
    }
private:
    vector<int> increment_sum;
    int sum = 0;
};

class SolutionLowerBound {
public:
    SolutionLowerBound(vector<int> &w) : prefix(w.size()) {
        std::partial_sum(w.begin(), w.end(), prefix.begin());
        total = prefix.back();
    }
    int pickIndex() {
        int target = std::rand() % total;
        return (int)(std::lower_bound(prefix.begin(), prefix.end(), target + 1) - prefix.begin());
    }
private:
    vector<int> prefix;
    int total = 0;
};

int main() {
    vector<int> w = {1, 3};
    SolutionLowerBound obj(w);
    for (int i = 0; i < 5; ++i) std::cout << obj.pickIndex() << " ";
    return 0;
}
