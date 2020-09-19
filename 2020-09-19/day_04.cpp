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

int main() {
    vector<char> s = {'h', 'e', 'l', 'l', 'o'};
    SolutionXOR s2;
    s2.reverseString(s);
    for (const auto &ch : s) std::cout << ch << " ";
    return 0;
}
