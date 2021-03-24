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


int main() {
    string s = "abc", t = "ahbgdc";

    Solution solution;
    SolutionBinarySearch solutionBS;
    std::cout << "two-ptr:" << solution.isSubsequence(s, t) << std::endl;
    std::cout << "bin-srch:" << solutionBS.isSubsequence(s, t) << std::endl;

    return 0;
}
