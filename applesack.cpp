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

/*
 * As long as you have more apples than you can hold, keep moving forward by 1 step. You will lose 1 apple for every such round you make.
 * The number of rounds you make is ceil(n/k). Instead of computing directly, you can check for divisibility and then compute as below.
 * Once you can hold all the apples you have left, just start walking. If you have k apples, you will make it k+1 more gates (you will be stopped at k+1 th gate)
 */
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n, k, ans = 0; //using n to represent num of apples left
  cin >> n >> k;
  if (n <= k) { //start walking with all apples immediately
    cout << n + 1;
    return 0;
  }
  if (k == 1) { //doesn't matter how many, you will only ever have enough to pay at checkpost 1. You will be stopped at the 2nd one no matter what.
    cout << 2;
    return 0; //had written 1 here before like an idiot. Think thru edge cases more carefully lol
  }
  while (n > k) {
    ans++; //walked 1 step

    //number of rounds made, paying 1 apple each round
    if (n % k == 0) {
      n -= (n/k);
    } else {
      n -= (n/k) + 1;
    }
  }

  //ending walk
  ans += n + 1;
  cout << ans;
  return 0;
}