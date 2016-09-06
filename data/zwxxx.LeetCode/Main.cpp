#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>
#include "Substring_with_Concatenation_of_All_Words.cpp"
using namespace std;
/*
 ListNode *head, *tail;

 void insert(int x) {
 if (!head) {
 head = new ListNode(x);
 tail = head;
 } else {
 tail->next = new ListNode(x);
 tail = tail->next;
 }
 }*/
int main() {
	 vector<string> L;
	 L.push_back("a");
	 Solution s;

	 s.findSubstring("a", L);
	return 0;
}
