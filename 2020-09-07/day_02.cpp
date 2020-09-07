#include <iostream>
#include <vector>

using std::vector;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    void deleteNode(ListNode *node) {
        node->val = node->next->val;
        node->next = node->next->next;
    }
};

class SolutionShift {
public:
    void deleteNode(ListNode *node) {
        ListNode *cur = node, *prev = nullptr;
        while (cur->next) {
            if (prev) prev->val = cur->val;
            prev = cur;
            cur = cur->next;
        }
        prev->val = cur->val;
        prev->next = nullptr;
    }
};

// Comparison:
//   Copy-next:  O(1) time, O(1) space  — copies next val, skips next node
//   Shift:      O(k) time, O(1) space  — shifts all trailing vals (k = nodes after target)
// Edge cases:
//   - node is the only node (no next)  -> both UB / crash; problem guarantees non-tail
//   - node is second-to-last           -> copy-next deletes tail correctly
//   - duplicate values in list         -> both work; identity by pointer, not value

int main() {
    auto *a = new ListNode(4);
    a->next = new ListNode(5);
    a->next->next = new ListNode(1);
    a->next->next->next = new ListNode(9);
    SolutionShift s;
    s.deleteNode(a->next);
    return 0;
}
