/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 27, 2012
 Problem:    Word Search
 Difficulty: easy
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Given a 2D board and a word, find if the word exists in the grid.

 The word can be constructed from letters of sequentially adjacent cell, where
 "adjacent" cells are those horizontally or vertically neighboring. The same
 letter cell may not be used more than once.

 For example,
 Given board =

 [
 ["ABCE"],
 ["SFCS"],
 ["ADEE"]
 ]
 word = "ABCCED", -> returns true,
 word = "SEE", -> returns true,
 word = "ABCB", -> returns false.

 Solution:
 When given this problem, I have two solutions instantly.
 1) construct a tree simliar to trie.
 2) DFS.
 The tree construction solution will get a very big tree and not so simple.
 The DFS method is simple to implement, although not so fast.
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
	int m;
	int n;

	bool valid(int &nx, int &ny, int dir, vector<vector<char> > &board, char c) {
		if (dir == 0) { nx--; }
		else if (dir == 1) { nx++; }
		else if (dir == 2) { ny--; }
		else { ny++; }

		if (0 <= nx && nx < m && 0 <= ny && ny < n && board[nx][ny] == c) {
			return true;
		}
		return false;
	}

	bool dfs(vector<vector<char> > &board, string word, int pos, int x, int y) {
		if (pos >= word.length()) {
			return true;
		}

		for (int i = 0, nx, ny; i < 4; i++) {
			nx = x, ny = y;
			if (valid(nx, ny, i, board, word[pos])) {
				char c = board[nx][ny];
				board[nx][ny] = '.';
				if (dfs(board, word, pos + 1, nx, ny)) {
					return true;
				}
				board[nx][ny] = c;
			}
		}
		return false;
	}

	bool exist(vector<vector<char> > &board, string word) {
		m = board.size();
		n = board[0].size();

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (board[i][j] == word[0]) {
					char c = board[i][j];
					board[i][j] = '.';
					if (dfs(board, word, 1, i, j)) {
						return true;
					}
					board[i][j] = c;
				}
			}
		}

		return false;
	}
}
;
