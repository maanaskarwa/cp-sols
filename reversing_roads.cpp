/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <list>
#include <cstring>

#define NIL (-1)

using namespace std;

vector<set<int>> scc_list;

/*
 * Below code for Tarjan's algorithm taken from https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/
 * Modified to add elements of an SCC to scc_list
 * */

struct graph {
    int V;
    vector<vector<int>> adj;
};

void addEdge(graph &g, int v, int w) { g.adj[v].push_back(w); }

void SCCUtil(graph &g, int u, int disc[], int low[], stack<int> &st, bool stackMember[]) {
  static int time = 0;
  disc[u] = low[u] = ++time;
  st.push(u);
  stackMember[u] = true;


  for (auto i = g.adj[u].begin(); i != g.adj[u].end(); ++i) {
    int v = *i;
    if (disc[v] == NIL) {
      SCCUtil(g, v, disc, low, st, stackMember);
      low[u] = min(low[u], low[v]);
    } else if (stackMember[v])
      low[u] = min(low[u], disc[v]);
  }

  int w = 0;
  if (low[u] == disc[u]) {
    set<int> scc;
    int scc_number_elements = 0;
    while (st.top() != u) {
      w = (int) st.top();
      scc.insert(w);
      ++scc_number_elements;
      stackMember[w] = false;
      st.pop();
    }
    w = (int) st.top();
    stackMember[w] = false;

    scc.insert(w);
    scc_list.push_back(scc);

    st.pop();
  }
}

void SCC(graph &g) {
  int disc[g.V];
  int low[g.V];
  bool stackMember[g.V];
  stack<int> st;

  for (int i = 0; i < g.V; i++) {
    disc[i] = NIL;
    low[i] = NIL;
    stackMember[i] = false;
  }
  for (int i = 0; i < g.V; i++)
    if (disc[i] == NIL)
      SCCUtil(g, i, disc, low, st, stackMember);
}

pair<int, int> edges[(50 * 49) / 2];
int m_vertices, n_edges, count = 0;

/*
 * Input graph, check if the entire thing is 1 SCC. If so, the graph is valid. Else, "flip" each edge and recheck. If non match, invalid
 */

int main() {
  while (cin >> m_vertices >> n_edges) {
    memset(edges, 0, sizeof(edges));
    scc_list.clear();
    graph g = {m_vertices, vector<vector<int>>(m_vertices)};
    ++count;
    for (int i = 0; i < n_edges; ++i) {
      int a, b;
      cin >> a >> b;
      edges[i] = {a, b};
      addEdge(g, a, b);
    }
    SCC(g);
    if (scc_list.size() == 1) {
      cout << "Case " << count << ": valid\n";
      continue;
    }
    bool found_ans = false;
    for (int i = 0; i < n_edges; ++i) {
      auto edge = edges[i];
      scc_list.clear();
      graph test_graph = {m_vertices, vector<vector<int>>(m_vertices)};
      for (int j = 0; j < n_edges; ++j) {
        if (i == j) { test_graph.adj[edge.second].push_back(edge.first); } // flipping edge
        else { test_graph.adj[edges[j].first].push_back(edges[j].second); }
      }
      SCC(test_graph);
      if (scc_list.size() == 1) {
        cout << "Case " << count << ": " << edge.first << " " << edge.second << "\n";
        found_ans = true;
        break;
      }
    }
    if (!found_ans) cout << "Case " << count << ": invalid\n";
  }
  return 0;
}