/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 18, 2012
 Problem:    Set Matrix Zeroes
 Difficulty: easy
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Given a m x n matrix, if an element is 0, set its entire row and column to 0.
 Do it in place.

 Follow up:
 Did you use extra space?
 A straight forward solution using O(mn) space is probably a bad idea.
 A simple improvement uses O(m + n) space, but still not the best solution.
 Could you devise a constant space solution?

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
	void setZeroes(vector<vector<int> > &matrix) {
		int n = matrix.size();
		int m = (n != 0 ? matrix[0].size() : 0);
		int x = -1, y = -1;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (!matrix[i][j]) {
					if (x == -1) {
						x = i;
						y = j;
					}
					matrix[x][j] = 0;
					matrix[i][y] = 0;
				}
			}
		}

		if (x == -1) {
			return;
		}

		for (int i = 0; i < n; i++) {
			if (!matrix[i][y] && i != x) {
				for (int j = 0; j < m; j++) {
					matrix[i][j] = 0;
				}
			}
		}
		for (int i = 0; i < m; i++) {
			if (!matrix[x][i] && i != y) {
				for (int j = 0; j < n; j++) {
					matrix[j][i] = 0;
				}
			}
		}
		for (int i = 0; i < n; i++) {
			matrix[i][y] = 0;
		}
		for (int i = 0; i < m; i++) {
			matrix[x][i] = 0;
		}
	}
};
