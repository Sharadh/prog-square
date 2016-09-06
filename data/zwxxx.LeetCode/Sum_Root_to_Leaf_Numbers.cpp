/*
Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

For example,

    1
   / \
  2   3
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.

Return the sum = 12 + 13 = 25.
*/

// by Ke Hu (mrhuke@gmail.com)
class Solution {
public:

    void dfs(TreeNode *root, int number, int &sum)
    {
        if (root == NULL) return;
        
        int newNumber = number*10+root->val;
        if (root->left==NULL && root->right==NULL)
            sum += newNumber;
            
        dfs(root->left, newNumber, sum);
        dfs(root->right, newNumber, sum);
    }

    int sumNumbers(TreeNode *root) {
        int sum = 0;
        dfs(root, 0, sum);
        return sum;
    }
};