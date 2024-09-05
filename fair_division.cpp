/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <algorithm>
#include <cmath>

#define ld long double
using namespace std;

pair<int, int> index_to_contribution[1000000];
short t;
int contribution_sum, n, p;

/*
 * Check what 1/nth of the price is. If somebody can pay a max lower than that, max them out, and recompute.
 * Continue till everybody left is above the threshold.
 * Then, divide up the remaining amount based on who can pay the most, and if there's a tie, whoever appeared first.
 */

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    contribution_sum = 0;
    cin >> p >> n;
    for (int i = 0; i < n; ++i) {
      int c;
      cin >> c;
      contribution_sum += c;
      index_to_contribution[i] = {i, c};
    }
    if (contribution_sum < p) { // edge case
      cout << "IMPOSSIBLE" << "\n";
      continue;
    }
    if (contribution_sum == p) { // edge case. No computation needed
      for (int i = 0; i < n; ++i) {
        cout << index_to_contribution[i].second << " ";
      }
      cout << "\n";
      continue;
    }
    sort(index_to_contribution, index_to_contribution + n,
         [](const pair<int, int> &p1, const pair<int, int> &p2) {
      // different contribution, so sort in ascending order
             if (p1.second != p2.second) return p1.second < p2.second;
             //if same contribution, sort such that when you iterate backwards, the earlier person shows up first
             return p1.first > p2.first;
         });
    int p_copy = p, n_copy = n, current_check_n = 0, ans[n];
    double threshold = (1.0 * p_copy) / n_copy;
    while (true) { //greedy iterations
      for (int i = current_check_n; i < n; ++i) {
        int current_index = index_to_contribution[i].first;
        int max_contribution = index_to_contribution[i].second;
        if (max_contribution < threshold) {
          ans[current_index] = max_contribution;
          p_copy -= max_contribution;
        } else {
          // the moment you land on a player who can afford the current threshold, you want to stop and continue checking with the new threshold
          current_check_n = i;
          break;
        }
      }
      n_copy = n - current_check_n; // number of people left now
      threshold = (1.0 * p_copy) / n_copy; // p_copy was decremented in iteration
      if (index_to_contribution[current_check_n].second >= threshold) {
        // if the current person is under the next threshold too, then we are done with greedy. everybody above this person will definitely be above the threshold
        break;
      }
    }
    for (int i = n - 1; i >= current_check_n; --i) {
      // assign remaining amounts
      int contribution = ceil(threshold);
      ans[index_to_contribution[i].first] = contribution;
      p_copy -= contribution;
      if (--n_copy == 0) break;
      threshold = (1.0 * p_copy) / n_copy;
    }
    for (int i = 0; i < n; ++i) cout << ans[i] << " ";
    cout << "\n";
  }
  return 0;
}