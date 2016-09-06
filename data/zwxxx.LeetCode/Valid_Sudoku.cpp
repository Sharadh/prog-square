/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 27, 2012
 Problem:    Valid Sudoku
 Difficulty: easy
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.

 The Sudoku board could be partially filled, where empty cells are filled with
 the character '.'.

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
	bool isValidSudoku(vector<vector<char> > &board) {
		bool number[10];

		for (int i = 0; i < 9; i++) {
			memset(number, 0, sizeof(number));
			for (int j = 0; j < 9; j++) {
				if (board[i][j] != '.') {
					if (number[board[i][j] - '0']) {
						return false;
					}
					number[board[i][j] - '0'] = true;
				}

			}
		}

		for (int i = 0; i < 9; i++) {
			memset(number, 0, sizeof(number));
			for (int j = 0; j < 9; j++) {
				if (board[j][i] != '.') {
					if (number[board[j][i] - '0']) {
						return false;
					}
					number[board[j][i] - '0'] = true;
				}
			}
		}

		for (int i = 0; i < 9; i++) {
			memset(number, 0, sizeof(number));
			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 3; y++) {
					int bx = i / 3 * 3, by = i % 3 * 3;
					if (board[bx + x][by + y] != '.') {
						if (number[board[bx + x][by + y] - '0']) {
							return false;
						}
						number[board[bx + x][by + y] - '0'] = true;
					}
				}
			}
		}

		return true;
	}
};
