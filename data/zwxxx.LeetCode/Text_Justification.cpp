/*
 Author:     Weixian Zhou, ideazwx@gmail.com
 Date:       Jul 26, 2012
 Problem:	 Text Justification
 Difficulty: easy
 Source:     http://www.leetcode.com/onlinejudge
 Notes:
 Given an array of words and a length L, format the text such that each line has
 exactly L characters and is fully (left and right) justified.

 You should pack your words in a greedy approach; that is, pack as many words as
 you can in each line. Pad extra spaces ' ' when necessary so that each line has
 exactly L characters.

 Extra spaces between words should be distributed as evenly as possible. If the
 number of spaces on a line do not divide evenly between words, the empty slots
 on the left will be assigned more spaces than the slots on the right.

 For the last line of text, it should be left justified and no extra space is
 inserted between words.

 For example,
 words: ["This", "is", "an", "example", "of", "text", "justification."]
 L: 16.

 Return the formatted lines as:
 [
 "This    is    an",
 "example  of text",
 "justification.  "
 ]
 Note: Each word is guaranteed not to exceed L in length.

 Corner Cases:
 A line other than the last line might contain only one word. What should you do in this case?
 In this case, that line should be left-justified.

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
	vector<string> fullJustify(vector<string> &words, int L) {
		vector<string> result;

		for (int i = 0, count = 0, len = 0; i < words.size(); i++) {
			len += words[i].length();
			count++;
			if (len + count - 1 > L) {
				len -= words[i].length();
				count--;
				int s = i - count;
				string str = words[s];

				if (count == 1) {
					int extra = L - len;
					while (extra > 0) {
						str += " ";
						extra--;
					}
				} else {
					int avg = (L - len) / (count - 1);
					int extra = (L - len) % (count - 1);
					for (int i = s + 1; i < s + count; i++) {
						int space = (extra-- > 0 ? avg + 1 : avg);
						for (int j = 0; j < space; j++) {
							str += " ";
						}
						str += words[i];
					}
				}

				result.push_back(str);
				len = 0;
				count = 0;
				i--;
			} else if (i == words.size() - 1) {
				string str = words[i - count + 1];
				for (int j = i - count + 2; j <= i; j++) {
					str += " " + words[j];
				}
				while (str.length() < L) {
					str += " ";
				}
				result.push_back(str);
			}
		}

		return result;
	}
}
;
