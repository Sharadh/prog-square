/*
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.
*/

// The idea is to use a hashset to do interval merge.
// 1) Scan once and add all numbers to a hashset
// 2) Scan the second time, for each number, try to increase and decrease it in both directions
// 3) return the longest interval after increase/decrease
// by Ke Hu (mrhuke@gmail.com) in Apr. 2013
class Solution {
public:

    // increase and decrease from current number as long as possible
    int search(set<int> &s, int val, bool toLeft)
    {
        int count = 0;
        while( s.find(val) != s.end() )
        {
            s.erase(val);
            count++;
            if (toLeft) val--;
            else val++;
        }
        return count;
    }

    int longestConsecutive(vector<int> &num) {
        set<int> s;
        for ( int i = 0; i < num.size(); ++i )
            s.insert(num[i]);
        
        int longest = 0;
        for ( int i = 0; i < num.size(); ++i ){
            if (s.find(num[i]) != s.end())
            {
                longest = max(longest, search(s, num[i], true) + search(s, num[i]+1, false));
            }
        }
        
        return longest;
    }
};