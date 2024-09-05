/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>
using namespace std;

//tilingState[i][j] = ways to do tiling till row i with j mask of row i tiled
int tilingState[31][1 << 3];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  int n;
  memset(tilingState, 0, sizeof(tilingState));
  tilingState[0][7] = 1; //base case
  for (int i = 1; i <= 30; i++) {
    /*
     * This comment will make code mostly self explanatory
     *
     * 0: empty row
     * 1: #
     *    -
     *    -
     *
     * 2: -
     *    #
     *    -
     *
     * 3: #
     *    #
     *    -
     *
     * 4: -
     *    -
     *    #
     *
     * 5: #
     *    -
     *    #
     *
     * 6: -
     *    #
     *    #
     *
     * 7: filled row
     */


    tilingState[i][0] = tilingState[i - 1][7]; //if no tile in this row, same as last row filled
    tilingState[i][1] = tilingState[i - 1][6];
    tilingState[i][3] = tilingState[i - 1][7] + tilingState[i - 1][4]; // fill entire i-1 and then put bar vertically, or leave space to put 2 bars horizontally
    tilingState[i][4] = tilingState[i - 1][3];
    tilingState[i][6] = tilingState[i - 1][7] + tilingState[i - 1][1]; //mirror of state 3

    //state[i-1][0]: prev row empty. now add 3 horizontal bars on top of each other
    //state[i-1][3] & [1][6]: Fit bars in an L shape
    tilingState[i][7] = tilingState[i - 1][0] + tilingState[i - 1][3] + tilingState[i - 1][6];

    //notice we never need to handle cases 2 & 5, they are invalid at the start itself
  }
  while (true) {
    cin >> n;
    if (n == -1)
      break;
    cout << tilingState[n][7] << "\n";
  }
}