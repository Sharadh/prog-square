/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 17, 2012
 Problem:    Search in Rotated Sorted Array
 Difficulty: medium
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Suppose a sorted array is rotated at some pivot unknown to you beforehand.

 (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

 You are given a target value to search. If found in the array return its index,
 otherwise return -1.

 You may assume no duplicate exists in the array.

 Solution:
 If we say the space between the minimal value and the maximal value is the 'gap'.
 Then the segment contains the 'gap' must have the first element is larger than
 the last element; otherwise the first element is smaller than the last element
 because it's ordered.
 Also be careful with the boundry conditons.
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
	int search(int A[], int n, int target) {
		int left = 0, right = n - 1;

		while (left <= right) {
			int mid = (left + right) / 2;
			if (target == A[mid]) {
				return mid;
			}
			if (target < A[mid]) {
				if (target < A[left] && A[left] <= A[mid]) {
					left = mid + 1;
				} else {
					right = mid - 1;
				}
			} else {
				if (target > A[mid]) {
					if (target > A[right] && A[right] >= A[mid]) {
						right = mid - 1;
					} else {
						left = mid + 1;
					}
				}
			}
		}
		return -1;
	}
};
