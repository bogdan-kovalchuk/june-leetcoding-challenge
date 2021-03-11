#include <iostream>

class Solution {
public:
    bool isPowerOfTwo(int n) {
        if (n <= 0) return false;
        while (n > 1) {
            if (n % 2 == 0) {
                n = n / 2;
            } else {
                return false;
            }
        }
        return true;
    }
};

class SolutionBit {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }
};

// Comparison:
//   iterative: O(log n) time, O(1) space
//   bit trick: O(1) time, O(1) space
// Edge cases:
//   - n=0 -> false
//   - n=1 -> true (2^0)
//   - n<0 -> false
//   - INT_MAX -> false
//   - 2^30 -> true

int main() {
    int tests[] = {0, 1, 2, 16, 218, 1024, -4, 1073741824};

    Solution solution;
    SolutionBit solutionBit;

    for (int n : tests) {
        bool r1 = solution.isPowerOfTwo(n);
        bool r2 = solutionBit.isPowerOfTwo(n);
        std::cout << "n=" << n << " => loop:" << r1 << " bit:" << r2;
        std::cout << (r1 == r2 ? " OK" : " MISMATCH") << std::endl;
    }

    return 0;
}
