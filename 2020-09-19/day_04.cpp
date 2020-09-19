#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
    void reverseString(vector<char> &s) {
        int i = 0, j = s.size() - 1;
        while (i <= j) {
            int tmp = s[i];
            s[i] = s[j];
            s[j] = tmp;
            i++;
            j--;
        }
    }
};

class SolutionXOR {
public:
    void reverseString(vector<char> &s) {
        int i = 0, j = (int)s.size() - 1;
        while (i < j) {
            s[i] ^= s[j];
            s[j] ^= s[i];
            s[i] ^= s[j];
            ++i; --j;
        }
    }
};

class SolutionRecursive {
public:
    void reverseString(vector<char> &s) { rev(s, 0, (int)s.size() - 1); }
    void rev(vector<char> &s, int i, int j) {
        if (i >= j) return;
        std::swap(s[i], s[j]);
        rev(s, i + 1, j - 1);
    }
};

// Comparison:
//   tmp-swap:    O(n) time, O(1) space, iterative
//   XOR-swap:    O(n) time, O(1) space, no temp var but 3 reads/writes per pair
//   recursive:   O(n) time, O(n) stack space (call depth n/2)
// Edge cases:
//   - empty vector -> no-op
//   - single element -> no-op
//   - even/odd length -> middle element stays in place for odd

int main() {
    vector<char> s = {'h', 'e', 'l', 'l', 'o'};
    SolutionXOR s2;
    s2.reverseString(s);
    for (const auto &ch : s) std::cout << ch << " ";
    return 0;
}
