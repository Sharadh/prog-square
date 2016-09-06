/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 17, 2012
 Problem:    Search for a Range
 Difficulty: easy
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Given a sorted array of integers, find the starting and ending position of a
 given target value.

 Your algorithm's runtime complexity must be in the order of O(log n).

 If the target is not found in the array, return [-1, -1].

 For example,
 Given [5, 7, 7, 8, 8, 10] and target value 8,
 return [3, 4].

 Solution:
 Variants of binary search.
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
	vector<int> searchRange(int A[], int n, int target) {
		int left = 0, right = n - 1;
		int x = -1, y = -1;
		vector<int> result;

		while (left <= right) {
			int mid = (left + right) / 2;
			if (target == A[mid]) {
				x = (x == -1 ? mid : min(x, mid));
				right = mid - 1;
			} else if (target < A[mid]) {
				right = mid - 1;
			} else {
				left = mid + 1;
			}
		}

		left = 0, right = n - 1;
		while (left <= right) {
			int mid = (left + right) / 2;
			if (target == A[mid]) {
				y = (y == -1 ? mid : max(y, mid));
				left = mid + 1;
			} else if (target < A[mid]) {
				right = mid - 1;
			} else {
				left = mid + 1;
			}
		}

		result.push_back(x);
		result.push_back(y);
		return result;
	}
};
