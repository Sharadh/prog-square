/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Oct 24, 2012
 Difficulty: 
 Source:     
 Problem:
 Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

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

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

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
	vector<struct TreeNode*> nodes;

	TreeNode* build(int start, int end) {
		if (start > end) {
			return NULL;
		}

		if (start == end) {
			return nodes[start];
		}

		int mid = (end + start) / 2;
		nodes[mid]->left = build(start, mid - 1);
		nodes[mid]->right = build(mid + 1, end);

		return nodes[mid];
	}

	TreeNode *sortedListToBST(ListNode *head) {
		nodes.clear();

		while (head) {
			struct TreeNode* n = new struct TreeNode(head->val);
			nodes.push_back(n);
			head = head->next;
		}

		return build(0, nodes.size() - 1);
	}
};
