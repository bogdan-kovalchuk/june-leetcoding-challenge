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


int main() {
    int n = 218;

    Solution solution;
    SolutionBit solutionBit;
    std::cout << "loop:" << solution.isPowerOfTwo(n) << std::endl;
    std::cout << "bit:" << solutionBit.isPowerOfTwo(n) << std::endl;

    return 0;
}
