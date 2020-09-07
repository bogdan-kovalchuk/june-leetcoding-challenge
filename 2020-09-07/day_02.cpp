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

int main() {
    auto *a = new ListNode(4);
    a->next = new ListNode(5);
    a->next->next = new ListNode(1);
    a->next->next->next = new ListNode(9);
    SolutionShift s;
    s.deleteNode(a->next);
    return 0;
}
