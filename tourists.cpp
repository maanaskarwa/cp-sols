/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long
#define vi vector<int>
#define vvi vector<vi>
#define pb(n) push_back((n));

using namespace std;
template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    explicit RMQ(const vector<T>& V) : jmp(1, V) {
      for (int pw = 1, k = 1; pw * 2 <= V.size(); pw *= 2, ++k) {
        jmp.emplace_back(V.size() - pw * 2 + 1);
        for(int j=0; j <(jmp[k]).size();j++) jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
      }
    }
    T query(int a, int b) {
      assert(a < b); // or return inf if a == b
      int dep = 31 - __builtin_clz(b - a);
      return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};
struct LCA {
    int T = 0;
    vi time, path, ret;
    RMQ<int> rmq;

    explicit LCA(const vector<vi>& C) : time(C.size()), rmq((dfs(C,0,-1), ret)) {}
    void dfs(const vector<vi>& C, int v, int par) {
      time[v] = T++;
      for (int y : C[v]) if (y != par) {
          path.push_back(v), ret.push_back(time[v]);
          dfs(C, y, v);
        }
    }

    int lca(int a, int b) {
      if (a == b) return a;
      tie(a, b) = minmax(time[a], time[b]);
      return path[rmq.query(a, b)];
    }
    //dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

const int mxn = 2e5;
vi distanceFromRoot(mxn + 1, INT32_MAX); // 1-indexed like Q
vvi children(mxn); // 0-indexed (since used for LCA)

// node is 0 indexed
// but distance from node is 1 indexed
void findDistanceFromRoot(int node, int parent) {
  for (auto const & child:children[node]) {
    distanceFromRoot[child + 1] = min(distanceFromRoot[child + 1], distanceFromRoot[node + 1] + 1);
    if (child != parent)
      findDistanceFromRoot(child, node);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  int n;
  cin >> n;
  for (int i = 0, x,y; i < n-1; i++) {
    cin >> x >> y;
    children[x-1].pb(y-1);
    children[y-1].pb(x-1);
  }
  ll ans = 0;
  distanceFromRoot[1]=0;
  findDistanceFromRoot(0,-1); //recursively find distance of all nodes from root
  LCA l = LCA(children); // in case u forgot LCA is lowest common ancestor
  // sieve of eratosthenes style checking of pairs
  // distance between 2 nodes = sum of distances to their LCA = sum of (node dist from root - LCA dist from root)
  // add 1 since want to include self sort of
  for (int i = 0; i < n; i++) {
    int correspondingOneIndexNode = i+1; // LCA and therefore graph is 0 indexed, but we need 1-indexed ans
    for (int multiple = correspondingOneIndexNode<<1; multiple <= n; multiple+=correspondingOneIndexNode) {
      int anc = l.lca(i, multiple-1);
      ans += distanceFromRoot[multiple] + distanceFromRoot[correspondingOneIndexNode] - (distanceFromRoot[anc + 1] * 2) + 1;
    }
  }
  cout << ans;
}

#undef ll
#undef vi
#undef vvi
#undef pb