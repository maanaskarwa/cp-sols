/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 **/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

pair<int, int> errand_coords[100000];
vector<int> y_vals;
int n, x_home, y_h, x_w, y_w, valid_n = 0;

/*
 * O(nlogn) LIS, taken from https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
 * Modified to allow non-decreasing
 */

int ceil_index(vector<int> &v, int l, int r, int key) {
  while (r - l > 1) {
    int m = l + (r - l) / 2;
    if (v[m] > key) //was >=. Want the highest index in case a num repeats
      r = m;
    else
      l = m;
  }
  return r;
}

int longest_non_decreasing_subsequence_length(vector<int> &v) {
  if (v.empty())
    return 0;
  vector<int> tail(v.size(), 0);
  int length = 1;
  tail[0] = v[0];
  for (size_t i = 1; i < v.size(); i++) {
    if (v[i] < tail[0]) {
      tail[0] = v[i];
    }
    else if (v[i] >= tail[length - 1]) { // was >.
      tail[length++] = v[i];
    }
    else {
      tail[ceil_index(tail, -1, length - 1, v[i])] = v[i];
    }
  }
  return length;
}

/*
 * Observations:
 * 1. 4 possible arrangements of home and office: office above and to right of home, office above and to left of home, office below and to right of home, office below and to left of home.
 * 2. Answer won't change whether I travel from home to office or the other way around. so of the 4 possible arrangements, there are only 2 unique ones.
 * 3. based on the orientation of home and office, there are always only 2 valid directions to travel in.
 * 4. if any location lies outside the "grid" between home and office, I would never visit it. Don't even need to store those coords

 * Other implementations I tried (and why they wouldn't fit the bill):
 * 1. Naive Max-sum DP (won't work because I would have a 10^9 by 10^9 array in the worst case, which would TLE and MLE).
 * 2. Optimized max-sum DP: Don't store all points, blank spaces can be optimized.
 *    eg. for this test case:
 *    3
      0 0 6 6
      5 4
      2 6
      3 1

      Original grid is:
      _ _ * _ _ _ W
      _ _ _ _ _ _ _
      _ _ _ _ _ * _
      _ _ _ _ _ _ _
      _ _ _ _ _ _ _
      _ _ _ * _ _ _
      H _ _ _ _ _ _
      it can be reduced to
      * _ _
      _ _ *
      _ * _
      and we would get the same ans by traversing from bottom left to top right.
      Pasting that code at the end of the file.
      Reason it wouldn't work is because in the case of every errand being on the diagonal, I would have a 10^5 by 10^5 DP grid, which will still TLE and MLE
 */

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> x_home >> y_h >> x_w >> y_w;
  int x_high = max(x_home, x_w),
    x_low = min(x_home, x_w),
    y_high = max(y_h, y_w),
    y_low = min(y_h, y_w);

  //want to normalize all directions to point to travelling in Northeast direction. Have altered coordinates accordingly
  if (!((x_home > x_w && y_h > y_w) ||
        (x_home < x_w && y_h < y_w))) { //travelling "northwest" or "southeast"
    // home and office are on the top left and bottom right of grid.
    // mirror the entire grid about the x axis so that home/office occupy bottom left and top right
    // we ensure that travelling northeast will get us from home to office or vice versa
    while (n--) {
      int x, y;
      cin >> x >> y;
      if (x > x_high || x < x_low || y > y_high || y < y_low) continue;
      errand_coords[valid_n] = {x_low - x + x_high, y};
      ++valid_n;
    }
  } else {
    while (n--) {
      int x, y;
      cin >> x >> y;
      if (x > x_high || x < x_low || y > y_high || y < y_low) continue;
      errand_coords[valid_n] = {x, y};
      ++valid_n;
    }
  }

  if (valid_n == 0) {cout << 0<<"\n";return 0;}

  sort(errand_coords, errand_coords + valid_n,
       [](const pair<int, int> &p1, const pair<int, int> &p2) {
           if (p1.first == p2.first) return p1.second < p2.second;
           return p1.first < p2.first;
       });

  //Having sorted x coords, do LIS on y coords
  y_vals.reserve(valid_n);
  for(int i = 0; i < valid_n; ++i) {
    y_vals.push_back(errand_coords[i].second);
  }
  cout << longest_non_decreasing_subsequence_length(y_vals) << "\n";
  return 0;
}

/*
 * Problem Statement: https://open.kattis.com/problems/manhattanmornings
 * As a New Yorker you are always very busy. Apart from your long work day you tend to have a very long list of errands that need to be done on any particular day.
 * You really hate getting up early so you always end up going over your to-do list after work, but this is starting to seriously hurt your free time.
 * One day you realize that some of the places you have to go by lie on your walk to the office, so you can visit them before work.
 * The next day you notice that if you take a slightly different route to work you can run most of your errands without increasing the length of your route.
 * Since errands take a negligible amount of time, you don’t even have to get up any earlier to do this!
 * This nice little side effect of the grid-like New York streets gets you thinking. Given all the locations of your errands on the New York grid, how many can you visit on your way to work without getting up any earlier?
 *
 * The New York grid is modelled with streets that are parallel to the x-axis and avenues that are parallel to the y-axis. Specifically, there is a street and an avenue given by every integer.
 * It is given that an errand always takes place on an intersection between a street and an avenue. Since you walk to your work, you can use all roads in both directions.
 *
 * Input:
 * The first line contains an integer 0 <= n <= 10^5, the number of errands you have to run that day.
 * The next line contains four integers 0 <= x_h, y_h, x_w, y_w <= 10^9 corresponding to the locations of your house and workplace.
 * The next n lines each contain two integers 9 <= x_i, y_i <= 10^9, the coordinates of your ith errand.
 *
 * Output:
 * Output a single line, containing the number of errands you can run before work without taking a longer route than necessary.

Sample Input 1
3
0 0 6 6
5 4
2 6
3 1

Sample Output 1
2

Sample Input 2
5
2 1 0 0
0 0
0 1
2 0
2 1
3 1

Sample Output 2
3

Sample Input 3
4
200 100 100 200
50 150
200 200
100 100
100 100

Sample Output 3
2
 */

/*
// Reduced Grid DP code:

#include <iostream>
#include <map>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

pair<int, int> errand_coords[100000];
map<int, int> x_mapping, y_mapping; // to reduce grid
map<int, bool> x_already_present, y_already_present;
int n, x_home, y_h, x_w, y_w, num_unique_x = 0, num_unique_y = 0, valid_n = 0;

//want to normalize all directions to point to travelling in Northeast direction. Have altered coordinates accordingly
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> x_home >> y_h >> x_w >> y_w;
  int x_high = max(x_home, x_w),
    x_low = min(x_home, x_w),
    y_high = max(y_h, y_w),
    y_low = min(y_h, y_w);

  if (!((x_home > x_w && y_h > y_w) || (x_home < x_w && y_h < y_w))) { //travelling "northwest" or "southeast"
    // home and office are on the top left and bottom right of grid.
    // mirror the entire grid about the x axis so that home/office occupy bottom left and top right
    // we ensure that travelling northeast will get us from home to office or vice versa
    while (n--) {
      int x, y;
      cin >> x >> y;
      if (x > x_high || x < x_low || y > y_high || y < y_low) continue;
      errand_coords[valid_n] = {x_low - x + x_high, y};
      ++valid_n;
      if (!x_already_present[x_low - x + x_high]) {
        x_already_present[x_low - x + x_high] = true;
        x_mapping[x_low - x + x_high] = x_low - x + x_high;
        ++num_unique_x;
      }
      if (!y_already_present[y]) {
        y_already_present[y] = true;
        y_mapping[y] = y;
        ++num_unique_y;
      }
    }
  } else {
    while (n--) {
      int x, y;
      cin >> x >> y;
      if (x > x_high || x < x_low || y > y_high || y < y_low) continue;
      errand_coords[valid_n] = {x, y};
      ++valid_n;
      if (!x_already_present[x]) {
        x_already_present[x] = true;
        x_mapping[x] = x;
        ++num_unique_x;
      }
      if (!y_already_present[y]) {
        y_already_present[y] = true;
        y_mapping[y] = y;
        ++num_unique_y;
      }
    }
  }

  // since hashmap has keys in ascending order, we can assign their relative positions directly form the index
  auto t = x_mapping.begin();
  for (int i = 0; i < num_unique_x; ++i, ++t) {
    t->second = i;
  }

  // since hashmap has keys in ascending order, we can assign their relative positions directly form the index
  t = y_mapping.begin();
  for (int i = 0; i < num_unique_y; ++i, ++t) {
    t->second = i;
  }

  // reduced grid
  int reduced_arr[num_unique_x][num_unique_y];
  memset(reduced_arr, 0, sizeof(reduced_arr));
  for (int i = 0; i < valid_n; ++i) {
    ++reduced_arr[x_mapping[errand_coords[i].first]][y_mapping[errand_coords[i].second]];
  }

  int dp[num_unique_x][num_unique_y];
  dp[0][0] = reduced_arr[0][0];
  for (int i = 1; i < num_unique_x; ++i) dp[i][0] = dp[i - 1][0] + reduced_arr[i][0];
  for (int j = 1; j < num_unique_y; ++j) dp[0][j] = dp[0][j - 1] + reduced_arr[0][j];

  for (int i = 1; i < num_unique_x; ++i) {
    for (int j = 1; j < num_unique_y; ++j) {
      dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]) + reduced_arr[i][j];
    }
  }
  cout << dp[num_unique_x - 1][num_unique_y - 1];
  return 0;
}
 */