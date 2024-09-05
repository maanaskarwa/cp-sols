/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

using namespace std;

const int mxn = 1e6;
int n;
int initialIndexOfNumbers[mxn + 1];
int fenwickTree[mxn + 2]; // stores whether there is a number at a given index
//initially, there are numbers at all indices 1 to n

void add(int index, int num) {
  // n+1 since 1-indexing
  for (int i = index + 1; i <= n + 1; i += (i & -i))
    fenwickTree[i] += num;
}

int sum(int index) {
  int ans = 0;
  for (int i = index + 1; i > 0; i -= (i & -i))
    ans += fenwickTree[i];
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  cin >> n;
  for (int i = 2, tmp; i <= n+1; ++i) {

    //setup fenwick tree, equivalent to calling add(1) on all indices from 1 to n
    fenwickTree[i] += 1;
    if (i + (i & -i) <= n + 1) fenwickTree[i + (i & -i)] += fenwickTree[i];

    cin >> tmp;
    initialIndexOfNumbers[tmp] = i-1;
  }
  //once a number is sorted, it's as good as deleted from the array.
  // can visualize as placing sorted numbers just outside the array on either side
  // such numbers will no longer contribute to any inversions

  for (int i = 1, numToMove; i <= n; i++) { //numToMove stores which number we are moving in this iteration
    if (i & 1) {
      numToMove = (i + 1) / 2;
      // count of numbers present on left. will cross all these numbers when sorting
      cout << sum(initialIndexOfNumbers[numToMove] - 1) << "\n";
      // number is sorted, so empty its slot
      add(initialIndexOfNumbers[numToMove], -1);
    } else {
      numToMove = n - i / 2 + 1;
      // i stores the loop count. i-1 will store the count of numbers we have already sorted, hence are deleted from array
      // so n - (i-1) is actually just sum(n).
      // need count of numbers on right, which is total - numbers on left
      cout << (n - i + 1) - sum(initialIndexOfNumbers[numToMove]) << "\n";
      // empty the slot
      add(initialIndexOfNumbers[numToMove], -1);
    }
  }
}