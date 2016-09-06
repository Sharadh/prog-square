/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 27, 2012
 Problem:    Unique Paths
 Difficulty: easy
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

 The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

 How many possible unique paths are there?
 Note: m and n will be at most 100.

 Solution:
 for a matrix of 5 * 5:
 1  1  1  1  1
 1  2  3  4  5
 1  3  6  10 15
 1  4  10 20 35
 1  5  15 35 70

 array[m][n] = array[m-1][n] + array[m][n-1]
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
	int uniquePaths(int m, int n) {
		int array[n];

		for (int i = 0; i < n; i++) {
			array[i] = 1;
		}
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				array[j] = array[j - 1] + array[j];
			}
		}
		return array[n - 1];
	}
};
