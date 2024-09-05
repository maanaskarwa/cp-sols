/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>
using namespace std;
const int mxn=1000;
int n;
struct Edge {
    int to, percentOfParent;
    bool superPower;
};
vector<double> flowNeededInNode(mxn + 1,0);
vector<vector<Edge>> edgesOfChildren(mxn + 1);

double finalFlowInNode(int nodeIndex) {
  // maximize the flow needed as per the children
  double needed = flowNeededInNode[nodeIndex];
  if (edgesOfChildren[nodeIndex].empty()) { // child node
    return needed; //already populated while taking input
  }
  for (const Edge& edgeToChild: edgesOfChildren[nodeIndex]) {
    // right number in max determines what flow this edge needs, and hence what this node should have
    // the max demand will dominate since that node must have its requirement met
    if (edgeToChild.superPower) {
      // if parent has x, (x * frac)^2 = childDemand, x = sqrt(childDemand)/frac
      // can greedily use superpower all the time since demand will be always >= 1. so using sqrt reduces parent requirement
      needed = max(needed, sqrt(finalFlowInNode(edgeToChild.to)) * 100.0/edgeToChild.percentOfParent);
    } else {
      needed = max(needed, finalFlowInNode(edgeToChild.to) * 100.0/edgeToChild.percentOfParent);
    }
  }
  flowNeededInNode[nodeIndex] = needed;
  return needed;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  cin >> n;
  for (int i = 0, a, b, x, t; i < n - 1; i++) {
    cin >> a >> b >> x >> t;
    edgesOfChildren[a].push_back(Edge{
      b, x, t == 1
    });
  }
  int required;
  for (int i = 1; i <= n; i++) {
    cin >> required;
    if (required != -1) flowNeededInNode[i] = required;
  }
  cout << fixed << setprecision(5) << finalFlowInNode(1);
}