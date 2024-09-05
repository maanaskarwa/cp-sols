/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

using namespace std;

// dp[i][k][r] = max value till row i having left out k rooms,
// and including what of this row? r = 0 -> left only, r = 1 -> right only
// int dp[200][200][3];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  int num1, num2;
  while (true) {
    int n, k0;
    cin >> n >> k0;
    if (!n && !k0) break;
    int weight[n][2];
    int dp[201][201][3];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; i++) {
      cin >> num1 >> num2;
      weight[i][0] = num1, weight[i][1] = num2;
    }
    //set up base cases
    dp[0][0][0] = weight[0][0]+weight[0][1];
    for (int i = 1; i < n; i++) {
      dp[i][0][0] = dp[i - 1][0][0]+weight[i][0]+weight[i][1];
    }
    dp[0][1][1] = weight[0][1];
    dp[0][1][2] = weight[0][0];

    //push DP
    for (int i = 0; i < n - 1; i++) {
      for (int k = 0; k <= i+1; k++) {
        //states: 0 means both cells of row i are open, 1 means left is closed, 2 means right is closed

        //keep current row open and add next row right cell OR close left of current row and add next row right cell
        dp[i+1][k+1][1] = max(dp[i][k][0]+weight[i+1][1], dp[i][k][1]+weight[i+1][1]);

        //keep current row open and add next row left cell OR close right of current row and add next row left cell
        dp[i+1][k+1][2] = max(dp[i][k][0]+weight[i+1][0], dp[i][k][2]+weight[i+1][0]);

        //use all cells of current row and next row OR restrict current row
        dp[i+1][k][0] = max(
          dp[i][k][0] + weight[i+1][0] + weight[i+1][1],
          max(dp[i][k][1] + weight[i+1][0] + weight[i+1][1], dp[i][k][2] + weight[i+1][0]+weight[i+1][1])
        );

      }
    }
    int ans = max(dp[n - 1][k0][0], max(dp[n - 1][k0][2], dp[n - 1][k0][1]));
    cout << ans << "\n";
  }
}
