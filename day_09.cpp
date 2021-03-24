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
    bool isSubsequence(const string &s, const string &t) {
        if (s.size() > t.size()) return false;
        if (s.empty()) return true;

        int i = 0, j = 0;
        while (i < s.size() && j < t.size()) {
            if (s[i] == t[j]) {
                i++;
            }
            j++;
        }
        return i == s.size();
    }
};

class SolutionBinarySearch {
public:
    bool isSubsequence(const string &s, const string &t) {
        map<char, vector<int>> idx;
        for (int i = 0; i < (int)t.size(); ++i)
            idx[t[i]].push_back(i);

        int pos = -1;
        for (char c : s) {
            auto it = idx.find(c);
            if (it == idx.end()) return false;
            auto nxt = std::upper_bound(it->second.begin(), it->second.end(), pos);
            if (nxt == it->second.end()) return false;
            pos = *nxt;
        }
        return true;
    }
};

// Comparison:
//   two-pointer:  O(|t|) time, O(1) space — single pass
//   binary search: O(|t| + |s|*log|t|) time, O(|t|) space — better for many queries on same t
// Edge cases:
//   - s empty -> true
//   - s longer than t -> false
//   - s == t -> true
//   - char in s not in t -> false
//   - all same characters -> works correctly

int main() {
    vector<pair<string, string>> tests = {
        {"abc", "ahbgdc"},
        {"axc", "ahbgdc"},
        {"", "abc"},
        {"abc", "abc"},
        {"aaaa", "aabbaa"},
        {"abc", "ab"}
    };

    Solution solution;
    SolutionBinarySearch solutionBS;

    for (const auto &test : tests) {
        bool r1 = solution.isSubsequence(test.first, test.second);
        bool r2 = solutionBS.isSubsequence(test.first, test.second);
        std::cout << "s=\"" << test.first << "\" t=\"" << test.second
                  << "\" => two-ptr:" << r1 << " bin-srch:" << r2;
        std::cout << (r1 == r2 ? " OK" : " MISMATCH") << std::endl;
    }

    return 0;
}
