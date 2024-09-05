/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <vector>

#define IMPOSSIBLE (2e7)
#define NEG_INF (-2e7)

using namespace std;
int n, m, q;
int graph[150][150];

/*
 * Floyd-warshall with additional tests:
 * 1. If i->k or k->j edge does not exist, no need to check. Skip
 * 2. If vertex is in negative cycle with itself, you can get there arbitrarily fast (just keep visiting it again, you'll be faster each time since the value is -ve)
 * 3. If there's a path form i->j through k and k is in a -ve cycle, you can go infinitely fast by cycling through k an infinite number of times.
 */

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  while (true) {
    cin >> n >> m >> q;
    if (n == 0) break;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) graph[i][j] = i == j ? 0 : IMPOSSIBLE;
    while (m--) {
      int a, b, c;
      cin >> a >> b >> c;
      if (a == b) {
        graph[a][b] = c < 0 ? NEG_INF : 0;
      } else { // use min to avoid junk inputs like 3->3 with input weight 1.
        graph[a][b] = min(graph[a][b], c);
      }
    }
    for (int k = 0; k < n; ++k) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if (graph[i][k] == IMPOSSIBLE || graph[k][j] == IMPOSSIBLE) continue;
          if ((graph[i][k] == NEG_INF ||
              graph[k][j] == NEG_INF) || (graph[k][k] < 0) || (i == j && graph[i][j] < 0)) {
            graph[i][j] = NEG_INF;
          } else if (graph[i][j] > graph[i][k] + graph[k][j]) { //regular relaxation step
            graph[i][j] = graph[i][k] + graph[k][j];
          }
        }
      }
    }
    while (q--) {
      int a, b;
      cin >> a >> b;
      if (graph[a][b] == IMPOSSIBLE) cout << "Impossible\n";
      else if (graph[a][b] == NEG_INF) cout << "-Infinity\n";
      else cout << graph[a][b] << "\n";
    }
    cout << "\n";
  }
  return 0;
}