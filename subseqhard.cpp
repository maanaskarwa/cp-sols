/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <map>
#include <vector>

#define ll long long

using namespace std;

/*
 * Note: Read code in reverse order for best understanding:
 * Approach 1 is naive brute force. O(n^2), 10^12, too slow
 *
 * Approach 2 is DP with a lot of frills:
 *  Array for prefix sum, histogram for sums
 *  Array for numbers themselves
 *  Logic:
 *  If the difference of 2 prefix sums is 47, that's an interesting pair.
 *  Since hashmaps are the most efficient ways of storing such stuff (and you could end up having multiple such sums), use them!
 *  Original plan:
 *  Use hashmap just like array, compute sum in ending:
   while (t--) {
      cin >> n;
      sum_histogram.clear();
      sum_till_index_excluding[0] = 0;
      sum_histogram[0] = 1;
      for (int i = 0; i < n; ++i) {
        cin >> nums[i];
        sum_till_index_excluding[i+1] = sum_till_index_excluding[i] + nums[i];
        ++sum_histogram[sum_till_index_excluding[i+1]];
      }
      int ans = 0;
      for (int i = 0; i < n + 1; ++i) {
        ans += sum_histogram[sum_till_index_excluding[i] - 47];
      }
      cout << ans << "\n";
    }
    return 0;
  }
 *  Problem with this is that in cases like 0 0 47, we will keep looking for key 47 - 47 in mao, will never find.
 *  Another issue is with cases like 47 -47 47 -47 47. You would get a hashmap with values 0: 3 (1 of prefix sum) and 47: 3.
 *  At each 47, you would add histogram[57-57] to your answer, and you'd do this thrice, resulting in 9. However, there are only 6 in the ans.
 *  Using histogram to compute stuff at the end could lead to double-counting values, so we need a better way.
 *
 *  Instead, compute at each step. Eg for sample input 2, break it down:
 *  Vals:      -2  7 1 8  2  8 -1  8  2  8  4 -5 -9
 *  Prefix Sum: 0 -2 5 6 14 16 24 23 31 33 41 45 40 31 (note that our iteration starts with prefix sum -2. 0 is precomputed because n+1 elements)
 *  Index:      0  1 2 3  4  5  6  7  8  9 10 11 12 13 (13 never executes, we stop at 12)
 *  At index  0, key  0-47=-47 has val 0. Add key -2.
 *  At index  1, key -2-47=-49 has val 0. Add key  5.
 *  At index  2, key  5-47=-42 has val 0. Add key  6.
 *  At index  3, key  6-47=-41 has val 0. Add key 14.
 *  At index  4, key 14-47=-33 has val 0. Add key 16.
 *  At index  5, key 16-47=-31 has val 0. Add key 24.
 *  At index  6, key 24-47=-23 has val 0. Add key 23.
 *  At index  7, key 23-47=-24 has val 0. Add key 31.
 *  At index  8, key 31-47=-16 has val 0. Add key 33.
 *  At index  9, key 33-47=-14 has val 0. Add key 41.
 *  At index 10, key 41-47= -6 has val 0. Add key 45.
 *  At index 11, key 45-47= -2 has val 1. Add key 40.
 *  At index 12, key 40-47= -7 has val 0. Add key 31.
 *  At end of loop, key 31-47=-16 has val 0. Done.
 *
 *  This approach will work for each set because at each step we are only computing the new subsequences and are not double-counting anything.
 *
 *  This is approach 2, it passes.
 *
 *  Approach 3 gets rid of all the frills.
 *  We don't use the array of nums anywhere. We don't even need a prefix sum, because all we are using is the sum from the previous iteration and the current sum.
 *  Clean up code accordingly
 */

map<int, int> sum_histogram;
ll prev_sum = 0, sum;
int n;
short t, num;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    cin >> n;
    sum_histogram.clear();
    prev_sum = 0;
    sum_histogram[0] = 1;
    int ans = 0;
    while (n--) {
      cin >> num;
      sum = prev_sum + num;
      ans += sum_histogram[prev_sum - 47];
      ++sum_histogram[sum];
      prev_sum = sum;
    }
    ans += sum_histogram[sum - 47];
    cout << ans << "\n";
  }
  return 0;
}



/* // DP with arrays etc
#include <iostream>
#include <map>
#include <vector>

#define ll long long

using namespace std;
ll sum_till_index_excluding[1000001];
map<ll, int> sum_histogram;
int nums[1000001];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  short t;
  int n;
  cin >> t;

  while (t--) {
    cin >> n;
    sum_histogram.clear();
    sum_till_index_excluding[0] = 0;
    sum_histogram[0] = 1;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      cin >> nums[i];
      sum_till_index_excluding[i+1] = sum_till_index_excluding[i] + nums[i];
      ans += sum_histogram[sum_till_index_excluding[i] - 47];
      ++sum_histogram[sum_till_index_excluding[i+1]];
    }
    ans += sum_histogram[sum_till_index_excluding[n] - 47];;
    cout << ans << "\n";
  }
  return 0;
}
*/

/* // Brute
#include <iostream>

#define ll long long
#define ld long double
#define u unsigned

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  short t;
  int n;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    cin >> n;
    int nums[n];
    for (int j = 0; j < n; ++j) {
      cin >> nums[j];
    }
    int ans = 0;
    for (int j = 0; j < n; ++j) {
      int sum = 0;
      for (int k = j; k < n; ++k) {
        sum += nums[k];
        if (sum == 47) {
          ++ans;
          break;
        }
      }
    }
    cout << ans << "\n";
  }
  return 0;
}*/

/*
 * https://open.kattis.com/problems/subseqhard
 *
 * “47 is the quintessential random number," states the 47 society. And there might be a grain of truth in that.
 *
 * For example, the first ten digits of the Euler’s constant are:
 * 2 7 1 8 2 8 1 8 2 8
 * And what’s their sum? Of course, it is 47.
 *
 * Try walking around with your eyes open. You may be sure that soon you will start discovering occurrences of the number everywhere.
 * You are given a sequence S of integers we saw somewhere in the nature. Your task will be to compute how strongly does this sequence support the above claims.
 * We will call a continuous subsequence of S interesting if the sum of its terms is equal to 47.
 *
 * E.g., consider the sequence {24,17,23,24,5,47}. Here we have two interesting continuous subsequences: the sequence {23,24} and {47}
 *
 * Given a sequence S, find the count of its interesting subsequences.
 * Input
 * The first line of the input file contains an integer T specifying the number of test cases.
 * There are at most 10 test cases and each test case is preceded by a blank line.
 * The first line of each test case contains the length of a sequence N <= 1000000.
 * The second line contains N space-separated integers – the elements of the sequence. All numbers don’t exceed 20000 in absolute value.
 *
 * Output:
 * For each test case output a single line containing a single integer – the count of interesting subsequences of the given sentence.

Sample Input 1
2

13
-2 7 1 8 2 8 -1 8 2 8 4 -5 -9

7
2 47 10047 47 1047 47 47

Sample Output 1
1
4
 */