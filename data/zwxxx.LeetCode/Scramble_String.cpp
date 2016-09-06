/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 16, 2012
 Problem:    Scramble String
 Difficulty: medium
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Given a string s1, we may represent it as a binary tree by partitioning it to
 two non-empty substrings recursively.

 Below is one possible representation of s1 = "great":

 great
 /    \
  gr    eat
 / \    /  \
g   r  e   at
 / \
          a   t
 To scramble the string, we may choose any non-leaf node and swap its two children.

 For example, if we choose the node "gr" and swap its two children, it produces a
 scrambled string "rgeat".

 rgeat
 /    \
  rg    eat
 / \    /  \
r   g  e   at
 / \
          a   t
 We say that "rgeat" is a scrambled string of "great".

 Similarly, if we continue to swap the children of nodes "eat" and "at", it produces
 a scrambled string "rgtae".

 rgtae
 /    \
  rg    tae
 / \    /  \
r   g  ta  e
 / \
      t   a
 We say that "rgtae" is a scrambled string of "great".

 Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string
 of s1.

 Solution:
 Say we have a string s1 = [0..n] and we scramble at position p, then s1 is
 splited into [0..p] and [p+1, n]. Then we sramble substrees at random positons.
 The point is, no matter how we scramble the substees, the children of [0..p]
 must within 0..p and the children of [p+1, n] must within p+1..n. Thus if s2
 is a scrambled string of s1, then it must have a point that the half before
 it is continuous, and another half after it is continuous too.
 For example, s1 = 1 2 3 4 5 6 7
 then [7 4 6 5] [2 1 3] is a scrambled string of s1.
 and  4 7 1 3 2 5 6 is not a scrambled string of s1, because no such point
 makes both halfs continuous.

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
	/*
	 * If s1 has the same character set with s2, return true.
	 * Otherwise return false;
	 */
	bool isSame(string s1, string s2) {
		int hash[26];
		for (int i = 0; i < 26; i++) {
			hash[i] = 0;
		}
		for (unsigned i = 0; i < s1.length(); i++) {
			hash[s1[i] - 'a']++;
		}
		for (unsigned i = 0; i < s1.length(); i++) {
			hash[s2[i] - 'a']--;
			if (hash[s2[i] - 'a'] < 0) {
				return false;
			}
		}
		return true;
	}
	bool isScramble(string s1, string s2) {
		unsigned len = s1.length();

		if (len != s2.length()) {
			return false;
		}

		if (len <= 2) {
			return isSame(s1, s2);
		}

		for (unsigned i = 1; i < len; i++) {
			if (isSame(s1.substr(0, i), s2.substr(0, i))
					&& isSame(s1.substr(i, len - i), s2.substr(i, len - i))) {
				bool left = isScramble(s1.substr(0, i), s2.substr(0, i));
				bool right = isScramble(s1.substr(i, len - i),
						s2.substr(i, len - i));
				if (left && right) {
					return true;
				}
			} else if (isSame(s1.substr(0, i), s2.substr(len - i, i))
					&& isSame(s1.substr(i, len - i), s2.substr(0, len - i))) {
				bool left = isScramble(s1.substr(0, i), s2.substr(len - i, i));
				bool right = isScramble(s1.substr(i, len - i),
						s2.substr(0, len - i));
				if (left && right) {
					return true;
				}
			}
		}

		return false;
	}
};
