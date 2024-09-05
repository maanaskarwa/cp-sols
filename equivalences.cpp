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

int t, n, m, in_0 = 0, out_0 = 0;
vector<int> v_graph[20000], v_graph_reversed[20000];
vector<set<int>> scc_list;

/*
 * Below code for Tarjan's algorithm taken from https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/
 * Modified to add elements of an SCC to scc_list
 * */

void SCCUtil(int u, int disc[], int low[], stack<int> &st, bool stackMember[]) {
  static int time = 0;
  disc[u] = low[u] = ++time;
  st.push(u);
  stackMember[u] = true;
  for (auto i = v_graph[u].begin(); i != v_graph[u].end(); ++i) {
    int v = *i;
    if (disc[v] == NIL) {
      SCCUtil(v, disc, low, st, stackMember);
      low[u] = min(low[u], low[v]);
    } else if (stackMember[v])
      low[u] = min(low[u], disc[v]);
  }

  int w;
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

void SCC() {
  int disc[n];
  int low[n];
  bool stackMember[n];
  stack<int> st;

  for (int i = 0; i < n; i++) {
    disc[i] = NIL;
    low[i] = NIL;
    stackMember[i] = false;
  }

  for (int i = 0; i < n; i++)
    if (disc[i] == NIL)
      SCCUtil(i, disc, low, st, stackMember);
}

/*
 * Logic: Contract the graph into SCCs (don't actually do it, simulate. Easier)
 * Once "contracted", check how many of in-flow and out-flow edges are missing.
 * For the entire thing to be one SCC, there needs to be a way in and a way out of each SCC
 */

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    in_0 = out_0 = 0;
    memset(v_graph, 0, sizeof(v_graph));
    memset(v_graph_reversed, 0, sizeof(v_graph_reversed));
    scc_list.clear();
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
      v_graph[i] = {};
      v_graph_reversed[i] = {};
    }
    for (int i = 0; i < m; ++i) {
      int s1, s2;
      cin >> s1 >> s2;
      s1--;
      s2--;
      v_graph[s1].push_back(s2);
      v_graph_reversed[s2].push_back(s1);
    }
    SCC();
    if (scc_list.size() == 1) {
      cout << "0\n";
      continue;
    }
    for (auto &scc: scc_list) {
      bool hasOutflowOtherThanSCC = false;
      for (int vertex: scc) {
        for (int to_check: v_graph[vertex]) {
          auto check = scc.insert(to_check);
          if (check.second) { // was inserted, implies was not a part of the SCC
            hasOutflowOtherThanSCC = true;
            scc.erase(check.first);
            break;
          }
        }
        if (hasOutflowOtherThanSCC) break;
      }
      if (!hasOutflowOtherThanSCC) ++out_0;

      bool hasInflowOtherThanSCC = false;
      /*
       * Use reversed graph to find all edges pointing at a vertex
       */
      for (int vertex: scc) {
        for (int to_check: v_graph_reversed[vertex]) {
          auto check = scc.insert(to_check);
          if (check.second) {
            hasInflowOtherThanSCC = true;
            scc.erase(check.first);
            break;
          }
        }
        if (hasInflowOtherThanSCC) break;
      }
      if (!hasInflowOtherThanSCC) ++in_0;
    }
    cout << max(in_0, out_0) << "\n";
  }
  return 0;
}