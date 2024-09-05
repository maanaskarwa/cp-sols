/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

using namespace std;

int n;
int perf[301];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  int t;cin>>t;
  while (t--) {
    cin >> n;
    for (int i = 0; i < n*3; i++)
      cin >> perf[i];
    sort(perf, perf+(n*3));
    int ans = 0;
    /*
     * In order to maximize the sum of medians, we need to choose teams in a
     * way that maximizes chosen medians.
     * Choose a team of besto & 2nd best player, and pick the worst player as the 3rd.
     * Median is the second best player
     *
     * Repeat for multiple teams
     * Essentially summing 2nd, 4th, 6th ... best players' result
     */
    for (int ct = 0; ct < n; ct++)
      ans += perf[(n*3)-2 - 2*(ct)];
    cout << ans << "\n";
  }
}