/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 26, 2012
 Problem:    Swap Nodes in Pairs
 Difficulty: easy
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Given a linked list, swap every two adjacent nodes and return its head.

 For example,
 Given 1->2->3->4, you should return the list as 2->1->4->3.

 Your algorithm should use only constant space. You may not modify the values
 in the list, only nodes itself can be changed.

 Solution:

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

class Solution {
public:
	ListNode *swapPairs(ListNode *head) {
		/* new head to make operation simpler */
		ListNode *newhead = new ListNode(0);
		ListNode *cur = newhead;
		newhead->next = head;

		while (cur->next != NULL && cur->next->next != NULL) {
			ListNode *n0 = cur;
			cur = cur->next;
			ListNode *n1 = cur;
			cur = cur->next;
			ListNode *n2 = cur;

			n0->next = n2;
			n1->next = n2->next;
			n2->next = n1;
			cur = n1;
		}

		head = newhead->next;
		delete newhead;
		return head;
	}
};
