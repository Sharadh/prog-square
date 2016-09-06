/*
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.
*/

// Ke Hu (mrhuke@gmail.com) May, 2013
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        if (prices.empty()) return 0;
        int minPrice = INT_MAX;
        int profit = 0;
        for ( int i = 0; i < prices.size(); ++i){
            minPrice = min(prices[i], minPrice);
            profit = max(profit, prices[i] - minPrice);
        }
        return profit;
    }
};