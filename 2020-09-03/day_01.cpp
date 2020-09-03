#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode *invertTree(TreeNode *root) {
        traverce(root);
        return root;
    }
    void traverce(TreeNode *root) {
        if (root == nullptr) return;
        TreeNode *tmp = root->left;
        root->left = root->right;
        root->right = tmp;
        traverce(root->right);
        traverce(root->left);
    }
};

class SolutionBFS {
public:
    TreeNode *invertTree(TreeNode *root) {
        if (!root) return nullptr;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode *n = q.front(); q.pop();
            std::swap(n->left, n->right);
            if (n->left)  q.push(n->left);
            if (n->right) q.push(n->right);
        }
        return root;
    }
};

// Comparison:
//   Recursive DFS: O(n) time, O(h) stack  (h = tree height, worst O(n))
//   Iterative BFS: O(n) time, O(w) queue  (w = max width, worst O(n/2))
// Edge cases:
//   null root, single node, left-only chain, right-only chain, complete tree

TreeNode *insertLevelOrder(vector<int> nodes, TreeNode *root, int i, int n) {
    if (i < n && nodes[i] != 0) {
        auto *temp = new TreeNode(nodes[i]);
        root = temp;
        root->left = insertLevelOrder(nodes, root->left, 2 * i + 1, n);
        root->right = insertLevelOrder(nodes, root->right, 2 * i + 2, n);
    }
    return root;
}

int main() {
    vector<int> nodes = {4, 2, 7, 1, 3, 6, 9};
    TreeNode *root = insertLevelOrder(nodes, root, 0, nodes.size());
    SolutionBFS s;
    TreeNode *out = s.invertTree(root);
    return 0;
}
