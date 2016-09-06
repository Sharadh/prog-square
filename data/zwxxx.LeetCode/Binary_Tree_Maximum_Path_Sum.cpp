/* Given a binary tree, find the maximum path sum.

The path may start and end at any node in the tree.

For example:
Given the below binary tree,

       1
      / \
     2   3
Return 6.
*/

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Ke Hu (mrhuke@gmail.com) Apr. 2013
class Solution {
public:

    int maxPathSum(TreeNode *root, int &leftToRoot, int &rightToRoot)
    {
        if (!root){
            leftToRoot = 0;
            rightToRoot = 0;
            return INT_MIN;
        }
        
        int leftLeftToRoot, leftRightToRoot,rightLeftToRoot, rightRightToRoot;
        int leftPath = maxPathSum(root->left, leftLeftToRoot, leftRightToRoot);
        int rightPath = maxPathSum(root->right, rightLeftToRoot, rightRightToRoot);
        
        leftToRoot = max( max(leftLeftToRoot, leftRightToRoot) + root->val, root->val);
        rightToRoot = max( max(rightLeftToRoot, rightRightToRoot) + root->val, root->val);
        int maxPath = max( leftToRoot + rightToRoot - root->val, max(leftPath, rightPath) );
        
        return maxPath;
    }

    int maxPathSum(TreeNode *root) {
        int leftToRoot, rightToRoot;
        return maxPathSum(root, leftToRoot, rightToRoot);
    }
};