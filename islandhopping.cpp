#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>


#define ll long long
#define ld long double
#define u unsigned

using namespace std;

int n,m;
pair<double,double> points[750];


class DSU {
    int* parent;
    int* rank;

public:
    DSU(int n)
    {
      parent = new int[n];
      rank = new int[n];

      for (int i = 0; i < n; i++) {
        parent[i] = -1;
        rank[i] = 1;
      }
    }

    // Find function
    int find(int i)
    {
      if (parent[i] == -1)
        return i;

      return parent[i] = find(parent[i]);
    }

    // Union function
    void unite(int x, int y)
    {
      int s1 = find(x);
      int s2 = find(y);

      if (s1 != s2) {
        if (rank[s1] < rank[s2]) {
          parent[s1] = s2;
        }
        else if (rank[s1] > rank[s2]) {
          parent[s2] = s1;
        }
        else {
          parent[s2] = s1;
          rank[s1] += 1;
        }
      }
    }
};

class Graph {
    vector<vector<double> > edgelist;
    int V;

public:
    Graph(int V) { this->V = V; }

    void addEdge(int x, int y, double w)
    {
      edgelist.push_back({ w, (double) x, (double) y });
    }

    double kruskals_mst()
    {
      sort(edgelist.begin(), edgelist.end());
      DSU s(V);
      double ans = 0;
      for (auto edge : edgelist) {
        double w = edge[0];
        int x = edge[1];
        int y = edge[2];
        if (s.find(x) != s.find(y)) {
          s.unite(x, y);
          ans += w;
        }
      }
      return ans;
    }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  while (n--) {
    cin >> m;
    Graph g(m);
    for (int i = 0; i < m; ++i) {
      double a,b;
      cin >> a >> b;
      points[i] = {a,b};
      for (int j = i - 1; j >=0;--j) {
        double weight = sqrt(pow(a - points[j].first, 2) + pow(b - points[j].second, 2));
        g.addEdge(i,j,weight);
      }
    }
    cout << setprecision(15) << g.kruskals_mst() << "\n";
  }
  return 0;
}