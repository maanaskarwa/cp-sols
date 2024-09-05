/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

using namespace std;

const int inf = 1e8;

struct Node {
    int value;
    bool isAndGate;
    bool isChangeable;
};

const int mxn = 10000;

Node tree[mxn + 1];
int stepsToMakeNodeIValue[mxn + 1][2];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  int n, m, v;

  cin >> n;
  for (int count = 1, g, C; count <= n; count++) {
    cin >> m >> v;

    int i = 1;
    for (; i <= (m - 1) / 2; ++i) {
      cin >> g >> C;
      tree[i] = {0, g == 1, C == 1};
      stepsToMakeNodeIValue[i][0] = inf;
      stepsToMakeNodeIValue[i][1] = inf;
    }
    for (; i <= m; ++i) {
      cin >> g;
      tree[i] = Node{g, false, false};
      stepsToMakeNodeIValue[i][g] = 0;
      stepsToMakeNodeIValue[i][!g] = inf;
    }
    for (i = (m - 1) / 2; i >= 1; i--) { // bottom up dp - populate each node's current val
      Node node = tree[i];
      int value;
      if (node.isAndGate)
        value = tree[i << 1].value && tree[i << 1 | 1].value;
      else
        value = tree[i << 1].value || tree[i << 1 | 1].value;
      tree[i].value = value;
      stepsToMakeNodeIValue[i][value] = 0;
      int l = stepsToMakeNodeIValue[i << 1][!value], r = stepsToMakeNodeIValue[i << 1 | 1][!value]; // how to make children other val
      if (value == 1) { //populate steps to make node have val 0 in this block
        if (node.isChangeable) { // either change children or change self
          if (node.isAndGate) { //change cheaper child to 0 or flip the gate to OR gate and make both children 0
            stepsToMakeNodeIValue[i][0] = min(min(l, r), 1 + l + r);
          } else { //make both children 0 or flip to AND gate and make cheaper child 0
            stepsToMakeNodeIValue[i][0] = min(l + r, 1 + min(l,r));
          }
        } else { //node not changeable, only possibility is to modify children
          if (node.isAndGate) { //make cheaper child 0
            stepsToMakeNodeIValue[i][0] = min(l, r);
          } else { //both children need to be 0
            stepsToMakeNodeIValue[i][0] = l + r;
          }
        }
      } else { //populate steps to make node have val 1 in this block
        if (node.isChangeable) {
          if (node.isAndGate) { // change both children to 1 or change to OR gate and make cheaper child 1
            stepsToMakeNodeIValue[i][1] = min(l + r, 1 + min(l,r));
          } else { // change cheaper child to 1 or change to AND gate and make both children 1
            stepsToMakeNodeIValue[i][1] = min(min(l, r), 1 + l + r);
          }
        } else {
          if (node.isAndGate) { //both children need to be 1
            stepsToMakeNodeIValue[i][1] = l + r;
          } else { // changing any child to 1 will do
            stepsToMakeNodeIValue[i][1] = min(l, r);
          }
        }
      }
    }

    int ans = stepsToMakeNodeIValue[1][v];
    if (ans >= inf)
      cout << "Case #" << count << ": IMPOSSIBLE\n";
    else
      cout << "Case #" << count << ": " << ans << "\n";
  }
}