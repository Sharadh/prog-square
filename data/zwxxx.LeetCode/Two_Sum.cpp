/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 27, 2012
 Problem:    Two Sum
 Difficulty: easy
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Given an array of integers, find two numbers such that they add up to a
 specific target number.

 The function twoSum should return indices of the two numbers such that they
 add up to the target, where index1 must be less than index2. Please note
 that your returned answers (both index1 and index2) are not zero-based.

 You may assume that each input would have exactly one solution.

 Input: numbers={2, 7, 11, 15}, target=9
 Output: index1=1, index2=2

 Solution:
 Hash.
 */
#include <vector>
#include <set>
#include <climits>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstring>
#include <map>
using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int> &numbers, int target) {
		map<int, int> hash;
		vector<int> result;

		for (int i = 0; i < numbers.size(); i++) {
			if (hash.find(target - numbers[i]) != hash.end()) {
				if (i + 1 < hash[target - numbers[i]]) {
					result.push_back(i + 1);
					result.push_back(hash[target - numbers[i]]);
				} else {
					result.push_back(hash[target - numbers[i]]);
					result.push_back(i + 1);
				}
				break;
			} else {
				hash[numbers[i]] = i + 1;
			}
		}
		return result;
	}
};
