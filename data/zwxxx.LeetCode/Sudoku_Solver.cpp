/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 26, 2012
 Problem:    Sudoku Solver
 Difficulty: easy
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Write a program to solve a Sudoku puzzle by filling the empty cells.

 Empty cells are indicated by the character '.'.

 You may assume that there will be only one unique solution.

 Solution:
 dfs
 */
#include <vector>
#include <set>
#include <climits>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstring>
#include <list>
#include <fstream>
using namespace std;

class Solution {
public:
	bool recursion(vector<vector<char> > &board, list<int> &blank) {
		if (blank.empty()) {
			return true;
		}

		int cell = blank.front();
		int x = cell / 9, y = cell % 9;
		bool available[10];

		for (int i = 1; i <= 9; i++) {
			available[i] = true;

		}
		for (int i = 0; i < 9; i++) {
			if (board[i][y] != '.') {
				available[board[i][y] - '0'] = false;
			}
			if (board[x][i] != '.') {
				available[board[x][i] - '0'] = false;
			}
		}

		for (int i = 0, mx = x / 3 * 3, my = y / 3 * 3; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[mx + i][my + j] != '.') {
					available[board[mx + i][my + j] - '0'] = false;
				}
			}
		}

		for (int i = 1; i <= 9; i++) {
			if (available[i]) {
				blank.pop_front();
				board[x][y] = '0' + i;
				if (recursion(board, blank)) {
					return true;
				}
				blank.push_front(cell);
				board[x][y] = '.';
			}
		}

		return false;
	}

	void solveSudoku(vector<vector<char> > &board) {
		list<int> blank;

		for (int i = 0, count = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (board[i][j] == '.') {
					blank.push_back(count);
				}
				count++;
			}
		}
		recursion(board, blank);
	}
};
