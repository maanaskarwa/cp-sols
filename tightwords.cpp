/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <cmath>
#include <cstring>

#define ld long double
#define s short

using namespace std;

/*
 * Logic: Imagine a grid (eg for k = 3, n = 5)
 *
 n=0 1 2 3 4
 -----------
 * 0 0 0 0 0
 * 1 1 1 1 1
 * 2 2 2 2 2
 * 3 3 3 3 3
 *
 * We need to walk from left to right, and we can only walk either horizontally or diagonally one up or down (since difference must be <= 1)
 * (X means both / and \ directions allowed)
 n=0 1 2 3 4
 -----------
 * 0-0-0-0-0
 *  X X X X
 * 1-1-1-1-1
 *  X X X X
 * 2-2-2-2-2
 *  X X X X
 * 3-3-3-3-3
 *
 * Number of such paths ending at length n is our answer.
 * Make dp array, where our dp is the number of paths to get till that point.
 * dp[i][j] = number of words of length (i+1 (0-indexing)) ending ot alphabet j.
 *
 * I could also change my dp because I only need the current sum and the prev row, but I'm already at 0.00s so I don't care :)
 */

short k, n;
ld dp[100][12]; // 100 is max n, chose 12 because 10 letters, and 2 for the DP padding on either side

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  while (cin >> k >> n) {
    memset(dp, 0, sizeof(dp));
    for (s i = 0; i < n; ++i) {
      for (s letter = 1; letter <= k + 1; ++letter) {
        if (i == 0) dp[i][letter] = 1;
        else dp[i][letter] = dp[i - 1][letter] + dp[i - 1][letter - 1] + dp[i - 1][letter + 1];
        /* Look at 3rd 2 in array, num of ways = ways to get to 2nd 1 + 2nd 2 + 2nd 3 since they are all valid moves before. */
      }
    }
    ld count = 0;
    for (s i = 1; i < k + 2; ++i) count += dp[n - 1][i];
    printf("%.8Lf\n", (100.0 * count) / powl(k + 1, n)); // k+1 because k begins from 0
  }
  return 0;
}