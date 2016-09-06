/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 23, 2012
 Problem:    Spiral Matrix
 Difficulty: easy
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Given a matrix of m x n elements (m rows, n columns), return all elements of
 the matrix in spiral order.

 For example,
 Given the following matrix:

 [
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
 ]
 You should return [1,2,3,6,9,8,7,4,5].

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
	void nextStep(int dir, int x, int y, int &nx, int &ny) {
		nx = x;
		ny = y;
		if (dir == 0) {
			ny++;
		} else if (dir == 1) {
			nx++;
		} else if (dir == 2) {
			ny--;
		} else {
			nx--;
		}
	}
	vector<int> spiralOrder(vector<vector<int> > &matrix) {
		int m = matrix.size();
		int n = (m != 0 ? matrix[0].size() : 0);
		int x = 0, y = 0, dir = 0, nx, ny;
		bool map[m][n];
		vector<int> result;

		if (m == 0) {
			return result;
		}

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				map[i][j] = true;
			}
		}

		while (true) {
			map[x][y] = false;
			result.push_back(matrix[x][y]);
			nextStep(dir, x, y, nx, ny);
			if (!(0 <= nx && nx < m && 0 <= ny && ny < n && map[nx][ny])) {
				dir = (dir + 1) % 4;
				nextStep(dir, x, y, nx, ny);
				if (!(0 <= nx && nx < m && 0 <= ny && ny < n && map[nx][ny])) {
					break;
				}
			}
			x = nx, y = ny;
		}
		return result;
	}
};
