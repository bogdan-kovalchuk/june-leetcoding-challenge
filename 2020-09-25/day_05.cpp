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

class SolutionAlias {
public:
    SolutionAlias(vector<int> &w) : n(w.size()), prob(n), alias(n) {
        vector<double> scaled(n);
        double sum = 0;
        for (int x : w) sum += x;
        for (int i = 0; i < n; ++i) scaled[i] = w[i] * n / sum;
        std::deque<int> small, large;
        for (int i = 0; i < n; ++i)
            (scaled[i] < 1.0 ? small : large).push_back(i);
        while (!small.empty() && !large.empty()) {
            int s = small.back(), l = large.back();
            small.pop_back(); large.pop_back();
            prob[s] = s; alias[s] = l;
            scaled[l] -= (1.0 - scaled[s]);
            (scaled[l] < 1.0 ? small : large).push_back(l);
        }
    }
    int pickIndex() {
        int idx = std::rand() % n;
        double r = (double)(std::rand() % 1000) / 1000.0;
        return r < 1.0 ? prob[idx] : alias[idx];
    }
private:
    int n;
    vector<int> prob, alias;
};

int main() {
    vector<int> w = {1, 3};
    SolutionLowerBound obj(w);
    for (int i = 0; i < 5; ++i) std::cout << obj.pickIndex() << " ";
    return 0;
}
