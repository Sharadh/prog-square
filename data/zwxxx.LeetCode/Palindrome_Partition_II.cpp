/*
Given a string s, partition s such that every substring of the partition is a palindrome.

Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.
*/


// a O(n^2) time, O(n^2) space solution, only pass small set test on Leetcode.com, by Ke Hu (mrhuke@gmail.com)
class Solution {
public:

    bool isPalindrome(string s, int i, int j)
    {
        if (i >= j) return true;
        if (s[i] != s[j]) return false;
        return isPalindrome(s, i+1, j-1);
    }

    int minCut(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<bool> > isPalin(s.size(), vector<bool>(s.size()));
        vector<int> cuts(s.size());
        
        // init
        for ( int i = 0; i < s.size(); ++i){
            cuts[i] = i;
            isPalin[i][i] = true;
            if (i < s.size()-1) isPalin[i+1][i] = true;
        }
        
        
        // DP
        for ( int i = 0; i < s.size(); ++i){
            if (isPalindrome(s, 0, i)){
                isPalin[0][i] = true;
                cuts[i] = 0;
            }
            for ( int j = 1; j <= i; ++j){
                if (j == i || (s[j] == s[i] && isPalin[j+1][i-1])){
                    isPalin[j][i] = true;
                    if (cuts[j-1] + 1 < cuts[i])
                        cuts[i] = 1+cuts[j-1];
                }
            }
        }
        
        return cuts[cuts.size()-1];
    }
};

