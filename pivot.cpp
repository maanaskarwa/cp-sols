#include <iostream>
#include <algorithm>

using namespace std;

/*
 * For a number to be a pivot, it must be the biggest till that point from the left
 * and the smallest till that point from the right.
 */

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, ans = 0;
  cin >> n;
  int nums[n];
  // maintain array of max and mins
  int max_value_from_start_till_index[n];
  int min_value_from_end_till_index[n];
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
    if (i == 0) max_value_from_start_till_index[0] = nums[0];
    else max_value_from_start_till_index[i] = max(nums[i], max_value_from_start_till_index[i - 1]);
  }
  min_value_from_end_till_index[n - 1] = nums[n - 1];
  for (int i = n - 2; i >= 0; --i)
    min_value_from_end_till_index[i] = min(nums[i], min_value_from_end_till_index[i + 1]);
  for (int i = 0; i < n; ++i) {
    if (nums[i] == max_value_from_start_till_index[i] &&
    nums[i] == min_value_from_end_till_index[i]) ++ans;
  }
  cout << ans;
  return 0;
}

/*
 * https://open.kattis.com/problems/pivot
 *
 * An O(n) Partition algorithm partitions an array A around a pivot element (pivot is a member of A) into three parts:
 * a left sub-array that contains elements that are <= pivot,
 * the pivot itself,
 * and a right sub-array that contains elements that are >= pivot.
 *
 * A Partition algorithm is an integral part of a popular sorting algorithm Quicksort.
 * Usually, the choice of pivot is randomized so that Quicksort has an expected O(nlogn) running time performance.
 *
 * Now the actual job in this problem is this: Starting from an array A that has n distinct integers, we partition A using one of the member of A as pivot to produce a transformed array A’.
 * Given this transformed array A’, your job is to count how many integers that could have been the chosen pivot.
 *
 * For example, if A’ = {2,1,3,4,7,5,6,8}, then 3 integers: {3,4,8} could have been the pivot of partition.
 *
 * e.g. {2,1,3} to the left of integer 4 are smaller than 4 and {7,5,6,8} to the right of integer 4 are greater than 4.
 *
 * However, the other 5 integers cannot possibly be the pivot, e.g. integer 7 cannot possibly be the pivot as there are {5,6} to the right of integer 7.
 *
 * Input
 * The input consists of two lines. The first line contains integer n (3 <= n <= 100000).
 * The second line contains n distinct 32-bit signed integers that describes the transformed array A'.
 *
 * Output:
 * Output the required answer as a single integer in one line.

Sample Input 1
8
2 1 3 4 7 5 6 8

Sample Output 1
3

Sample Input 2
7
1 2 3 4 5 7 6

Sample Output 2
5
 */