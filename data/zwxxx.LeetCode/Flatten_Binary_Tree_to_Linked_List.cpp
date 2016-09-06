/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Oct 24, 2012
 Difficulty: medium
 Source:     
 Problem:
 Flatten Binary Tree to Linked List
 Given a binary tree, flatten it to a linked list in-place.

 For example,
 Given

         1
        / \
       2   5
      / \   \
     3   4   6
 The flattened tree should look like:
   1
    \
     2
      \
       3
        \
         4
          \
           5
            \
             6
 Hints:
 If you notice carefully in the flattened tree, each node's right child points
 to the next node of a pre-order traversal.
 Note:
 
 */
#include <vector>
#include <set>
#include <climits>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstring>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};

class Solution {
public:
	TreeNode* inOrder(TreeNode* root) {
		if (!root) {
			return NULL;
		}
		if (!root->left && !root->right) {
			return root;
		}

		TreeNode* left_last = inOrder(root->left);
		TreeNode* right_last = inOrder(root->right);

		if (left_last && right_last) {
			left_last->right = root->right;
			root->right = root->left;
			root->left = NULL;
			return right_last;
		}

		if (left_last) {
			root->right = root->left;
			root->left = NULL;
			return left_last;
		}

		root->left = NULL;
		return right_last;
	}

	void flatten(TreeNode *root) {
		inOrder(root);
	}
};
