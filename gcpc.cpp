/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define pii pair<int,int>
using namespace std;
using namespace __gnu_pbds;

struct team {
    int index;
    pii score; // num problems solved,total penalty
};

bool operator<(const team &A, const team &B) {
  auto a = A.score;
  auto b = B.score;
  if (a.first != b.first)
    return a.first > b.first;
  if (a.second != b.second)
    return a.second < b.second;
  return A.index < B.index;
}

#define ordered_set tree<team, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>
ordered_set teamToScore;
pii score[100001]; // num problems solved,total penalty

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    score[i] = {0, 0};
    teamToScore.insert({i, {0, 0}});
  }
  int t, p;
  while (m--) {
    cin >> t >> p;

    teamToScore.erase( {t, score[t]});
    score[t].first++;
    score[t].second += p;
    teamToScore.insert( {t, score[t]});
    int ans = teamToScore.order_of_key({1, score[1]}); // find team's rank
    cout << ans +1<< "\n"; // 1-indexing
  }
}
#undef pii