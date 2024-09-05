/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <vector>
#include <stack>
#include <map>

#define NIL (-1)

using namespace std;

vector<vector<int>> scc_list;

/*
 * Below code for Tarjan's algorithm taken from https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/
 * Modified to add elements of an SCC to scc_list
 * */

class Graph {
    int V;
    vector<vector<int>> adj;
    void SCCUtil(int u, int disc[], int low[],
                 stack<int> &st, bool stackMember[]);

public:
    explicit Graph(int V);
    void addEdge(int v,
                 int w);
    void SCC();
};

Graph::Graph(int V) {
  this->V = V;
  adj = vector<vector<int>>(V);
}

void Graph::addEdge(int v, int w) { adj[v].push_back(w); }

void Graph::SCCUtil(int u, int disc[], int low[], stack<int> &st, bool stackMember[]) {
  static int time = 0;
  disc[u] = low[u] = ++time;
  st.push(u);
  stackMember[u] = true;

  for (auto i = adj[u].begin(); i != adj[u].end(); ++i) {
    int v = *i;
    if (disc[v] == NIL) {
      SCCUtil(v, disc, low, st, stackMember);
      low[u] = min(low[u], low[v]);
    } else if (stackMember[v])
      low[u] = min(low[u], disc[v]);
  }

  int w = 0;
  if (low[u] == disc[u]) {
    vector<int> scc;
    int scc_number_elements = 0;
    while (st.top() != u) {
      w = (int) st.top();
      scc.push_back(w);
      ++scc_number_elements;
      stackMember[w] = false;
      st.pop();
    }
    w = (int) st.top();
    stackMember[w] = false;
    scc.push_back(w);
    scc_list.push_back(scc);
    st.pop();
  }
}

void Graph::SCC() {
  int disc[V];
  int low[V];
  bool stackMember[V];
  stack<int> st;

  for (int i = 0; i < V; i++) {
    disc[i] = NIL;
    low[i] = NIL;
    stackMember[i] = false;
  }

  for (int i = 0; i < V; i++)
    if (disc[i] == NIL)
      SCCUtil(i, disc, low, st, stackMember);
}

int n, city_count = 0;
auto graph = Graph(5001); // max possible vertices is 5000 since we have 5000 edges at max
map<string, int> city_to_int;
map<int, vector<int>> map_graph;

map<int, bool> safe;

bool dfs(int v) {
  if (safe[v]) return true;
  bool is_safe = false;
  for (auto i: map_graph[v]) {
    is_safe |= dfs(i);
  }
  safe[v] = is_safe;
  return is_safe;
}

/*
 * Convert input city strings to ints, make graph, do SCC.
 * If the size of the SCC > 1 AKA loop, every element in that SCC is safe.
 * Then DFS over remaining elements to see if they are connected to a loop.
 */

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    string a, b;
    int a_cnt, b_cnt;
    cin >> a >> b;
    if (city_to_int.find(a) == city_to_int.end()) city_to_int[a] = city_count++;
    if (city_to_int.find(b) == city_to_int.end()) city_to_int[b] = city_count++;
    a_cnt = city_to_int[a];
    b_cnt = city_to_int[b];
    graph.addEdge(a_cnt, b_cnt);
    map_graph[a_cnt].push_back(b_cnt);
  }
  graph.SCC();

  for (const auto& scc_elements: scc_list) {
    if (scc_elements.size() > 1) {
      // added s <= city_count condition because I initialized the Graph to max number of vertices, and hence scc_list has a bunch of junk inputs
      for (auto s: scc_elements) if (s <= city_count) safe[s] = true;
    }
  }

  for (const auto& i:map_graph) {
    if (!safe[i.first]) dfs(i.first);
  }
  string city;
  while (cin >> city) {
    if (safe[city_to_int[city]]) cout << city << " safe\n";
    else cout << city << " trapped\n";
  }
  return 0;
}

/* graph contraction version:

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <list>

#define NIL (-1)

using namespace std;

vector<set<int>> scc_list;

class Graph {
    int V;
    vector<vector<int>> adj;
 void SCCUtil(int u, int disc[], int low[],
                 stack<int> &st, bool stackMember[]);

public:
    explicit Graph(int V);
    void addEdge(int v,
                 int w);
    void SCC();
};

Graph::Graph(int V) {
  this->V = V;
  adj = vector<vector<int>>(V);
}

void Graph::addEdge(int v, int w) { adj[v].push_back(w); }

void Graph::SCCUtil(int u, int disc[], int low[], stack<int> &st, bool stackMember[]) {
  static int time = 0;
 disc[u] = low[u] = ++time;
  st.push(u);
  stackMember[u] = true;
  for (auto i = adj[u].begin(); i != adj[u].end(); ++i) {
    int v = *i;

    if (disc[v] == NIL) {
      SCCUtil(v, disc, low, st, stackMember);
      low[u] = min(low[u], low[v]);
    } else if (stackMember[v] == true)
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

void Graph::SCC() {
  int disc[V];
  int low[V];
  bool stackMember[V];
  stack<int> st;

  for (int i = 0; i < V; i++) {
    disc[i] = NIL;
    low[i] = NIL;
    stackMember[i] = false;
  }

  for (int i = 0; i < V; i++)
    if (disc[i] == NIL)
      SCCUtil(i, disc, low, st, stackMember);
}

int n, city_count = 0, new_city_count;
auto graph = Graph(10001);
map<string, int> city_to_int;
map<int, set<int>> map_graph;
map<int, set<int>> map_graph_reversed;

map<int, bool> safe;
map<int, int> scc_edges;
map<int, set<int>> reduced_graph;

bool dfs_reduced_graph(int v) {
  if (v > city_count) { safe[v] = true; return true; }
  bool is_safe = false;
  for (auto i: reduced_graph[v]) {
    is_safe |= dfs_reduced_graph(i);
  }
  safe[v] = is_safe;
  return is_safe;
}

int main() {
//  ios_base::sync_with_stdio(false);
//  cin.tie(nullptr);
  cin >> n;
  for (int i = 0; i < n; ++i) {
    string a, b;
    int a_cnt, b_cnt;
    cin >> a >> b;
    if (city_to_int[a] == 0) city_to_int[a] = ++city_count;
    if (city_to_int[b] == 0) city_to_int[b] = ++city_count;
    a_cnt = city_to_int[a];
    b_cnt = city_to_int[b];
    graph.addEdge(a_cnt, b_cnt);
    map_graph[a_cnt].insert(b_cnt);
    map_graph_reversed[b_cnt].insert(a_cnt);
  }
  graph.SCC();
  new_city_count = city_count;

  for (auto scc_set: scc_list) {
    if (scc_set.size() == 1) {
      for (auto i: scc_set) { if (i > 0 && i <= city_count) scc_edges[i] = i; }
    } else {
      ++new_city_count;
      for (auto i: scc_set) if (i > 0 && i <= city_count) scc_edges[i] = new_city_count;
    }
  }


  for (const auto& vertex: map_graph) {
    int scc_rep = scc_edges[vertex.first];
    for (auto edge: vertex.second) {
      if (scc_rep != scc_edges[edge])reduced_graph[scc_rep].insert(scc_edges[edge]);
    }
  }
  for (const auto& i: map_graph) {
    if (scc_edges[i.first] > city_count) safe[scc_edges[i.first]] = true;
  }

  for (const auto& i: map_graph) {
    if (scc_edges[i.first] <= i.first) dfs_reduced_graph(i.first);
  }
  string city;
  while (cin >> city) {
    if (safe[scc_edges[city_to_int[city]]]) cout << city << " safe\n";
    else cout << city << " trapped\n";
  }
  return 0;
}
*/