/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long
#define u unsigned
#define pii pair<int,int>

using namespace std;

int n, tmp;
pii indexToNumbers[100000];
ll fenwickTree[100001], fenwickTreeRev[100001];
//fenwickTree:     used to track numbers as we see them - add 1 each time
//fenwickTreeRev:  used to track numbers we haven't seen yet
// Since we are processing the numbers in ascending order, we can determine how many numbers we have seen based on the sums

void add(ll *tree, int index, ll num) {
  for (int i = index + 1; i <= n; i += (i & -i)) {
    tree[i] += num;
  }
}

ll sum(ll *tree, int index) {
  ll val = 0;
  for (int i = index + 1; i > 0; i -= (i & -i)) {
    val += tree[i];
  }
  return val;
}

// for any number, number of inversions = bigger numbers to left * smaller numbers to right
// maintain 2 fenwick trees to keep track of each
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  cin >> n;
  if (n < 3) {
    cout << 0;
    return 0;
  }
  memset(fenwickTree, 0, sizeof(fenwickTree[0]) * (n + 1));

  for (int i = 0; i < n; ++i) {
    add(fenwickTreeRev, i, 1); // initialize rev tree saying we have seen them all.
    // When we actually come across a number, we will subtract it. So the count always maintains how many numbers we
    // actually haven't seen

    cin >> tmp;
    indexToNumbers[i] = {i, tmp};
  }

  sort(indexToNumbers, indexToNumbers + n, [](pair<int, int> &p1, pair<int, int> &p2) -> bool {
    if (p1.second == p2.second) return p1.first < p2.first;
    return p1.second < p2.second;
  });
  pii num;
  int index;
  ll ans = 0, smallerNumbersToRight, biggerNumbersToLeft;
  for (int i = 0; i < n; i++) { // i is numbers seen so far
    num = indexToNumbers[i];
    index = num.first;
    biggerNumbersToLeft = sum(fenwickTreeRev, index - 1);
    smallerNumbersToRight = i - sum(fenwickTree, index); // total - numbers to left
    ans += smallerNumbersToRight * biggerNumbersToLeft;
    add(fenwickTree, index, 1);
    add(fenwickTreeRev, index, -1); //we have seen this number now
  }
  cout << ans;
}