/*
Author:     Weixian Zhou, ideazwx@gmail.com
Date:       June 28, 2012
Problem:    Divide two integers
Difficulty: Low
Source:     http://www.leetcode.com/onlinejudge
Notes:
Divide two integers without using multiplication, division and mod operator.

Solution:
A recursive solution added by Ke Hu (mrhuke@gmail.com) in apr. 2013
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

// Recusive solution by ke (mrhuke@gmail.com) in apr. 2013
class Solution {
public:

    int divide(int dividend, int divisor) {
       // Start typing your C/C++ solution below
       // DO NOT write int main() function
        
        // special case when denominator == INT_MIN
       if (divisor == INT_MIN){
           if (dividend == INT_MIN) return 1;
           else return 0;
       }
       
       // special case when enumerator is INT_MIN
       if (dividend == INT_MIN){
            if (divisor > 0)
                return -1 + divide(dividend + divisor, divisor);
            else
                return 1 + divide(dividend - divisor, divisor);
       }
       
       // simply by considering division of absolute values
       bool neg = false;
       if ( (dividend > 0 && divisor < 0) || (dividend < 0 && divisor > 0) )
            neg = true;
       
       int a = fabs(dividend), b=fabs(divisor);
       if (b == 0){
           return INT_MAX;
       }
       else if (a < b){
           return 0;
       }else if (a == b){
           if (neg) return -1;
           else return 1;
       }
       
       // binary search
       int res = 1;
       int q = b;
       while(q <= a - q){
           q <<= 1;
           res <<= 1;
       }
       
       // recursive
       res += divide(a - q, b);
       
       if (neg){
           return -res;
       }else{
           return res;
       }
    }
};

