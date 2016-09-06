/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 6, 2012
 Problem:    Merge k Sorted Lists
 Difficulty: medium
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Merge k sorted linked lists and return it as one sorted list. Analyze and
 describe its complexity.

 Solution:
 Use min heap, the time complexity is O(n*lgk), n is the number of elelments
 of all lists.
 */
#include <vector>
#include <set>
#include <climits>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

struct Compare {
	bool operator ()(const ListNode* a, const ListNode* b) {
		return a->val > b->val;
	}
};
class Solution {
public:
	ListNode *mergeKLists(vector<ListNode *> &lists) {
		priority_queue<ListNode *, vector<ListNode *>, Compare> min_heap;
		ListNode *head = NULL;
		ListNode *tail = NULL;

		for (unsigned i = 0; i < lists.size(); i++) {
			if (lists[i] != NULL) {
				min_heap.push(lists[i]);
			}
		}

		while (!min_heap.empty()) {
			ListNode *node = min_heap.top();
			min_heap.pop();
			if (head == NULL) {
				head = node;
				tail = node;
			} else {
				tail->next = node;
				tail = node;
			}
			node = node->next;
			if (node != NULL) {
				min_heap.push(node);
			}
		}

		return head;
	}
};

// pairwise merge, Ke Hu (mrhuke@gmail.com)
class Solution {
public:

    ListNode *mergeTwoLists(ListNode *a, ListNode *b)
    {
        if (!a || !b) return a == NULL ? b : a;
        if (a->val < b->val){
            ListNode *merged = mergeTwoLists(a->next, b);
            a->next = merged;
            return a;
        }
        else{
            ListNode *merged = mergeTwoLists(a, b->next);
            b->next = merged;
            return b;
        }
    }

    ListNode *mergeKLists(vector<ListNode *> &lists) {
        
        if (lists.empty()) return NULL;
        int curSize = lists.size();
        while(curSize > 1){
            int halfSize = curSize/2;
            for ( int i = 0; i < halfSize; ++i){
                ListNode *a = lists[i];
                ListNode *b = lists[i+halfSize+curSize%2];
                ListNode *c = mergeTwoLists(a,b);
                lists[i] = c;
            }
            curSize = halfSize + curSize % 2;
        }
        return lists[0];
    }
};

// a merge-sort like idea, mrhuke@gmail.com, may. 13
public class Solution {
    
    public ListNode mergeTwoLists(ListNode list1, ListNode list2)
    {
        if (list1 == null || list2 == null) 
            return list1 == null ? list2 : list1;
        
        ListNode newHead = null, cur = null;
        while( list1 != null && list2 != null ){
            if ( list1.val < list2.val ){
                if (newHead == null){
                    newHead = cur = list1;
                }else{
                    cur.next = list1;
                    cur = cur.next;
                }
                list1 = list1.next;
            }
            else{
                if (newHead == null){
                    newHead = cur = list2;
                }else{
                    cur.next = list2;
                    cur = cur.next;
                }
                list2 = list2.next;
            }
        }
        
        if (list1 != null)
            cur.next = list1;
        if (list2 != null)
            cur.next = list2;
        return newHead;
    }
    
    public ListNode mergeLists(ArrayList<ListNode> lists, int i, int j)
    {
        if ( i >= j ) return lists.get(i);
        int mid = (i+j)/2;
        ListNode list1 = mergeLists(lists, i, mid);
        ListNode list2 = mergeLists(lists, mid+1, j);
        ListNode merged = mergeTwoLists(list1, list2);
        return merged;
    }
    
    public ListNode mergeKLists(ArrayList<ListNode> lists) {
        if (lists.isEmpty()) return null;
        return mergeLists(lists, 0, lists.size()-1);
    }
}
