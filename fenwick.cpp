/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long

using namespace std;

int n,q;
ll fenwickTree[5000001];

void add(int index, ll num) {
  for (int i = index + 1; i <= n; i += (i & -i)) {
    fenwickTree[i] += num;
  }
}

ll sum(int index) {
  ll val = 0;
  for (int i = index+1; i > 0; i -= (i & -i)) {
    val += fenwickTree[i];
  }
  return val;
}

//code TLEd without fast I/O. Keep in mind when dealing with huge amount of IO
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  memset(fenwickTree, 0, sizeof(fenwickTree));
  cin >> n >> q;
  char c; int t1,t2;
  while (q--) {
    cin >> c;
    if (c == '+') {
      cin >> t1 >> t2;
      add(t1,t2);
    } else if (c == '?') {
      cin >> t1;
      if (!t1) cout << "0\n"; //edge case
      else cout << sum(t1-1) << "\n"; //t1 -1 since they interpreted as sum till that index
    }
  }
}