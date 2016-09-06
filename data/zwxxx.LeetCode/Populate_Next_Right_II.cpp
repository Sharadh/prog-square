/*
Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous solution still work?

Note:

You may only use constant extra space.
For example,
Given the following binary tree,

         1
       /  \
      2    3
     / \    \
    4   5    7
After calling your function, the tree should look like:

         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \    \
    4-> 5 -> 7 -> NULL
*/

// Ke Hu (mrhuke@gmail.com) May, 2013
// The idea is, at level, link the nodes at the next level, and do that recursively
// This is done by using three pointers, cur (current node), prev (previous pointer in the next level), next(the starting node in the next layer to connect)
// Each recursion deals with one level.

/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (!root) return;
        
        TreeLinkNode *cur = root, *prev = NULL, *next = NULL;
        while(cur)
        {
            if (cur->left){
                if (prev) prev->next = cur->left;  // link nodes
                prev = cur->left;
                if (!next) next = cur->left; // record next node
            }
            if (cur->right){
                if (prev) prev->next = cur->right; // link nodes
                prev = cur->right;
                if (!next) next = cur->right; // record next node
            }
            cur = cur->next; // deal with the next node's children at the same level
        }
        connect(next); // recursion
    }
};