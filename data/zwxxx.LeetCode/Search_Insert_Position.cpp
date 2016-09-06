/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 18, 2012
 Problem:    Search Insert Position
 Difficulty: easy
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Given a sorted array and a target value, return the index if the target is
 found. If not, return the index where it would be if it were inserted in order.

 You may assume no duplicates in the array.

 Here are few examples.
 [1,3,5,6], 5 → 2
 [1,3,5,6], 2 → 1
 [1,3,5,6], 7 → 4
 [1,3,5,6], 0 → 0

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

class Solution {
public:
	int searchInsert(int A[], int n, int target) {
		int left = 0, right = n - 1, mid, pos;

		while (left <= right) {
			mid = (left + right) / 2;
			if (target == A[mid]) {
				return mid;
			}
			if (target < A[mid]) {
				right = mid - 1;
				pos = mid;
			} else {
				left = mid + 1;
				pos = mid + 1;
			}
		}

		return pos;
	}
};
