/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 25, 2012
 Problem:    Substring with Concatenation of All Words
 Difficulty: medium
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 You are given a string, S, and a list of words, L, that are all of the same
 length. Find all starting indices of substring(s) in S that is a concatenation
 of each word in L exactly once and without any intervening characters.

 For example, given:
 S: "barfoothefoobarman"
 L: ["foo", "bar"]

 You should return the indices: [0,9].
 (order does not matter).

 Solution:
 Hash. The overall time complexity is O(len(S) * sizeof(L)).
 substr() is a time consuming operation. If I don't replace substr() with a
 variable sub, the program will be TLE.
 Here I implement map instead of hash. The program will be faster if hash
 is implemented.
 I don't think this is the best solution. Faster algorithm might exists.
 */
#include <vector>
#include <set>
#include <climits>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstring>
#include <queue>
#include <map>
using namespace std;

class Solution {
public:
	vector<int> findSubstring(string S, vector<string> &L) {
		map<string, int> l;
		map<string, int> s;
		vector<int> result;

		if (L.size() == 0 || L.size() * L[0].length() > S.length()) {
			return result;
		}

		for (int i = 0; i < L.size(); i++) {
			l[L[i]]++;
		}

		int len = L[0].length();
		for (int i = 0, j; i <= S.length() - L.size() * len; i++) {
			s.clear();
			for (j = 0; j < L.size(); j++) {
				string sub = S.substr(i + len * j, len);
				if (l.find(sub) == l.end()) {
					break;
				}
				s[sub]++;
				if (s[sub] > l[sub]) {
					break;
				}
			}
			if (j == L.size()) {
				result.push_back(i);
			}
		}

		return result;
	}
};
