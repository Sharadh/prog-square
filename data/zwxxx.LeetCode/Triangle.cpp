/*
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.
*/

// Ke Hu (mrhuke@gmail.com) May. 2013
// O(n) space solution
class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        
        vector<int> prevSum(triangle.size());
        vector<int> curSum(triangle.size());
        for ( int i = 0; i < triangle.size(); ++i)
        {
            if ( i == 0 ) curSum[0] = triangle[i][0];
            else{
                for ( int j = 0; j < triangle[i].size(); ++j)
                {
                    if (j == 0) curSum[j] = prevSum[j] + triangle[i][j];
                    else if ( j == triangle[i].size()-1) curSum[j] = prevSum[j-1] + triangle[i][j];
                    else{
                        curSum[j] = min(prevSum[j-1], prevSum[j]) + triangle[i][j];
                    }
                }
            }
            prevSum = curSum;
        }
        
        return *min_element(curSum.begin(), curSum.end());
    }
};