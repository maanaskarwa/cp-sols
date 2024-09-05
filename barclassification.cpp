/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long
#define ld long double
#define u unsigned
#define DEBUG false
using namespace std;

int main() {
  int n;
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  char tmp[n]; // to take input and parse each number
  int rowWiseCount[n]; // maintain count of 1s per row
  int colWiseCount[n]; // count per col
  memset(rowWiseCount, 0, sizeof (rowWiseCount));
  memset(colWiseCount,0, sizeof(colWiseCount));
  for (int i = 0; i < n; i++) {
    cin >> tmp;
    for (int j = 0; j < n; j++) {
      bool temp = tmp[j] - '0';
      if (temp) {
        rowWiseCount[i]++;
        colWiseCount[j]++;
      }
    }
  }

  /* simulate a transformation from every starting position to current state.
   * starting positions are a matrix with all 0s except a row/col of 1s
   * a transformation was possible if it could be done in at most n flips
   * */
  bool rowPossible = false;
  //check row wise
  for (int i = 0; !rowPossible && i < n; i++) {
    // i represents the index of the row we are simulating
    int totalFlipsNeeded = 0;
    for (int j = 0; j < n; j++) {
      if (i == j)totalFlipsNeeded += n - rowWiseCount[j]; // 0s in the target row - created by flipping
      else totalFlipsNeeded += rowWiseCount[j]; //1s in other rows - created by flipping
    }
    if (totalFlipsNeeded <= n) { rowPossible = true; }
  }

  bool colPossible =false;
  //check col wise
  for (int i = 0; !colPossible && i < n; i++) {
    int totalFlipsNeeded = 0;
    for (int j = 0; j < n; j++) {
      if (i == j)totalFlipsNeeded += n - colWiseCount[j];
      else totalFlipsNeeded += colWiseCount[j];
    }
    if (totalFlipsNeeded <= n) colPossible=true;
  }
  // notice we don't actually need to store the entire input. the 2 counter arrays had all the info needed
  if (rowPossible && colPossible) {
    cout << "+";
  } else if (rowPossible) {
    cout << "-";
  } else {
    cout << "|";
  }
  return 0;

}