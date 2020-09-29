#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>> &people) {
        std::sort(people.begin(), people.end(), [](const vector<int> &a, const vector<int> &b) {
            return a[0] > b[0] || (a[0] == b[0] && a[1] < b[1]);
        });
        vector<vector<int>> out;
        for (const auto &p : people)
            out.insert(out.begin() + p[1], p);
        return out;
    }
};

class SolutionMap {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>> &people) {
        std::map<int, vector<int>, std::greater<int>> m;
        for (const auto &p : people) m[p[0]].emplace_back(p[1]);
        vector<vector<int>> tmp;
        for (auto &p : m) {
            std::sort(p.second.begin(), p.second.end());
            for (const auto &h : p.second) tmp.emplace_back(vector<int>{p.first, h});
        }
        vector<vector<int>> out;
        for (const auto &p : tmp) out.insert(out.begin() + p[1], p);
        return out;
    }
};

// Comparison:
//   sort+insert:  O(n log n) sort + O(n^2) inserts (vector shift) = O(n^2) total
//   map approach: O(n log n) map ops + O(n^2) inserts = O(n^2) total, more overhead
// Edge cases:
//   - all same height -> sorted by k, inserted in order
//   - all different heights -> tallest first, k=0 for all
//   - single person -> returned as-is
//   - invalid input (k >= n) -> undefined; problem guarantees valid input

int main() {
    vector<vector<int>> people = {{7, 0}, {4, 4}, {7, 1}, {5, 0}, {6, 1}, {5, 2}};
    Solution s;
    auto out = s.reconstructQueue(people);
    for (const auto &p : out) std::cout << p[0] << "," << p[1] << " ";
    return 0;
}
