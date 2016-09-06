/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 22, 2012
 Problem:    Sort Colors
 Difficulty: hard
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Given an array with n objects colored red, white or blue, sort them so that
 objects of the same color are adjacent, with the colors in the order red,
 white and blue.

 Here, we will use the integers 0, 1, and 2 to represent the color red, white,
 and blue respectively.

 Note:
 You are not suppose to use the library's sort function for this problem.

 Follow up:
 A rather straight forward solution is a two-pass algorithm using counting sort.
 First, iterate the array counting number of 0's, 1's, and 2's, then overwrite
 array with total number of 0's, then 1's and followed by 2's.

 Could you come up with an one-pass algorithm using only constant space?

 Solution:
 We know that 0's in the front of array, 2's at the end of array and 1's in the
 middle. Thus three pointers point to the end of 0's, the end of 1's and the
 beginning of 2's (2's growing from end to head). Traverse the array with the
 1's pointer until it meets the 2's pointer:
 1) if it is 0, swap p0 with p1 and increase p0 and p1 by 1; p1 can increase
 because p0 points to 1 always.
 2) if it is 1, increase p1 by 1.
 3) if it is 2, swap p1 with p2 and decrease p2 by 1.
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
	void sortColors(int A[], int n) {
		int p0 = 0, p1 = 0, p2 = n - 1;
		while (p1 <= p2) {
			if (A[p1] == 0) {
				A[p1] = A[p0];
				A[p0] = 0;
				p1++;
				p0++;
			} else if (A[p1] == 1) {
				p1++;
			} else {
				A[p1] = A[p2];
				A[p2] = 2;
				p2--;
			}
		}
	}
};
