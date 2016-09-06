/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 17, 2012
 Problem:    Search in Rotated Sorted Array II
 Difficulty: easy
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Follow up for "Search in Rotated Sorted Array":
 What if duplicates are allowed?

 Would this affect the run-time complexity? How and why?

 Write a function to determine if a given target is in the array.

 Solution:
 If the duplicates are allowed, the binary search is no longer feasible.
 For example,
 1 1 1 3 1, and search for 3
 target > A[mid] and we compare A[mid] and A[right].
 We found A[mid] == A[right], but 3 can appear at both sides.
 Thus I think the time timplexity is O(n) in the worst case.
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

class Solution {
public:
	bool search(int A[], int n, int target) {
		for (int i = 0; i < n; i++) {
			if (A[i] == target) {
				return true;
			}
		}
		return false;
	}
};
