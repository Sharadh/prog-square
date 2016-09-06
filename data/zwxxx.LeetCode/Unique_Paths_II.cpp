/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 27, 2012
 Problem:    Unique Paths II
 Difficulty: 
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Follow up for "Unique Paths":

 Now consider if some obstacles are added to the grids. How many unique paths
 would there be?

 An obstacle and empty space is marked as 1 and 0 respectively in the grid.

 For example,
 There is one obstacle in the middle of a 3x3 grid as illustrated below.

 [
 [0,0,0],
 [0,1,0],
 [0,0,0]
 ]
 The total number of unique paths is 2.

 Note: m and n will be at most 100.

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
	int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
		int m = obstacleGrid.size();
		int n = obstacleGrid[0].size();
		int array[n], i, j;

		array[0] = (obstacleGrid[0][0] == 0 ? 1 : 0);
		for (int i = 1; i < n; i++) {
			array[i] = 0;
		}

		for (i = 0; i < m; i++) {
			for (j = 0; j < n; j++) {
				if (obstacleGrid[i][j] == 0) {
					array[j] = (j > 0 ?array[j - 1] + array[j] : array[j]);
				} else {
					array[j] = 0;
				}
			}
		}

		return array[n - 1];
	}
};
