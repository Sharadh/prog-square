/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 24, 2012
 Problem:    Subsets
 Difficulty: easy
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Given a set of distinct integers, S, return all possible subsets.

 Note:
 Elements in a subset must be in non-descending order.
 The solution set must not contain duplicate subsets.
 For example,
 If S = [1,2,3], a solution is:

 [
 [3],
 [1],
 [2],
 [1,2,3],
 [1,3],
 [2,3],
 [1,2],
 []
 ]

 Solution:
 There is another good solution provided by
 https://github.com/anson627/leetcode/blob/master/Subsets/src/Subsets.cpp
 .
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
	vector<vector<int> > result;
	void recursion(int dep, int max_dep, int s, vector<int> &subset,
			vector<int> &S) {
		if (dep == max_dep) {
			result.push_back(subset);
		}
		for (unsigned i = s; i < S.size(); i++) {
			subset.push_back(S[i]);
			recursion(dep + 1, max_dep, i + 1, subset, S);
			subset.pop_back();
		}
	}
	vector<vector<int> > subsets(vector<int> &S) {
		result.clear();
		sort(S.begin(), S.end());
		for (unsigned i = 0; i <= S.size(); i++) {
			vector<int> subset;
			recursion(0, i, 0, subset, S);
		}
		return result;
	}
};
