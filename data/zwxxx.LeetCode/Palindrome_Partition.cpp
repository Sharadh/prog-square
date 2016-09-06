/* 
Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

  [
    ["aa","b"],
    ["a","a","b"]
  ]
*/

// A solution using backtracking by Ke Hu (mrhuke@gmail.com)
class Solution {
public:

    bool isPalindrome(string s, int i, int j)
    {
        if (i >= j) return true;
        if (s[i] != s[j]) return false;
        return isPalindrome(s, i+1, j-1);
    }
    
    void partition(string s, int i, vector<string> &current, vector<vector<string> > &res)
    {
        // corner case
        if ( i == s.size() ){
            res.push_back(current);
            return;
        }    
        
        // DFS
        for ( int j = i; j < s.size(); ++j){
            if (isPalindrome(s, i, j)){
                current.push_back(s.substr(i,j-i+1));
                partition(s, j+1, current, res);
                current.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        vector<string> current;
        vector<vector<string> > res;
        partition(s, 0, current, res);
        return res;
    }
};