/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>
using namespace std;

const int mxn = 1e6+1;
vector<int> fenwickTree(mxn + 2, 0); //maintains number of on bits till given index.
vector<bool> bitState(mxn + 1, false);//maintain whether a bit is on or off
int n, k;

void add(int index, int num) {
  // need n+1 since 1-indexing
  for (int i = index + 1; i <= n + 1; i += (i & -i)) fenwickTree[i] += num;
}

int sum(int index) {
  int val = 0;
  for (int i = index + 1; i > 0; i -= (i & -i)) val += fenwickTree[i];
  return val;
}

void flip(int bit) {
  if (bitState[bit]) add(bit, -1), bitState[bit] = false; // turn bit off
  else add(bit, 1), bitState[bit] = true; //turn bit on
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  cin >> n >> k;
  char c;
  int t1, t2;
  while (k--) {
    cin >> c;
    if (c == 'F') cin >> t1, flip(t1);
    else {
      cin >> t1 >> t2;
      if (t1 == t2)
        cout << (bitState[t1] ? "1\n" : "0\n"); //short-circuit fenwick tree call if checking single bit
      else
        cout << sum(t2) - sum(t1 - 1) << "\n"; // (number of bits on from 1-t2) - (number of bits on from 1-(t1-1))
    }
  }
}