/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long
#define vi vector<int>
#define vvi vector<vi>
#define pb(n) push_back((n))

using namespace std;

const int mxn = 1e5;
int n, k;
/*logic: the number of times a player's skill will contribute to the happiness is the number of times that player plays
 * we want to maximize players with higher skill level
 * think of a player's path through the draw - the highest skilled player will have a path all the way from a leaf to the root
 * however, another path that intersects somewhere with this path will stop at the intersection itself, since that player will not go any further
 * so that player's contribution is the skill of the player x the length of the players path
 */
ll final_path_lengths[mxn], skillLevels[mxn];
vi adj[mxn];
int finalPathCount = 0;

// dfs returns the depth of the child with the max depth
// essentially the longest path containing this node
// we also find all paths that were cut short at this node and add them to the final list of paths
ll dfs(int u) {
  if (adj[u].empty()) { // child node
    return 0;
  }
  vector<ll> childrenDepths;
  childrenDepths.reserve(adj[u].size());
  ll maxDepth = 0;
  for (auto const &child: adj[u]) {
    ll depth = 1 + dfs(child);
    maxDepth = max(maxDepth, depth);
    childrenDepths.pb(depth);
  }
  bool excludedMax = false;
  for (auto depth: childrenDepths) {
    if (depth == maxDepth) {
      if (excludedMax) { //handling of multiple children with same depth. exclude once - denoting the path we are continuing
        final_path_lengths[finalPathCount++] = depth;
      } else excludedMax = true;
    } else final_path_lengths[finalPathCount++] = depth;
  }
  return maxDepth;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  cin >> n >> k;
  for (int i = 0, tmp; i < k; i++) {
    cin >> tmp;
    skillLevels[i] = tmp;
  }
  sort(skillLevels,skillLevels + k);
  for (int i = 1, tmp; i <= n - 1; i++) {
    cin >> tmp;
    adj[tmp].pb(i);
  }
  final_path_lengths[k-1] = (dfs(0)); // dfs(0) gives max depth of root
  // we want player with highest skill to take this path

  ll ans = 0;
  sort(final_path_lengths,final_path_lengths + k);
  for (int i = 0; i < k; i++)
    ans += final_path_lengths[i] * skillLevels[i]; // greedy, highest skill gets longest path
  cout << ans;
}

#undef ll
#undef vi
#undef vvi
#undef pb