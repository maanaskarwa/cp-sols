/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define vvi vector<vi>
#define vi vector<int>
#define pb(n) push_back((n));
#define pii pair<int,int>

using namespace std;

vvi graphA(2000), graphB(2000);
int n1, n2, m1, m2;
bool visitedAInNumSteps[2000][2001];
bool visitedBInNumSteps[2000][2001];
vector<bool> ans(2001, false);
set<int> numStepsToReachN1;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  cin >> n1 >> n2 >> m1 >> m2;
  memset(visitedAInNumSteps, false, sizeof(visitedAInNumSteps));
  memset(visitedBInNumSteps, false, sizeof(visitedBInNumSteps));
  for (int i = 0, v, w; i < m1; i++) {
    cin >> v >> w;
    graphA[v - 1].pb(w - 1); //store vertices as 0-indexed
  }
  for (int i = 0, v, w; i < m2; i++) {
    cin >> v >> w;
    graphB[v - 1].pb(w - 1); //store vertices as 0-indexed
  }

  queue<pii > bfsQ; //vertex, number of steps to reach
  bfsQ.push({0, 0});
  visitedAInNumSteps[0][0] = true;
  while (!bfsQ.empty()) {
    auto top = bfsQ.front();
    bfsQ.pop();
    if (top.first != n1-1){ // n1-1 since everything was changed from 1-indexed input to 0-indexed. n1-1 is end vertex
      for (auto v: graphA[top.first]) {
        if (!visitedAInNumSteps[v][top.second + 1]) {
          visitedAInNumSteps[v][top.second + 1] = true;
          bfsQ.push({v, top.second + 1});
        }
      }
    } else { //store the possible ways to reach n1
      numStepsToReachN1.insert(top.second);
    }
  }

  bfsQ.push({0, 0});
  visitedBInNumSteps[0][0] = true;
  while (!bfsQ.empty()) {
    auto top = bfsQ.front();
    bfsQ.pop();
    if (top.first != n2-1) {
      for (auto v: graphB[top.first]) {
        if (!visitedBInNumSteps[v][top.second + 1]) {
          visitedBInNumSteps[v][top.second + 1] = true;
          bfsQ.push({v, top.second + 1});
        }
      }
    } else { //preprocess all answers
      int stepsInB = top.second; // num steps to reach N2 in graph B

      // You can get to N2 in k steps. Now, if you can get to N1 in some p steps, then k + p is an answer
      for (auto const& stepsInA : numStepsToReachN1) {
        if (stepsInA + stepsInB <= 2000)
          ans[stepsInA+stepsInB]=true;
      }
    }
  }

  int Q, q;
  cin >> Q;
  while (Q--) {
    cin >> q;
    if (ans[q])
      cout << "Yes\n";
    else
      cout <<"No\n";
  }


}

#undef vi
#undef vvi
#undef pb
#undef pii