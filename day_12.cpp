#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <cstdlib>


using std::vector;
using std::set;

class RandomizedSet {
public:
    RandomizedSet() {}

    bool insert(int val) {
        bool retval = false;
        if (s.find(val) == s.end()){
            s.insert(val);
            retval = true;
        }
        return retval;
    }

    bool remove(int val) {
        bool retval = false;
        if (s.find(val) != s.end()){
            s.erase(val);
            retval = true;
        }
        return retval;
    }

    int getRandom() {
        auto it = s.begin();
        int random = std::rand() % s.size();
        std::advance(it, random);
        return *it;
    }
private:
    set<int> s;
};

class RandomizedSetO1 {
public:
    bool insert(int val) {
        if (valToIndex.count(val)) return false;
        valToIndex[val] = vals.size();
        vals.push_back(val);
        return true;
    }

    bool remove(int val) {
        if (!valToIndex.count(val)) return false;
        int idx = valToIndex[val];
        int last = vals.back();
        vals[idx] = last;
        valToIndex[last] = idx;
        vals.pop_back();
        valToIndex.erase(val);
        return true;
    }

    int getRandom() {
        return vals[std::rand() % vals.size()];
    }
private:
    vector<int> vals;
    std::unordered_map<int, int> valToIndex;
};

// Comparison:
//   set-based:  insert O(log n), remove O(log n), getRandom O(n) — advance is linear
//   O(1) set:   insert O(1), remove O(1), getRandom O(1) — swap-with-last trick
// Edge cases:
//   - insert duplicate -> false, no change
//   - remove non-existent -> false
//   - getRandom on single element -> always returns it
//   - remove then re-insert -> works correctly
//   - empty set getRandom -> undefined; problem guarantees non-empty
// Complexity:
//   O(1) set uses amortized O(1) via unordered_map + vector swap-remove

int main() {
    RandomizedSetO1 rs;
    std::cout << "insert 1: " << rs.insert(1) << std::endl;
    std::cout << "remove 2: " << rs.remove(2) << std::endl;
    std::cout << "insert 2: " << rs.insert(2) << std::endl;
    std::cout << "getRandom: " << rs.getRandom() << std::endl;
    std::cout << "remove 1: " << rs.remove(1) << std::endl;
    std::cout << "insert 2 dup: " << rs.insert(2) << std::endl;
    std::cout << "getRandom: " << rs.getRandom() << std::endl;

    return 0;
}
