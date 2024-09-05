/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long
#define ld long double
#define u unsigned
#define DEBUG false
#define PANIC {return 2;}

using namespace std;

ll choose[51][51];

int main() {

// precompute nCr from 0 to 50
  memset(choose, 0, sizeof(choose));
  for (int i = 0; i < 51; i++) { choose[i][0]=1;choose[i][1] = i; }
  for (int n = 0; n < 50; n++) {
    for (int r = 1; r <= n+1; r++) {
      choose[n+1][r] = choose[n][r] + choose[n][r-1]; // n C r + n C r-1 = n+1 C r
      // if u use factorials directly there will be overflow
    }
  }
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    int n, v1, v2, w;
    cin >> n >> v1 >> v2 >> w;
    int votes_remaining = n - v1 - v2;
    if (v1 + votes_remaining < n/2 + 1) { // no way of getting strictly over half the votes
      cout << "RECOUNT!\n";
      continue;
    }
    ld cases_where_winning = 0;
    // finalVotes >= n/2 + 1. v1 + x >= n/2 + 1, x >= n/2 + 1 - v1
    //probability = winning_cases/total.
    for (int x = n/2 + 1 - v1; x <= votes_remaining; x++) cases_where_winning += choose[votes_remaining][x]; // ways of picking people who voted in favor
    for (int i = 0; i < votes_remaining; i++) cases_where_winning /= 2; //Total is 2^votes_remaining, divided in loop since 2^votes_remaining could overflow beyond ll as well
    if (cases_where_winning * 100 > w) cout << "GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!\n";
    else cout <<"PATIENCE, EVERYONE!\n";
  }
}