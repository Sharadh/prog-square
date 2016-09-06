/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 27, 2012
 Problem:    Valid Parentheses
 Difficulty: easy
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Given a string containing just the characters '(', ')', '{', '}', '[' and ']',
 determine if the input string is valid.

 The brackets must close in the correct order, "()" and "()[]{}" are all valid
 but "(]" and "([)]" are not.

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
	bool isValid(string s) {
		stack<char> stk;

		for (int i = 0; i < s.length(); i++) {
			if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
				stk.push(s[i]);
			} else {
				if (stk.empty()) {
					return false;
				}
				char c = stk.top();
				stk.pop();
				if ((s[i] == ')' && c != '(') || (s[i] == ']' && c != '[')
						|| (s[i] == '}' && c != '{')) {
					return false;
				}
			}
		}
		if (!stk.empty()) {
			return false;
		}
		return true;
	}
};
