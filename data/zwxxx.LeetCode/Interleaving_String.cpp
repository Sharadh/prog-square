/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Oct 24, 2012
 Difficulty: easy
 Source:     http://www.leetcode.com/onlinejudge
 Problem:
 Interleaving String

 Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

 For example,
 Given:
 s1 = "aabcc",
 s2 = "dbbca",

 When s3 = "aadbbcbcac", return true.
 When s3 = "aadbbbaccc", return false.

 Note:
 DP.

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
	bool isInterleave(string s1, string s2, string s3) {
		int n = s1.length();
		int m = s2.length();
		bool f[n + 1][m + 1];

		if (n + m != s3.length()) {
			return false;
		}

		f[0][0] = true;
		for (int i = 1; i <= n; i++) {
			f[i][0] = s1.substr(0, i).compare(s3.substr(0, i)) == 0;
		}

		for (int j = 1; j <= m; j++) {
			f[0][j] = s2.substr(0, j).compare(s3.substr(0, j)) == 0;
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				f[i][j] = false;
				if (s1[i - 1] == s3[i + j - 1] && f[i - 1][j]) {
					f[i][j] = true;
				}
				if (s2[j - 1] == s3[i + j - 1] && f[i][j - 1]) {
					f[i][j] = true;
				}
			}
		}

		return f[n][m];
	}
};

