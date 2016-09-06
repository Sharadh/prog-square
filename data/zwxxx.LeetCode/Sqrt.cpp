/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 23, 2012
 Problem:    Sqrt(x)
 Difficulty: medium
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Implement int sqrt(int x).

 Compute and return the square root of x.

 Solution:
 Binary search. Return the lower bound.
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
using namespace std;

class Solution {
public:
	int sqrt(int x) {
		int low = 0, high = x, root;

		while (low <= high) {
			int mid = low + (high - low) / 2;	// avoid overflow
			if (mid > 46340) { 					// 46340^2 ~= INT_MAX
				high = mid - 1;
				continue;
			}

			int multi = mid * mid;
			if (multi == x) {
				return mid;
			}
			if (multi > x) {
				high = mid - 1;
			} else {
				low = mid + 1;
				root = mid;
			}
		}

		return root;
	}
};
