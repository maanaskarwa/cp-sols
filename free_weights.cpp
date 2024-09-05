/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <map>
#include <algorithm>

#define ll long long
#define ld long double
#define u unsigned

using namespace std;

/*
 * BSTA
 * If we can lift a certain weight, we can lift all weights below that amount.
 * As good as throwing them out.
 * Once you do that, is everything else paired up?
 */

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  map<int, short> histogram; // used simply to find cases where weights are on a different line, not efficient. Couldn't get better way to work that time.
  cin >> n;
  int row_1[n], row_2[n];
  int max_weight = 0; //BSTA upper limit
  int ans = 0;

  for (int i = 0; i < n; ++i) {
    int w;
    cin >> w;
    max_weight = max(w, max_weight);
    ++histogram[w];
    row_1[i] = w;
  }
  for (auto i = histogram.end(); i != histogram.begin(); --i) {
    if (i->second == 1) {
      // other weight on 2nd rack
      // since iterating backward, only need first instance
      ans = i->first;
      break;
    }
  }
  for (int i = 0; i < n; ++i) {
    int w;
    cin >> w;
    row_2[i] = w;
    max_weight = max(w, max_weight);
  }
  if (n == 1) { //edge case
    cout << row_1[0];
    return 0;
  }
  int low = 0, high = max_weight;
  while (low < high) {
    int mid = low + (high - low) / 2;
    bool possible_with_weight = true;
    int pointer1, pointer2;
    // adjacent weights (assuming we threw out the weights <= mid) should be paired up
    for (pointer1 = 0, pointer2 = 1; pointer2 < n;) {
      if (row_1[pointer1] <= mid) {
        // move entire sliding window forward
        ++pointer1;
        ++pointer2;
      } else if (row_1[pointer2] <= mid) ++pointer2;
      else if (row_1[pointer1] != row_1[pointer2]) {
        possible_with_weight = false;
        break;
      } else {
        // check next set
        pointer1 = pointer2 + 1;
        pointer2 = pointer1 + 1;
      }
    }

    //repeat for other rack
    for (pointer1 = 0, pointer2 = 1; pointer2 < n;) {
      if (row_2[pointer1] <= mid) {
        ++pointer1;
        ++pointer2;
      } else if (row_2[pointer2] <= mid) ++pointer2;
      else if (row_2[pointer1] != row_2[pointer2]) {
        possible_with_weight = false;
        break;
      } else {
        pointer1 = pointer2 + 1;
        pointer2 = pointer1 + 1;
      }
    }
    if (!possible_with_weight) {
      low = mid + 1;
    } else { high = mid; }
  }
  // low is the smallest weight where both were on same line. ans is the biggest weight that we have to pick up (on different lines)
  cout << max(ans, low);
  return 0;
}