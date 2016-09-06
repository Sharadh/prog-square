/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 18, 2012
 Problem:    Simplify Path
 Difficulty: medium
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Given an absolute path for a file (Unix-style), simplify it.

 For example,
 path = "/home/", => "/home"
 path = "/a/./b/../../c/", => "/c"

 Corner Cases:
 Did you consider the case where path = "/../"?
 In this case, you should return "/".
 Another corner case is the path might contain multiple slashes '/' together,
 such as "/home//foo/".
 In this case, you should ignore redundant slashes and return "/home/foo".

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
#include <stack>
using namespace std;

class Solution {
public:
	string simplifyPath(string path) {
		vector<string> simple;
		int start = 1;

		simple.push_back("/");
		for (unsigned i = 1; i < path.length(); i++) {
			if (path[i] == '/') {
				string level = path.substr(start, i - start + 1);
				if (level.compare("../") == 0) {
					if (simple.size() > 1) {
						simple.pop_back();
					}
				} else if (level.compare("./") != 0
						&& level.compare("/") != 0) {
					simple.push_back(level);
				}
				start = i + 1;
			} else if (i == path.length() - 1) {
				string level = path.substr(start, i - start + 1);
				if (level.compare("..") == 0) {
					if (simple.size() > 1) {
						simple.pop_back();
					}
				} else if (level.compare(".") != 0) {
					simple.push_back(level);
				}
			}
		}

		string result;
		for (unsigned i = 0; i < simple.size(); i++) {
			result += simple[i];
		}
		if (result.length() > 1 && result[result.length() - 1] == '/') {
			result = result.substr(0, result.length() - 1);
		}
		return result;
	}
};
