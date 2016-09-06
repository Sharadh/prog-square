/*
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/

// Ke Hu (mrhuke@gmail.com) in Apr. 2013
// divided and conquer, for each i, calculate the first buy profit if selling at i and second profit if buying at i
// 1) scan forward to get firstBuy[i] which is the max profit if buy once at i
// 2) scan backward to calculate the second buy profit at i and combine with firstBuy[i]

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        
        if (prices.empty()) return 0;
        
        vector<int> firstBuy(prices.size());
        
        // first scan
        int minPrice = INT_MAX;
        int maxProfit = INT_MIN;
        for ( int i = 0; i < prices.size(); ++i )
        {
            minPrice = min(minPrice, prices[i]);
            if (prices[i] - minPrice > maxProfit)
                maxProfit = prices[i] - minPrice;
            firstBuy[i] = maxProfit;
        }
        
        // second scan
        int maxPrice = INT_MIN;
        int totalProfit = INT_MIN;
        for ( int i = prices.size()-1; i >= 0; --i )
        {
            maxPrice = max(maxPrice, prices[i]);
            if (maxPrice - prices[i] + firstBuy[i] > totalProfit)
                totalProfit = maxPrice - prices[i] + firstBuy[i];
        }
        
        return totalProfit;
    }
};