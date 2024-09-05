/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long
#define ld long double
#define u unsigned

using namespace std;

const int mxn = 1e5;
const int fenwickSize = (2 * mxn) + 1;
int fenwickTree[fenwickSize + 1]; // at any position, a 1 means a movie is present. 0 means empty space
// top 100k initially empty slots for movies to be watched and placed. movies placed at 1e5 + 1 onwards

int currentPosition[mxn+1];

int m, r;

void add(int index, int num) {
  for (int i = index + 1; i <= fenwickSize; i += (i & -i)) {
    fenwickTree[i] += num;
  }
}

int sum(int index, int loopTill) {
  int val = 0;
  // slight speedup, fenwick tree doesn't need to sum till 0, only till last used index
  for (int i = index + 1; i >= max(1,loopTill); i -= (i & -i))
    val += fenwickTree[i];
  return val;
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  int t;
  cin >> t;
  while (t--) {
    cin >> m >> r;
    memset(fenwickTree, 0, sizeof(fenwickTree));

    for (int i = 1, j; i <= m; ++i) {

      currentPosition[i] = mxn + i;

      j = mxn + i + 1;
      // set up tree in linear time. Taken from CP-Book (Steven Halim) Chap 2.4.3
      fenwickTree[j] += 1;
      if ((j + (j & -j)) <= fenwickSize) {
        fenwickTree[j + (j & -j)] += fenwickTree[j];
      }
    }
    for (int i = 0, tmp; i < r; ++i) {
      cin >> tmp;
      int position = currentPosition[tmp]; // if a movie has already been removed, you don't want to query the empty space
      // store current position of every movie and use that for queries
      cout << sum(position - 1, mxn - i) << " ";
      add(position, -1), add(mxn - i, 1); //empty old position, place in new position
      currentPosition[tmp] = mxn - i;
    }
    cout << "\n";
  }
}