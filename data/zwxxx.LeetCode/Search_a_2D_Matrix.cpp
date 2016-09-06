/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 17, 2012
 Problem:    Search a 2D Matrix
 Difficulty: easy
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Write an efficient algorithm that searches for a value in an m x n matrix.
 This matrix has the following properties:

 Integers in each row are sorted from left to right.
 The first integer of each row is greater than the last integer of the previous
 row.
 For example,

 Consider the following matrix:

 [
 [1,   3,  5,  7],
 [10, 11, 16, 20],
 [23, 30, 34, 50]
 ]
 Given target = 3, return true.

 Solution:
 If you picture the matrix as an one dimension array and use binary search, the
 time complexity is O(lg(m*n)).
 If you first binary search the array of first elements of all rows, then binary
 search the elements in that row, the time complexity is still O(lg(m*n)).
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
	int n;
	int m;
	bool searchMatrix(vector<vector<int> > &matrix, int target) {
		n = matrix.size();
		m = (n != 0 ? matrix[0].size() : 0);
		int left = 0, right = n * m - 1, x, y;

		while (left <= right) {
			int mid = (left + right) / 2;
			if (target == matrix[mid / m][mid % m]) {
				return true;
			}
			if (target < matrix[mid / m][mid % m]) {
				right = mid - 1;
			} else {
				left = mid + 1;
			}
		}
		return false;
	}
};
