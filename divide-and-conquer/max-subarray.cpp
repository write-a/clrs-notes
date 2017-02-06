// This is the divide-and-conquer algorithm used
// to solve the maximum subarray problem described in CLRS 4.1
//
// One version of the dramatization of this problem is the max profit problem
// in stock buying which is used CLRS 4.1
// One pitfall in this dramatization is to think buying at the
// lowest and selling at the highest can always produce the max profit
// which can lead to wrong abstraction of the problem.  It's easy
// to construct a counter example, suppose the max price is at the beginning
// of the price series, then the lowest price may have not even appeared
// yet.
//
// What is guaranteed to find the max profit is to find the subarray
// with the maximum sum of price differences.
//
// Once this point is realized, it remains the problem of solving
// the max subarray problem.
// In divide and conquer, we must divide the array into two equal sized
// subarrays.  But we want to find a globally maximum sum subarray.
// The maximum sum subarray can either lie on the left subarray, 
// the right subarray, or has a part on the left and a part on the right
// crossing the mid point.  The first two cases can be happily 
// delegated to recursions on subproblems, the essence is to solve
// the cross-midpoint subarray.
//
// It's actually not that difficult because we have a constraint working
// in our favor.  The subarray must contain the midpoint!  Once we realize
// that, it's straigth forward, it's a consecutive array that's anchored on
// the midpoint, we just need to extend the subarray from the midpoint to
// the left and find the point where we can make the max profit and do the same for
// the right part of the array.
// 
// ATTENTION, don't stop extending to the left if your running sum starts
// decreasing, there may be bigger elements ahead to reverse the situation.
// You must go through the whole left half to find out.
//
// Once we have the max array from the left half, the max array from the right half
// from the two recursions, and we have the cross-midpoint subarray, we
// just need to compare the max sum of the three and choose the true maximum sum subarray!
// 
// Concretely, we need a find_max_crossing_subarray procedure to deal with
// the crossing subarray case and find_max_subarray to deal the rest.
//
// We'll first use int indexed vector to represent the array and 
// do a vanilla implementation that is fidel to the pseudo-code in CLRS.
// Later we can modify the procedures to support iterators and use std c++ algorithms as an exercise.
//
// g++ max-subarray.cpp -std=c++14
#include <limits>
#include <tuple>
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

decltype(auto) find_max_crossing_subarray(const vector<int>& v, int low, int mid, int high){

    int left_sum = numeric_limits<int>::min();
    // from midpoint and extend to the left as much as possible
    // to maximize the left sum
    int sum = 0; // records the running sum
    int leftest = mid; // records the leftest point
    for(auto i = mid; i >= low; --i){
         sum += v[i]; // accumulate the sum (accumulate you say? that reminds me of something...)
         if(sum > left_sum){
            left_sum = sum;
            leftest = i;
         }
         // ATTENTION: don't break prematurelly, the running sum can go up and down
         // we must go through the whole left half to find out the max point.
    }
    // Now do the right half, 
    int right_sum = numeric_limits<int>::min();
    sum = 0;
    int rightest = mid;
    //Aha, you're doing copy-paste! (probably an opportunity
    // for refactoring, look at the beautiful symmetry)
    for(auto i = mid+1; i <= high; ++i){
         sum += v[i]; // accumulate the sum (accumulate you say? that reminds me of something...)
         if(sum > right_sum){
            right_sum = sum;
            rightest = i;
         }
         // ATTENTION: don't break prematurelly, the running sum can go up and down
         // we must go through the whole left half to find out the max point.
    }
   
    // now I have the max crossing subarray
    return make_tuple(leftest, rightest, left_sum+right_sum);

}

decltype(auto) find_max_subarray(const vector<int>& v, int low, int high){
    // the base case (recursion end point)
    if(low == high)
        return make_tuple(low, high, v[low]);
    int mid = (low+high)/2;
    auto left_max_subarray = find_max_subarray(v, low, mid);
    auto right_max_subarray = find_max_subarray(v, mid+1, high);
    auto max_crossing_subarray = find_max_crossing_subarray(v, low, mid, high);
    // make a 3-way comparison to determine the true max subarray
    auto max_subarray = (get<2>(left_max_subarray) > get<2>(right_max_subarray))? left_max_subarray : right_max_subarray;
    max_subarray = (get<2>(max_subarray) > get<2>(max_crossing_subarray))? max_subarray : max_crossing_subarray;
    return max_subarray;
}


int main(){

    // This test case is taken exactly from CLRS P.68 Figure 4.1
    // Here we only show the price changes (not the real price)
    // max subarray                                                 |  |    |  |
    vector<int> price_changes = {13, -3, -25, 20, 3, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
    // the max profit strategy should be buy one share a day before day 8 (price change 18)
    // sell all after day 11 (price change 12)
    auto max_subarray = find_max_subarray(price_changes, 0, price_changes.size()-1);
    cout << get<0>(max_subarray) << "," << get<1>(max_subarray) << "," << get<2>(max_subarray) << "\n"; 
    assert(get<0>(max_subarray) == 8);
    assert(get<1>(max_subarray) == 11);
    assert(get<2>(max_subarray) == 43);

}
