/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 23, 2012
 Problem:    Spiral Matrix II
 Difficulty: easy
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Given an integer n, generate a square matrix filled with elements from 1 to
 n2 in spiral order.

 For example,
 Given n = 3,

 You should return the following matrix:
 [
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
 ]

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
	vector<vector<int> > generateMatrix(int n) {
		int x = 0, y = 0, dir = 0, nx, ny;
		int count = 1;
		vector<vector<int> > result;
		int matrix[n][n];

		if (n == 0) {
			return result;
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				matrix[i][j] = 0;
			}
		}

		while (true) {
			matrix[x][y] = count++;
			nextStep(dir, x, y, nx, ny);
			if (!(0 <= nx && nx < n && 0 <= ny && ny < n && !matrix[nx][ny])) {
				dir = (dir + 1) % 4;
				nextStep(dir, x, y, nx, ny);
				if (!(0 <= nx && nx < n && 0 <= ny && ny < n && !matrix[nx][ny])) {
					break;
				}
			}
			x = nx, y = ny;
		}

		for (int i = 0; i < n; i++) {
			vector<int> row(matrix[i], matrix[i] + n);
			result.push_back(row);
		}

		return result;
	}
};
