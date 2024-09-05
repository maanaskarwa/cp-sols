///*
// * Author: Maanas Karwa
// * It is ok to share my code anonymously for educational purposes
// * */
//
//#include <bits/stdc++.h>
//
//using namespace std;
//
//int n, m, d;
//map<string, int> nameToIndex;
//int idx = 0;
//string s, s1, s2;
//int skepticism;
//
//struct Person {
//    int skepticism;
//    vector<int> adj;
//};
//
//Person graph[1000000];
//
//int main() {
//  ios_base::sync_with_stdio(false);
//  cin.tie(nullptr);
//  cin >> n >> m >> d;
//  for (int i = 0; i < n; i++) {
//    cin >> s >> skepticism;
//    nameToIndex[s] = idx++;
//    graph[idx - 1].skepticism = skepticism;
//  }
//  for (int i = 0; i < m; i++) {
//    cin >> s1 >> s2;
//    auto id1 = nameToIndex[s1], id2 = nameToIndex[s2];
//    graph[id1].adj.push_back(id2);
//    graph[id2].adj.push_back(id1);
//  }
//  cin >> s;
//  auto startIdx = nameToIndex[s];
//  queue<pair<int,int>> q, nextQ;
//  q.push({startIdx, 0});
//  for (int i = 0; i < d; i++) {
//    while (!q.empty()) {
//      auto t = q.front();
//      q.pop();
//
//    }
//    q = nextQ;
//  }
//  return 0;
//}