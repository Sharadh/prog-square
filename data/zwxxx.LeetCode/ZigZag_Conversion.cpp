/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 28, 2012
 Problem:    ZigZag Conversion
 Difficulty: easy
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 The string "PAYPALISHIRING" is written in a zigzag pattern on a given number
 of rows like this: (you may want to display this pattern in a fixed font for
 better legibility)

 P   A   H   N
 A P L S I I G
 Y   I   R
 And then read line by line: "PAHNAPLSIIGYIR"
 Write the code that will take a string and make this conversion given a number
 of rows:

 string convert(string text, int nRows);
 convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".

 Solution:
 rows = 3:
 P   A   H   N    0, 4, 8..
 A P L S I I G    1, 3, 5..
 Y   I   R        2, 6, 10..
 rows = 4:
 P     I     N    0, 6, 12..        6, 6, 6, 6...
 A   L S   I G    1, 5, 7, 11, 13   4, 2, 4, 2
 Y A   H R        2, 4, 8, 10, 14   2, 4, 2 ,4
 P     I          3, 9, 15          6

 rows = 5:
 P       H       0, 8, 16..         8, 8
 A     S I       1, 7, 9..          6, 2
 Y   I   R       2, 6, 10..         4, 4
 P L     I G     3, 5, 11..         2, 6
 A       N       4, 12..            8, 8
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
	string convert(string s, int nRows) {
		string ss;

		for (int i = 0; i < nRows; i++) {
			for (int j = 0, k = i; k < s.length(); j++) {
				ss += s[k];
				if (nRows == 1) {
					k += 1;
				} else if (i == 0 || i == nRows - 1) {
					k += (nRows - 1) * 2;
				} else {
					k = (j & 1 ? i + (nRows - 1) * (j + 1) : k + (nRows - 1 - i) * 2);
				}
			}
		}

		return ss;
	}
};
